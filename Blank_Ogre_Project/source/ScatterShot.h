#pragma once
#include <OGRE/OgreSceneNode.h>
#include <OGRE/OgreSceneManager.h>
#include "GameObject.h"

class ScatterShot
{
public:
	ScatterShot(void);
	~ScatterShot(void);
	Ogre::SceneNode& getNode();

	void move();
	void collide();
	void explode();

private:
	
	int countdown;
	float accel_Rate; 
	void update(void);


};

