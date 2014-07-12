#include "../GL/glew.h"
#include "../GL/freeglut.h"
#include "screen_manager.h"
#include "../2d/2d.h"
#include <iostream>
#include <algorithm>
using std::cout;
using std::cin;
using std::endl;

using _screen_manager::ScreenManager;
using _2d::Vector_2d;
using _2d::Point_2d;

const int window_width = 400;
const int window_height = 400;

ScreenManager screen;

void init();
void display();
void motion(int x, int y);


int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE| GLUT_RGB);
    glutInitWindowSize(window_width, window_height);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("doyoubi");
    if (glewInit() != GLEW_OK)
    {
        std::cerr << "glew init failed" << endl;
        exit(1);
    }
    init();
    glutDisplayFunc(display);
    glutMotionFunc(motion);

    glutMainLoop();

    return 0; 
}

void init()
{    
    glClearColor (0.0, 0.0, 0.0, 1.0);
    glShadeModel(GL_FLAT);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    screen.set_draw_square(0, 0, 400, 400);

    RGB rgb(255,0,0);
    for(int i = 0; i < 400; i++)
        screen.draw(i, 100, rgb);

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
}

