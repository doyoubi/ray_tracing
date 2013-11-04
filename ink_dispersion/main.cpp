#include<iostream>
using std::cout;
using std::cin;
using std::endl;
#include<gl/glut.h>

const int width = 640;
const int height = 480;

const int w= 30;
const int h= 30;
GLubyte image[w][h][3];

void init()
{    
    glClearColor (0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    for(int x = 0; x < w; x++)
        for(int y = 0; y < h; y++)
        {
            image[x][y][0] = 255;
            image[x][y][1] = 0;
            image[x][y][2] = 0;
        }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glRasterPos2i(0, 0);
    glDrawPixels(w, h, GL_RGB, GL_UNSIGNED_BYTE, image);
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

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE| GLUT_RGB);
    glutInitWindowSize(width, height);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);

    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    glutMainLoop();

    return 0; 
}
