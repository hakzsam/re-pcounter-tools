#include <unistd.h>
#include <GL/glut.h>

#include "common.h"

static void (*run_test)(void) = NULL;

void gl_init(int argc, char **argv, int width, int height, char *name)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(width, height);
    glutCreateWindow(name);
}

static void idle()
{
    /* Only draw one frame per sec. */
    sleep(1);

    /* Draw the current frame. */
    glutPostRedisplay ();
}

static void reshape(int w, int h)
{
    glViewport(0,0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, w / h, 1, 10);
    glMatrixMode(GL_MODELVIEW);
}

static void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, 0, -10, 0, 0, 0, 0, 1, 0);

    run_test();

    glutSwapBuffers();
}

void gl_run_test(void (*func)(void))
{
    run_test = func;

    glutIdleFunc(idle);
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutMainLoop();
}
