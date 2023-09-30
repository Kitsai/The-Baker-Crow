#ifndef Vec2_h_
#define Vec2_h_

/// @brief A objects that represents a bidimensional vector.
class Vec2 {
    public:
        float x;
        float y;

        Vec2(float x = 0, float y = 0);


        void operator = (const Vec2& v);
        Vec2 operator + (const Vec2& v);
        Vec2 operator - (const Vec2& v);
        Vec2 operator * (float e);
        Vec2 operator / (float e);
        void operator += (const Vec2& v);
        void operator -= (const Vec2& v);
        
        float magnitude();
        Vec2 normalized();
        float distVec2(const Vec2& b);
        float incl();
        float inclVec2(const Vec2& b);
        Vec2 GetRotated(float d);
};

#endif