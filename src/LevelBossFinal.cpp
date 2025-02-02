#include "LevelBossFinal.hpp" // level header file
#include "Boss.hpp"
#include "CustomText.hpp"
#include "GameUI.hpp"
#include "Puzzle.hpp"
#include "Success.hpp"
using namespace std;
using namespace sf;

void LevelBossFinal::Show(RenderWindow& window, Event& event)
{
	while (LevelHelper::shouldKeepPlaying())
	{
		Puzzle puzzle;
		// puzzle.make(3, 4, 5, 4, 7, 7, 60);
		puzzle.makeRandom(35);

		////// mandatory //////
		cout << "in level 1 " << endl;
		Success success;
		LevelFailed levelFailedObj;
		LevelHelper levelhelp;
		GameUI::init();
		Helper::resetEnemyDiedCounter();
		Player::resetMissileCounter();
		Background background;
		Player yuri;

		////// mandatory //////

		CustomText custext1;
		CustomText custext2;
		CustomText custext3;

		Boss boss;

		Music music;
		music.openFromFile("res/music/boss.wav");
		music.setVolume(80);
		music.play();

		boss.setStyle(Boss::Style::ShakaLala);
		boss.enemySprite.setScale(0.6, 0.6);
		boss.bulletDamage = 12;
		boss.missileDamage = 18;

		boss.healthValue = 750;
		bool inversed = false;
		float puzzleHealth = 90;
		float inverseHealth = 70;

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
					GameUI::handleClose(window, window.mapPixelToCoords(Mouse::getPosition(window)));
					success.handleClose(window.mapPixelToCoords(Mouse::getPosition(window)));
					levelFailedObj.handleClose(window.mapPixelToCoords(Mouse::getPosition(window)));
				}
			}

			window.clear(Color::Blue);
			background.Show(window);
			yuri.fireBullet();
			if (Mouse::isButtonPressed(Mouse::Right))
			{
				yuri.fireMissile();
			}

			if (!inversed)
			{
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
			}
			else
			{
				if (Keyboard::isKeyPressed(Keyboard::D))
				{
					yuri.moveLeft();
				}
				if (Keyboard::isKeyPressed(Keyboard::A))
				{
					yuri.moveRight();
				}
				if (Keyboard::isKeyPressed(Keyboard::S))
				{
					yuri.moveUp();
				}
				if (Keyboard::isKeyPressed(Keyboard::W))
				{
					yuri.moveDown();
				}
			}

			custext1.Show(window, "Caution: MSHPGX7C approaching", 80, 200, 200, 2, true, 0.1);

			if (custext1.hidingFinished)
			{
				boss.move(400);
			}
			boss.missileCount = 10;
			boss.fireBullet(yuri, 1000, 900, 800);
			boss.fireMissile(yuri, 1000, 900, 780);

			levelhelp.isHitBody(yuri, boss);
			levelhelp.isHitBullet(yuri, boss);
			levelhelp.isHitMissile(yuri, boss);
			boss.Show(window);
			if (puzzleHealth > yuri.healthValue && yuri.isDead == false)
			{
				if (custext2.hidingFinished)
				{
					if (puzzle.getState() == Puzzle::Nothing && Helper::enemiesDied() < 1)
					{
						puzzle.Show(window, event);
					}
					if (inverseHealth > yuri.healthValue && custext2.hidingFinished)
					{
						cout << "inverse: " << yuri.healthValue << endl;
						custext3.Show(window, "Malfunction: Movement controls inversed.", 40, 20, 120, -1, true, 0.01);
						if (custext3.fullShowed)
						{
							inversed = true;
						}
					}
				}
				else
				{
					custext2.Show(window, "ZenMeter failed to calibrate. You need to calibrate manually.", 40, 20, 120, 4, true, 0.01);
				}
			}

			yuri.Show(window);

			// cout << "state: " << success.getState() << endl;
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
