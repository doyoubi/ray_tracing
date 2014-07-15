#include <algorithm>
#include <vector>
#include <limits>
#include <tuple>
#include <cmath>
#include "../Eigen/Dense"
#include "screen_manager.h"
#include "../2d/2d.h"
#include "object.h"
#include "settings.h"
#include "coordinate.h"
#include "debug.h"

using namespace dyb;
using Eigen::Vector3d;
using std::min;
using std::max;
using std::vector;
using std::tuple;
using std::tie;
using std::isfinite;
using _screen_manager::ScreenManager;

Camera camera(Vector3d(0,0,1) ,Vector3d(0,1,0), Vector3d(0,0,2),
              angToRad(90),angToRad(90), 1);
LatticeMaterial latticeMaterial(0.2, 0);
PhongMaterial phongMaterial(Vector3d(1,0.8,0.8).normalized(), Vector3d(0.5,0.5,0.5).normalized(), 16, 0);
SinglePlane plane(Vector3d(0,1,0).normalized(), Vector3d(0,-1,0), &latticeMaterial);
Ball ball(Vector3d(0,0,3), 1.0, &phongMaterial);

const vector<Geometry*> objectArray{ &plane, &ball };

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

typedef tuple<IntersectResult, Geometry*> IntersectionPack;

vector<IntersectionPack> findIntersection(const Ray & ray)
{
    vector<IntersectionPack> resultArray;
    for(auto obj : objectArray)
    {
        IntersectResult result = obj->intersect(ray);
        if(result == noHit) continue;
        if(result == insideObject) continue;
        if((result.position - camera.c).dot(camera.forward) < 1) continue;
        debugCheck(isfinite(result.distance), __FILE__, __LINE__, "invalid result");
        resultArray.push_back(IntersectionPack(result, obj));
    }
    return resultArray;
}

IntersectionPack findNearestResult(const vector<IntersectionPack> & resultArray)
{
    debugCheck(!resultArray.empty(), __FILE__, __LINE__, "empty result");
    // require resultArray not empty
    double minDistance = std::numeric_limits<double>::infinity();
    const IntersectionPack * pPack = nullptr;
    for(auto & pack : resultArray)
    {
        IntersectResult result = std::get<0>(pack);
        if(result.distance < minDistance)
        {
            pPack = &pack;
            minDistance = result.distance;
        }
    }
    debugCheck(pPack != nullptr, __FILE__, __LINE__, "pPack is nullptr");
    return *pPack;
}

Vector3d rayTraceRecursive(const Ray & ray, int maxReflect)
{
    vector<IntersectionPack> packArray = findIntersection(ray);
    if(packArray.empty()) return Vector3d(0,0,0);
    IntersectionPack nearest = findNearestResult(packArray);
    IntersectResult result = std::get<0>(nearest);
    Geometry *      obj    = std::get<1>(nearest);
    double ref = 0.4;

    if(ref <= 0 || maxReflect == 0) return obj->sample(ray, result);
    Vector3d r = ray.d - 2 * ray.d.dot(result.normal) * result.normal;
    return (1-ref) * obj->sample(ray, result)
         +    ref  * rayTraceRecursive(Ray(result.position, r.normalized()), maxReflect-1);
}

void render(ScreenManager * screen)
{
    for(int y = 0; y < window_width; y++)
    {
        for(int x = 0; x < window_height; x++)
        {
            double Nx = double(2*x) / window_width - 1;
            double Ny = double(2*y) / window_height - 1;
            Vector3d d = camera.generateRayDirection(Nx, Ny);
            Ray ray(Vector3d(0,0,0), d);
            Vector3d color = rayTraceRecursive(ray, 3);
            screen->draw(x,y, vecToRGB(color));
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
    // double x = window_width/2 + 200/3/std::sqrt(2);
    // double y = window_height/2;
    // double Nx = double(2*x) / window_width - 1;
    // double Ny = double(2*y) / window_height - 1;
    // Vector3d d = camera.generateRayDirection(Nx, Ny);
    // Ray ray(Vector3d(0,0,0), d);
    // IntersectResult result = ball.intersect(ray);
    // if(result == noHit) return;
    // if(result == insideObject) return;
}

