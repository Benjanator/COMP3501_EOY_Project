#pragma once
#include "GameObject.h"
#include <OGRE/OgreSceneNode.h>


class Carrier: public GameObject
{
public:
	Carrier(Ogre::SceneNode*);
	~Carrier(void);

	Ogre::SceneNode& getNode();

	void update(void);

	protected:
	void move();
};

