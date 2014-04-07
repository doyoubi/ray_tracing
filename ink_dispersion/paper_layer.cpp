#include<iostream>
#include<numeric>
#include<algorithm>
#include<random>
using std::cout;
using std::cin;
using std::endl;

#include"paper_layer.h"
#include"formula.h"
#include"utils.h"

#include"screen_manager.h"
using _screen_manager::ScreenManager;
extern ScreenManager screen;

namespace _paper_layer
{
// class Lattice

/* 6 2 5
 * 3 0 1
 * 7 4 8 */
const Point_2d<int> Lattice::next_position[9] = {
    Point_2d<int>(0,0),  Point_2d<int>(1,0),   Point_2d<int>(0,1),
    Point_2d<int>(-1,0), Point_2d<int>(0,-1),  Point_2d<int>(1,1),
    Point_2d<int>(-1,1), Point_2d<int>(-1,-1), Point_2d<int>(1,-1)
};

const int opposite_direction[9] = {0,3,4,1,2, 7,8,5,6};

double Lattice::rho()const
{
    return std::accumulate(f, f+9, 0.0);
}

const Vector_2d<double> Lattice::u()const
{
    Vector_2d<double> u(0, 0);
    for(int i = 0; i < 9; i++)
        u += f[i] * next_position[i];
    return u;
}

// class FlowLayer
FlowLayer::FlowLayer(int width, int height)
    :state1(width, height), state2(width, height),
     pigment(width, height), glue(width, height),
     wet(width, height), pigment_temp(width, height),
     last_water(width, height)
{
    curr_state = &state1;
    last_state = &state2;
    std::fill(glue.begin(), glue.end(), 0.0);
    std::fill(pigment.begin(), pigment.end(), 0.0);
}

void FlowLayer::stream()
{
    for(int y = 0; y < state1.get_height(); y++)
        for(int x = 0; x < state1.get_width(); x++)
            last_water[x][y] = (*curr_state)[x][y].rho();
    std::swap(curr_state, last_state);
    for(int y = 1; y < state1.get_height()-1; y++)
        for(int x = 1; x < state1.get_width()-1; x++)
        {
            for(int i = 0; i < 9; i++)
                (*curr_state)[x][y].f[i] =
                    fi_next(i, (*last_state)[x][y]);
            if((*last_state)[x][y].rho() > 0.0000001)
                wet[x][y] = true;
        }
    std::swap(curr_state, last_state);
    // calculate block
    for(int y = 1; y < state1.get_height()-1; y++)
    for(int x = 1; x < state1.get_width()-1; x++)
    {
        double theshold = 0.02 + 0.1 * glue[x][y];
        double sqrt_2 = 1.41421356237;
        texture.block[x][y] = 2;
        for(int i = 1; i < 9; i++)
        {
            if((*last_state)[Point_2d<int>(x,y) - Lattice::next_position[i]].f[i] > (i>4? sqrt_2:1)*theshold)
            {
                texture.block[x][y] = 0;
                break;
            }
        }
        if(texture.block[x][y] == 0 || (*curr_state)[x][y].rho() > 0.00000001)
            texture.block[x][y] = texture.alum[x][y] * 0.1 + 0.1 * glue[x][y];
    }
    // stream
    for(int y = 1; y < state1.get_height()-1; y++)
    for(int x = 1; x < state1.get_width()-1; x++)
    {
        Lattice & lattice = (*curr_state)[x][y];
        for(int i = 0; i < 9; i++)
        {
            double block = (texture.block[x][y] + texture.block[Point_2d<int>(x,y)-Lattice::next_position[i]]) / 2;
            if(block > 1) block = 1;
            (*curr_state)[x][y].f[i] =
                (1-block) * (*last_state)[Point_2d<int>(x,y) - Lattice::next_position[i]].f[i]
                  + block * (*last_state)[x][y].f[opposite_direction[i]];
        }
    }
    // calculate pigment and glue
    for(int y = 1; y < state1.get_height()-1; y++)
    for(int x = 1; x < state1.get_width()-1; x++)
    {
        double p = 0, g = 0;
        if(wet[x][y])
        {
            Point_2d<double> last = Point_2d<double>(x,y) - (*curr_state)[x][y].u();
            p = utils::text2d(pigment, last);
            g = utils::text2d(glue, last);
        }
        else if((*curr_state)[x][y].rho() > 0.001)
        {
            Point_2d<int> curr(x,y);
            for(int i = 1; i < 9; i++)
            {
                Point_2d<int> back(curr - Lattice::next_position[i]);
                p += pigment[back] * (*curr_state)[x][y].f[i];
                g += glue[back] * (*curr_state)[x][y].f[i];
            }
            p /= (*curr_state)[x][y].rho();
            g /= (*curr_state)[x][y].rho();
        }
        double gamma = utils::lerp(1, 0.0,
                utils::smoothstep(0,0.04,(*curr_state)[x][y].u().norm()) );
        pigment_temp[x][y] = utils::lerp(p, pigment[x][y], gamma);
        glue[x][y] = utils::lerp(g, glue[x][y], gamma);
    }

    for(int y = 1; y < state1.get_height()-1; y++)
        for(int x = 1; x < state1.get_width()-1; x++)
            pigment[x][y] = pigment_temp[x][y];
}

const double glue_density = 0.8;
void FlowLayer::add_water(double seep, Point_2d<int> position)
{
    for(int i = 0; i < 9; i++)
        (*curr_state)[position].f[i] += seep/9;
    wet[position] = true;
    pigment[position] = 1;
    glue[position] = glue_density;
}

Texture::Texture() : alum(100, 100), block(100, 100)
{
    std::random_device rd;
    std::mt19937 eng(rd());
    std::uniform_real_distribution<> dist(0.1,0.2);
    std::generate(alum.begin(), alum.end(), [&]{return dist(eng);});
}

SurfaceLayer::SurfaceLayer(int x, int y) 
    : water(x,y), glue(x,y), pigment(x,y)
{
    std::fill(water.begin(), water.end(), 0.0);
    std::fill(pigment.begin(), pigment.end(), 0.0);
    std::fill(glue.begin(), glue.end(), 0.0);
}

void SurfaceLayer::add_water(double density, Point_2d<int> position)
{
    water[position] = density;
    glue[position] = glue_density * density;
    pigment[position] = 1 * density;
}

void SurfaceLayer::seep(FlowLayer & flowlayer)
{
    for(int y = 0; y < water.get_height(); y++)
    for(int x = 0; x < water.get_width(); x++)
    {
        double phi = utils::clamp(water[x][y], 0, 1-(*flowlayer.curr_state)[x][y].rho());
        water[x][y] -= phi;
        double rho = (*flowlayer.curr_state)[x][y].rho();
        if(rho + phi < 0.00001) continue;
        flowlayer.glue[x][y] = ( rho * flowlayer.glue[x][y] + phi * glue[x][y]) / (rho+phi);
        flowlayer.pigment[x][y] = (rho * flowlayer.pigment[x][y] + phi * pigment[x][y]) 
                                / (rho+phi);
        (*flowlayer.curr_state)[x][y].f[0] += phi;
    }
}

FixtureLayer::FixtureLayer(int width, int height)
    : pigment(width, height), glue(width, height)
{
    std::fill(pigment.begin(), pigment.end(), 0.0);
    std::fill(glue.begin(), glue.end(), 0.0);
}

void FixtureLayer::seep(FlowLayer & flowlayer)
{
    for(int y = 0; y < pigment.get_height(); y++)
    for(int x = 0; x < pigment.get_width(); x++)
    {
        double rho = (*flowlayer.curr_state)[x][y].rho();
        double wLoss = 
            std::max(flowlayer.last_water[x][y] - rho, 0.0);
        if(wLoss > 0)
            double FixFactor = wLoss / flowlayer.last_water[x][y];
        else
            double FixFactor = 0;
        double mu = utils::clamp(0.1+flowlayer.glue[x][y]*0.1, 0,1);
        double FixFactor = std::max(FixFactor*(1-utils::smoothstep(0,mu,rho)), 0.1);

        pigment[x][y] += FixFactor * flowlayer.pigment[x][y];
        glue[x][y] += FixFactor * flowlayer.glue[x][y];

        flowlayer.pigment[x][y] -= FixFactor * flowlayer.pigment[x][y];
        flowlayer.glue[x][y] -= FixFactor * flowlayer.glue[x][y];
    }
}


}
