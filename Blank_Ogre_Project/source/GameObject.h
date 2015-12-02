#pragma once

#include "OGRE\OgreSceneNode.h"
#include <OgreMaterialManager.h>
#include "OGRE/OgreRoot.h"
#include "OGRE/OgreEntity.h"

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
					platform,
					rocket,
					laser,
					scattershot};

	GameObject(objectType);
	~GameObject(void);

	int numMaterials;

	virtual void update(float) = 0;
	virtual void collide() = 0;
	virtual void collide(int) = 0;
	Ogre::SceneNode& getNode();

	Ogre::Vector3 getMotionDirection();
	bool isIndestructable();
	bool isDead();
	int getTeam();
	void setTeam(int);
	objectType getType();

	Ogre::Vector3 getAABBCenter();
	Ogre::Vector3 getAABBSize();

protected:
	Ogre::SceneNode* m_pNode;

	objectType type;
	int team;

	bool indestructable;
	bool hasExploded;
	bool dead;
	Ogre::Vector3 drift_Direction;
	Ogre::Vector3 forward_Direction;

	Ogre::Vector3 aabbCenter;
	Ogre::Vector3 aabbSize;
};

