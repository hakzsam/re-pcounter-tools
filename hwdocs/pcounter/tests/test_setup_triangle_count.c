#include <GL/glut.h>

#include "common.h"

#define MAX_TRIANGLES 50000

/*
 * === NV86 signals ===
 *
 * set 1 [graph]:
 * 0xd5: NV_setup_triangle_count
 */

void test_setup_triangle_count()
{
    int i;

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
    gl_init(argc, argv, 10, 10, "test_setup_triangle_count");
    gl_run_test(test_setup_triangle_count);

    return 0;
}
