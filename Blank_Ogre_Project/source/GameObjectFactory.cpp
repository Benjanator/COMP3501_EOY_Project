#include "GameObjectFactory.h"


GameObjectFactory::GameObjectFactory(Ogre::SceneManager* _sm): SAF_id(0), SEF_id(0), SAB_id(0), SEB_id(0), LAC_id(0), LEC_id(0), RCKT_id(0), LSR_id(0)
{
	scene_manager = _sm;
	factory = new ParticleFactory(scene_manager);
	factory->CreateThrusterParticleGeometry("_Thruster", 200000);
	factory->CreateExplosionParticleGeometry("_Explosion",2000000);
}


GameObjectFactory::~GameObjectFactory(void)
{
	scene_manager = 0;
}

GameObject* GameObjectFactory::createGameObject(GameObject::objectType _type)
{
	GameObject* newObject = nullptr;
	switch(_type){
	case GameObject::smallAlly_fighter:
		newObject = new SmallShip(create_SAF());
		newObject->setTeam(0);
		break;
	case GameObject::smallEnemy_fighter:
		//newObject = new SmallShip(create_SEF());
		newObject = new Fighter(create_SEF());
		newObject->setTeam(1);
		break;
	case GameObject::smallAlly_bomber:
		//newObject->setTeam(0);
		break;
	case GameObject::smallEnemy_bomber:
		//newObject = new SmallShip(create_SEB());
		newObject = new Bomber(create_SEB());
		newObject->setTeam(1);
		break;
	case GameObject::largeEnemy_cmd:
		//newObject = new SmallShip(create_LEC());
		newObject = new Carrier(create_LEC());
		newObject->setTeam(1);
		break;
	case GameObject::largeAlly_cmd:
		break;
	case GameObject::asteroid:
		break;
	case GameObject::platform:
		newObject = new SmallShip(create_EP());
		newObject->setTeam(1);
		break;
	default:
		break;
	}

	return newObject;
}


GameObject* GameObjectFactory::createGameRocket(Ogre::Quaternion shipOrientation,Ogre::Vector3 shipPosition, Ogre::Vector3 shipDirection){
		GameObject* newObject = nullptr;
		newObject = new Rocket(create_RCKT(shipOrientation,shipPosition),shipOrientation,shipPosition,shipDirection);
		newObject->setTeam(1);
		return newObject;
}

GameObject* GameObjectFactory::createGameLaser(Ogre::Quaternion shipOrientation,Ogre::Vector3 shipPosition,bool LasrLR){
		GameObject* newObject = nullptr;
		newObject = new Laser(create_LSR(shipOrientation,shipPosition),shipOrientation,shipPosition, LasrLR);
		newObject->setTeam(1);
		return newObject;
}

Ogre::SceneNode* GameObjectFactory::create_SAF()
{
	Ogre::String _objectName = "SAF_" + Ogre::StringConverter::toString(SAF_id);
	SAF_id++;
	Ogre::SceneNode* root_scene_node = scene_manager->getRootSceneNode();

	Ogre::Entity* entity = scene_manager->createEntity(_objectName, "Base_Ship.mesh");
	Ogre::SceneNode* node = root_scene_node->createChildSceneNode(_objectName);
	//entity->setMaterialName("ShinyMaterial");
	entity->setMaterialName("ShinyTextureMaterial");
	node->attachObject(entity);

	node->setPosition(0.0f,0.0f,0.0f);
	node->setScale(1.0,1.0,1.0);
	//node->showBoundingBox(true);

	//cockpit
	entity = scene_manager->createEntity(_objectName + "_Cockpit", "Cockpit.mesh");
	Ogre::SceneNode* child = node->createChildSceneNode(_objectName + "_Cockpit");
	entity->setMaterialName("BlueMaterial");
	child->attachObject(entity);

	//child->rotate(Ogre::Quaternion(Ogre::Radian(1.570797f), Ogre::Vector3(0.0,0.0,-1.0)));
	//child->translate(-1.22f, -0.17430f, 0.0f);

	//

	//generators
	entity =  scene_manager->createEntity(_objectName + "_Generator", "Generator.mesh");
	child = node->createChildSceneNode(_objectName + "_Generator");
	entity->setMaterialName("ObjectMaterial");
	child->attachObject(entity);

	//child->translate(0.5f, 0.0f, 0.0f);

	//engines
	entity =  scene_manager->createEntity(_objectName + "_Engines", "Engines.mesh");
	child = node->createChildSceneNode(_objectName + "_Engines");
	entity->setMaterialName("ShinyBlueMaterial");
	child->attachObject(entity);

	//child->rotate(Ogre::Quaternion(Ogre::Radian(3.01f), Ogre::Vector3(-1.0,0.0,0.0)));
	//child->translate(-0.02796f, -0.92620f, -0.87242f);

	//
	entity =  scene_manager->createEntity(_objectName + "_Impulse", "Impule_Engine.mesh");
	child = node->createChildSceneNode(_objectName + "_Impulse");
	entity->setMaterialName("ObjectMaterial");
	child->attachObject(entity);

	//child->translate(1.69124f, 0.31351f, 0.005f);

	//launchers
	entity =  scene_manager->createEntity(_objectName + "_Launcher", "Launcher_Weapon.mesh");
	child = node->createChildSceneNode(_objectName + "_Launcher");
	entity->setMaterialName("ShinyBlueMaterial");
	child->attachObject(entity);

	//child->translate(1.64124f, 0.2f, 0.005f);

	//laser
	entity =  scene_manager->createEntity(_objectName + "_Laser", "Laser_Weapon.mesh");
	child = node->createChildSceneNode(_objectName + "_Laser");
	entity->setMaterialName("ShinyBlueMaterial");
	child->attachObject(entity);


	//factory->CreateThrusterParticleGeometry(_objectName + "_Thruster", 200000);

	child = factory->CreateParticleEntity("_Thruster","FireMaterial",node, Ogre::Vector3(0.5,0.5,0.5));
	child->setOrientation((Ogre::Quaternion(Ogre::Degree(180),Ogre::Vector3::UNIT_Y)));
	child->translate(-2.4f,-0.5f,3.0f);

	child = factory->CreateParticleEntity("_Thruster","FireMaterial",node, Ogre::Vector3(0.5,0.5,0.5));
	child->setOrientation((Ogre::Quaternion(Ogre::Degree(180),Ogre::Vector3::UNIT_Y)));
	child->translate(-1.5f,0.7f,3.0f);

	child = factory->CreateParticleEntity("_Thruster","FireMaterial",node, Ogre::Vector3(0.5,0.5,0.5));
	child->setOrientation((Ogre::Quaternion(Ogre::Degree(180),Ogre::Vector3::UNIT_Y)));
	child->translate(1.5f,0.7f,3.0f);

	child = factory->CreateParticleEntity("_Thruster","FireMaterial",node, Ogre::Vector3(0.5,0.5,0.5));
	child->setOrientation((Ogre::Quaternion(Ogre::Degree(180),Ogre::Vector3::UNIT_Y)));
	child->translate(2.4f,-0.5f,3.0f);

	

	//child->translate(1.66224f, 0.21f, 0.005f);
	
	//
	// reset Orientation
	//
	node->resetOrientation();
	//node->translate(0.0f, 0.0f, 2.5f);
	factory->resetCounter();
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

	
	node->setPosition(0.0,0.0 + 20.0 * SEF_id,-50.0);
	node->setScale(1.0,1.0,1.0);

	//factory->CreateThrusterParticleGeometry(_objectName + "_Thruster", 200000);
		
	Ogre::SceneNode* child = factory->CreateParticleEntity("_Thruster","FireMaterial",node, Ogre::Vector3(1,1,1));
	child->setOrientation((Ogre::Quaternion(Ogre::Degree(180),Ogre::Vector3::UNIT_Y)));
	child->translate(-3.3f,-1.8f,5.5f);
	//child->showBoundingBox(true);

	child = factory->CreateParticleEntity("_Thruster","FireMaterial",node, Ogre::Vector3(1,1,1));
	child->setOrientation((Ogre::Quaternion(Ogre::Degree(180),Ogre::Vector3::UNIT_Y)));
	child->translate(3.3f,-1.7f,5.5f);
	factory->resetCounter();
	return node;
}



Ogre::SceneNode* GameObjectFactory::create_SEB()
{
	Ogre::String _objectName = "SEB_" + Ogre::StringConverter::toString(SEB_id);
	SEB_id++;
	Ogre::SceneNode* root_scene_node = scene_manager->getRootSceneNode();

	//Ogre::Entity* entity = scene_manager->createEntity(_objectName, "Lancer.mesh");
	Ogre::Entity* entity = scene_manager->createEntity(_objectName, "Platform.mesh");
	Ogre::SceneNode* node = root_scene_node->createChildSceneNode(_objectName);
	entity->setMaterialName("ShinyMaterial");
	node->attachObject(entity);

	node->setPosition(0.0,0.0 + 20 * SEB_id,-100.0);
	//node->setScale(1.0,1.0,1.0);

	node->setScale(0.5,1.0,0.5);
	factory->resetCounter();
	return node;
}



Ogre::SceneNode* GameObjectFactory::create_LEC()
{
	Ogre::String _objectName = "LEC_" + Ogre::StringConverter::toString(LEC_id);
	LEC_id++;
	Ogre::SceneNode* root_scene_node = scene_manager->getRootSceneNode();

	Ogre::Entity* entity = scene_manager->createEntity(_objectName, "Carrier.mesh");
	Ogre::SceneNode* node = root_scene_node->createChildSceneNode(_objectName);
	entity->setMaterialName("ShinyTextureMaterial");
	node->attachObject(entity);


	node->setPosition(0.0,0.0 + 5.0 * LEC_id,-150);
	node->setScale(10.0,10.0,10.0);
	factory->resetCounter();
	return node;
	
}

Ogre::SceneNode* GameObjectFactory::create_AP()
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
	factory->resetCounter();
	return node;

}

Ogre::SceneNode* GameObjectFactory::create_EP()
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
	factory->resetCounter();
	return node;

}


Ogre::SceneNode* GameObjectFactory::create_RCKT(Ogre::Quaternion shipOrientation,Ogre::Vector3 shipPosition)
{
	Ogre::String _objectName = "RCKT_" + Ogre::StringConverter::toString(RCKT_id);
	RCKT_id++;
	Ogre::SceneNode* root_scene_node = scene_manager->getRootSceneNode();

	Ogre::Entity* entity = scene_manager->createEntity(_objectName, "Rocket.mesh");
	Ogre::SceneNode* node = root_scene_node->createChildSceneNode(_objectName);
	entity->setMaterialName("ShinyMaterial");
	node->attachObject(entity);
	node->setScale(0.5,0.5,0.5);

	//factory->CreateThrusterParticleGeometry(_objectName + "_Thruster", 200000);


	Ogre::SceneNode* child = factory->CreateParticleEntity("_Thruster","FireMaterial",node, Ogre::Vector3(1,1,1));
	child->setOrientation((Ogre::Quaternion(Ogre::Degree(-90),Ogre::Vector3::UNIT_Y)));
	child->translate(5,0,0);

	child = factory->CreateParticleEntity("_Explosion","ParticleMaterial",node, Ogre::Vector3(0.5,0.5,0.5));
	
	

	factory->resetCounter();
	return node;

}

Ogre::SceneNode* GameObjectFactory::create_LSR(Ogre::Quaternion shipOrientation,Ogre::Vector3 shipPosition)
{
	Ogre::String _objectName = "LSR_" + Ogre::StringConverter::toString(LSR_id);
	LSR_id++;
	Ogre::SceneNode* root_scene_node = scene_manager->getRootSceneNode();

	Ogre::Entity* entity = scene_manager->createEntity(_objectName, "Laser.mesh");
	Ogre::SceneNode* node = root_scene_node->createChildSceneNode(_objectName);
	entity->setMaterialName("BlueMaterial");
	node->attachObject(entity);
	node->setScale(0.5,0.5,3.0);

	factory->resetCounter();
	return node;

}