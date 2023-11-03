#ifndef Rect_h_
#define Rect_h_

#include "Vec2.h"

/// @brief An alrithmethic object that represents a rectangle.
class Rect {
    public:
        /// @brief position on the x axis.
        float x;
        /// @brief position on the y axis.
        float y;
        /// @brief rectangle width.
        float w;
        /// @brief rectangle height.
        float h;

        
        /// @brief Parameterized constructor for Rect that initializes Rect with custom values.
        /// @param x Position on X axis. Default = 0.
        /// @param y Position on Y axis. Default = 0.
        /// @param w Rectangle width. Default = 0.
        /// @param h Rectangle height. Default = 0.
        Rect(float x = 0,float y = 0, float w = 0, float h = 0);
        Rect(const Rect& other);

        // OPERATIOS WITH VECTORS.
        Rect operator+(const Vec2& v);
        Rect operator-(const Vec2& v);
        void operator=(const Vec2& v);
        void operator+=(const Vec2& v);
        void operator-=(const Vec2& v);

        // OPERATIONS WITH OTHER RECTS
        Rect operator+(const Rect& r);
        Rect operator-(const Rect& r);
        void operator=(const Rect& r);       

        /// @brief Get the position of the box.
        /// @return A vector containing the positions x and y of the box.
        Vec2 GetPos();
        /// @brief A Getter for the center of the box.
        /// @return A vector containing the position of the center of the box.
        Vec2 GetCenter();
        /// @brief Sets the center of the box to the point given by vector. Useful for dealing with scale changes.
        /// @param r a vector containing where the center of the box should be.
        void SetCenter(const Vec2& r);

        /// @brief calculates the distance between the centers of two rectangles.
        /// @param r box that should be compared to.
        /// @return float indicating the distance.
        float distRect(Rect& r); 
        /// @brief Cheks if given point is inside the rectangle.
        /// @param v Vector indicating the position.
        /// @return true if the point is inside the rectangle area.
        bool isInside(const Vec2& v);
        /// @brief Cheks if given point is inside the rectangle.
        /// @param x Position on the x axis that should be checked.
        /// @param y Position on the y axis that should be checked.
        /// @return true if the point is inside the rectangle area.
        bool isInside(float x,float y);
};

#endif