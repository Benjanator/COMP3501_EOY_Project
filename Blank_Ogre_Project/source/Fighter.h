#pragma once
#include "GameObject.h"
#include <OGRE/OgreSceneNode.h>



class Fighter: public GameObject
{
public:
	Fighter(Ogre::SceneNode*);
	~Fighter(void);

	Ogre::SceneNode& getNode();

	void update(float _timer, ObjectManager*);
	void collide();
	void collide(int);
	void shoot(GameObjectFactory* ,ObjectManager*,GameObject*);

	protected:
	void move();

private:

	bool hasExploded;
	float personalTimer;
	
};

