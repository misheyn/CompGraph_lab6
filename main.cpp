#include <GL\glut.h>
#include "AreaFill.h"

#define WinW 830
#define WinH 600
#define STEP 50

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(WinW, WinH);
    glutInitWindowPosition(300, 80);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutCreateWindow("Area fill");
    glClearColor(255, 255, 255, 255);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(100, timer, 0);
    glutMainLoop();
    return 0;
}