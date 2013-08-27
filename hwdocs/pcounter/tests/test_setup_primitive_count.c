#include <GL/glut.h>

#include "common.h"

#define MAX_POINTS      10000
#define MAX_LINES       10000
#define MAX_TRIANGLES   10000

/*
 * === NV86 signals ===
 *
 * set 1 [graph]:
 * 0xd2: NV_setup_primitive_count
 */

void test_setup_primitive_count()
{
    int i;

    for (i = 0; i < MAX_POINTS; i++) {
        glBegin(GL_POINTS);
        glVertex2i(0, 0);
        glEnd();
    }

    for (i = 0; i < MAX_LINES; i++) {
        glBegin(GL_LINES);
        glVertex2i(0, 0);
        glVertex2i(1, 1);
        glEnd();
    }

    for (i = 0; i < MAX_TRIANGLES; i++) {
        glBegin(GL_TRIANGLES);
        glVertex2i(0, 0);
        glVertex2i(1, 0);
        glVertex2i(0, 1);
        glEnd();
    }
}

int main(int argc, char **argv)
{
    gl_init(argc, argv, 10, 10, "test_setup_primitive_count");
    gl_run_test(test_setup_primitive_count);

    return 0;
}
