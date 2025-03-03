// Copyright (c) 2025 Joshua Villanova

#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include <string>

// Students: Add code to this file, Actor.cpp, StudentWorld.h, and
// StudentWorld.cpp

class StudentWorld;

class Actor : public GraphObject {
 public:
  Actor(int img, int x, int y, StudentWorld* world);
  virtual void doSomething() = 0;
  virtual void getAttacked() = 0;
  virtual bool canMoveTo(int x, int y, int directionTried) { return false; }
  virtual bool canBeMovedThrough() = 0;
  virtual bool onLadder(int x, int y) { return false; }
  virtual bool climbable() = 0;
  virtual bool bonfireable() = 0;
  virtual bool killsPlayerOnContact() = 0;
  StudentWorld* getWorld() const;
  bool isAlive() const;
  void setAlive(bool b);
 private:
  StudentWorld* m_world;
  bool m_alive;
};

class Player : public Actor {
 public:
  Player(int x, int y, StudentWorld* world);
  virtual void doSomething();
  virtual void getAttacked() { setAlive(false); }
  virtual bool canMoveTo(int x, int y, int directionTried);
  virtual bool canBeMovedThrough() { return true; }
  virtual bool onLadder(int x, int y) const;
  virtual bool climbable() { return false; }
  virtual bool bonfireable() { return true; }
  virtual bool killsPlayerOnContact() { return false; }
 private:
  int m_jumpTick = 0, m_key = 0;
  bool m_jumping;
};

class Floor : public Actor {
 public:
  Floor(int x, int y);
  virtual void doSomething();
  virtual void getAttacked() { return; }
  virtual bool canBeMovedThrough() { return false; }
  virtual bool climbable() { return false; }
  virtual bool bonfireable() { return false; }
  virtual bool killsPlayerOnContact() { return false; }
 private:
};

class Ladder : public Actor {
 public:
  Ladder(int x, int y);
  virtual void doSomething();
  virtual void getAttacked() { return; }
  virtual bool canBeMovedThrough() { return true; }
  virtual bool climbable() { return true; }
  virtual bool bonfireable() { return false; }
  virtual bool killsPlayerOnContact() { return false; }
 private:
};

class Bonfire : public Actor {
 public:
  Bonfire(int x, int y, StudentWorld* world);
  virtual void doSomething();
  virtual void getAttacked() { return; }
  virtual bool canBeMovedThrough() { return true; }
  virtual bool climbable() { return false; }
  virtual bool bonfireable() { return false; }
  virtual bool killsPlayerOnContact() { return true; }
 private:
};

#endif  // ACTOR_H_
