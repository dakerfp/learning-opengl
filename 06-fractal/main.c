
#include <GL/glut.h>
#include <GL/glu.h>

typedef enum { FALSE = 0, TRUE = 1 } bool;

void init(void)
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glShadeModel(GL_FLAT);
}

void drawFractal(int level, bool isRoot)
{
    if (level < 0)
        return;

    glutWireCube(1.0);

    glPushMatrix();
        glTranslatef(0.0, 0.75, 0.0);
        glScalef(0.75, 0.75, 0.75);
        glRotatef(10.0, 0.0, 0.0, -1.0);
        drawFractal(level - 1, FALSE);
    glPopMatrix();

    if (!isRoot)
        return;

    glPushMatrix();
        glTranslatef(0.75, 0.0, 0.0);
        glScalef(0.75, 0.75, 0.75);
        glRotatef(90, 0.0, 0.0, -1.0);
        glRotatef(10.0, 0.0, 0.0, -1.0);
        drawFractal(level - 1, FALSE);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0.0, -0.75, 0.0);
        glScalef(0.75, 0.75, 0.75);
        glRotatef(180, 0.0, 0.0, -1.0);
        glRotatef(10.0, 0.0, 0.0, -1.0);
        drawFractal(level - 1, FALSE);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-0.75, 0.0, 0.0);
        glScalef(0.75, 0.75, 0.75);
        glRotatef(270, 0.0, 0.0, -1.0);
        glRotatef(10.0, 0.0, 0.0, -1.0);
        drawFractal(level - 1, FALSE);
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
    drawFractal(15, TRUE);
    glFlush();
}

void reshape(int w, int h)
{
    glViewport(0.0f, 0.0f, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    float ratio = ((float) w) / h;
    glFrustum(-ratio, ratio, -1.0, 1.0, 1.5, 20.0);
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
