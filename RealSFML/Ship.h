#pragma once
#include<SFML/Graphics.hpp>
#include "Animation.h"
#include"Collider.h"
using namespace sf;
class Ship
{
public:
	Ship(Texture* texture, Vector2u imageCount, float switchTime, float speed);
	void Update(float time);
	void Draw(RenderWindow& window);
	Vector2f GetPosition() { return body.getPosition(); }
	Collider GetCollider() { return Collider(body); }
	float GetHealth() { return info_ally.health; }
	Vector2f GetSize() { return body.getSize(); }
	float GetMaxHealth() { return info_ally.maxHealth; }
	float GetMaxMana() { return info_ally.maxmana; }
	float GetMana() { return info_ally.mana; }
	struct info
	{
		float health;
		float maxHealth;
		int atkSpd;
		float mana;
		float maxmana;
	} info_ally;
	Vector2f velocity;
	float speed;
	RectangleShape body;
private:
	
	Animation animation;
	unsigned int row;
	

};