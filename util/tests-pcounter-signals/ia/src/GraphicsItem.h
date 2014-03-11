#ifndef __GRAPHICS_ITEM_H
#define __GRAPHICS_ITEM_H

/**
 * \class GraphicsItem
 * \brief This abstract class represents a graphics item.
 */
class GraphicsItem {

    public:
        /**
         * \brief Render a graphics item.
         */
        virtual void render() = 0;
};

#endif /* __GRAPHICS_ITEM_H */
