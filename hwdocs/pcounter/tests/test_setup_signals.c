#include <unistd.h>
#include <GL/glut.h>

/**
 * This test program experiments counts points, lines, triangles, primitives
 * and primitives culled. It should return the following results :
 *
 *  - setup_primitive_count: 100000 (ie. setup_point_count + setup_line_count +
 *                                   setup_triangle_count)
 *  - setup_point_count: 20000
 *  - setup_line_count: 32000
 *  - setup_triangle_count: 48000
 *  - setup_primitive_culled_count: 48000
 */

#define POINT_COUNT     20000
#define LINE_COUNT      32000
#define TRIANGLE_COUNT  48000

static void test_setup_point_count()
{
    int i;

    glBegin(GL_POINTS);
    for (i = 0; i < POINT_COUNT; ++i)
        glVertex2i(0, 0);
    glEnd();
}

static void test_setup_line_count()
{
    int i;

    glBegin(GL_LINES);
    for (i = 0; i < LINE_COUNT; ++i) {
        glVertex2i(0, 0);
        glVertex2i(1, 1);
    }
    glEnd();
}

static void test_setup_triangle_count()
{
    int i;

    glBegin(GL_TRIANGLES);
    for (i = 0; i < TRIANGLE_COUNT; ++i) {
        glVertex2i(0, 0);
        glVertex2i(1, 0);
        glVertex2i(0, 1);
    }
    glEnd();
}

static void test_setup_primitive_culled_count()
{
    glEnable(GL_CULL_FACE);
    test_setup_triangle_count(); /* This is just an example... */
    glDisable(GL_CULL_FACE);
}

static void run_tests()
{
    test_setup_point_count();
    test_setup_line_count();
    test_setup_triangle_count();
    test_setup_primitive_culled_count();
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

    run_tests();

    glutSwapBuffers();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(800, 600);
    glutCreateWindow("NVIDIA SETUP signals test");

    glutIdleFunc(idle);
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
