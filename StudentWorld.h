// Copyright (c) 2025 Joshua Villanova

#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "Actor.h"
#include "GameWorld.h"
#include "Level.h"
#include <list>
#include <string>
#include <vector>

// Students: Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class StudentWorld : public GameWorld {
 public:
  explicit StudentWorld(std::string assetPath);
  ~StudentWorld();
  virtual int init();
  virtual int move();
  virtual void cleanUp();
  bool noActors(int x, int y) const;
  std::vector<Actor*>::iterator createIterator(int x, int y);
  void addActor(Actor* a, int x, int y);
  void removeActor(std::vector<Actor*>::iterator it, int x, int y);
  std::vector<Actor*> getActorsInCell(int x, int y) const;

  bool checkIfCanBeMovedThrough(int x, int y) const;
  bool checkForLadder(int x, int y) const;
  bool cellEmpty(int x, int y) const { return actorList[x][y].empty(); }
  void incinerate(int x, int y);
 private:
  std::vector<std::vector<std::vector<Actor*>>> actorList;
};

#endif  // STUDENTWORLD_H_
