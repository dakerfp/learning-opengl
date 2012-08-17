
#include <GL/glut.h>

#include <stdio.h>

void drawSquare(void)
{
    glColor3f(1.0f, 1.0f, 1.0f);

    glBegin(GL_QUADS);
        glVertex2f(-1.0f, -1.0f);
        glVertex2f( 1.0f, -1.0f);
        glVertex2f( 1.0f,  1.0f);
        glVertex2f(-1.0f,  1.0f);
    glEnd();
}

void init(void)
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    drawSquare();
    glFlush();
}

void reshape(int w, int h)
{
    glViewport(0.0f, 0.0f, (GLsizei) w, (GLsizei) h);
    glLoadIdentity();
    glScalef(0.5f, 0.5f, 0.5f);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 800);
    glutCreateWindow ("Hello");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();

    return 0;
}
