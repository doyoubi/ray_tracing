#include<algorithm>
#include<GL/freeglut.h>
#include<iostream>
#include"screen_manager.h"
#include"paper_layer.h"
#include"../2d/2d.h"
using std::cout;
using std::cin;
using std::endl;

using _screen_manager::ScreenManager;
using _paper_layer::Lattice;
using _2d::Vector_2d;
using _2d::Point_2d;

_paper_layer::FlowLayer flowlayer(100,100);
ScreenManager screen;

const int window_width = 640;
const int window_height = 480;

void init();
void display();
void motion(int x, int y);

void validate_positive(_paper_layer::FlowLayer &flowlayer);
void validate_sum(_paper_layer::FlowLayer &flowlayer);

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

    for(int y = 0; y < 10; y++)
        for(int x = 0; x < 10; x++)
            flowlayer.add_water(1.0, Point_2d<int>(45+x,45+y));
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    screen.set_draw_square(0, 0, 200, 200);
    flowlayer.draw();
    flowlayer.stream();

    glDrawBuffer(GL_BACK);
    glRasterPos2i(-1, -1);
    glDrawPixels(window_width, window_height, GL_RGB,
                 GL_UNSIGNED_BYTE, screen.generate_screem_image());
    glutSwapBuffers();

    validate_sum(flowlayer);
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
