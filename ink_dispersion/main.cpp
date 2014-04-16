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
using _2d::Vector_2d;
using _2d::Point_2d;

using _paper_layer::FlowLayer;
using _paper_layer::SurfaceLayer;

const int window_width = 640;
const int window_height = 480;

FlowLayer flowlayer(100,100);
SurfaceLayer surfacelayer(100,100);
ScreenManager screen;

void init();
void display();
void motion(int x, int y);

void validate_positive(_paper_layer::FlowLayer &flowlayer);
void validate_sum(_paper_layer::FlowLayer &flowlayer);

void draw(const FlowLayer & flowlayer);

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

    for(int y = 0; y < 30; y++)
        for(int x = 0; x < 30; x++)
        {
            flowlayer.w[45+x][45+y] = 1;
        }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    screen.set_draw_square(0, 0, 100, 100);
    draw(flowlayer);

    flowlayer.stream();

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
    for(double num : flowlayer.w)
        if(num < 0)
            std::cout<<"negative appeared: "<< num <<endl;
}

void validate_sum(_paper_layer::FlowLayer &flowlayer)
{
    double water_sum = std::accumulate(flowlayer.w.begin(), flowlayer.w.end(), 0.0);
    cout<< water_sum <<endl;
}


void draw(const FlowLayer & flowlayer)
{
    for(int y = 0; y < flowlayer.w.get_height(); y++)
    for(int x = 0; x < flowlayer.w.get_width(); x++)
    {
        double rho = flowlayer.w[x][y];
        RGB rgb;
        rgb.r = rgb.g = rgb.b = 0xff *(1 - rho);
        screen.draw(x, y, rgb);
    }
}

