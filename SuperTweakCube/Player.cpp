#include"Player.h"

Player::Player(Ogre::SceneManager* SceneMgr,Ogre::Camera* camera)
{
	m_pSceneMgr=SceneMgr;
	m_pCamera = camera;
	PlayerTranslate = Ogre::Vector3(0,0,0);
	walkedud=0;
	walkedlr=0;
	Cubeattack=false;
	Create();
}

void Player::Create()
{
	//载入玩家模型
	_PlayerEnt = m_pSceneMgr->createEntity("You","Sinbad.mesh");
	_PlayerNode = m_pSceneMgr->createSceneNode("PNode");
	m_pSceneMgr->getRootSceneNode()->addChild(_PlayerNode);
	_PlayerNode->setScale(3.0f,3.0f,3.0f);
	_PlayerNode->setPosition(Ogre::Vector3(10.0f,4.0f,0.0f));
	_PlayerNode->attachObject(_PlayerEnt);

	Ogre::Entity* sword1 = m_pSceneMgr->createEntity("Sword1", "Sword.mesh");
	Ogre::Entity* sword2 = m_pSceneMgr->createEntity("Sword2", "Sword.mesh");

	_PlayerEnt->attachObjectToBone("Handle.L", sword1);
	_PlayerEnt->attachObjectToBone("Handle.R", sword2);

	_aniState =_PlayerEnt->getAnimationState("RunBase");
	_aniState->setEnabled(true);
	_aniState->setLoop(false);

	_aniStateTop = _PlayerEnt->getAnimationState("RunTop");
	_aniStateTop->setEnabled(true);
	_aniStateTop->setLoop(false);

	_CubeEnt = m_pSceneMgr->createEntity("Cube","Cube.mesh");
	_CubeNode = m_pSceneMgr->createSceneNode("CubeNode");
	m_pSceneMgr->getRootSceneNode()->addChild(_CubeNode);
}

void Player::keyPressed(const OIS::KeyEvent &evt)		//按键
{
	if(evt.key==OIS::KC_W)
	{
		PlayerTranslate += Ogre::Vector3(0,0,-1);		//移动方向
		if(COgreFramework::getSingletonPtr()->m_pKeyboard->isKeyDown(OIS::KC_A))
			_rotation = -2.36f;							//转动方向
		else if(COgreFramework::getSingletonPtr()->m_pKeyboard->isKeyDown(OIS::KC_D))
			_rotation = 2.36f;
		else
			_rotation = 3.14f;
		walkedud++;
	}
	if(evt.key==OIS::KC_S)
	{
		PlayerTranslate += Ogre::Vector3(0,0,1);
		if(COgreFramework::getSingletonPtr()->m_pKeyboard->isKeyDown(OIS::KC_A))
			_rotation = -0.79f;
		else if(COgreFramework::getSingletonPtr()->m_pKeyboard->isKeyDown(OIS::KC_D))
			_rotation = 0.79f;
		else
			_rotation = 0.0f;
		walkedud--;
	}
	if(evt.key==OIS::KC_A)
	{
		PlayerTranslate += Ogre::Vector3(-1,0,0);
		if(COgreFramework::getSingletonPtr()->m_pKeyboard->isKeyDown(OIS::KC_W))
			_rotation = -2.36f;
		else if(COgreFramework::getSingletonPtr()->m_pKeyboard->isKeyDown(OIS::KC_S))
			_rotation = -0.79f;
		else
			_rotation = -1.57f;
		walkedlr++;
	}
	if(evt.key==OIS::KC_D)
	{
		PlayerTranslate += Ogre::Vector3(1,0,0);
		if(COgreFramework::getSingletonPtr()->m_pKeyboard->isKeyDown(OIS::KC_W))
			_rotation = 2.36f;
		else if(COgreFramework::getSingletonPtr()->m_pKeyboard->isKeyDown(OIS::KC_S))
			_rotation = 0.79f;
		else
			_rotation = 1.57f;
		walkedlr--;
	}
}

void Player::keyReleased(const OIS::KeyEvent &evt)		//按键
{
	if(evt.key==OIS::KC_W)
	{
		PlayerTranslate -= Ogre::Vector3(0,0,-1);
		walkedud--;
		if(COgreFramework::getSingletonPtr()->m_pKeyboard->isKeyDown(OIS::KC_A))
			_rotation = -1.57f;
		else if(COgreFramework::getSingletonPtr()->m_pKeyboard->isKeyDown(OIS::KC_D))
			_rotation = 1.57f;
	}
	if(evt.key==OIS::KC_S)
	{
		PlayerTranslate -= Ogre::Vector3(0,0,1);
		walkedud++;
		if(COgreFramework::getSingletonPtr()->m_pKeyboard->isKeyDown(OIS::KC_A))
			_rotation = -1.57f;
		else if(COgreFramework::getSingletonPtr()->m_pKeyboard->isKeyDown(OIS::KC_D))
			_rotation = 1.57f;
	}
	if(evt.key==OIS::KC_A)
	{
		PlayerTranslate -= Ogre::Vector3(-1,0,0);
		walkedlr--;
		if(COgreFramework::getSingletonPtr()->m_pKeyboard->isKeyDown(OIS::KC_W))
			_rotation = 3.14f;
		else if(COgreFramework::getSingletonPtr()->m_pKeyboard->isKeyDown(OIS::KC_S))
			_rotation = 0;
	}
	if(evt.key==OIS::KC_D)
	{
		PlayerTranslate -= Ogre::Vector3(1,0,0);
		walkedlr++;
		if(COgreFramework::getSingletonPtr()->m_pKeyboard->isKeyDown(OIS::KC_W))
			_rotation = 3.14f;
		else if(COgreFramework::getSingletonPtr()->m_pKeyboard->isKeyDown(OIS::KC_S))
			_rotation = 0;
	}
}

void Player::addTime(double time)
{
	if(walkedud!=0||walkedlr!=0)			//假如行走
	{
		_aniState->setEnabled(true);
		_aniStateTop->setEnabled(true);
		if(_aniState->hasEnded())
		{	
			_aniState->setTimePosition(0.0f);
		}
		if(_aniStateTop->hasEnded())
		{
			_aniStateTop->setTimePosition(0.0f);
		}
	}
	else
	{
		_aniState->setTimePosition(0.0f);
		_aniState->setEnabled(false);
		_aniStateTop->setTimePosition(0.0f);
		_aniStateTop->setEnabled(false);
	}
	_aniState->addTime(time/1000);
	_aniStateTop->addTime(time/1000);

	_PlayerNode->translate(PlayerTranslate * time/20);
	_PlayerNode->resetOrientation();
	if(Cubeattack==false)
		_PlayerNode->yaw(Ogre::Radian(_rotation));

	if(Cubeattack==true)
	{
		if(Cubetime>0)
		{
			Cubetime--;
			_CubeNode->translate(Cubedirect * time/300);
			_PlayerNode->setDirection(-Cubedirect);
		}
		else
		{
			Cubeattack=false;
			_CubeNode->detachAllObjects();
		}
	}
}

void Player::mousePressed(OIS::MouseButtonID id)
{
	if(id == OIS::MB_Left)
		remoteAttack();
}
void Player::remoteAttack()
{
	Ogre::Ray mouseRay=COgreFramework::getSingletonPtr()->m_pTrayMgr->getCursorRay(m_pCamera);
	if(Cubeattack==false)
	{
		_CubeNode->setScale(0.1f,0.1f,0.1f);
		Cubedirect=(mouseRay.getPoint((mouseRay.intersects(Ogre::Plane(Ogre::Vector3::UNIT_Y, 4))).second)-_PlayerNode->getPosition());
		_CubeNode->setPosition(_PlayerNode->getPosition());
		_CubeNode->attachObject(_CubeEnt);
		_CubeNode->setDirection(Cubedirect);			//调整朝向
		Cubetime=100;
		Cubeattack=true;
	}
}