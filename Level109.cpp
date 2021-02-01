#include "Level109.hpp" // level header file
#include "Puzzle.hpp"
using namespace std;
using namespace sf;

void Level109::Show(RenderWindow& window, Event& event)
{
	while (LevelHelper::shouldKeepPlaying())
	{
		Puzzle puzzle;

		puzzle.make(29, 0, 21, 30, 12, 11, 60);

		cout << "in level 109 " << endl;
		Success success;
		LevelFailed levelFailedObj;
		LevelHelper levelhelp;
		GameUI::init();
		Helper::resetEnemyDiedCounter();
		Player::resetMissileCounter();
		Background background;
		Player yuri;
		bool someone_is_alive;
		CustomText custext1;
		CustomText custext2;
		CustomText custext3;
		bool isHit = false;
		float playerHealth = 90;

		Enemy4 enemy; // create 2 enemies
		Music music;
		music.openFromFile("res/music/boss.wav");
		music.setVolume(20);
		music.play();

		enemy.setStyle(Enemy3::Style::RedRanger);
		enemy.enemySprite.setScale(1 * Helper::getWidthScalingFactor(), 1 * Helper::getWidthScalingFactor());
		enemy.bulletLeft.sprite.setScale(2 * Helper::getWidthScalingFactor(), 2 * Helper::getWidthScalingFactor());
		enemy.bulletRight.sprite.setScale(2 * Helper::getWidthScalingFactor(), 2 * Helper::getWidthScalingFactor());
		enemy.missile.sprite.setScale(2 * Helper::getWidthScalingFactor(), 2 * Helper::getWidthScalingFactor());
		enemy.bigExplosion.sprite.setScale(2 * Helper::getWidthScalingFactor(), 2 * Helper::getWidthScalingFactor());
		enemy.bulletDamage = 25;
		enemy.missileDamage = 40;
		enemy.healthValue = 700;

		while (window.isOpen())
		{
			Helper::resetClock();
			while (window.pollEvent(event))
			{
				if (event.type == Event::Closed)
				{
					window.close();
					exit(0);
				}
				else if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left)
				{
					yuri.startFiringBullet();
					GameUI::handleClose(window, Mouse::getPosition(window));
					success.handleClose(Mouse::getPosition(window));
					levelFailedObj.handleClose(Mouse::getPosition(window));
				}
			}
			window.clear(Color::Blue);
			background.Show(window);
			if (Mouse::isButtonPressed(Mouse::Right))
			{
				yuri.fireMissile();
			}
			yuri.fireBullet();
			if (Keyboard::isKeyPressed(Keyboard::A))
			{
				yuri.moveLeft();
			}
			if (Keyboard::isKeyPressed(Keyboard::D))
			{
				yuri.moveRight();
			}
			if (Keyboard::isKeyPressed(Keyboard::W))
			{
				yuri.moveUp();
			}
			if (Keyboard::isKeyPressed(Keyboard::S))
			{
				yuri.moveDown();
			}

			custext1.Show(window, "Caution: MIG10X approaching", 80, 200, 200, 2, true, 0.1);
			cout << "first " << endl;
			if (someone_is_alive == false)
				someone_is_alive = true;
			if (custext1.hidingFinished)
			{
				enemy.move(400);
			}
			enemy.fireBullet(yuri, 500, 400, 440);
			enemy.fireMissile(yuri, 500, 300, 400);
			levelhelp.isHitBody(yuri, enemy);
			levelhelp.isHitBullet(yuri, enemy);
			levelhelp.isHitMissile(yuri, enemy);
			enemy.Show(window);

			if (playerHealth > yuri.healthValue && isHit == false)
			{
				isHit = true;
			}

			if (isHit == true && custext2.hidingFinished == false)
			{
				custext2.Show(window, "ZenMeter failed to calibrate. You need to calibrate manually.", 40, 20, 120, 4, true, 0.01);
			}

			if (custext2.hidingFinished == true && puzzle.getState() == Puzzle::Nothing && yuri.isDead == false)
			{
				puzzle.Show(window, event);
			}

			yuri.Show(window);

			if (yuri.isDead || puzzle.getState() == Puzzle::Failed)
			{
				if (levelFailedObj.isFinishedShowing(window))
				{
					break;
				}
			}
			//            enemies[0].healthValue = 3;
			if (Helper::enemiesDied() == 1)
			{
				if (success.isFinishedShowing(window) == true)
				{
					return;
				}
			}
			GameUI::showPlayerUI(window);
			window.display();
		}
	}
}
