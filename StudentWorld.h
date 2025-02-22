#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "Actor.h"
#include "GameWorld.h"
#include "Level.h"
#include <list>
#include <string>
#include <vector>
using namespace std;

// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class StudentWorld : public GameWorld
{
public:
	StudentWorld(string assetPath);
	~StudentWorld();
	virtual int init();
	virtual int move();
	virtual void cleanUp();
	bool noActors(int x, int y) const;
	list<Actor*>::iterator createIterator(int x, int y);
	void addActor(Actor* a, int x, int y);
	void removeActor(list<Actor*>::iterator it, int x, int y);
	list<Actor*> getActorsInCell(int x, int y) const;
private:
	vector<vector<list<Actor*>>> actorList;
};

#endif // STUDENTWORLD_H_
