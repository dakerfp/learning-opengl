
#include <GL/glut.h>
#include <GL/glu.h>

void init(void)
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glShadeModel(GL_FLAT);
}

void drawFractal(int level)
{
    if (level < 0)
        return;

    glPushMatrix();
    glutWireCube(1.0);
    glTranslatef(0.0, 1.0, 0.0);
    glScalef(0.5, 0.5, 0.5);
    glRotatef(30.0, 0.0, 0.0, -1.0);
    drawFractal(level - 1);
    glPopMatrix();
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 5.0, // Eye position
              0.0, 0.0, 0.0, // Looking at
              0.0, 1.0, 0.0); // With normal vector
    glRotatef(30.0, 0.0, 0.0, -1.0);
    drawFractal(10);
    glFlush();
}

void reshape(int w, int h)
{
    glViewport(0.0f, 0.0f, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 20.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow (argv[0]);
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}
