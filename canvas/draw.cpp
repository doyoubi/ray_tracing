#include <algorithm>
#include "../Eigen/Dense"
#include "screen_manager.h"
#include "../2d/2d.h"
#include "object.h"
#include "settings.h"
#include "coordinate.h"

using namespace dyb;
using Eigen::Vector3d;
using std::min;
using std::max;
using _screen_manager::ScreenManager;

Camera camera(Vector3d(0,0,1) ,Vector3d(0,1,0), Vector3d(0,0,0),
              angToRad(90),angToRad(90), 1);
LatticeMaterial latticeMaterial(0.2);
PhongMaterial phongMaterial(Vector3d(0.5,0.5,0.5), Vector3d(0.5,0.5,0.5), 32, 1);
SinglePlane plane(Vector3d(0,1,0), Vector3d(0,-1,3).normalized(), &phongMaterial);
Ball ball(Vector3d(0,0,3), 1.0, &phongMaterial);

const double maxDepth = 5.0;


typedef RGB (*getResultMemFunc)(const IntersectResult & result);

RGB getDepth(const IntersectResult & result)
{
    double depthColor = 255 - min(255 * result.distance / maxDepth, 255.0);
    return RGB(depthColor, depthColor, depthColor);
}

RGB getNormal(const IntersectResult & result)
{
    Vector3d vec = result.normal;
    auto f = [](double a){ return 255*(a+1)/2; };
    return RGB(f(vec.x()), f(vec.y()), f(vec.z()) );
}

void render(ScreenManager * screen)
{
    Geometry * obj = &ball;
    for(int y = 0; y < window_width; y++)
    {
        for(int x = 0; x < window_height; x++)
        {
            double Nx = double(2*x) / window_width - 1;
            double Ny = double(2*y) / window_height - 1;
            Vector3d d = camera.generateRayDirection(Nx, Ny);
            Ray ray(Vector3d(0,0,0), d);
            IntersectResult result = obj->intersect(ray);
            if(result == noHit) continue;
            if(result == insideObject) continue;
            // RGB rgb = getNormal(result);
            RGB rgb = obj->sample(ray, result);
            screen->draw(x,y, rgb);
        }
    }
    cout<<"renderComplete"<<endl;
}

void draw(_screen_manager::ScreenManager * screen)
{
    static bool renderComplete = false;
    if(!renderComplete)
    {
       render(screen);
       renderComplete = true;        
    }
}

void check()
{
    double x = window_width/2 + 200/3/std::sqrt(2);
    double y = window_height/2;
    double Nx = double(2*x) / window_width - 1;
    double Ny = double(2*y) / window_height - 1;
    Vector3d d = camera.generateRayDirection(Nx, Ny);
    Ray ray(Vector3d(0,0,0), d);
    IntersectResult result = ball.intersect(ray);
    if(result == noHit) return;
    if(result == insideObject) return;
    cout<< result.normal <<endl;
    RGB rgb = getNormal(result);
    cout<<(int)rgb.r<<' '<<(int)rgb.g<<' '<<(int)rgb.b<<endl;
}

