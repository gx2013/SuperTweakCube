#include "RunState.h"

using namespace Ogre;

CRunState::CRunState()
{
	m_bQuit = false;
	translate=Ogre::Vector3(0,0,0);
	SinbadTranslate = Ogre::Vector3(0,0,0);
	walkedud=0;
	walkedlr=0;
	m_FrameEvent = Ogre::FrameEvent();
	Cubeattack=false;
}

void CRunState::Enter()
{
	COgreFramework::getSingletonPtr()->m_pLog->logMessage("Entering GameState...");

	m_pSceneMgr = COgreFramework::getSingletonPtr()->m_pRoot->createSceneManager(ST_GENERIC, "RunSceneMgr");
	m_pSceneMgr->setAmbientLight(Ogre::ColourValue(0.7f, 0.7f, 0.7f));

	m_pCamera = m_pSceneMgr->createCamera("RunCam");
	m_pCamera->setPosition(Vector3(0, 300, 200));
	m_pCamera->lookAt(Vector3(0.0f,4.0f,0.0f));
	m_pCamera->setNearClipDistance(1);

	COgreFramework::getSingletonPtr()->m_pViewport->setCamera(m_pCamera);

	COgreFramework::getSingletonPtr()->m_pTrayMgr->showCursor();

	CreateScene();
}

void CRunState::CreateScene()
{
	COgreFramework::getSingletonPtr()->m_pViewport->setBackgroundColour(ColourValue(1.0f, 1.0f, 0.8f));

	Ogre::SceneNode* node = m_pSceneMgr->createSceneNode("Node1");
	m_pSceneMgr->getRootSceneNode()->addChild(node);
	_SinbadEnt = m_pSceneMgr->createEntity("Sinbad","Sinbad.mesh");
	_SinbadNode = node->createChildSceneNode("SinbadNode");
	_SinbadNode->setScale(3.0f,3.0f,3.0f);
	_SinbadNode->setPosition(Ogre::Vector3(0.0f,4.0f,0.0f));
	_SinbadNode->attachObject(_SinbadEnt);

	Ogre::Entity* sword1 = m_pSceneMgr->createEntity("Sword1", "Sword.mesh");
	Ogre::Entity* sword2 = m_pSceneMgr->createEntity("Sword2", "Sword.mesh");

	_SinbadEnt->attachObjectToBone("Handle.L", sword1);
	_SinbadEnt->attachObjectToBone("Handle.R", sword2);

	Plane plane(Vector3::UNIT_Y, -10);
	MeshManager::getSingleton().createPlane("plane",
			ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, plane,
			1500,1500,200,200,true,1,5,5,Vector3::UNIT_Z);

	Entity* floor = m_pSceneMgr->createEntity("LightPlaneEntity", "plane");
    floor->setMaterialName("Examples/Rockwall");
    m_pSceneMgr->getRootSceneNode()->attachObject(floor);

	Light* light = m_pSceneMgr->createLight("Light1");
	light->setType(Ogre::Light::LT_DIRECTIONAL);
	light->setDirection(Ogre::Vector3(1,-1,0));

	_aniState = _SinbadEnt->getAnimationState("RunBase");
	_aniState->setEnabled(true);
	_aniState->setLoop(false);

	_aniStateTop = _SinbadEnt->getAnimationState("RunTop");
	_aniStateTop->setEnabled(true);
	_aniStateTop->setLoop(false);

	_CubeEnt = m_pSceneMgr->createEntity("Cube","Cube.mesh");
	_CubeNode = m_pSceneMgr->createSceneNode("CubeNode");
	m_pSceneMgr->getRootSceneNode()->addChild(_CubeNode);

	Enemy=new RunStateEnemy(m_pSceneMgr);
	Enemy->CreateEnemy();
}

void CRunState::Exit()
{
	COgreFramework::getSingletonPtr()->m_pLog->logMessage("Leaving MenuState...");

	m_pSceneMgr->destroyCamera(m_pCamera);

	if (m_pSceneMgr)
		COgreFramework::getSingletonPtr()->m_pRoot->destroySceneManager(m_pSceneMgr);

	COgreFramework::getSingletonPtr()->m_pTrayMgr->clearAllTrays();
	COgreFramework::getSingletonPtr()->m_pTrayMgr->destroyAllWidgets();
	COgreFramework::getSingletonPtr()->m_pTrayMgr->setListener(NULL);
}

bool CRunState::Pause()
{
	return true;
}

void CRunState::Resume()
{

}

bool CRunState::keyPressed(const OIS::KeyEvent &evt)
{
	
	if (evt.key==OIS::KC_ESCAPE)
	{
		m_bQuit = true;
		return true;
	}
	if(evt.key==OIS::KC_W)
	{
		translate += Ogre::Vector3(0,0,-1);
		SinbadTranslate += Ogre::Vector3(0,0,-1);
		if(COgreFramework::getSingletonPtr()->m_pKeyboard->isKeyDown(OIS::KC_A))
			_rotation = -2.36f;
		else if(COgreFramework::getSingletonPtr()->m_pKeyboard->isKeyDown(OIS::KC_D))
			_rotation = 2.36f;
		else
			_rotation = 3.14f;
		walkedud++;
	}
	if(evt.key==OIS::KC_S)
	{
		translate += Ogre::Vector3(0,0,1);
		SinbadTranslate += Ogre::Vector3(0,0,1);
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
		translate += Ogre::Vector3(-1,0,0);
		SinbadTranslate += Ogre::Vector3(-1,0,0);
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
		translate += Ogre::Vector3(1,0,0);
		SinbadTranslate += Ogre::Vector3(1,0,0);
		if(COgreFramework::getSingletonPtr()->m_pKeyboard->isKeyDown(OIS::KC_W))
			_rotation = 2.36f;
		else if(COgreFramework::getSingletonPtr()->m_pKeyboard->isKeyDown(OIS::KC_S))
			_rotation = 0.79f;
		else
			_rotation = 1.57f;
		walkedlr--;
	}

	COgreFramework::getSingletonPtr()->keyPressed(evt);

	return true;
}

bool CRunState::keyReleased(const OIS::KeyEvent &evt)
{
	if(evt.key==OIS::KC_W)
	{
		translate -= Ogre::Vector3(0,0,-1);
		SinbadTranslate -= Ogre::Vector3(0,0,-1);
		walkedud--;
		if(COgreFramework::getSingletonPtr()->m_pKeyboard->isKeyDown(OIS::KC_A))
			_rotation = -1.57f;
		else if(COgreFramework::getSingletonPtr()->m_pKeyboard->isKeyDown(OIS::KC_D))
			_rotation = 1.57f;
	}
	if(evt.key==OIS::KC_S)
	{
		translate -= Ogre::Vector3(0,0,1);
		SinbadTranslate -= Ogre::Vector3(0,0,1);
		walkedud++;
		if(COgreFramework::getSingletonPtr()->m_pKeyboard->isKeyDown(OIS::KC_A))
			_rotation = -1.57f;
		else if(COgreFramework::getSingletonPtr()->m_pKeyboard->isKeyDown(OIS::KC_D))
			_rotation = 1.57f;
	}
	if(evt.key==OIS::KC_A)
	{
		translate -= Ogre::Vector3(-1,0,0);
		SinbadTranslate -= Ogre::Vector3(-1,0,0);
		walkedlr--;
		if(COgreFramework::getSingletonPtr()->m_pKeyboard->isKeyDown(OIS::KC_W))
			_rotation = 3.14f;
		else if(COgreFramework::getSingletonPtr()->m_pKeyboard->isKeyDown(OIS::KC_S))
			_rotation = 0;
	}
	if(evt.key==OIS::KC_D)
	{
		translate -= Ogre::Vector3(1,0,0);
		SinbadTranslate -= Ogre::Vector3(1,0,0);
		walkedlr++;
		if(COgreFramework::getSingletonPtr()->m_pKeyboard->isKeyDown(OIS::KC_W))
			_rotation = 3.14f;
		else if(COgreFramework::getSingletonPtr()->m_pKeyboard->isKeyDown(OIS::KC_S))
			_rotation = 0;
	}
	COgreFramework::getSingletonPtr()->keyPressed(evt);
	return true;
}

bool CRunState::mouseMoved(const OIS::MouseEvent &evt)
{
	if (COgreFramework::getSingletonPtr()->m_pTrayMgr->injectMouseMove(evt))
		return true;

	return true;
}

bool CRunState::mousePressed( const OIS::MouseEvent &evt, OIS::MouseButtonID id )
{
	if(id == OIS::MB_Left)
		mouseEvent();
	return true;
}

bool CRunState::mouseReleased( const OIS::MouseEvent &evt, OIS::MouseButtonID id )
{

	return true;
}

void CRunState::Update(double timeSinceLastFrame)
{

	m_FrameEvent.timeSinceLastFrame = timeSinceLastFrame;
	COgreFramework::getSingletonPtr()->m_pTrayMgr->frameRenderingQueued(m_FrameEvent);

	if (m_bQuit == true)
	{
		Shutdown();
		return;
	}

	if(walkedud!=0||walkedlr!=0)
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
	
	_aniState->addTime(timeSinceLastFrame/1000);
	_aniStateTop->addTime(timeSinceLastFrame/1000);
	m_pCamera->move(translate*timeSinceLastFrame/20);

	_SinbadNode->translate(SinbadTranslate * timeSinceLastFrame/20);
	_SinbadNode->resetOrientation();
	_SinbadNode->yaw(Ogre::Radian(_rotation));
	if(Cubeattack==true)
	{
		if(Cubetime>0)
		{
			Cubetime--;
			_CubeNode->translate(Cubedirect * timeSinceLastFrame/300);
		}
		else
		{
			Cubeattack=false;
			_CubeNode->detachAllObjects();
		}
	}
}

void CRunState::mouseEvent()
{
	Ray mouseRay=COgreFramework::getSingletonPtr()->m_pTrayMgr->getCursorRay(m_pCamera);
	if(Cubeattack==false)
	{
		_CubeNode->setScale(0.1f,0.1f,0.1f);
		Cubedirect=(mouseRay.getPoint((mouseRay.intersects(Plane(Vector3::UNIT_Y, -5))).second)-_SinbadNode->getPosition());
		_CubeNode->setPosition(_SinbadNode->getPosition());
		_CubeNode->attachObject(_CubeEnt);
		Cubetime=100;
		Cubeattack=true;
	}
}