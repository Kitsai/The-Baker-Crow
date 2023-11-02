#include <Rect.h>

Rect::Rect(float x, float y, float w, float h) {
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
}

Rect Rect::operator+(const Vec2& v) {
    Rect rect;
    rect.x = x+v.x;
    rect.y = y+v.y;
    rect.w = w;
    rect.h = h;
    return rect;
}

Rect Rect::operator-(const Vec2& v) {
    Rect rect;
    rect.x = x-v.x;
    rect.y = y-v.y;
    rect.w = w;
    rect.h = h;
    return rect;
}

void Rect::operator=(const Vec2& v) {
    x = v.x;
    y = v.y;
}

void Rect::operator+=(const Vec2& v) {
    x += v.x;
    y += v.y;
}

void Rect::operator-=(const Vec2& v) {
    x -= v.x;
    y -= v.y;
}

Rect Rect::operator+(const Rect& r) {
    Rect rect;
    rect.x = x+r.x;
    rect.y = y+r.y;
    rect.w = w+r.w;
    rect.h = h+r.h;
    return rect;    
}

Rect Rect::operator-(const Rect& r) {
    Rect rect;
    rect.x = x-r.x;
    rect.y = y-r.y;
    rect.w = w-r.w;
    rect.h = h-r.h;
    return rect;    
}

void Rect::operator=(const Rect& r) {
    x = r.x;
    y = r.y;
    w = r.w;
    h = r.h;
}

Vec2 Rect::GetPos() {
    return {x,y};
}

Vec2 Rect::GetCenter() {
    Vec2 ret;
    ret.x = x+(w/2);
    ret.y = y+(h/2);
    return ret;
}

void Rect::SetCenter(const Vec2& v) {
    x = v.x - (w/2);
    y = v.y - (h/2);
}

float Rect::distRect(Rect& r) {
    return GetCenter().distVec2(r.GetCenter());
}

bool Rect::isInside(const Vec2& v) {
    if((v.x >= 0 && v.x <= w) && (v.y >= 0 && v.y <= h)) 
        return true;
    else
        return false;
}

bool Rect::isInside(float x, float y) {
    float newX = x-this->x;
    float newY = y-this->y;
    if(newX >= 0 && newX <= this->w && newY > 0 && newY <= this->h)
        return true;
    else    
        return false; 
}