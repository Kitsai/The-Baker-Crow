#include "Vec2.h"
#include <cmath>

Vec2::Vec2(float x, float y) {
    this->x = x;
    this->y = y;
}

void Vec2::operator = (const Vec2& v) {
    this->x = v.x;
    this->y = v.y;
}

Vec2 Vec2::operator + (const Vec2& v) {
    return Vec2(this->x +v.x,this->y+ v.y);
}

Vec2 Vec2::operator - (const Vec2& v) {
    return Vec2(this->x - v.x, this->y - v.y);
}

void Vec2::operator += (const Vec2& v) {
    this->x += v.x;
    this->y += v.y;
}
void Vec2::operator -= (const Vec2& v) {
    this->x -= v.x;
    this->y -= v.y;
}
Vec2 Vec2::operator*(float scalar){
    return Vec2(this->x * scalar, this->y * scalar);
}

Vec2 Vec2::operator / (float e) {
    return Vec2(this->x/e, this->y/e);
}

bool Vec2::operator==(const Vec2& v) {
    return this->x==v.x && this->y==v.y;
}

bool Vec2::operator!=(const Vec2& v) {
    return not operator==(v);
}

bool Vec2::operator==(float f) {
    return magSquare() == f*f;
}

bool Vec2::operator!=(float f) {
    return !operator==(f);
}

bool Vec2::operator<(Vec2& v) {
    return magSquare() < v.magSquare();
}

bool Vec2::operator<=(Vec2& v) {
    return operator<(v) && operator==(v);
}

bool Vec2::operator>(Vec2& v) {
    return !operator<=(v);
}

bool Vec2::operator>=(Vec2& v) {
    return !operator<(v);
}


float Vec2::magnitude() {
    return sqrt(magSquare());
}

float Vec2::magSquare() {
    return x*x + y*y;
}

Vec2 Vec2::normalized() {
    Vec2 ret;
    //float inv = calcInvRoot(x*x + y*y);
    //ret.x = x * inv;
    //ret.y = y * inv;
    float mag = magnitude();
    if (mag != 0) {
        ret.x = this->x / mag;
        ret.y = this->y / mag;
    } else {
        ret.x = this->x;
        ret.y = this->y;
    }
    return ret;
}


float Vec2::distVec2(const Vec2& b) {
    return (*this-b).magnitude();
}

float Vec2::incl() {
    return atan2(this->y,this->x);
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