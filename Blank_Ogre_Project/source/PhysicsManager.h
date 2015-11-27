#pragma once

#include "ObjectManager.h"

using namespace Ogre;
class PhysicsManager
{
public:
	PhysicsManager(ObjectManager*);
	~PhysicsManager(void);

	void pollTotalEvents(float);

private:
	bool testcollidableDistance(GameObject* _focus, GameObject* _collidie);
	void elasticCollision(GameObject* _focus, GameObject* _collidie);


	ObjectManager* objectManager;
};

