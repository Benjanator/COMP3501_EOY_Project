#pragma once
#include "GameObject.h"
#include <OGRE/OgreSceneNode.h>



class Carrier: public GameObject
{
public:
	Carrier(Ogre::SceneNode*);
	~Carrier(void);

	Ogre::SceneNode& getNode();

	void update(float _timer);
	void collide();
	void collide(int);
	void shoot(	GameObjectFactory* ,ObjectManager*, GameObject* player);

	protected:
	void move();

	void turn_right(Ogre::Degree);
	void turn_left(Ogre::Degree);

	float degree;
	Ogre::Vector3 velocity;

private:
	int health;
	bool hasExploded;
	float personalTimer;
};

