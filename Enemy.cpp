#include "Enemy.h"
#include <Novice.h>

Enemy::Enemy() {
	pos.x = 100.0f;
	pos.y = 400.0f;
	speed.x = 5.0f;
	speed.y = 5.0f;
	radius = 16;
}

void Enemy::Move() {
	pos.x += speed.x;
	pos.y += speed.y;
	
	if (pos.x > 1280 - radius || pos.x < radius) {
		speed.x *= -1;
	}
	if (pos.y > 720 - radius || pos.y < radius) {
		speed.y *= -1;
	}
	
}

void Enemy::Draw() {
	Novice::DrawEllipse((int)pos.x, (int)pos.y, radius, radius, 0.0f, WHITE, kFillModeSolid);
}