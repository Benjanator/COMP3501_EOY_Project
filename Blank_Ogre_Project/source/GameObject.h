#pragma once

#include "OGRE\OgreSceneNode.h"

class GameObject
{
public:
	enum objectType{empty = -1,
					smallAlly_fighter = 0, 
					smallEnemy_fighter, 
					smallAlly_bomber = 10, 
					smallEnemy_bomber, 
					largeEnemy_cmd = 20, 
					largeAlly_cmd, 
					asteroid = 100,
					platform};

	GameObject(objectType);
	~GameObject(void);
	virtual void update() = 0;
	virtual Ogre::SceneNode& getNode() = 0;

	Ogre::Vector3 getMotionDirection();
	bool isIndestructable();
	int getTeam();
	void setTeam(int);

	Ogre::Vector3 getAABBCenter();
	Ogre::Vector3 getAABBSize();

protected:
	Ogre::SceneNode* m_pNode;

	objectType type;
	int team;

	bool indestructable;
	Ogre::Vector3 drift_Direction;

	Ogre::Vector3 aabbCenter;
	Ogre::Vector3 aabbSize;
};

