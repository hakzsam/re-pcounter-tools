#include <GL/glut.h>

#include "common.h"

#define MAX_POINTS 50000

/*
 * === NV86 signals ===
 *
 * set 1 [graph]:
 * 0xd3: NV_setup_point_count
 */

void test_setup_point_count()
{
    int i;

    for (i = 0; i < MAX_POINTS; i++) {
        glBegin(GL_POINTS);
        glVertex2i(0, 0);
        glEnd();
    }
}

int main(int argc, char **argv)
{
    gl_init(argc, argv, 10, 10, "test_setup_point_count");
    gl_run_test(test_setup_point_count);

    return 0;
}
