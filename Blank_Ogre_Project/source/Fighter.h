#pragma once
#include "GameObject.h"
#include <OGRE/OgreSceneNode.h>


class Fighter: public GameObject
{
public:
	Fighter(Ogre::SceneNode*);
	~Fighter(void);

	Ogre::SceneNode& getNode();

	void update(float _timer);
	void collide();
	void collide(int);

	protected:
	void move();

private:
	int health;
};

