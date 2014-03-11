#ifndef __GRAPHICS_SCENE_H
#define __GRAPHICS_SCENE_H

#include <string>
#include <vector>

#include "GraphicsItem.h"

/**
 * \class GraphicsScene
 * \brief This class represents the OpenGL scene.
 */
class GraphicsScene {

    public:
        GraphicsScene(bool drawGrid = true);

        /**
         * \brief Initialize OpenGL scene.
         */
        void init() const;

        /**
         * \brief Render OpenGL scene.
         */
        void render();

        /**
         * \brief Idle OpenGL scene.
         */
        void idle();

        /**
         * \brief Reshape window.
         */
        void reshape(int & w, int & h) const;

        /**
         * \brief Special event.
         */
        void specialEvent(int & key, int & x, int &y);

        /**
         * \brief Keyboard event.
         */
        void keyboardEvent(unsigned char & key, int & x, int & y);

        /**
         * \brief Mouse event.
         */
        void mouseEvent(int & button, int & state, int & x, int & y);

        /**
         * \brief Add a graphics item.
         */
        void addGraphicsItem(GraphicsItem * item);

    private:
        /**
         * \brief Draw a white grid on the "floor".
         */
        void drawGrid() const;

        /**
         * \brief Compute the number of frame per second.
         */
        void calculateFPS();

        double m_centerX, m_centerY, m_centerZ;
        std::vector<GraphicsItem *> m_items;
        double m_eyeX, m_eyeY, m_eyeZ;
        double m_rotateX, m_rotateY;
        bool m_drawGrid;

        /* FPS counter */
        int m_currentTime, m_previousTime;
        int m_frameCount;
        float m_fps;
};

#endif /* __GRAPHICS_SCENE_H */
