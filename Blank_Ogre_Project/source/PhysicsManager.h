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
<<<<<<< HEAD
	void pollAiShots(GameObjectFactory *,ObjectManager* );
=======
	void pollAiShots(GameObjectFactory * );
	bool spawnNextWave();

>>>>>>> 44bb272a9008709b22b268255caf9e61d3c31ec6
private:
	bool testcollidableDistance(GameObject* _focus, GameObject* _collidie);
	void elasticCollision(GameObject* _focus, GameObject* _collidie);
	
	ObjectManager* objectManager;
	bool waveClear;
};

