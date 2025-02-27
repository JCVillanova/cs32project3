// Copyright (c) 2025 Joshua Villanova

#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"

// Students: Add code to this file, Actor.cpp, StudentWorld.h, and
// StudentWorld.cpp

class StudentWorld;

class Actor : public GraphObject {
 public:
  Actor(int img, int x, int y, StudentWorld* world);
  virtual int getActorType() const = 0;
  virtual void doSomething() = 0;
  virtual bool canMoveTo(int x, int y, int directionTried) { return false; }
  virtual bool onLadder() { return false; }
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
  virtual int getActorType() const;
  virtual void doSomething();
  virtual bool canMoveTo(int x, int y, int directionTried);
  virtual bool onLadder() const;
 private:
  int m_jumpTick = 0, m_key = 0;
  bool m_jumping;
};

class Floor : public Actor {
 public:
  Floor(int x, int y);
  virtual int getActorType() const;
  virtual void doSomething();
 private:
};

class Ladder : public Actor {
 public:
  Ladder(int x, int y);
  virtual int getActorType() const;
  virtual void doSomething();
 private:
};

#endif  // ACTOR_H_
