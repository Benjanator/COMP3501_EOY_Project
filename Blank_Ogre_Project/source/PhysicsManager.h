#pragma once

#include "ObjectManager.h"
#include "GameObjectFactory.h"
#include "GameObject.h"

using namespace Ogre;
class PhysicsManager
{
public:
	PhysicsManager(ObjectManager*);
	~PhysicsManager(void);

	void pollTotalEvents(float);
	void pollAiShots(GameObjectFactory *,ObjectManager* );
private:
	bool testcollidableDistance(GameObject* _focus, GameObject* _collidie);
	void elasticCollision(GameObject* _focus, GameObject* _collidie);
	

	ObjectManager* objectManager;
};

