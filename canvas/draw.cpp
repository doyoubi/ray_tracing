#include <algorithm>
#include "../Eigen/Dense"
#include "screen_manager.h"
#include "../2d/2d.h"
#include "object.h"
#include "settings.h"

using namespace dyb;
using Eigen::Vector3d;
using std::min;
using std::max;

Camera camera(Vector3d(0,0,1) ,Vector3d(0,1,0), Vector3d(0,0,0),
              angToRad(90),angToRad(90), 1);
Sphere sphere(Vector3d(0,0,3), 2);


void renderDepth(_screen_manager::ScreenManager * screen)
{
    const double maxDepth = 5.0;
    for(int y = 0; y < window_width; y++)
    {
        for(int x = 0; x < window_height; x++)
        {
            double Nx = double(2*x) / window_width - 1;
            double Ny = double(2*y) / window_height - 1;
            Vector3d d = camera.generateRayDirection(Nx, Ny);
            Ray ray(Vector3d(0,0,0), d);
            IntersectResult result = sphere.intersect(ray);
            if(result == noHit) continue;
            if(result == insideObject) continue;
            double depthColor = 255 - min(255 * result.distance / maxDepth, 255.0);
            RGB rgb(depthColor, depthColor, depthColor);
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
      renderDepth(screen);
      renderComplete = true;        
    }
}

void check()
{
    // const double maxDepth = 7.0;
    // double x = window_width/2 - 60, y = window_height/2;
    // double Nx = 2*x / window_width - 1;
    // double Ny = 2*y / window_height - 1;
    // Vector3d d = camera.generateRayDirection(Nx, Ny);
    // Ray ray(Vector3d(0,0,0), d);
    // IntersectResult result = sphere.intersect(ray);
    // if(result == noHit)
    // {
    //     cout<<"noHit"<<endl;
    // }
    // else if(result == insideObject)
    // {
    //     cout<<"insideObject"<<endl;
    // }
    // else
    // {
    //     cout<< result.distance <<endl;
    //     double depthColor = 255 - min(255 * result.distance / maxDepth, 255.0);
    //     RGB rgb(depthColor, depthColor, depthColor);
    //     cout<< (int)(rgb.r)<<endl;
    // }
}

