#include <iostream>
#include <fstream>
#include <sstream>

#include "gl.h"
#include "GraphicsScene.h"

using namespace std;

GraphicsScene::GraphicsScene(bool drawGrid)
{
    /* Camera settings. */
    m_eyeX     = 0.0f;
    m_eyeY     = 1.0f;
    m_eyeZ     = 10.0f;
    m_centerX  = 0.0f;
    m_centerY  = 0.0f;
    m_centerZ  = -1.0f;

    /* GraphicsScene settings. */
    m_rotateX  = 25.0f;
    m_rotateY  = 15.0f;

    /* FPS counter settings. */
    m_currentTime  = 0;
    m_previousTime = 0;
    m_frameCount   = 0;
    m_fps          = 0.0;

    /* Debug settings. */
    m_drawGrid = drawGrid;
}

void GraphicsScene::init() const
{
    glClearColor(0.6, 0.6, 0.6, 1.0);
    glColor3f(1.0, 1.0, 1.0);

    glEnable(GL_BLEND);
    glEnable(GL_DEPTH);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void GraphicsScene::render()
{
    vector<GraphicsItem *>::iterator it;

    /* Clear the scene and reset matrix. */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    /* Set the camera. */
    gluLookAt(m_eyeX, m_eyeY, m_eyeZ, m_eyeX + m_centerX, m_eyeY + m_centerY,
              m_eyeZ + m_centerZ, 0.0f, 1.0f,  0.0f);

    /* Rotate the scene on the X axis. */
    glRotatef(m_rotateX, 1.0, 0.0, 0.0);

    if (m_drawGrid)
        drawGrid();

    /* Rotate the items on the Y axis. */
    glRotatef(m_rotateY, 0.0, 1.0, 0.0);

    /* Render all of the items. */
    for (it = m_items.begin(); it != m_items.end(); it++) {
        (*it)->render();
    }

    /* Print the number of FPS. */
    cout << "FPS: " << m_fps << endl;

    glutSwapBuffers();
}

void GraphicsScene::idle()
{
    /* Compute the number of frame per second. */
    calculateFPS();

    /* Draw the current frame. */
    glutPostRedisplay();
}

void GraphicsScene::reshape(int & w, int & h) const
{
    float ratio;

    /* Prevent a divide by zero when windows is too short. */
    if (h == 0)
        h = 1;

    /* Compute the new ratio of the perspective. */
    ratio = 1.0 * w / h;

    /* Use the projection matrix and reset it. */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    /* Set the viewport to the entire window. */
    glViewport(0, 0, w, h);

    /* Set the correct perspective. */
    gluPerspective(45, ratio, 1, 1000);

    /* Get back to the modelview matrix. */
    glMatrixMode(GL_MODELVIEW);
}

void GraphicsScene::specialEvent(int & key, int & x, int & y)
{
    switch (key) {
        case GLUT_KEY_RIGHT:
            m_rotateY -= 5;
            break;
        case GLUT_KEY_LEFT:
            m_rotateY += 5;
            break;
        case GLUT_KEY_UP:
            m_rotateX += 5;
            break;
        case GLUT_KEY_DOWN:
            m_rotateX -= 5;
            break;
        default:
            break;
    }
}

void GraphicsScene::keyboardEvent(unsigned char & key, int & x, int & y)
{
    switch (key) {
        case 'g':
            m_drawGrid = !m_drawGrid;
            break;
        default:
                break;
    }
}

void GraphicsScene::mouseEvent(int & button, int & state, int & x, int & y)
{
    float factor = 0.5f;

    if (button == 3 || button == 4) {
        if (button == 3) {
            m_eyeX += m_centerX * factor;
            m_eyeZ += m_centerZ * factor;
        } else {
            m_eyeX -= m_centerX * factor;
            m_eyeZ -= m_centerZ * factor;
        }
    }
}

void GraphicsScene::addGraphicsItem(GraphicsItem * item)
{
    m_items.push_back(item);
}

void GraphicsScene::drawGrid() const
{
    GLfloat i;

    /* Draw a white grid "floor" */
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINES);
    for (i = -2.5; i <= 2.5; i += 0.25) {
        glVertex3f(i, 0, 2.5);
        glVertex3f(i, 0, -2.5);
        glVertex3f(2.5, 0, i);
        glVertex3f(-2.5, 0, i);
    }
    glEnd();
}

void GraphicsScene::calculateFPS()
{
    /* Increase frame count. */
    m_frameCount++;

    /* Get the number of milliseconds since glutInit called
     * (or first call to glutGet(GLUT ELAPSED TIME)).*/
    m_currentTime = glutGet(GLUT_ELAPSED_TIME);

    /*  Calculate time passed. */
    int timeInterval = m_currentTime - m_previousTime;

    if (timeInterval > 1000) {
        /* Calculate the number of frames per second. */
        m_fps = m_frameCount / (timeInterval / 1000.0f);

        /* Set time. */
        m_previousTime = m_currentTime;

        /* Reset frame count. */
        m_frameCount = 0;
    }
}

