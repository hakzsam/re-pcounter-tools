#ifndef __GRAPHICS_PGM3D_ITEM_H
#define __GRAPHICS_PGM3D_ITEM_H

#include <inttypes.h>

#include <string>
#include <vector>

#include "gl.h"
#include "GraphicsItem.h"

/**
 * \class GraphicsPGM3DItem
 * \brief This class represents a PGM3D item.
 */
class GraphicsPGM3DItem : public GraphicsItem {

    public:
        GraphicsPGM3DItem();

        /**
         * \brief Load the PGM3D image.
         */
        bool load(const std::string & filename);

        /**
         * \brief Render the PGM3D image.
         */
        void render();

    private:
        /**
         * \brief Init Vertex Buffer Object.
         */
        void initVBO();

        /**
         * \brief Build geometry and colors.
         */
        void build(std::vector<GLint> & vertices,
                   std::vector<GLubyte> & colors) const;

        /**
         * \brief Render the PGM3D image using VBO.
         */
        void renderVBO() const;

        /**
         * \brief Render the PGM3D image using immediate mode.
         */
        void renderImmediate() const;

        /**
         * \brief Get grayscale value at the give voxel.
         */
        const uint16_t & voxel(const int & x, const int & y,
                               const int & z) const {
            return m_voxels[x + y * m_shiftY + z * m_shiftZ];
        }

        /**
         * \brief Get the corresponding alpha value of the grayscale.
         *        This method returns 255 when the given value is not
         *        contained by this very basic lookup table.
         */
        const int lut(const int & grayscale) const;

    private:
        /**
         * \brief TRUE for using VBO mode.
         */
        static const bool useVBO;

    private:
        /* Image data. */
        std::vector<uint16_t> m_voxels;
        int m_sizeX, m_sizeY, m_sizeZ;
        int m_shiftY, m_shiftZ;
        uint16_t m_grayscale;

        /* VBO rendering. */
        bool m_VBOIsInitialized;
        GLsizei m_numIndices;
        GLuint m_buffers[3];
};

#endif /* __GRAPHICS_PGM3D_ITEM_H */
