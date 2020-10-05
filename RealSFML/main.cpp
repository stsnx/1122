#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include<iostream>
#include <sstream>
#include <string>
#include<vector>
#include<Windows.h>
#include "Ship.h"
#include "Platform.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Skill.h"
#include "EnemyBullet.h"
#include "Eliminate.h"
using namespace sf;
using namespace std;
template <typename T>
string str(const T& x)
{
	ostringstream oss;
	oss << x;
	return oss.str();
}
static const float	VIEW_IN = 512.0F;
void ReSizeView(const RenderWindow& window, View& view)
{
	float ratio = float(window.getSize().x) / float(window.getSize().y);
	view.setSize(ratio * VIEW_IN, VIEW_IN);
}
int randomRange(int l, int r)
{
	int t = rand() % r- rand() % r;
	while (t<l || t>r) t = rand() % r - rand() % r;
	return t;
}
int main()
{
	//setuptime
	srand(time(NULL));
	float time = 0.0f;
	float delayShoot;
	float delayEnemyShoot;
	float delayDeploy;
	float delayUltimate;
	float cooldown_Ultimate = 0;
	float count_Ultimate ;
	int score = 0;
	Clock clock;
	Clock clock2;
	Clock clock3;
	Clock clock4;
	Clock clock5;
	Clock Cooldown;
	//put object
	Font font;
	font.loadFromFile("C:/Users/STSNX/source/repos/RealSFML/Source/arial.ttf");
	if (!font.loadFromFile("C:/Users/STSNX/source/repos/RealSFML/Source/arial.ttf"));
	{
		cout << "Failed to load file";
	}
	RenderWindow window(VideoMode(1024, 768), "Kuy", Style::Close | Style::Titlebar | Style::Resize);
	View view(Vector2f(0.0f, 0.0f), Vector2f(VIEW_IN, VIEW_IN));
	Texture spaceShip,blueBullet,enemy,laser,redBullet,bodyLaser,enemyDestroyed,interfaceShip,shipDestroyed;
	spaceShip.loadFromFile("C:/Users/STSNX/source/repos/RealSFML/Source/ship2.png");
	blueBullet.loadFromFile("C:/Users/STSNX/source/repos/RealSFML/Source/fakeBlueBullet.png");
	enemy.loadFromFile("C:/Users/STSNX/source/repos/RealSFML/Source/enemy.png");
	laser.loadFromFile("C:/Users/STSNX/source/repos/RealSFML/Source/headUltimateLaser.png");
	bodyLaser.loadFromFile("C:/Users/STSNX/source/repos/RealSFML/Source/ultimateLaser.png");
	redBullet.loadFromFile("C:/Users/STSNX/source/repos/RealSFML/Source/fakeRedBullet.png");
	enemyDestroyed.loadFromFile("C:/Users/STSNX/source/repos/RealSFML/Source/enemyShipDestroyed.png");
	interfaceShip.loadFromFile("C:/Users/STSNX/source/repos/RealSFML/Source/interface.png");
	shipDestroyed.loadFromFile("C:/Users/STSNX/source/repos/RealSFML/Source/shipDestroyed.png");
	Texture healthbar, manaShip;
	healthbar.loadFromFile("C:/Users/STSNX/source/repos/RealSFML/Source/Healthbar.png");
	manaShip.loadFromFile("C:/Users/STSNX/source/repos/RealSFML/Source/mana.png");
	Texture skill, skillused;
	skill.loadFromFile("C:/Users/STSNX/source/repos/RealSFML/Source/LuxMaliceCannon.png");
	skillused.loadFromFile("C:/Users/STSNX/source/repos/RealSFML/Source/LuxMaliceCannonUsed.png");
	Ship ship(&spaceShip, Vector2u(3, 3), 0.1f, 300.0f);
	vector<Bullet> bullets;
	vector<Platform> platforms;
	vector<Platform> interface_ShipHealth;
	vector<Platform> interface_ShipMana; 
	vector<Platform> interface_ShipSkill;
	vector<EnemyBullet> enemybullets;
	vector<Enemy> enemys;
	vector<Skill> skills;
	vector<Eliminate> players;
	bool ultimateOn = false;
	while (window.isOpen())
	{
		//settime;
		time = clock.restart().asSeconds();
		delayShoot = clock2.getElapsedTime().asMilliseconds();
		delayDeploy = clock3.getElapsedTime().asMilliseconds();
		delayUltimate = clock4.getElapsedTime().asMilliseconds();
		delayEnemyShoot = clock5.getElapsedTime().asMilliseconds();
		count_Ultimate = Cooldown.getElapsedTime().asMilliseconds();
		Event ev;
		while (window.pollEvent(ev))
		{
			switch (ev.type)
			{
			case Event::Closed: window.close(); break;
			case Event::Resized: ReSizeView(window, view);
			}
		}
		//putobject
		
		platforms.push_back(Platform(&interfaceShip, Vector2f(500.0f, 100.0f), Vector2f(0.0f, 200.0f)));

		if (!interface_ShipHealth.empty()) interface_ShipHealth.pop_back();
		if (ship.GetHealth() > 0 && ship.GetHealth() <= ship.GetMaxHealth())
		{
			float current = 287 * ship.GetHealth() / ship.GetMaxHealth();
			Platform hb(&healthbar, Vector2f(current, 8.0f), Vector2f(232.0f - (287 - current), 226.0f));
			hb.body.setOrigin(hb.body.getSize());
			interface_ShipHealth.push_back(hb);
		}
		if (!interface_ShipMana.empty()) interface_ShipMana.pop_back();
		if (ship.GetMana() > 0&& ship.GetMana()<=ship.GetMaxMana())
		{
			float current = 287 * ship.GetMana() / ship.GetMaxMana();
			Platform mn(&manaShip, Vector2f(current, 8.0f), Vector2f(232.0f - (287 - current), 240.0f));
			mn.body.setOrigin(mn.body.getSize());
			interface_ShipMana.push_back(mn);
		}
		if (!interface_ShipSkill.empty()) interface_ShipSkill.pop_back();
		if (cooldown_Ultimate==0&& ship.GetMana() >= 500)
		{
			Platform sk(&skill, Vector2f(34.0f, 32.0f), Vector2f(139.0f, 185.0f));
			interface_ShipSkill.push_back(sk);
		}
		else 
		{
			Platform sk(&skillused, Vector2f(34.0f, 32.0f), Vector2f(139.0f, 185.0f));
			interface_ShipSkill.push_back(sk);
		}
		//shoot bullet
		if (Keyboard::isKeyPressed(Keyboard::Space))
		{
			if (delayShoot > 300)
			{
				Vector2f tempPosition = ship.GetPosition();
				Bullet temp(&blueBullet, Vector2u(2, 1), 0.1f, Vector2f(tempPosition.x, tempPosition.y - 50.0f));
				bullets.push_back(temp);
				clock2.restart();
			}
		}
		//ultimateskill
		if (Keyboard::isKeyPressed(Keyboard::R))
		{
			if (ship.GetMana()>=500&&cooldown_Ultimate==0)
			{
				Vector2f tempPosition = ship.GetPosition();
				Skill temp(&laser, Vector2u(2, 1), 0.1f, Vector2f(tempPosition.x - 1.0f, tempPosition.y - 50.0f) , 300.0f,Vector2f(100.0f,50.0f));
				Skill temp2(&bodyLaser, Vector2u(1, 1), 0.1f, Vector2f(tempPosition.x+2.0f, tempPosition.y - 340.0f), 300.0f, Vector2f(18.0f, 550.0f));
				skills.push_back(temp);
				skills.push_back(temp2);
				ultimateOn = true;
				cooldown_Ultimate = 20;
				ship.info_ally.mana -= 500;
				if (ship.info_ally.mana < 0) ship.info_ally.mana = 0;
				Cooldown.restart();
				clock4.restart();
			}
		}
		
		//spawn enemy
		if(delayDeploy>5000)
			{
			Enemy temp(&enemy, Vector2u(3, 3), 0.1f, Vector2f(randomRange(-240, 240),-300.0f));
			enemys.push_back(temp);
			clock3.restart();
			}
		//randombullet
		for (Enemy& Enemys : enemys)
		{
			if (delayEnemyShoot > 1000)
			{
				if (rand() % 100 > 50)
				{
					Vector2f tempPosition = Enemys.GetPosition();
					EnemyBullet temp(&redBullet, Vector2u(2, 1), 0.1f, Vector2f(tempPosition.x, tempPosition.y + 50.0f));
					enemybullets.push_back(temp);
					clock5.restart();
				}
			}
		}
		//checkultimate
		if (ultimateOn)
		{
			if (delayUltimate == 2000)
			{
				skills.erase(skills.begin());
				skills.erase(skills.begin());
				clock4.restart();
				ultimateOn = false;
			}
		}
		
		//check collition
		vector<Enemy>::iterator enemyItr = enemys.begin();	
		while(enemyItr!=enemys.end())
		{
			bool checkCollitionByLaser = false;
			bool checkCollitionByBullet = false;
			vector<Bullet>::iterator bulletItr = bullets.begin();
			Enemy tempEnemy = *enemyItr;
			float bulletDmg,laserDmg;
			while (bulletItr != bullets.end())
			{
				Bullet tempBullet = *bulletItr;
				
				
				Collider bulletHit = tempBullet.GetCollider();
				if (tempEnemy.GetCollider().CheckCollision(bulletHit))
				{
					score += 50;
					ship.info_ally.mana += 75;
					if (ship.info_ally.mana > ship.GetMaxMana()) ship.info_ally.mana = ship.GetMaxMana();
					bulletDmg = (*bulletItr).dmg;
					bulletItr = bullets.erase(bulletItr);
					checkCollitionByBullet = true;
				}
				
				else
				bulletItr++;
			}
			if (ultimateOn)
			{
				Skill tempskill = *skills.begin();
				Skill tempskill2 = *(skills.begin()+1);
				Collider laserHit = tempskill.GetCollider();
				Collider laserHit2 = tempskill2.GetCollider();
				if (tempEnemy.GetCollider().CheckCollision(laserHit)|| tempEnemy.GetCollider().CheckCollision(laserHit2))
				{
						score += 100;
						ship.info_ally.mana += 35;
						if (ship.info_ally.mana > ship.GetMaxMana()) ship.info_ally.mana = ship.GetMaxMana();
						laserDmg = (*skills.begin()).dmg;
						checkCollitionByLaser = true;
				}
			}
			if (checkCollitionByBullet|| checkCollitionByLaser)
			{
				if (checkCollitionByBullet) (*enemyItr).info_enemy.health -= bulletDmg;
				if (checkCollitionByLaser) (*enemyItr).info_enemy.health -= laserDmg;
				if ((*enemyItr).info_enemy.health <= 0)
				{
					Vector2f tempPosition = tempEnemy.GetPosition();
					Vector2f tempSize = tempEnemy.GetSize();
					Eliminate dead(&enemyDestroyed, Vector2u(5, 1), 0.15f, Vector2f(tempPosition.x, tempPosition.y));
					//cout << tempEnemy.GetSize().x << " Six:Siy " << tempEnemy.GetSize().y<< tempEnemy.GetPosition().x << " Pox:Poy " << tempEnemy.GetPosition().y<<endl;
					players.push_back(dead);
					enemyItr = enemys.erase(enemyItr);
				}
			}
			else enemyItr++; 
			bulletItr = bullets.begin();
		}
		/// checkshipcollition
		vector<EnemyBullet>::iterator enemyBulletItr = enemybullets.begin();
		
		while (enemyBulletItr != enemybullets.end())
		{
			float bulletDmg;
			bool checkCollitionByBullet = false;
			EnemyBullet tempBullet = *enemyBulletItr;
				
				
			Collider bulletHit = tempBullet.GetCollider();
			if (ship.GetCollider().CheckCollision(bulletHit))
			{
				bulletDmg = (*enemyBulletItr).dmg;
				enemyBulletItr = enemybullets.erase(enemyBulletItr);
				checkCollitionByBullet = true;
			}
				
				else
					enemyBulletItr++;
			if (checkCollitionByBullet)
			{
				ship.info_ally.health -= bulletDmg;
				if (ship.info_ally.health <= 0)
				{
					Vector2f tempPosition = ship.GetPosition();
					Vector2f tempSize = ship.GetSize();
					Eliminate dead(&shipDestroyed, Vector2u(5, 1), 0.15f, Vector2f(tempPosition.x, tempPosition.y));
					//cout << tempEnemy.GetSize().x << " Six:Siy " << tempEnemy.GetSize().y<< tempEnemy.GetPosition().x << " Pox:Poy " << tempEnemy.GetPosition().y<<endl;
					players.push_back(dead);
				}
			}
		}
		vector<Enemy>::iterator enemysItr = enemys.begin();
		while (enemysItr != enemys.end())
		{
			float bodyDmg;
			bool checkCollitionByBody = false;
			Enemy tempBullet = *enemysItr;


			Collider bulletHit = tempBullet.GetCollider();
			if (ship.GetCollider().CheckCollision(bulletHit))
			{
				bodyDmg = (*enemysItr).dmg;
				Vector2f tempPosition = ship.GetPosition();
				Vector2f tempSize = ship.GetSize();
				Eliminate dead(&enemyDestroyed, Vector2u(5, 1), 0.15f, Vector2f(tempPosition.x, tempPosition.y));
				//cout << tempEnemy.GetSize().x << " Six:Siy " << tempEnemy.GetSize().y<< tempEnemy.GetPosition().x << " Pox:Poy " << tempEnemy.GetPosition().y<<endl;
				players.push_back(dead);
				enemysItr = enemys.erase(enemysItr);
				checkCollitionByBody = true;
			}
			//set snemy dead by smash ship
			else
				enemysItr++;
			if (checkCollitionByBody)
			{
				ship.info_ally.health -= bodyDmg;
				if (ship.info_ally.health <= 0)
				{
					Vector2f tempPosition = ship.GetPosition();
					Vector2f tempSize = ship.GetSize();
					Eliminate dead(&shipDestroyed, Vector2u(5, 1), 0.15f, Vector2f(tempPosition.x, tempPosition.y));
					//cout << tempEnemy.GetSize().x << " Six:Siy " << tempEnemy.GetSize().y<< tempEnemy.GetPosition().x << " Pox:Poy " << tempEnemy.GetPosition().y<<endl;
					players.push_back(dead);
				}
			}
		}

		//text 
		sf::Text health_text, mana_text,cd,skillCost;
		health_text.setString(str(ship.GetHealth())+"/" + str(ship.GetMaxHealth()));
		mana_text.setString(str(ship.GetMana()) + "/" + str(ship.GetMaxMana()));
		cd.setString(str(cooldown_Ultimate));
		skillCost.setString("500");
		health_text.setFont(font);
		mana_text.setFont(font);
		cd.setFont(font);
		skillCost.setFont(font);
		health_text.setCharacterSize(9);
		mana_text.setCharacterSize(9);
		cd.setCharacterSize(20);
		skillCost.setCharacterSize(10);
		health_text.setPosition(60.0f, 217.0f);
		mana_text.setPosition(60.0f, 231.0f);
		cd.setPosition(127.0f, 170.0f);
		skillCost.setPosition(140.0f, 190.0f);
		health_text.setFillColor(Color::White);
		mana_text.setFillColor(Color::White);
		cd.setFillColor(Color::White);
		//update
		Collider tempShip = (*platforms.begin()).GetCollider();
		if (!ship.GetCollider().CheckCollision(tempShip))
		{
			ship.Update(time);
		}
		else
		{
			ship.velocity.y -= ship.speed;
			ship.body.move(ship.velocity* time);
		}
		for (Bullet& Bullets : bullets) Bullets.Update(time);
		for (Enemy& Enemys : enemys)Enemys.Update(time);
		for (Skill& Skills : skills)Skills.Update(time);
		for (EnemyBullet& Enemybullets : enemybullets)Enemybullets.Update(time);
		for (Eliminate& Videoplayers : players) Videoplayers.Update(time);
		//vector<Eliminate>::iterator playerItr = players.begin();
		vector<Eliminate>::iterator playerItr = players.begin();
		while (playerItr != players.end())
		{
			Eliminate temp = *playerItr;
			temp.Update(time);
			if (temp.getValue())
			{
				playerItr=players.erase(playerItr);
			}
			
			else playerItr++;
		}
		if (cooldown_Ultimate > 0)
		{
			if (count_Ultimate > 1000)
			{
				cooldown_Ultimate -= 1;
				Cooldown.restart();
			}
		}
		else cooldown_Ultimate = 0;
		//display
		window.clear();
		window.setView(view);
		
		
		ship.Draw(window);
		for (Bullet& Bullets : bullets) Bullets.Draw(window);
		for (Enemy& Enemys : enemys) Enemys.Draw(window);
		for (Skill& Skills : skills)Skills.Draw(window);
		for (Eliminate& Videoplayers : players)
		{
			Videoplayers.Draw(window);
		}
		for (EnemyBullet & Enemybullets : enemybullets)Enemybullets.Draw(window);
		for (Platform& Platforms : interface_ShipSkill) Platforms.Draw(window);
		(*platforms.begin()).Draw(window);
		for (Platform& Platforms :interface_ShipHealth) Platforms.Draw(window);
		for (Platform& Platforms : interface_ShipMana) Platforms.Draw(window);
		
		cout << count_Ultimate<<endl;
		window.draw(health_text);
		window.draw(mana_text);
		if(cooldown_Ultimate>0) window.draw(cd);
		window.draw(skillCost);
		window.display();
	}
	return 0;
}