#pragma once
#include<SFML/Graphics.hpp>
#include"Collider.h"
#include"Animation.h"
using namespace sf;
class EnemyBullet
{
public:
	EnemyBullet(Texture* texture, Vector2u imageCount, float switchTime, Vector2f position);
	void Draw(RenderWindow& window);
	void Update(float time);
	Collider GetCollider() { return Collider(body); }
	Vector2f GetPosition() { return body.getPosition(); }
	float GetDmg() { return dmg; }
	float dmg;

private:
	RectangleShape body;
	Animation animation;
	Vector2f velocity;
	unsigned int row;
};

