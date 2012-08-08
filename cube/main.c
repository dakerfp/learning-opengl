
#include <GL/glut.h>

void drawCube(void)
{
    glColor4f(1.0f, 1.0f, 1.0f, 0.5);

    glBegin(GL_QUADS);

    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f( 1.0f, -1.0f, -1.0f);
    glVertex3f( 1.0f,  1.0f, -1.0f);
    glVertex3f(-1.0f,  1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);

    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f( 1.0f, -1.0f,  1.0f);
    glVertex3f( 1.0f,  1.0f,  1.0f);
    glVertex3f(-1.0f,  1.0f,  1.0f);
    glVertex3f(-1.0f, -1.0f,  1.0f);

    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(-1.0f,  1.0f, -1.0f);
    glVertex3f(-1.0f,  1.0f,  1.0f);
    glVertex3f(-1.0f, -1.0f,  1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);

    glColor3f(1.0f, 1.0f, 0.0f);
    glVertex3f( 1.0f,  1.0f, -1.0f);
    glVertex3f( 1.0f,  1.0f,  1.0f);
    glVertex3f( 1.0f, -1.0f,  1.0f);
    glVertex3f( 1.0f, -1.0f, -1.0f);

    glColor3f(1.0f, 0.0f, 1.0f);
    glVertex3f( 1.0f, -1.0, -1.0f);
    glVertex3f( 1.0f, -1.0,  1.0f);
    glVertex3f(-1.0f, -1.0,  1.0f);
    glVertex3f(-1.0f, -1.0, -1.0f);

    glColor3f(0.0f, 1.0f, 1.0f);
    glVertex3f( 1.0f,  1.0, -1.0f);
    glVertex3f( 1.0f,  1.0,  1.0f);
    glVertex3f(-1.0f,  1.0,  1.0f);
    glVertex3f(-1.0f,  1.0, -1.0f);

    glEnd();
}

void init(void)
{
    glShadeModel(GL_SMOOTH);
    glFrontFace(GL_FRONT | GL_BACK);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    drawCube();
    glFlush();
}

void reshape(int w, int h)
{
    glViewport(0.0f, 0.0f, (GLsizei) w, (GLsizei) h);
    glLoadIdentity();
    glScalef(0.5f, 0.5f, 0.5f);
}

int mouseEnterX;
int mouseEnterY;
int mouseActive;

void handleMouse(int button, int state, int x, int y)
{
    if (state == GLUT_DOWN) {
        mouseEnterX = x;
        mouseEnterY = y;
        mouseActive = 1;
    } else if (state == GLUT_UP) {
        mouseActive = 0;
    }
}

void handleMouseMove(int x, int y)
{
    if (mouseActive) {
        glRotated((GLfloat) (x - mouseEnterX) * 0.5f, 0.0f, 1.0f, 1.0f);
        glRotated((GLfloat) (y - mouseEnterY) * 0.5f, 1.0f, 1.0f, 0.0f);
        mouseEnterX = x;
        mouseEnterY = y;
    }
    glutPostRedisplay();
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
    glutMouseFunc(handleMouse);
    glutMotionFunc(handleMouseMove);
    glutMainLoop();

    return 0;
}
