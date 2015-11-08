#pragma once

#include "ObjectManager.h"

using namespace Ogre;
class PhysicsManager
{
public:
	PhysicsManager(ObjectManager*);
	~PhysicsManager(void);

	void pollTotalEvents();

private:
	bool testcollidableDistance(SceneNode& _focus, SceneNode& _collidie);



	ObjectManager* objectManager;
};

