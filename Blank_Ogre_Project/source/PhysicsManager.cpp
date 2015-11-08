#include "PhysicsManager.h"


PhysicsManager::PhysicsManager(ObjectManager* _manager)
{
	objectManager = _manager;
}


PhysicsManager::~PhysicsManager(void)
{
	objectManager = 0;
}

void PhysicsManager::pollTotalEvents()
{
	std::vector<GameObject*> tempList = objectManager->getObjectList();
	
	for(unsigned int i = 0; i < tempList.size(); i++)
	{
		for(unsigned int j = i; j < tempList.size(); j++){
			bool collide = false;
			
			if(i != j){
				collide = testcollidableDistance(tempList.at(i)->getNode(), tempList.at(j)->getNode());
			}

			if(collide){

			}
			else{
				tempList.at(i)->update();
			}
		}
	}
}

/*
 * Private Functions
 * 
 */


/*	
*	sphere test // not fully calibrated, i shall blame shields
*/
bool PhysicsManager::testcollidableDistance(SceneNode& _focus, SceneNode& _collidie)
{	
	if( _focus._getWorldAABB().getCenter().squaredDistance(_collidie._getWorldAABB().getCenter()) < Math::Sqr(_focus._getWorldAABB().getHalfSize().length()) + Math::Sqr(_collidie._getWorldAABB().getHalfSize().length())){
		return true;
	}
	
	return false;
}