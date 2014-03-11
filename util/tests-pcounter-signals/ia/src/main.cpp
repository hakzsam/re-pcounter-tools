#include <iostream>
#include <string>

#include "gl.h"
#include "GraphicsPGM3DItem.h"
#include "GraphicsScene.h"

using namespace std;

GraphicsScene scene;

/* Forward GLUT events to the graphics scene. */
static void display()
{
    scene.render();
}

static void idle()
{
    scene.idle();
}

static void reshape(int w, int h)
{
    scene.reshape(w, h);
}

static void special(int key, int x, int y)
{
    scene.specialEvent(key, x, y);
}

static void keyboard(unsigned char key, int x, int y)
{
    scene.keyboardEvent(key, x, y);
}

static void mouse(int button, int state, int x, int y)
{
    scene.mouseEvent(button, state, x, y);
}

int main(int argc, char **argv)
{
    GraphicsPGM3DItem img;
    string filename;

    if (argc < 2) {
        cerr << "Usage: %s <file.pgm3d>\n" << argv[0] << endl;
        return 1;
    }
    filename = string(argv[1]);

    /* Load the PGM3D image. */
    if (!img.load(filename)) {
        cerr << "Failed to load '" << filename << "'!" << endl;
        return 1;
    }

    /* Add it to the scene. */
    scene.addGraphicsItem(&img);

    /* Init GLUT and create a window. */
    glutInit(&argc, argv);
    glutInitWindowSize(800, 600);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutCreateWindow("PGM3D Viewer");

    /* Register callbacks. */
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(idle);
    glutSpecialFunc(special);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);

    /* Init OpenGL scene. */
    scene.init();

    /* Enter GLUT event processing cycle. */
    glutMainLoop();

    return 0;
}
