#ifndef Vec2_h_
#define Vec2_h_

/// @brief A objects that represents a bidimensional vector.
class Vec2 {
    public:
        /// @brief position of point on the x axis.
        float x;
        /// @brief position of point on the y axis
        float y;

        /// @brief Constructor for the vector.
        /// @param x Value for x axis. Default = 0.
        /// @param y Value for y axis. Default = 0
        Vec2(float x = 0, float y = 0);


        void operator = (const Vec2& v);
        Vec2 operator + (const Vec2& v);
        Vec2 operator - (const Vec2& v);
        void operator += (const Vec2& v);
        void operator -= (const Vec2& v);
        Vec2 operator * (float e);
        Vec2 operator / (float e);
        
        /// @brief Gets the vector magnitude.
        /// @return magnitude as a float.
        float magnitude();
        /// @brief Normalizes the vector using its magnitude.
        /// @return A normalized version of the vector.
        Vec2 normalized();
        /// @brief Calculates the distance between two points.
        /// @param b Vector to be compared with.
        /// @return floating point equivalent to the distance.
        float distVec2(const Vec2& b);
        /// @brief Inclination of the current vector.
        /// @return An float representing th inclination in radians.
        float incl();
        /// @brief Inlination of the angle between two vectors.
        /// @param b Vector to be compared with.
        /// @return floating point representing the inclination in radians.
        float inclVec2(const Vec2& b);
        /// @brief Gets a version of the vector rotated.
        /// @param d Radians to rotate the vector.
        /// @return Rotated version of vector by d radians.
        Vec2 GetRotated(float d);
};

#endif