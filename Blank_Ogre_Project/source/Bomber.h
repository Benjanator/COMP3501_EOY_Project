#pragma once
#include "GameObject.h"
#include <OGRE/OgreSceneNode.h>


class Bomber: public GameObject
{
public:
	Bomber(Ogre::SceneNode*);
	~Bomber(void);

	Ogre::SceneNode& getNode();

	void update(float _timer);

	protected:


	void move();
};

