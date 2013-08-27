#include <GL/glut.h>

#include "common.h"

#define MAX_LINES 50000

/*
 * === NV86 signals ===
 *
 * set 1 [graph]:
 * 0xd4: NV_setup_line_count
 */

static void test_setup_line_count()
{
    int i;

    for (i = 0; i < MAX_LINES; i++) {
        glBegin(GL_LINES);
        glVertex2i(0, 0);
        glVertex2i(1, 1);
        glEnd();
    }
}

int main(int argc, char **argv)
{
    gl_init(argc, argv, 10, 10, "test_setup_line_count");
    gl_run_test(test_setup_line_count);

    return 0;
}
