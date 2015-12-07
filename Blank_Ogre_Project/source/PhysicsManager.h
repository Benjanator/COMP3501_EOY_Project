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

	void pollTotalEvents(float,ObjectManager* );

	void pollAiShots(GameObjectFactory *,ObjectManager* );
	bool spawnNextWave();


private:
	bool testcollidableDistance(GameObject* _focus, GameObject* _collidie);
	void elasticCollision(GameObject* _focus, GameObject* _collidie);
	
	ObjectManager* objectManager;
	bool waveClear;
};

