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
        // Grab if on a ladder, stopping jump
        if (onLadder()) {
          m_jumpTick = 0;
          m_jumping = false;
          break;
        }

        // Execute next jump tick
        if (canMoveTo(getX()+dirMove, getY(), KEY_PRESS_SPACE)) {
          moveTo(getX()+dirMove, getY());
          ++m_jumpTick;
        } else {
          m_jumpTick = 0;
          m_jumping = false;
        }
        break;
      case 4:
        // Grab if on a ladder, stopping jump
        if (onLadder()) {
          m_jumpTick = 0;
          m_jumping = false;
          break;
        }

        // Execute last jump tick
        if (canMoveTo(getX(), getY()-1, KEY_PRESS_SPACE)) {
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
  if (canMoveTo(getX(), getY()-1, 1004)) {
    moveTo(getX(), getY()-1);
    return;
  }

  if (getWorld()->getKey(m_key)) {
    switch (m_key) {
      case KEY_PRESS_LEFT: {
        // Switch direction if needed, don't move
        if (getDirection() == right) {
          setDirection(left);
          break;
        }

        // Move if possible
        if (canMoveTo(getX()-1, getY(), KEY_PRESS_LEFT))
          moveTo(getX()-1, getY());
        break;
      }
      case KEY_PRESS_RIGHT: {
        // Switch direction if needed, don't move
        if (getDirection() == left) {
          setDirection(right);
          break;
        }

        // Move if possible
        if (canMoveTo(getX()+1, getY(), KEY_PRESS_RIGHT)) {
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
      case KEY_PRESS_UP: {
        if (canMoveTo(getX(), getY()+1, KEY_PRESS_UP))
          moveTo(getX(), getY()+1);
        break;
      }
      case KEY_PRESS_DOWN: {
        if (canMoveTo(getX(), getY()-1, KEY_PRESS_DOWN))
          moveTo(getX(), getY()-1);
        break;
      }
      case KEY_PRESS_SPACE: {
        if (!m_jumping && canMoveTo(getX(), getY()+1, KEY_PRESS_SPACE)) {
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

bool Player::canMoveTo(int x, int y, int directionTried) {
  if (y >= VIEW_WIDTH) return false;  // Can't go out of bounds

  std::list<Actor *> cellList = getWorld()->getActorsInCell(x, y);
  for (auto i : cellList) {
    if (i->getActorType() == IID_FLOOR) {  // Can't move through floors
      return false;
      break;
    }
  }

  // Check for ladders (going up)
  cellList = getWorld()->getActorsInCell(x, y-1);
  if (directionTried == KEY_PRESS_UP) {
    if (cellList.empty()) return false;  // Can't move up while in open air
    for (auto i : cellList) {
      // Also can't move up when not on a ladder
      if (i->getActorType() != IID_LADDER) return false;
    }
  }

  // Check for ladders (going down), or for letting go of a ladder from bottom
  cellList = getWorld()->getActorsInCell(x, y);
  if (directionTried == KEY_PRESS_DOWN) {
    for (auto i : cellList) {
      // Also can't move down when not on a ladder
      if (i->getActorType() != IID_LADDER) {
        cellList = getWorld()->getActorsInCell(x, y+1);
        for (auto i : cellList) {
          // Allow letting go of ladder
          if (i->getActorType() != IID_LADDER) return false;
        }
      }
    }
  }

  cellList = getWorld()->getActorsInCell(x, y);
  // There is no keybind for falling, so we use 1004
  if (directionTried == 1004) {
    for (auto i : cellList) {
      // Player can't fall when above a ladder
      if (i->getActorType() == IID_LADDER) return false;
    }
    cellList = getWorld()->getActorsInCell(x, y+1);
    for (auto i : cellList) {
      // Player can't fall when on a ladder
      if (i->getActorType() == IID_LADDER) return false;
    }
  }
  return true;
}

bool Player::onLadder() const {
  std::list<Actor *> cellList = getWorld()->getActorsInCell(getX(), getY());
  for (auto i : cellList) {
    if (i->getActorType() == IID_LADDER) return true;
  }
  return false;
}

Floor::Floor(int x, int y) : Actor(IID_FLOOR, x, y) {}

int Floor::getActorType() const { return IID_FLOOR; }

void Floor::doSomething() { return; }

Ladder::Ladder(int x, int y) : Actor(IID_LADDER, x, y) {}

int Ladder::getActorType() const { return IID_LADDER; }

void Ladder::doSomething() { return; }
