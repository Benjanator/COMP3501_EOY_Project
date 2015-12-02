#include "PhysicsManager.h"


PhysicsManager::PhysicsManager(ObjectManager* _manager)
{
	objectManager = _manager;
}


PhysicsManager::~PhysicsManager(void)
{
	objectManager = 0;
}

void PhysicsManager::pollTotalEvents(float timer)
{
	std::vector<GameObject*> tempList = objectManager->getObjectList();
	
	for(unsigned int i = 0; i < tempList.size(); i++)
	{
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
		tempList.at(i)->update(timer);
	}
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
		//std::cout << "collide" + std::to_string(i) << std::endl;
		i++;
		return true;
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

	//std::cout << "old:: " << dif << std::endl;

	vel1 = vel1.dotProduct(dif);

	//std::cout << "new:: " << vel1 << std::endl;

	
	std::cout << "focus:: " << _focus->getType() << std::endl;
	std::cout << "collide:: " << _collidie->getType()  << std::endl;
	

	if(_focus->getType() == GameObject::objectType::rocket && _collidie->getType() == GameObject::objectType::smallEnemy_fighter || _focus->getType() == GameObject::objectType::smallEnemy_fighter && _collidie->getType() == GameObject::objectType::rocket ||
		_focus->getType() == GameObject::objectType::rocket && _collidie->getType() == GameObject::objectType::smallEnemy_bomber || _focus->getType() == GameObject::objectType::smallEnemy_bomber && _collidie->getType() == GameObject::objectType::rocket ||
		_focus->getType() == GameObject::objectType::rocket && _collidie->getType() == GameObject::objectType::largeEnemy_cmd || _focus->getType() == GameObject::objectType::largeEnemy_cmd && _collidie->getType() == GameObject::objectType::rocket){
			_focus->collide(5);
			_collidie->collide(5);
			std::cout << "HIT WITH ROCKET: " << std::endl;
	}else if(_focus->getType() == GameObject::objectType::laser && _collidie->getType() == GameObject::objectType::smallEnemy_fighter || _focus->getType() == GameObject::objectType::smallEnemy_fighter && _collidie->getType() == GameObject::objectType::laser ||
		_focus->getType() == GameObject::objectType::laser && _collidie->getType() == GameObject::objectType::smallEnemy_bomber || _focus->getType() == GameObject::objectType::smallEnemy_bomber && _collidie->getType() == GameObject::objectType::laser ||
		_focus->getType() == GameObject::objectType::laser && _collidie->getType() == GameObject::objectType::largeEnemy_cmd || _focus->getType() == GameObject::objectType::largeEnemy_cmd && _collidie->getType() == GameObject::objectType::laser){
				_focus->collide(1);
				_collidie->collide(1);
				std::cout << "HIT WITH LASER: " << std::endl;
	}else if(_focus->getType() == GameObject::objectType::scattershot && _collidie->getType() == GameObject::objectType::smallEnemy_fighter || _focus->getType() == GameObject::objectType::smallEnemy_fighter && _collidie->getType() == GameObject::objectType::scattershot ||
		_focus->getType() == GameObject::objectType::scattershot && _collidie->getType() == GameObject::objectType::smallEnemy_bomber || _focus->getType() == GameObject::objectType::smallEnemy_bomber && _collidie->getType() == GameObject::objectType::scattershot||
		_focus->getType() == GameObject::objectType::scattershot && _collidie->getType() == GameObject::objectType::largeEnemy_cmd|| _focus->getType() == GameObject::objectType::largeEnemy_cmd && _collidie->getType() == GameObject::objectType::scattershot ||
		_focus->getType() == GameObject::objectType::scattershot && _collidie->getType() == GameObject::objectType::smallAlly_fighter|| _focus->getType() == GameObject::objectType::smallAlly_fighter && _collidie->getType() == GameObject::objectType::scattershot){
				_focus->collide(2);
				_collidie->collide(2);
				std::cout << "HIT WITH SCATTERSHOT: " << std::endl;
	}else{
	_focus->collide();
	_collidie->collide();
	}
}