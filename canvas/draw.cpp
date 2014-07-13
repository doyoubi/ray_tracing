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
              angToRad(45),angToRad(45), 1);
Sphere sphere(Vector3d(0,0,3), 1);


void renderDepth(_screen_manager::ScreenManager * screen)
{
    const double maxDepth = 7.0;
    for(int y = 0; y < window_width; y++)
    {
        for(int x = 0; x < window_height; x++)
        {
            double Nx = 2*x / window_width - 1;
            double Ny = 2*y / window_height - 1;
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
    //const double maxDepth = 7.0;
    //double x = 0, y = 0;
    //double Nx = 2*x / window_width - 1;
    //double Ny = 2*y / window_height - 1;
    //Vector3d d = camera.generateRayDirection(Nx, Ny);
    //Ray ray(Vector3d(0,0,0), d);
    //IntersectResult result = sphere.intersect(ray);
    //if(result == noHit) continue;
    //if(result == insideObject) continue;
    //double depthColor = 255 - min(255 * result.distance / maxDepth, 255.0);
    //RGB rgb(depthColor, depthColor, depthColor);
    //screen->draw(x,y, rgb);
}

