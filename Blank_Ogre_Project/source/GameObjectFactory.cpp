#include "GameObjectFactory.h"


GameObjectFactory::GameObjectFactory(Ogre::SceneManager* _sm): SAF_id(0), SEF_id(0), SAB_id(0), SEB_id(0), LAC_id(0), LEC_id(0)
{
	scene_manager = _sm;
}


GameObjectFactory::~GameObjectFactory(void)
{
}

GameObject* GameObjectFactory::createGameObject(GameObject::objectType _type)
{
	GameObject* newObject = nullptr;
	switch(_type){
	case GameObject::smallAlly_fighter:
		newObject = new SmallShip(create_SAF());
		break;
	case GameObject::smallEnemy_fighter:
		newObject = new SmallShip(create_SEF());
		break;
	case GameObject::smallAlly_bomber:
		break;
	case GameObject::smallEnemy_bomber:
		newObject = new SmallShip(create_SEB());
		break;
	case GameObject::largeEnemy_cmd:
		newObject = new SmallShip(create_LEC());
		break;
	case GameObject::largeAlly_cmd:
		break;
	default:
		break;
	}

	return newObject;
}

Ogre::SceneNode* GameObjectFactory::create_SAF()
{
	Ogre::String _objectName = "SAF_" + Ogre::StringConverter::toString(SAF_id);
	SAF_id++;
	Ogre::SceneNode* root_scene_node = scene_manager->getRootSceneNode();

	Ogre::Entity* entity = scene_manager->createEntity(_objectName, "Base_Ship.mesh");
	Ogre::SceneNode* node = root_scene_node->createChildSceneNode(_objectName);
	entity->setMaterialName("ShinyMaterial");
	node->attachObject(entity);

	//node->setPosition(0.0,0.0,0.0);
	node->setScale(1.0,1.0,1.0);
	node->showBoundingBox(true);

	//cockpit
	entity = scene_manager->createEntity(_objectName + "_Cockpit", "Cockpit.mesh");
	Ogre::SceneNode* child = node->createChildSceneNode(_objectName + "_Cockpit");
	entity->setMaterialName("BlueMaterial");
	child->attachObject(entity);

	child->rotate(Ogre::Quaternion(Ogre::Radian(1.570797f), Ogre::Vector3(0.0,0.0,-1.0)));
	child->translate(-1.22, -0.17430, 0.0f);

	//
	/*
	Ogre::SceneNode* camera = scene_manager->getSceneNode("MyCameraNode");
	Ogre::Camera* mCam = (Ogre::Camera*)camera->detachObject("MyCamera");
	scene_manager->destroySceneNode("MyCameraNode");
	
	mCam->setPosition(child->_getDerivedPosition());
	mCam->setOrientation(child->_getDerivedOrientation());
	mCam->move(Ogre::Vector3(0.0, 0.5, 0.0));

	cout << mCam->getPosition() << endl;
	child->attachObject(mCam);
	
	child = child->createChildSceneNode("MyCameraNode");
	child->attachObject(mCam);

	child->rotate(Ogre::Quaternion(Ogre::Radian(3.14159f), Ogre::Vector3(-1.0, 0.0, 1.0)));
	child->pitch(Ogre::Degree(95));
	child->translate(0.0, -1.6, 0.0);
	*/

	//generators
	entity =  scene_manager->createEntity(_objectName + "_Generator", "Generator.mesh");
	child = node->createChildSceneNode(_objectName + "_Generator");
	entity->setMaterialName("ObjectMaterial");
	child->attachObject(entity);

	child->translate(0.5f, 0.0f, 0.0f);

	//engines
	entity =  scene_manager->createEntity(_objectName + "_Engines", "Engines.mesh");
	child = node->createChildSceneNode(_objectName + "_Engines");
	entity->setMaterialName("ShinyBlueMaterial");
	child->attachObject(entity);

	child->rotate(Ogre::Quaternion(Ogre::Radian(3.01f), Ogre::Vector3(-1.0,0.0,0.0)));
	child->translate(-0.02796f, -0.92620f, -0.87242f);

	//
	entity =  scene_manager->createEntity(_objectName + "_Impulse", "Impule_Engine.mesh");
	child = node->createChildSceneNode(_objectName + "_Impulse");
	entity->setMaterialName("ObjectMaterial");
	child->attachObject(entity);

	child->translate(1.69124f, 0.31351f, 0.005f);

	//launchers
	entity =  scene_manager->createEntity(_objectName + "_Launcher", "Launcher_Weapon.mesh");
	child = node->createChildSceneNode(_objectName + "_Launcher");
	entity->setMaterialName("ShinyBlueMaterial");
	child->attachObject(entity);

	child->translate(1.64124f, 0.2, 0.005);

	//laser
	entity =  scene_manager->createEntity(_objectName + "_Laser", "Laser_Weapon.mesh");
	child = node->createChildSceneNode(_objectName + "_Laser");
	entity->setMaterialName("ShinyBlueMaterial");
	child->attachObject(entity);

	child->translate(1.66224f, 0.21, 0.005);

	//

	return node;
}

Ogre::SceneNode* GameObjectFactory::create_SEF()
{
	Ogre::String _objectName = "SEF_" + Ogre::StringConverter::toString(SEF_id);
	SEF_id++;
	Ogre::SceneNode* root_scene_node = scene_manager->getRootSceneNode();

	Ogre::Entity* entity = scene_manager->createEntity(_objectName, "Enemy_Fighter.mesh");
	Ogre::SceneNode* node = root_scene_node->createChildSceneNode(_objectName);
	entity->setMaterialName("ShinyMaterial");
	node->attachObject(entity);

	node->setPosition(10.0,0.0,0.0);
	node->setScale(1.0,1.0,1.0);

	return node;
}



Ogre::SceneNode* GameObjectFactory::create_SEB()
{
	Ogre::String _objectName = "SEB_" + Ogre::StringConverter::toString(SEB_id);
	SEB_id++;
	Ogre::SceneNode* root_scene_node = scene_manager->getRootSceneNode();

	Ogre::Entity* entity = scene_manager->createEntity(_objectName, "Lancer.mesh");
	Ogre::SceneNode* node = root_scene_node->createChildSceneNode(_objectName);
	entity->setMaterialName("ShinyMaterial");
	node->attachObject(entity);

	node->setPosition(50.0,0.0,0.0);
	node->setScale(1.0,1.0,1.0);

	return node;
}



Ogre::SceneNode* GameObjectFactory::create_LEC()
{
	Ogre::String _objectName = "LEC_" + Ogre::StringConverter::toString(LEC_id);
	LEC_id++;
	Ogre::SceneNode* root_scene_node = scene_manager->getRootSceneNode();

	Ogre::Entity* entity = scene_manager->createEntity(_objectName, "Carrier.mesh");
	Ogre::SceneNode* node = root_scene_node->createChildSceneNode(_objectName);
	entity->setMaterialName("ShinyMaterial");
	node->attachObject(entity);

	node->setPosition(100.0,0.0,0.0);
	node->setScale(1.0,1.0,1.0);

	return node;

}
