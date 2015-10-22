#include "InputInterface.h"


InputInterface::InputInterface(SceneNode* _player, OIS::Keyboard* _keyboard, OIS::Mouse* _mouse)
{
}


InputInterface::~InputInterface(void)
{
}

void InputInterface::pollInput()
{
	m_Keyboard->capture();
	m_Mouse->capture();

	
}