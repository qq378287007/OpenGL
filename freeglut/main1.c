#include "GL/glut.h"

void renderScene(void)
{ 
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_TRIANGLES);
    glColor3f(0, 1.0, 0);
    glVertex3f(-0.5, -0.5, 0.0);
    glVertex3f(0.5, 0.0, 0.0);
    glVertex3f(0.0, 0.5, 0.0);
    glEnd();

    glFlush();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);           
    glutInitWindowSize(320, 320);               
    glutCreateWindow("3D Tech- GLUT Tutorial"); 
    glutDisplayFunc(renderScene);               
    glutMainLoop();                             
    return 0;
}

/*
gcc -o main main.c -L. -lopengl32 -lfreeglut
*/



