// Copyright (c) 2025 Joshua Villanova

#include "Actor.h"
#include "GameConstants.h"
#include "StudentWorld.h"
#include <list>

// Students: Add code to this file, Actor.h, StudentWorld.h, and
// StudentWorld.cpp

Actor::Actor(int img, int x, int y, StudentWorld *world = nullptr)
  : GraphObject(img, x, y), m_world(world), m_alive(true) {}

StudentWorld *Actor::getWorld() const { return m_world; }

bool Actor::isAlive() const { return m_alive; }

void Actor::setAlive(bool b) { m_alive = b; }

Player::Player(int x, int y, StudentWorld *world)
  : Actor(IID_PLAYER, x, y, world) {}

int Player::getActorType() const { return IID_PLAYER; }

void Player::doSomething() {
  if (!isAlive()) return;  // Return if player is dead

  bool collided = false;
  if (getWorld()->getKey(key)) {
    switch (key) {
    case KEY_PRESS_LEFT: {
      setDirection(left);

      std::list<Actor *> cellList = getWorld()->getActorsInCell(getX() - 1,
                                                                getY());
      for (auto i : cellList) {
        if (i->getActorType() == IID_FLOOR) {
          collided = true;
          break;
        }
      }

      if (collided) {
        collided = false;
        break;
      }
      moveTo(getX() - 1, getY());
      break;
    }
    case KEY_PRESS_RIGHT: {
      setDirection(right);

      std::list<Actor *> cellList = getWorld()->getActorsInCell(getX() + 1,
                                                                getY());
      for (auto i : cellList) {
        if (i->getActorType() == IID_FLOOR) {
          collided = true;
          break;
        }
      }

      if (collided) {
        collided = false;
        break;
      }
      moveTo(getX() + 1, getY());
      break;
    }
    default: {
      break;
    }
    }
  }
}

Floor::Floor(int x, int y) : Actor(IID_FLOOR, x, y) {}

int Floor::getActorType() const { return IID_FLOOR; }

void Floor::doSomething() { return; }
