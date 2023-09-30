#ifndef Rect_h_
#define Rect_h_

#include <Vec2.h>

/// @brief An alrithmethic object that represents a rectangle.
class Rect {
    public:
        float x;
        float y;
        float w;
        float h;


        Rect(float x = 0,float y = 0, float w = 0, float h = 0);

        Rect operator+(const Vec2& v);
        Rect operator-(const Vec2& v);
        void operator=(const Vec2& v);
        void operator+=(const Vec2& v);
        void operator-=(const Vec2& v);

        Rect operator+(const Rect& r);
        Rect operator-(const Rect& r);
        void operator=(const Rect& r);       

        Vec2 GetPos();
        Vec2 GetCenter();
        void SetCenter(const Vec2& r);

        float distRect(Rect& r); 
        bool isInside(const Vec2& v);
        bool isInside(float x,float y);
};

#endif