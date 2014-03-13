#include<GL/freeglut.h>
#include<iostream>
using std::cout;
using std::cin;
using std::endl;

#include"screen_manager.h"
using _screen_manager::ScreenManager;
ScreenManager screen;
#include"paper_layer.h"
_paper_layer::FlowLayer flowlayer(100,100);
void init_flowlayer();
using _paper_layer::Lattice;
#include"../2d/2d.h"
using _2d::Vector_2d;
using _2d::Point_2d;

const int window_width = 640;
const int window_height = 480;

void init();
void display();
void reshape(int width, int height);
void motion(int x, int y);

void draw_circle();

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE| GLUT_RGB);
    glutInitWindowSize(window_width, window_height);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("doyoubi");

    init();
    glutDisplayFunc(display);
    //glutReshapeFunc(reshape);
    glutMotionFunc(motion);

    glutMainLoop();

    return 0; 
}

void init()
{    
    glClearColor (1.0, 0.0, 1.0, 1.0);
    init_flowlayer();
    glShadeModel(GL_FLAT);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    for(int y = 0; y < 10; y++)
        for(int x = 0; x < 10; x++)
            flowlayer.add_water(1.0, Point_2d<int>(45+x,45+y));
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    //RGB rgb;
    //rgb.r = 0xff;
    //rgb.g = rgb.b = 0;
    //screen.set_draw_square(50, 50, 100, 100);
    //for(int i = 0; i < window_width; i++)
    //    screen.draw(i, i, rgb);

    screen.set_draw_square(0, 0, 200, 200);
    flowlayer.draw();
    flowlayer.stream();

    glDrawBuffer(GL_BACK);
    glRasterPos2i(0, 0);
    glDrawPixels(window_width, window_height, GL_RGB,
                 GL_UNSIGNED_BYTE, screen.generate_screem_image());
    glutSwapBuffers();
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

void init_flowlayer()
{
}
