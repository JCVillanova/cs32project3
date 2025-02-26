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
  StudentWorld* getWorld() const;
 private:
  StudentWorld* m_world;
};

class Player : public Actor {
 public:
  Player(int x, int y, StudentWorld* world);
  virtual int getActorType() const;
  virtual void doSomething();
 private:
  int key = 0;
};

class Floor : public Actor {
 public:
  Floor(int x, int y);
  virtual int getActorType() const;
  virtual void doSomething();
 private:
};

#endif  // ACTOR_H_
