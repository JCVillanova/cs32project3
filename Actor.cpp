#include "Actor.h"
#include "GameConstants.h"
#include "Level.h"
#include "StudentWorld.h"

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp

Actor::Actor(int img, int x, int y, StudentWorld* world = nullptr) : GraphObject(img, x, y), m_world(world) {}

StudentWorld* Actor::getWorld() const
{
	return m_world;
}

Player::Player(int x, int y, StudentWorld* world) : Actor(IID_PLAYER, x, y, world) {}

int Player::getActorType() const { return IID_PLAYER; }

void Player::doSomething()
{
	bool collided = false;
	if(getWorld()->getKey(key))
	{
		switch(key)
		{
			case KEY_PRESS_LEFT:
				{
					setDirection(left);

					list<Actor*> cellList = getWorld()->getActorsInCell(getX() - 1, getY());
					for(auto i : cellList)
					{
						if(i->getActorType() == IID_FLOOR)
						{
							collided = true;
							break;
						}
					}

					if(collided)
					{
						collided = false;
						break;
					}
					moveTo(getX() - 1, getY());
					break;
				}
			case KEY_PRESS_RIGHT:
				{
					setDirection(right);

					list<Actor*> cellList = getWorld()->getActorsInCell(getX() + 1, getY());
					for(auto i : cellList)
					{
						if(i->getActorType() == IID_FLOOR)
						{
							collided = true;
							break;
						}
					}

					if(collided)
					{
						collided = false;
						break;
					}
					moveTo(getX() + 1, getY());
					break;
				}
			default:
				{
					break;
				}
		}
	}
}

Floor::Floor(int x, int y) : Actor(IID_FLOOR, x, y) {}

int Floor::getActorType() const { return IID_FLOOR; }

void Floor::doSomething()
{
	return;
}
