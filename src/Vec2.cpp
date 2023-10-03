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

void Vec2::operator += (const Vec2& v) {
    x += v.x;
    y += v.y;
}

void Vec2::operator -= (const Vec2& v) {
    x -= v.x;
    y -= v.y;
}

float Vec2::magnitude() {
    return sqrt((pow(x,2) + pow(y,2)));
}

Vec2 Vec2::normalized() {
    Vec2 ret;
    float mag = magnitude();
    ret.x = x / mag;
    ret.y = y / mag;
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

