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
: Actor(IID_PLAYER, x, y, world), m_jumping(false) {}

int Player::getActorType() const { return IID_PLAYER; }

void Player::doSomething() {
  if (!isAlive()) return;  // Return if player is dead

  // Jump if player is jumping
  if (m_jumping) {
    // NOTE: Must terminate jump sequence if a ladder is hit (once implemented)
    // Also must check for player freezes and death (maybe make a function to
    // check these)
    int dirMove = getDirection() == left ? -1 : 1;  // Create jump direction
                                                    // based on current
                                                    // direction faced
    switch (m_jumpTick) {
      case 1:
      case 2:
      case 3:
        if (canMoveTo(getX()+dirMove, getY())) {
          moveTo(getX()+dirMove, getY());
          ++m_jumpTick;
        } else {
          m_jumpTick = 0;
          m_jumping = false;
        }
        break;
      case 4:
        if (canMoveTo(getX(), getY()-1)) {
          moveTo(getX(), getY()-1);
        }
        m_jumpTick = 0;
        m_jumping = false;
        break;
      default:
        m_jumping = false;
        break;
    }
    return;
  }

  // NOTE: Must do some action for when the player is frozen

  // Fall if player has no ground beneath them
  // NOTE: Must check for ladder beneath (once implemented)
  if (canMoveTo(getX(), getY()-1)) {
    moveTo(getX(), getY()-1);
    return;
  }

  if (getWorld()->getKey(m_key)) {
    switch (m_key) {
      case KEY_PRESS_LEFT: {
        setDirection(left);

        if (canMoveTo(getX()-1, getY())) moveTo(getX()-1, getY());
        break;
      }
      case KEY_PRESS_RIGHT: {
        setDirection(right);
        if (canMoveTo(getX()+1, getY())) {
          // NOTE: This functionality might be broken, you will find out when
          // doing collisions with moving objects

          // Remove the actor from its previous position
          std::list<Actor *> prevList = getWorld()->getActorsInCell(getX(),
                                                                    getY());

          std::list<Actor *> cellList = getWorld()->getActorsInCell(getX()+1,
                                                                    getY());
          for (auto i = prevList.begin(); i != prevList.end(); ++i) {
            if ((*i)->getActorType() == IID_PLAYER) {
              getWorld()->removeActor(i, getX(), getY());
              break;
            }
          }

          // Add the actor back at its new position
          cellList.push_back(this);
          moveTo(getX()+1, getY());
        }
        break;
      }
      case KEY_PRESS_SPACE: {
        if (!m_jumping && canMoveTo(getX(), getY()+1)) {
          m_jumping = true;
          moveTo(getX(), getY()+1);  // First jump tick
          ++m_jumpTick;
        }
        break;
      }
      default: {
        break;
      }
    }
  }
}

bool Player::canMoveTo(int x, int y) {
  bool collided = false;
  std::list<Actor *> cellList = getWorld()->getActorsInCell(x, y);
  for (auto i : cellList) {
    if (i->getActorType() == IID_FLOOR) {
      collided = true;
      break;
    }
  }
  return !collided;
}

Floor::Floor(int x, int y) : Actor(IID_FLOOR, x, y) {}

int Floor::getActorType() const { return IID_FLOOR; }

void Floor::doSomething() { return; }

bool Floor::canMoveTo(int x, int y) { return false; }
