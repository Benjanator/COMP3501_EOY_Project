#include "ObjectManager.h"


ObjectManager::ObjectManager(Ogre::SceneManager* _sm)
{
	scene_manager = _sm;
	Score = 0;

}


ObjectManager::~ObjectManager(void)
{
	scene_manager = 0;

	while(!objectList.empty())
	{
		GameObject* temp = objectList.back();
		objectList.pop_back();
		delete temp;
	}
}


int ObjectManager::getScore(){
	return Score;
}

int ObjectManager::getPlayerHealth(){
	if(objectList.at(0)->getType() == GameObject::objectType::smallAlly_fighter ){
	  return objectList.at(0)->getHealth();
	}else{
	  return 0;
	}
}


void ObjectManager::addObject(GameObject* _obj)
{

	objectList.push_back(_obj);
	
}

void ObjectManager::removeObject(GameObject* _obj)
{
	GameObject* temp;



	for(unsigned int i = 0; i < objectList.size(); i++){
		if(objectList.at(i) == _obj)
		{
			temp = objectList.at(i);
			
			if(temp->getType() == GameObject::objectType::smallEnemy_fighter || temp->getType() == GameObject::objectType::smallEnemy_bomber ||temp->getType() == GameObject::objectType::largeEnemy_cmd ){
				Score++;
			}
			objectList.erase(objectList.begin() + i);
			destroyList.push_back(temp);
			break;
		}
	}
}



void ObjectManager::cleanDestroyedObjects()
{
	while(!destroyList.empty()){
		scene_manager->getRootSceneNode()->removeAndDestroyChild(destroyList.back()->getNode().getName());
		destroyList.pop_back();
	}
}

vector<GameObject*>& ObjectManager::getObjectList()
{
	return objectList;
}

int ObjectManager::getListSize()
{
	return objectList.size();
}


