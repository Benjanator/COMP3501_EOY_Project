#include "GameObjectFactory.h"


GameObjectFactory::GameObjectFactory(Ogre::SceneManager* _sm): SAF_id(0), SEF_id(0), SAB_id(0), SEB_id(0), LAC_id(0), LEC_id(0), RCKT_id(0), LSR_id(0), SCTR_id(0)
{
	scene_manager = _sm;
	factory = new ParticleFactory(scene_manager);
	factory->CreateThrusterParticleGeometry("_Thruster", 200000);
	factory->CreateExplosionParticleGeometry("_Explosion",2000000);
	factory->CreateExplosionParticleGeometry("_Laser",200000);
	factory->CreateImplosionParticleGeometry("_Implosion",30000);



	factory->CreateSplineParticleGeometry("_SField", 20000);
	factory->CreateSplineParticleGeometry("_SFieldP", 20000);

}


GameObjectFactory::~GameObjectFactory(void)
{
	scene_manager = 0;
}

GameObject* GameObjectFactory::createGameObject(GameObject::objectType _type, Ogre::Vector3 _spawnPoint)
{
	GameObject* newObject = nullptr;
	Ogre::SceneNode* sceneObject = nullptr;

	switch(_type){
	case GameObject::smallAlly_fighter:
		sceneObject = create_SAF();
		sceneObject->setPosition(_spawnPoint);
		newObject = new SmallShip(sceneObject);
		newObject->setTeam(0);
		break;
	case GameObject::smallEnemy_fighter:
		sceneObject = create_SEF();
		sceneObject->setPosition(_spawnPoint);
		newObject = new Fighter(sceneObject);
		newObject->setTeam(1);
		break;
	case GameObject::smallAlly_bomber:
		//newObject->setTeam(0);
		break;
	case GameObject::smallEnemy_bomber:
		sceneObject = create_SEB();
		sceneObject->setPosition(_spawnPoint);
		newObject = new Bomber(sceneObject);
		newObject->setTeam(1);
		break;
	case GameObject::largeEnemy_cmd:
		sceneObject = create_LEC();
		sceneObject->setPosition(_spawnPoint);
		newObject = new Carrier(sceneObject);
		newObject->setTeam(1);
		break;
	case GameObject::largeAlly_cmd:
		break;
	case GameObject::asteroid:
		break;
	case GameObject::platform:
		sceneObject = create_EP();
		sceneObject->setPosition(_spawnPoint);
		newObject = new SmallShip(sceneObject);
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

GameObject* GameObjectFactory::createGameScatterShot(Ogre::Quaternion shipOrientation,Ogre::Vector3 shipPosition,bool LasrLR){
		GameObject* newObject = nullptr;
		newObject = new ScatterShot(create_SCTR(shipOrientation,shipPosition),shipOrientation,shipPosition, LasrLR);
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
	entity->setMaterialName("ShinyShipTextureMaterial");
	node->attachObject(entity);

	node->setPosition(0.0f,0.0f,0.0f);
	node->setScale(1.0,1.0,1.0);
	//node->showBoundingBox(true);

	//cockpit
	entity = scene_manager->createEntity(_objectName + "_Cockpit", "Cockpit.mesh");
	Ogre::SceneNode* child = node->createChildSceneNode(_objectName + "_Cockpit");
	entity->setMaterialName("ShinyCockpitTextureMaterial");
	child->attachObject(entity);

	//child->rotate(Ogre::Quaternion(Ogre::Radian(1.570797f), Ogre::Vector3(0.0,0.0,-1.0)));
	//child->translate(-1.22f, -0.17430f, 0.0f);

	//

	//generators
	entity =  scene_manager->createEntity(_objectName + "_Generator", "Generator.mesh");
	child = node->createChildSceneNode(_objectName + "_Generator");
	entity->setMaterialName("ShinyGeneratorTextureMaterial");
	child->attachObject(entity);

	//child->translate(0.5f, 0.0f, 0.0f);

	//engines
	entity =  scene_manager->createEntity(_objectName + "_Engines", "Engines.mesh");
	child = node->createChildSceneNode(_objectName + "_Engines");
	entity->setMaterialName("ShinyEngineTextureMaterial");
	child->attachObject(entity);

	//child->rotate(Ogre::Quaternion(Ogre::Radian(3.01f), Ogre::Vector3(-1.0,0.0,0.0)));
	//child->translate(-0.02796f, -0.92620f, -0.87242f);

	//
	entity =  scene_manager->createEntity(_objectName + "_Impulse", "Impule_Engine.mesh");
	child = node->createChildSceneNode(_objectName + "_Impulse");
	entity->setMaterialName("ShinyImpulseTextureMaterial");
	child->attachObject(entity);

	//child->translate(1.69124f, 0.31351f, 0.005f);

	//launchers
	entity =  scene_manager->createEntity(_objectName + "_Launcher", "Launcher_Weapon.mesh");
	child = node->createChildSceneNode(_objectName + "_Launcher");
	entity->setMaterialName("ShinyGunTextureMaterial");
	child->attachObject(entity);

	//child->translate(1.64124f, 0.2f, 0.005f);

	//laser
	entity =  scene_manager->createEntity(_objectName + "_Laser", "Laser_Weapon.mesh");
	child = node->createChildSceneNode(_objectName + "_Laser");
	entity->setMaterialName("ShinyGunTextureMaterial");
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

	
	//for(int i = 0; i <= 25; i++){
	 //factory ->CreateSplineControlPoints("ControlPoints"+ Ogre::StringConverter::toString(i), 64, "SplineParticleMaterial");
	 //child = factory->CreateParticleEntity("_SField","SplineParticleMaterial",node, Ogre::Vector3(0.2,0.2,0.2));
	 //child->translate(0.0f,0.0f,-2.0f);
	//}


	//child->translate(1.66224f, 0.21f, 0.005f);
	
	//
	// reset Orientation
	//

	
	child = factory->CreateParticleEntity("_Explosion","ParticleMaterial",node, Ogre::Vector3(1,1,1));


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
	entity->setMaterialName("ShinyFighterTextureMaterial");
	node->attachObject(entity);

	
	node->setPosition(0.0,0.0 + 40.0 * SEF_id,-50.0);
	//node->lookAt(Ogre::Vector3(0.0,0.0 + 40.0 * SEF_id,-10.0),Ogre::Node::TS_WORLD);
	//node->setDirection(Ogre::Vector3(0,1,0),Ogre::Node::TS_WORLD,Ogre::Vector3::NEGATIVE_UNIT_Z);
	//node->setOrientation((Ogre::Quaternion(Ogre::Degree(-90),Ogre::Vector3::UNIT_X)));
	node->rotate((Ogre::Quaternion(Ogre::Degree(180),Ogre::Vector3::UNIT_Y)),Ogre::Node::TS_WORLD);
	node->rotate((Ogre::Quaternion(Ogre::Degree(90),Ogre::Vector3::UNIT_X)),Ogre::Node::TS_WORLD);
	
	//node->lookAt(Ogre::Vector3(0.0,0.0,0.0),Ogre::Node::TS_WORLD);

	node->setScale(1.0,1.0,1.0);
	//node->showBoundingBox(true);
	//factory->CreateThrusterParticleGeometry(_objectName + "_Thruster", 200000);
		
	Ogre::SceneNode* child = factory->CreateParticleEntity("_Thruster","FireMaterial",node, Ogre::Vector3(1,1,0.1));
	child->setOrientation((Ogre::Quaternion(Ogre::Degree(-90),Ogre::Vector3::UNIT_X)));
	child->translate(-3.3f,-3.9f,-1.6f);
	//child->showBoundingBox(true);

	child = factory->CreateParticleEntity("_Thruster","FireMaterial",node, Ogre::Vector3(1,1,0.1));
	child->setOrientation((Ogre::Quaternion(Ogre::Degree(-90),Ogre::Vector3::UNIT_X)));
	child->translate(3.3f,-3.9f,-1.6f);


	
	child = factory->CreateParticleEntity("_Explosion","ParticleMaterial",node, Ogre::Vector3(1,1,1));
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
	entity->setMaterialName("ShinyPlatformTextureMaterial");
	node->attachObject(entity);

	node->setPosition(0.0,0.0 + 40 * SEB_id,-100.0);
	//node->lookAt(Ogre::Vector3(0.0,0.0 + 40 * SEB_id,-10.0),Ogre::Node::TS_WORLD);
	node->rotate((Ogre::Quaternion(Ogre::Degree(90),Ogre::Vector3::UNIT_Y)),Ogre::Node::TS_WORLD);
	//node->setDirection(Ogre::Vector3(1,0,0),Ogre::Node::TS_WORLD);
	//node->lookAt(Ogre::Vector3(0.0,0.0 + 40 * SEB_id,-10.0),Ogre::Node::TS_WORLD);
	node->setScale(0.5,0.5,1.0);

	//node->setScale(0.5,1.0,0.5);

	Ogre::SceneNode* child;

	for(int i = 0; i <= 25; i++){
	 factory ->CreateSplineControlPoints(_objectName+ "ControlPoints"+ Ogre::StringConverter::toString(i), 64, "SplineParticleMaterial");
	 child = factory->CreateParticleEntity("_SField","SplineParticleMaterial",node, Ogre::Vector3(0.4,0.08,0.08));
	 child->setOrientation((Ogre::Quaternion(Ogre::Degree(-90),Ogre::Vector3::UNIT_Y)));
	  child->translate(0.0f, 0.0f,-5.4f);
	  child->setScale(0.05,0.1,0.2);
	}

	
	child = factory->CreateParticleEntity("_Explosion","ParticleMaterial",node, Ogre::Vector3(1,1,1));
	child->translate(0.0f, -5.0f,-5.4f);

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
	entity->setMaterialName("ShinyCarrierTextureMaterial");
	node->attachObject(entity);

	//node->setOrientation((Ogre::Quaternion(Ogre::Degree(-90),Ogre::Vector3::UNIT_X)));
	node->setPosition(0.0,0.0 + 5.0 * LEC_id,-200);
	node->setScale(10.0,10.0,10.0);


	Ogre::SceneNode* child ;


	child = factory->CreateParticleEntity("_Thruster","FireMaterial",node, Ogre::Vector3(0.5,0.5,0.1));
	child->setOrientation((Ogre::Quaternion(Ogre::Degree(90),Ogre::Vector3::UNIT_Y)));
	child->translate(-5.1f,-2.7f,1.6f);

	child = factory->CreateParticleEntity("_Thruster","FireMaterial",node, Ogre::Vector3(1.15,1.15,0.08));
	child->setOrientation((Ogre::Quaternion(Ogre::Degree(90),Ogre::Vector3::UNIT_Y)));
	child->translate(-5.1f,-2.7f,-0.02f);

	child = factory->CreateParticleEntity("_Thruster","FireMaterial",node, Ogre::Vector3(0.5,0.5,0.1));
	child->setOrientation((Ogre::Quaternion(Ogre::Degree(90),Ogre::Vector3::UNIT_Y)));
	child->translate(-5.1f,-2.7f,-1.7f);

	for(int i = 0; i <= 25; i++){
	 factory ->CreateSplineControlPoints(_objectName+ "ControlPoints"+ Ogre::StringConverter::toString(i), 64, "SplineParticleMaterial");
	 child = factory->CreateParticleEntity("_SField","SplineParticleMaterial",node, Ogre::Vector3(0.18,0.05,0.05));
	 child->translate(7.1f, -2.7f,0.0f);
	}



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
	entity->setMaterialName("ShinyRocketTextureMaterial");
	node->attachObject(entity);
	node->setScale(0.5,0.5,0.5);

	//factory->CreateThrusterParticleGeometry(_objectName + "_Thruster", 200000);
	//node->showBoundingBox(true);

	Ogre::SceneNode* child = factory->CreateParticleEntity("_Thruster","FireMaterial",node, Ogre::Vector3(1,1,1));
	child->setOrientation((Ogre::Quaternion(Ogre::Degree(-90),Ogre::Vector3::UNIT_Y)));
	child->translate(5,0,0);

	child = factory->CreateParticleEntity("_Explosion","ParticleMaterial",node, Ogre::Vector3(1,1,1));
	

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
	entity->setMaterialName("ShinyLaserTextureMaterial");
	node->attachObject(entity);
	node->setScale(0.5,0.5,3.0);

	Ogre::SceneNode* child = factory->CreateParticleEntity("_Laser","Fire2Material",node, Ogre::Vector3(10,10,2));
	child->setScale(500,500,10);

	factory->resetCounter();
	return node;

}


Ogre::SceneNode* GameObjectFactory::create_SCTR(Ogre::Quaternion shipOrientation,Ogre::Vector3 shipPosition)
{
	Ogre::String _objectName = "SCTR_" + Ogre::StringConverter::toString(SCTR_id);
	SCTR_id++;
	Ogre::SceneNode* root_scene_node = scene_manager->getRootSceneNode();

	Ogre::Entity* entity = scene_manager->createEntity(_objectName, "ScatterShot.mesh");
	Ogre::SceneNode* node = root_scene_node->createChildSceneNode(_objectName);
	entity->setMaterialName("ShinyScatterShotTextureMaterial");
	node->attachObject(entity);
	node->setScale(0.5,0.5,0.5);


	Ogre::SceneNode* child = factory->CreateParticleEntity("_Implosion","ImplosionParticleMaterial",node, Ogre::Vector3(2,2,2));

	factory->resetCounter();
	return node;

}