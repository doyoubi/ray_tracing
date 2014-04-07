#include<algorithm>
#include<GL/freeglut.h>
#include<iostream>
#include"screen_manager.h"
#include"paper_layer.h"
#include"../2d/2d.h"
#include"primitive.hpp"
using std::cout;
using std::cin;
using std::endl;

using _screen_manager::ScreenManager;
using _paper_layer::Lattice;
using _2d::Vector_2d;
using _2d::Point_2d;

using _paper_layer::FlowLayer;
using _paper_layer::FixtureLayer;
using _paper_layer::SurfaceLayer;

FlowLayer flowlayer(100,100);
FixtureLayer fixlayer(100,100);
SurfaceLayer surfacelayer(100,100);
ScreenManager screen;

const int window_width = 640;
const int window_height = 480;

void init();
void display();
void motion(int x, int y);

void validate_positive(_paper_layer::FlowLayer &flowlayer);
void validate_sum(_paper_layer::FlowLayer &flowlayer);
void validate_avg(_paper_layer::FlowLayer &flowlayer);

void draw(const FlowLayer & flowlayer, const FixtureLayer fixlayer);

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE| GLUT_RGB);
    glutInitWindowSize(window_width, window_height);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("doyoubi");

    init();
    glutDisplayFunc(display);
    glutMotionFunc(motion);

    glutMainLoop();

    return 0; 
}

void init()
{    
    glClearColor (1.0, 0.0, 1.0, 1.0);
    glShadeModel(GL_FLAT);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    //for(int y = 0; y < 30; y++)
    //    for(int x = 0; x < 30; x++)
    //    {
    //        flowlayer.add_water(1.0, Point_2d<int>(45+x,45+y));
    //        surfacelayer.add_water(1.0, Point_2d<int>(45+x,45+y));
    //    }
    const int r = 15;
    draw_circle(r,[&](int x, int y){
                for(int i = -x; i <= x; i++)
                    if(!flowlayer.pigment[50+i][50+y])
                    {
                        flowlayer.add_water(1.0, Point_2d<int>(50+i, 50+y));
                        surfacelayer.add_water(1.0, Point_2d<int>(50+i,50+y));
                    }
            });
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    screen.set_draw_square(0, 0, 400, 200);
    draw(flowlayer, fixlayer);

    surfacelayer.seep(flowlayer);
    flowlayer.stream();
    //fixlayer.seep(flowlayer);
    
    //validate_sum(flowlayer);
    //validate_avg(flowlayer);

    glDrawBuffer(GL_BACK);
    glRasterPos2i(-1, -1);
    glDrawPixels(window_width, window_height, GL_RGB,
                 GL_UNSIGNED_BYTE, screen.generate_screem_image());
    glutSwapBuffers();
    glutPostRedisplay();
}

void reshape(int width, int height)
{
    glViewport(0, 0, (GLsizei) width, (GLsizei) height);
    glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluOrtho2D(0.0, (GLdouble) width, 0.0, (GLdouble) height);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void motion(int x, int y)
{
    display();
}

void validate_positive(_paper_layer::FlowLayer &flowlayer)
{
    for(auto &lattice : *flowlayer.curr_state)
        if(lattice.rho() < 0)
            std::cout<<"negative appeared: "<< lattice.rho() <<endl;
}

void validate_sum(_paper_layer::FlowLayer &flowlayer)
{
    double water_sum = std::accumulate((*flowlayer.curr_state).begin(),
                                       (*flowlayer.curr_state).end(),
                                       0.0,
                                       [](double x, Lattice &l)
                                       { return x + l.rho(); }
                                       );
    cout<< water_sum <<endl;
}

void validate_avg(_paper_layer::FlowLayer &flowlayer)
{
    double pig_sum = 0;
    for(int x = 0; x < flowlayer.curr_state->get_width(); x++)
    for(int y = 0; y < flowlayer.curr_state->get_width(); y++)
    {
        double rho = (*flowlayer.curr_state)[x][y].rho();
        pig_sum += flowlayer.pigment[x][y] * rho;
    }
    cout<< pig_sum <<endl;
}

void draw(const FlowLayer & flowlayer, const FixtureLayer fixlayer)
{
    for(int y = 0; y < flowlayer.pigment.get_height(); y++)
    for(int x = 0; x < flowlayer.pigment.get_width(); x++)
    {
        double rho = (*flowlayer.curr_state)[x][y].rho();
        RGB rgb;
        rgb.r = rgb.g = rgb.b = 0xff *(1 - rho);
        screen.draw(x, y, rgb);
        double pigment = flowlayer.pigment[x][y] + fixlayer.pigment[x][y];
        rgb.r = rgb.g = rgb.b = 0xff * (1 - pigment);
        screen.draw(x+100, y, rgb);
    }
}
