#include "Ship.h"
Ship::Ship(Texture* texture, Vector2u imageCount, float switchTime, float speed) :
	animation(texture, imageCount, switchTime)
{
	this->speed = speed;
	this->info_ally.maxHealth = 1200;
	this->info_ally.health = this->info_ally.maxHealth;
	this->info_ally.maxmana = 500;
	this->info_ally.mana = this->info_ally.maxmana;
	row = 1;
	body.setSize(Vector2f(40.0f, 50.0f)),
		body.setPosition(Vector2f(100.0f, 100.0f));
	body.setOrigin(body.getSize() / 2.0f);
	body.setTexture(texture);
	
}
void Ship::Update(float time)
{
	velocity.x = 0.0f;
	velocity.y = 0.0f;
	if (Keyboard::isKeyPressed(Keyboard::A))
		velocity.x -= speed,row=0;
	if (Keyboard::isKeyPressed(Keyboard::D))
		velocity.x += speed,row=2;
	if (Keyboard::isKeyPressed(Keyboard::W))
		velocity.y -= speed;
	if (Keyboard::isKeyPressed(Keyboard::S))
		velocity.y += speed;
	animation.Updateyx(row, time);
	body.setTextureRect(animation.xyRect);
	body.move(velocity * time);
	row = 1;
}

void Ship::Draw(RenderWindow& window)
{
	window.draw(body);
}
