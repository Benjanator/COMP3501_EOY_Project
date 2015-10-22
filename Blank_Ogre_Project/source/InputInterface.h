#pragma once
#include <OGRE/OgreSceneNode.h>
#include <OIS\OISKeyboard.h>
#include <OIS\OISMouse.h>

using namespace Ogre;

class InputInterface
{
public:
	InputInterface(SceneNode* _player, OIS::Keyboard* _keyboard, OIS::Mouse* _mouse);
	~InputInterface(void);
	void pollInput();

private:
	SceneNode* m_Player;
	OIS::Keyboard* m_Keyboard;
	OIS::Mouse* m_Mouse;
};

