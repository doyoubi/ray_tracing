#include<iostream>
using std::cout;
using std::cin;
using std::endl;
#include<gl/glut.h>

#include"screen_manager.h"
using screen_manager::ScreenManager;
ScreenManager screen;

//const int window_width = 640;
//const int window_height = 480;
const int window_width = 640;
const int window_height = 480;

GLubyte background_buffer[window_height][window_width][3];

void init();
void display();
void reshape(int width, int height);
void motion(int x, int y);

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE| GLUT_RGB);
    glutInitWindowSize(window_width, window_height);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);

    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMotionFunc(motion);

    glutMainLoop();

    return 0; 
}

void init()
{    
    //glClearColor (0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    // init left buffer which used to be background
    for(int x = 0; x < window_width; x++)
        for(int y = 0; y < window_height; y++)
        {
            background_buffer[y][x][0] = 0xff;
            background_buffer[y][x][1] = 0xff;
            background_buffer[y][x][2] = 0xff;
        }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    RGB rgb;
    rgb.r = 0xff;
    rgb.g = rgb.b = 0;
    screen.set_draw_square(0, 0, 100, 100);
    for(int i = 0; i < window_width; i++)
        screen.draw(i, i, rgb);

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
{ display(); }
