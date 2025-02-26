// Copyright (c) 2025 Joshua Villanova

#include "StudentWorld.h"
#include "GameConstants.h"
#include <list>
#include <string>
#include <vector>

GameWorld* createStudentWorld(std::string assetPath) {
  return new StudentWorld(assetPath);
}

// Students: Add code to this file, StudentWorld.h, Actor.h, and Actor.cpp

StudentWorld::StudentWorld(std::string assetPath)
  : GameWorld(assetPath), actorList(VIEW_WIDTH,
std::vector<std::list<Actor*>>(VIEW_HEIGHT)) {}

StudentWorld::~StudentWorld() {
  cleanUp();
}

int StudentWorld::init() {
  // Check level
  std::string currentLevel = "level0" + std::to_string(getLevel()) + ".txt";
  Level lev(assetPath());
  Level::LoadResult result = lev.loadLevel(currentLevel);
  if (result == Level::load_fail_file_not_found ||
  result == Level::load_fail_bad_format) {
    return GWSTATUS_LEVEL_ERROR;
  }

  // Initialize data structure for actors
  Level::MazeEntry item;
  for (int x = 0; x < VIEW_WIDTH; ++x) {
    for (int y = 0; y < VIEW_HEIGHT; ++y) {
      item = lev.getContentsOf(x, y);
      if (item == Level::player) {
        addActor(new Player(x, y, this), x, y);
      } else if (item == Level::floor) {
        addActor(new Floor(x, y), x, y);
      }
    }
  }

  return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move() {
  // This code is here merely to allow the game to build, run, and terminate
  // after you type q

  setGameStatText("Game will end when you type q");

  for (int x = 0; x < VIEW_WIDTH; ++x) {
    for (int y = 0; y < VIEW_HEIGHT; ++y) {
      for (auto actor : actorList[x][y]) {
        actor->doSomething();
      }
    }
  }

  return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::cleanUp() {
  for (int x = 0; x < VIEW_WIDTH; ++x) {
    for (int y = 0; y < VIEW_HEIGHT; ++y) {
      while (!noActors(x, y)) {
        removeActor(createIterator(x, y), x, y);
      }
    }
  }
}

bool StudentWorld::noActors(int x, int y) const {
  return actorList[x][y].empty();
}

std::list<Actor*>::iterator StudentWorld::createIterator(int x, int y) {
  return actorList[x][y].begin();
}

void StudentWorld::addActor(Actor* a, int x, int y) {
  actorList[x][y].push_back(a);
}

void StudentWorld::removeActor(std::list<Actor*>::iterator it, int x, int y) {
  delete *it;
  it = actorList[x][y].erase(it);
}

std::list<Actor*> StudentWorld::getActorsInCell(int x, int y) const {
  return actorList[x][y];
}
