#include "Bullet.h"
Bullet::Bullet(Texture* texture, Vector2u imageCount, float switchTime,Vector2f position) :
	animation(texture, imageCount, switchTime)
{
	Vector2f size(10.0f,10.0f);
	body.setSize(size);
	body.setOrigin(size / 2.0f);
	body.setTexture(texture);
	body.setPosition(position);
	this->row = 0;
	this->dmg = 100.0;
}

void Bullet::Draw(RenderWindow & window)
{
	window.draw(body);
}

void Bullet::Update(float time)
{
		velocity.x = 0.0f;
		velocity.y = -300.0f;
		animation.Updatexy(row, time);
		body.setTextureRect(animation.xyRect);
		body.move(velocity * time);
}
