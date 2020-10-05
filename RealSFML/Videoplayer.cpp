#include "Videoplayer.h"
Videoplayer::Videoplayer(Texture* texture, Vector2u imageCount, float switchTime)
{
	this->value = 0;
	this->imageCount = imageCount;
	this->switchTime = switchTime;
	totalTime = 0.0f;
	currentImage.y = 0;
	currentImage.x = 0;
	xyRect.width = texture->getSize().x / float(imageCount.x);
	xyRect.height = texture->getSize().y / float(imageCount.y);
}
int Videoplayer::Updateyx(int row, float time)
{
	currentImage.x = row;
	totalTime += time;
	if (totalTime >= switchTime)
	{
		totalTime -= switchTime;
		currentImage.y++;
		if (currentImage.y >= imageCount.y)
		{
			this->value = 1; 
			return 0;
		}
		
	}
	xyRect.left = currentImage.x * xyRect.width;
	xyRect.top = currentImage.y * xyRect.height;
	return 0;
}
int  Videoplayer::Updatexy(int row, float time)
{
	currentImage.y = row;
	totalTime += time;
	if (totalTime >= switchTime)
	{
		totalTime -= switchTime;
		currentImage.x++;
		if (currentImage.x >= imageCount.x)
		{
			this->value = 1;
			return 0;
		}
	}
	xyRect.left = currentImage.x * xyRect.width;
	xyRect.top = currentImage.y * xyRect.height;
	return 0; 
}