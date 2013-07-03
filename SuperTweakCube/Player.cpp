#include"Player.h"

Player::Player(Ogre::SceneManager* SceneMgr,Ogre::Camera* camera)
{
	m_pSceneMgr=SceneMgr;
	m_pCamera = camera;
	PlayerTranslate = Ogre::Vector3(0,0,0);
	walkedud=0;
	walkedlr=0;
	Cubeattack=false;
	PlayerAction=FREE;		//表示人物空闲
	ActionTime=0;
	Create();
	Health = 100;			//初始生命为100
}

void Player::Create()
{
	//载入玩家模型
	_PlayerEnt = m_pSceneMgr->createEntity("You","Sinbad.mesh");
	_PlayerNode = m_pSceneMgr->createSceneNode("PNode");
	m_pSceneMgr->getRootSceneNode()->addChild(_PlayerNode);
	_PlayerNode->setScale(1.5f,1.5f,1.5f);
	_PlayerNode->setPosition(Ogre::Vector3(120.0f,-3.0f,280.0f));				//玩家起始位置
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

	_aniStateSlice = _PlayerEnt->getAnimationState("SliceVertical");
	_aniStateSlice->setEnabled(true);
	_aniStateSlice->setLoop(false);

	_CubeEnt = m_pSceneMgr->createEntity("Cube","Cube.MESH");
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
		else
			_rotation = 3.14f;
	}
	if(evt.key==OIS::KC_S)
	{
		PlayerTranslate -= Ogre::Vector3(0,0,1);
		walkedud++;
		if(COgreFramework::getSingletonPtr()->m_pKeyboard->isKeyDown(OIS::KC_A))
			_rotation = -1.57f;
		else if(COgreFramework::getSingletonPtr()->m_pKeyboard->isKeyDown(OIS::KC_D))
			_rotation = 1.57f;
		else
			_rotation = 3.14f;
	}
	if(evt.key==OIS::KC_A)
	{
		PlayerTranslate -= Ogre::Vector3(-1,0,0);
		walkedlr--;
		if(COgreFramework::getSingletonPtr()->m_pKeyboard->isKeyDown(OIS::KC_W))
			_rotation = 3.14f;
		else if(COgreFramework::getSingletonPtr()->m_pKeyboard->isKeyDown(OIS::KC_S))
			_rotation = 0;
		else
			_rotation = 3.14f;
	}
	if(evt.key==OIS::KC_D)
	{
		PlayerTranslate -= Ogre::Vector3(1,0,0);
		walkedlr++;
		if(COgreFramework::getSingletonPtr()->m_pKeyboard->isKeyDown(OIS::KC_W))
			_rotation = 3.14f;
		else if(COgreFramework::getSingletonPtr()->m_pKeyboard->isKeyDown(OIS::KC_S))
			_rotation = 0;
		else
			_rotation = 3.14f;
	}
}

void Player::addTime(double time)
{
	if((walkedud!=0||walkedlr!=0)&&PlayerAction!=ATTACK)			//假如行走且非攻击状态
	{
		_aniStateTop->setEnabled(true);
		if(_aniStateTop->hasEnded())
		{
			_aniStateTop->setTimePosition(0.0f);
		}
		_aniStateTop->addTime(time/1000);
		_aniState->setEnabled(true);
		if(_aniState->hasEnded())
		{
			_aniState->setTimePosition(0.0f);
		}
		_aniState->addTime(time/1000);
		
	}
	else
	{
		_aniState->setTimePosition(0.0f);
		_aniState->setEnabled(false);
		_aniStateTop->setTimePosition(0.0f);
		_aniStateTop->setEnabled(false);
	}

	_PlayerNode->resetOrientation();
	//_PlayerNode->setOrientation(m_pCamera->getOrientation());
	//float rotX = COgreFramework::getSingletonPtr()->m_pMouse->getMouseState().X.rel * time* -1;
	//_PlayerNode->yaw(Ogre::Radian(rotX)/300);
	Ogre::Vector3 playerdir = m_pCamera->getDerivedPosition()-_PlayerNode->getPosition();
	playerdir = Ogre::Vector3(playerdir.x,0.0f,playerdir.z);
	playerdir = -playerdir/playerdir.length();					//获得人物朝向，转化为单位向量
	_PlayerNode->setDirection(playerdir);						//设置人物节点朝向
	_PlayerNode->yaw(Ogre::Radian(_rotation));				//行走转动

	if(PlayerAction==REMOTEATTACK)			//当动作为远程时
	{
		if(ActionTime>0)
		{
			ActionTime-=time;
		}
		else
		{
			PlayerAction=FREE;
			ActionTime=0.0;
		}
	}
	else if(PlayerAction==ATTACK)				//当动作为近战攻击时
	{
		_aniStateSlice->setEnabled(true);
		Attack(time);
		if(_aniStateSlice->hasEnded())
		{	
			_aniStateSlice->setTimePosition(0.0f);
			_aniStateSlice->setEnabled(false);
			PlayerAction=FREE;
			ActionTime=0;
		}
	}
	
	_PlayerNode->translate(-playerdir * PlayerTranslate.z * time/20);
	_PlayerNode->translate(Ogre::Vector3(-playerdir.z,0.0f,playerdir.x) * PlayerTranslate.x * time/20);
	if(Cubeattack==true)
	{
		if(Cubetime>0)
		{
			Cubetime-=time;
			_CubeNode->translate(playerdir * time/5);
			_CubeNode->yaw(Ogre::Radian(0.1f));		//旋转
		}
		else
		{
			Cubetime=0;
			Cubeattack=false;
			_CubeNode->detachAllObjects();
		}
	}
}

void Player::mousePressed(OIS::MouseButtonID id)
{
	if(id == OIS::MB_Right)
		remoteAttack();
	else if(id == OIS::MB_Left)
	{
		ActionTime=300;
		PlayerAction=ATTACK;
	}
}


void Player::remoteAttack()
{
	if(Cubeattack==false)
	{
		_CubeNode->setScale(0.2f,0.2f,0.2f);
		_CubeNode->setPosition(_PlayerNode->getPosition());
		_CubeNode->attachObject(_CubeEnt);
		_CubeNode->resetOrientation();					//方向复位
		Cubetime=1000;
		Cubeattack=true;
		ActionTime=300;
		PlayerAction=REMOTEATTACK;
	}
}

void Player::Attack(double time)
{
	_aniStateSlice->addTime(time/1000);
}