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
	void collide();
	void collide(int);
	void shoot(GameObjectFactory* ,ObjectManager *, GameObject* );

	protected:


	void move();

private:
	int health;
	bool hasExploded;
	float personalTimer;
};

