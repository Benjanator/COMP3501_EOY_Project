#include "PhysicsManager.h"


PhysicsManager::PhysicsManager(ObjectManager* _manager)
{
	objectManager = _manager;
	waveClear = false;
}


PhysicsManager::~PhysicsManager(void)
{
	objectManager = 0;
}

void PhysicsManager::pollTotalEvents(float timer, ObjectManager* manager)
{
	std::vector<GameObject*> tempList = objectManager->getObjectList();
	int enemyCount = 0;

	for(unsigned int i = 0; i < tempList.size(); i++)
	{
		if(tempList.at(i)->getType() == GameObject::objectType::smallEnemy_fighter || tempList.at(i)->getType() == GameObject::objectType::smallEnemy_bomber)
		{
			enemyCount++;
		}
		if(tempList.at(i)->isDead())
		{
			objectManager->removeObject(tempList.at(i));
			continue;
		}
		for(unsigned int j = 0; j < tempList.size(); j++){
			bool collide = false;

			if(i != j){
				collide = testcollidableDistance(tempList.at(i), tempList.at(j));
			}

			if(collide){
				elasticCollision(tempList.at(i), tempList.at(j));
			}
			else{
				
			}
		}
		tempList.at(i)->update(timer,manager);
	}

	if(enemyCount == 0){
		waveClear = true;
	}
	else{
		waveClear = false;
	}
}

void PhysicsManager::pollAiShots(GameObjectFactory* factory,ObjectManager* manager){
	std::vector<GameObject*> tempList = objectManager->getObjectList();
	
	for(unsigned int i = 0; i < tempList.size(); i++)
	{
		
		tempList.at(i)->shoot(factory,manager, tempList.at(0));
	}

 }

bool PhysicsManager::spawnNextWave()
{
	return waveClear;
}

/*
 * Private Functions
 * 
 */


/*	
*	sphere test // not fully calibrated, i shall blame shields
*/
bool PhysicsManager::testcollidableDistance(GameObject* _focus, GameObject* _collidie)
{	
	static int i = 0;

	if(_focus->getType() == GameObject::objectType::rocket && _collidie->getType() == GameObject::objectType::rocket ||
		_focus->getType() == GameObject::objectType::laser && _collidie->getType() == GameObject::objectType::laser){
		return false;
	}
	if(_focus->getTeam() == _collidie->getTeam())
	{
	
		return false;
	}
	

	if( _focus->getAABBCenter().squaredDistance(_collidie->getAABBCenter()) < Math::Sqr((_focus->getAABBSize() * 0.5).length()) + Math::Sqr((_collidie->getAABBSize() * 0.5).length())){
		Vector3 box1_center = _focus->getAABBCenter();
		Vector3 box1_half = 0.5 * _focus->getAABBSize();

		Vector3 box2_center = _collidie->getAABBCenter();
		Vector3 box2_half = 0.5 * _collidie->getAABBSize();
		
		//box1
		float box1_minX = box1_center.x - box1_half.x;
		float box1_maxX = box1_center.x + box1_half.x;

		float box1_minY = box1_center.y - box1_half.y;
		float box1_maxY = box1_center.y + box1_half.y;

		float box1_minZ = box1_center.z - box1_half.z;
		float box1_maxZ = box1_center.z + box1_half.z;

		//box2
		float box2_minX = box2_center.x - box2_half.x;
		float box2_maxX = box2_center.x + box2_half.x;

		float box2_minY = box2_center.y - box2_half.y;
		float box2_maxY = box2_center.y + box2_half.y;

		float box2_minZ = box2_center.z - box2_half.z;
		float box2_maxZ = box2_center.z + box2_half.z;


		if(box1_maxX > box2_minX &&
			box1_minX < box2_maxX &&
			box1_maxY > box2_minY &&
			box1_minY < box2_maxY &&
			box1_maxZ > box2_minZ  &&
			box1_minZ < box2_maxZ){
				i++;
				return true;
		}
		//i++;
		//return true;
	}
	
	return false;
}

void PhysicsManager::elasticCollision(GameObject* _focus, GameObject* _collidie)
{
	Vector3 pos1 = _focus->getNode()._getDerivedPosition();
	Vector3 pos2 = _collidie->getNode()._getDerivedPosition();

	Vector3 vel1 = _focus->getMotionDirection();
	Vector3 vel2 = _collidie->getMotionDirection();

	Vector3 dif = pos1 - pos2;
	Vector3 half = pos1 - (0.5 * dif);



	vel1 = vel1.dotProduct(dif);

	
	

	if(_focus->getType() == GameObject::objectType::rocket && _collidie->getType() == GameObject::objectType::smallEnemy_fighter || _focus->getType() == GameObject::objectType::smallEnemy_fighter && _collidie->getType() == GameObject::objectType::rocket ||
		_focus->getType() == GameObject::objectType::rocket && _collidie->getType() == GameObject::objectType::smallEnemy_bomber || _focus->getType() == GameObject::objectType::smallEnemy_bomber && _collidie->getType() == GameObject::objectType::rocket ||
		_focus->getType() == GameObject::objectType::rocket && _collidie->getType() == GameObject::objectType::largeEnemy_cmd || _focus->getType() == GameObject::objectType::largeEnemy_cmd && _collidie->getType() == GameObject::objectType::rocket ||
		_focus->getType() == GameObject::objectType::rocket && _collidie->getType() == GameObject::objectType::smallAlly_fighter|| _focus->getType() == GameObject::objectType::smallAlly_fighter && _collidie->getType() == GameObject::objectType::rocket){
			_focus->collide(5);
			_collidie->collide(5);
			
	}else if(_focus->getType() == GameObject::objectType::laser && _collidie->getType() == GameObject::objectType::smallEnemy_fighter || _focus->getType() == GameObject::objectType::smallEnemy_fighter && _collidie->getType() == GameObject::objectType::laser ||
		_focus->getType() == GameObject::objectType::laser && _collidie->getType() == GameObject::objectType::smallEnemy_bomber || _focus->getType() == GameObject::objectType::smallEnemy_bomber && _collidie->getType() == GameObject::objectType::laser ||
		_focus->getType() == GameObject::objectType::laser && _collidie->getType() == GameObject::objectType::largeEnemy_cmd || _focus->getType() == GameObject::objectType::largeEnemy_cmd && _collidie->getType() == GameObject::objectType::laser ||
	   _focus->getType() == GameObject::objectType::laser && _collidie->getType() == GameObject::objectType::smallAlly_fighter|| _focus->getType() == GameObject::objectType::smallAlly_fighter && _collidie->getType() == GameObject::objectType::laser){
				_focus->collide(1);
				_collidie->collide(1);
				
	}else if(_focus->getType() == GameObject::objectType::scattershot && _collidie->getType() == GameObject::objectType::smallEnemy_fighter || _focus->getType() == GameObject::objectType::smallEnemy_fighter && _collidie->getType() == GameObject::objectType::scattershot ||
		_focus->getType() == GameObject::objectType::scattershot && _collidie->getType() == GameObject::objectType::smallEnemy_bomber || _focus->getType() == GameObject::objectType::smallEnemy_bomber && _collidie->getType() == GameObject::objectType::scattershot||
		_focus->getType() == GameObject::objectType::scattershot && _collidie->getType() == GameObject::objectType::largeEnemy_cmd|| _focus->getType() == GameObject::objectType::largeEnemy_cmd && _collidie->getType() == GameObject::objectType::scattershot ||
		_focus->getType() == GameObject::objectType::scattershot && _collidie->getType() == GameObject::objectType::smallAlly_fighter|| _focus->getType() == GameObject::objectType::smallAlly_fighter && _collidie->getType() == GameObject::objectType::scattershot){
				_focus->collide(2);
				_collidie->collide(2);
				
	}else{
		_focus->collide(50);
		_collidie->collide(50);
	}
}