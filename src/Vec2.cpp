#include <Vec2.h>
#include <cmath>


Vec2::Vec2(float x, float y) {
    this->x = x;
    this->y = y;
}

void Vec2::operator = (const Vec2& v) {
    x = v.x;
    y = v.y;
}

Vec2 Vec2::operator + (const Vec2& v) {
    Vec2 vec;
    vec.x = x + v.x;
    vec.y = y + v.y;
    return vec;
}
Vec2 Vec2::operator - (const Vec2& v) {
    Vec2 vec;
    vec.x = x - v.x;
    vec.y = y - v.y;
    return vec;
}
void Vec2::operator += (const Vec2& v) {
    x += v.x;
    y += v.y;
}
void Vec2::operator -= (const Vec2& v) {
    x -= v.x;
    y -= v.y;
}
Vec2 Vec2::operator * (float e) {
    Vec2 vec;
    vec.x = x*e;
    vec.y = y*e;
    return vec;
}

Vec2 Vec2::operator / (float e) {
    Vec2 vec;
    vec.x = x/e;
    vec.y = y/e;
    return vec;
}



float Vec2::magnitude() {
    return sqrt(x*x + y*y);
}

Vec2 Vec2::normalized() {
    Vec2 ret;
    // float inv = calcInvRoot(x*x + y*y);
    // ret.x = x * inv;
    // ret.y = y * inv;

    float mag = magnitude();
    ret.x = x/mag;
    ret.y = y/mag;

    return ret;
}

float Vec2::distVec2(const Vec2& b) {
    return (*this-b).magnitude();
}

float Vec2::incl() {
    return atan2(y,x);
}

float Vec2::inclVec2(const Vec2& b) {
    return (*this-b).incl();
}

Vec2 Vec2::GetRotated(float d) {
    Vec2 vec;
    vec.x = (x*cos(d)) - (y*sin(d));
    vec.y = (y*cos(d)) + (x*sin(d));
    return vec;
}

float Vec2::calcInvRoot(float x) {
    long long i;
    float x2 = x * 0.5F;
    float y = x;
    
    i = *(long long*) &y;
    i = 0x5f3759df - (i >> 1);
    y = *(float*) &i;
    y *= (1.5F - (x2 * y * y));
    y *= (1.5F - (x2 * y * y));
    return y;
}