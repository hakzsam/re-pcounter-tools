#include <fstream>
#include <sstream>
#include <iostream>

#include "gl.h"
#include "GraphicsPGM3DItem.h"

using namespace std;

/**
 * Around 30 FPS with immediate mode on my NV98 with Nouveau/Mesa
 * and 163 FPS with VBO.
 */
const bool GraphicsPGM3DItem::useVBO = true;

GraphicsPGM3DItem::GraphicsPGM3DItem()
{
    m_sizeX     = 0;
    m_sizeY     = 0;
    m_sizeZ     = 0;
    m_grayscale = 0;
    m_voxels    = vector<uint16_t>();
}

bool GraphicsPGM3DItem::load(const string & filename)
{
    string line;
    ifstream f;

    f.open(filename.c_str());
    if (!f.is_open())
        return false;

    /* Put the contents of the file to a buffer. */
    string buf(static_cast<stringstream const &>(stringstream() << f.rdbuf()).str());
    f.close();

    /* Parse the file. */
    istringstream iss(buf);

    /* Read magic number. */
    getline(iss, line);
    if (line.compare("PGM3D")) {
        cerr << "Invalid magic number!" << endl;
        return false;
    }

    /* Read dimensions. */
    getline(iss, line);
    istringstream iss1(line);
    iss1 >> m_sizeX >> m_sizeY >> m_sizeZ;

    /* Read grayscale value. */
    getline(iss, line);
    istringstream iss2(line);
    iss2 >> m_grayscale;

    /* Read voxels. */
    while (getline(iss, line)) {
        int voxel;
        istringstream iss3(line);
        iss3 >> voxel;
        m_voxels.push_back(voxel);
    }

    /* Compute shift. */
    m_shiftY = m_sizeX;
    m_shiftZ = m_shiftY * m_sizeY;

    return true;
}

void GraphicsPGM3DItem::render()
{
    /* Scale and translate it to the center of the scene in order to
     * improve visualization. */
    glScalef(0.05, 0.05, 0.05);
    glTranslatef(-m_sizeX / 2, 0, -m_sizeZ / 2);

    if (useVBO) {
        if (!m_VBOIsInitialized) {
            initVBO();
            m_VBOIsInitialized = true;
        }
        renderVBO();
    } else {
        renderImmediate();
    }
}

void GraphicsPGM3DItem::build(vector<GLint> & vertices,
                              vector<GLubyte> & colors) const
{
#define ADD_VERTEX(g, a, x, y, z)   \
    colors.push_back(g);            \
    colors.push_back(g);            \
    colors.push_back(g);            \
    colors.push_back(a);            \
    vertices.push_back(x);          \
    vertices.push_back(y);          \
    vertices.push_back(z)

    for (int x = 1; x < m_sizeX - 1; x++) {
        for (int y = 1; y < m_sizeY - 1; y++) {
            for (int z = 1; z < m_sizeZ - 1; z++) {
                int g = voxel(x, y, z), a;

                /* Get the corresponding alpha value of the grayscale. */
                a = lut(g);

                if (g != voxel((x-1), y, z)) {
                    ADD_VERTEX(g, a, x, y, z-1);
                    ADD_VERTEX(g, a, x, y-1, z-1);
                    ADD_VERTEX(g, a, x, y, z);
                    ADD_VERTEX(g, a, x, y-1, z);
                }

                if (g != voxel((x+1), y, z)) {
                    ADD_VERTEX(g, a, x+1, y, (z-1));
                    ADD_VERTEX(g, a, x+1, y-1, z-1);
                    ADD_VERTEX(g, a, x+1, y, z);
                    ADD_VERTEX(g, a, x+1, y-1, z);
                }

                if (g != voxel(x, (y+1), z)) {
                    ADD_VERTEX(g, a, x, y, z);
                    ADD_VERTEX(g, a, x+1, y, z);
                    ADD_VERTEX(g, a, x, y, z-1);
                    ADD_VERTEX(g, a, x+1, y, z-1);
                }

                if (g != voxel(x, (y-1), z)) {
                    ADD_VERTEX(g, a, x, y-1, z);
                    ADD_VERTEX(g, a, x+1, y-1, z);
                    ADD_VERTEX(g, a, x, y-1, z-1);
                    ADD_VERTEX(g, a, x+1, y-1, z-1);
                }

                if (g != voxel(x, y, (z+1))) {
                    ADD_VERTEX(g, a, x, y, z);
                    ADD_VERTEX(g, a, x+1, y, z);
                    ADD_VERTEX(g, a, x, y-1, z);
                    ADD_VERTEX(g, a, x+1, y-1, z);
                }

                if (g != voxel(x, y, (z-1))) {
                    ADD_VERTEX(g, a, x, y, z-1);
                    ADD_VERTEX(g, a, x+1, y, z-1);
                    ADD_VERTEX(g, a, x, y-1, z-1);
                    ADD_VERTEX(g, a, x+1, y-1, z-1);
                }
            }
        }
    }
#undef ADD_VERTEX
}

void GraphicsPGM3DItem::renderImmediate() const
{
    glBegin(GL_QUADS);
    for (int x = 1; x < m_sizeX - 1; x++) {
        for (int y = 1; y < m_sizeY - 1; y++) {
            for (int z = 1; z < m_sizeZ - 1; z++) {
                int g = voxel(x, y, z), a;

                /* Get the corresponding alpha value of the grayscale. */
                a = lut(g);

                /* Set the color of the current voxel. */
                glColor4ub(g, g, g, a);

                if (g != voxel(x, y, (z+1))) {
                    glVertex3i(x, y, z);
                    glVertex3i(x+1, y, z);
                    glVertex3i(x+1, y-1, z);
                    glVertex3i(x, y-1, z);
                }

                if (g != voxel(x, y, (z-1))) {
                    glVertex3i(x, y, z-1);
                    glVertex3i(x+1, y, z-1);
                    glVertex3i(x+1, y-1, z-1);
                    glVertex3i(x, y-1, z-1);
                }

                if (g != voxel((x+1), y, z)) {
                    glVertex3i(x+1, y, z);
                    glVertex3i(x+1, y, z-1);
                    glVertex3i(x+1, y-1, z-1);
                    glVertex3i(x+1, y-1, z);
                }

                if (g != voxel((x-1), y, z)) {
                    glVertex3i(x, y, z);
                    glVertex3i(x, y, z-1);
                    glVertex3i(x, y-1, z-1);
                    glVertex3i(x, y-1, z);
                }

                if (g != voxel(x, (y+1), z)) {
                    glVertex3i(x, y, z);
                    glVertex3i(x+1, y, z);
                    glVertex3i(x+1, y, z-1);
                    glVertex3i(x, y, z-1);
                }

                if (g != voxel(x, (y-1), z)) {
                    glVertex3i(x, y-1, z);
                    glVertex3i(x+1, y-1, z);
                    glVertex3i(x+1, y-1, z-1);
                    glVertex3i(x, y-1, z-1);
                }
            }
        }
    }
    glEnd();
}

void GraphicsPGM3DItem::initVBO()
{
    vector<GLint> vertices;
    vector<GLubyte> colors;
    int numVertices, numColors, numIndices;

    /* Build geometry and colors. */
    build(vertices, colors);

    /* Compute number of vertices, colors and indices. */
    numVertices = vertices.size();
    numColors   = numVertices + numVertices / 3;
    numIndices  = numVertices / 2;

    /* Store the number of indices to draw. */
    m_numIndices = numIndices;

    /* Quads indices are always 0,1,2,2,1,3. */
    GLuint *indices = new GLuint[numIndices];
    for (int i = 0, incr = 0; i < numIndices; i += 6, incr += 4) {
        indices[i]   = incr+0;
        indices[i+1] = incr+1;
        indices[i+2] = incr+2;
        indices[i+3] = incr+2;
        indices[i+4] = incr+1;
        indices[i+5] = incr+3;
    }

    /* Generate buffers. */
    glGenBuffers(3, m_buffers);

    /* Vertices buffer. */
    glBindBuffer(GL_ARRAY_BUFFER, m_buffers[0]);
    glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(GLint),
                 &vertices[0], GL_STATIC_DRAW);

    /* Colors buffer. */
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_buffers[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, numColors * sizeof(GLubyte),
                 &colors[0], GL_STATIC_DRAW);

    /* Indices buffer. */
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_buffers[2]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndices * sizeof(GLuint),
                 indices, GL_STATIC_DRAW);

    /* Free buffer memory. */
    delete[] indices;
}

void GraphicsPGM3DItem::renderVBO() const
{
    glBindBuffer(GL_ARRAY_BUFFER, m_buffers[0]);
    glVertexPointer(3, GL_INT, 3 * sizeof(GLint), 0);

    glBindBuffer(GL_ARRAY_BUFFER, m_buffers[1]);
    glColorPointer(4, GL_UNSIGNED_BYTE, 4 * sizeof(GLubyte), 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_buffers[2]);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    glDrawElements(GL_TRIANGLES, m_numIndices, GL_UNSIGNED_INT, 0);

    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
}

const int GraphicsPGM3DItem::lut(const int & grayscale) const
{
    int a = 255;

    switch (grayscale) {
        case 0: /* The "hull" of the ghost. */
            a = 0;
            break;
        case 51:
        case 255:
            a = 50;
            break;
        default:
            break;
    }

    return a;
}
