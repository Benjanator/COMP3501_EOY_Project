#pragma once
#include "GameObject.h"
#include <OGRE/OgreSceneNode.h>


class Fighter: public GameObject
{
public:
	Fighter(Ogre::SceneNode*);
	~Fighter(void);

	Ogre::SceneNode& getNode();

	void update(void);

	protected:
	void move();
};

