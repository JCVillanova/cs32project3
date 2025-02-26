// Copyright (c) 2025 Joshua Villanova

#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "Actor.h"
#include "GameWorld.h"
#include "Level.h"
#include <list>
#include <string>
#include <vector>

// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class StudentWorld : public GameWorld {
 public:
  explicit StudentWorld(std::string assetPath);
  ~StudentWorld();
  virtual int init();
  virtual int move();
  virtual void cleanUp();
  bool noActors(int x, int y) const;
  std::list<Actor*>::iterator createIterator(int x, int y);
  void addActor(Actor* a, int x, int y);
  void removeActor(std::list<Actor*>::iterator it, int x, int y);
  std::list<Actor*> getActorsInCell(int x, int y) const;
 private:
  std::vector<std::vector<std::list<Actor*>>> actorList;
};

#endif  // STUDENTWORLD_H_
