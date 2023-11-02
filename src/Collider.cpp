#include <Collider.h>
#include <algorithm>


#ifdef DEBUG
#include "Camera.h"
#include "Game.h"

#include <SDL2/SDL.h>
#endif // DEBUG

Collider::Collider(GameObject& associated, Vec2 scale, Vec2 offSet, SDL_Color color): Component(associated) {
	this->scale = scale;
	offset = offSet;
	this->color = color;
}

void Collider::Update(float dt) {
	box = associated.box;
	box.w *= scale.x;
	box.h *= scale.y;
	box.SetCenter((associated.box.GetCenter() + offset.GetRotated(associated.angleDeg)));
}

void Collider::Render() {
    #ifdef DEBUG
	Vec2 center( box.GetCenter() );
	SDL_Point points[5];

	Vec2 point = (Vec2(box.x, box.y) - center).GetRotated( associated.angleDeg )
					+ center - Camera::pos;
	points[0] = {(int)point.x, (int)point.y};
	points[4] = {(int)point.x, (int)point.y};
	
	point = (Vec2(box.x + box.w, box.y) - center).GetRotated( associated.angleDeg )
					+ center - Camera::pos;
	points[1] = {(int)point.x, (int)point.y};
	
	point = (Vec2(box.x + box.w, box.y + box.h) - center).GetRotated( associated.angleDeg )
					+ center - Camera::pos;
	points[2] = {(int)point.x, (int)point.y};
	
	point = (Vec2(box.x, box.y + box.h) - center).GetRotated( associated.angleDeg )
					+ center - Camera::pos;
	points[3] = {(int)point.x, (int)point.y};

	SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), color.r , color.g, color.b, color.a);
	SDL_RenderDrawLines(Game::GetInstance().GetRenderer(), points, 5);
#endif // DEBUG
}

bool Collider::Is(std::string type) {
    if(type == "Collider") 
        return true;
    else
        return false; 
}

void Collider::SetScale(Vec2 scale) {
	this->scale = scale;
}

void Collider::SetOffset(Vec2 offset) {
	this->offset = offset;
}

void Collider::SetColor(SDL_Color color) {
	this->color = color;
}