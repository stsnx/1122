#include "EnemyBullet.h"
EnemyBullet::EnemyBullet(Texture* texture, Vector2u imageCount, float switchTime, Vector2f position) :
	animation(texture, imageCount, switchTime)
{
	this->dmg = 100;
	Vector2f size(10.0f, 10.0f);
	body.setSize(size);
	body.setOrigin(size / 2.0f);
	body.setTexture(texture);
	body.setPosition(position);
	this->row = 0;
}

void EnemyBullet::Draw(RenderWindow& window)
{
	window.draw(body);
}

void EnemyBullet::Update(float time)
{
	velocity.x = 0.0f;
	velocity.y = 300.0f;
	animation.Updatexy(row, time);
	body.setTextureRect(animation.xyRect);
	body.move(velocity * time);
}