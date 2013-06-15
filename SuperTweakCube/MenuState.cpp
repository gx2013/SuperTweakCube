#include "MenuState.h"

using namespace Ogre;

CMenuState::CMenuState()
{
	m_bQuit = false;
	m_FrameEvent = Ogre::FrameEvent();
}

void CMenuState::Enter()
{
	Ogre::FontManager::getSingleton().getByName("SdkTrays/Caption")->load();
	COgreFramework::getSingletonPtr()->m_pLog->logMessage("Entering MenuState.h.");

	m_pSceneMgr = COgreFramework::getSingletonPtr()->m_pRoot->createSceneManager(ST_GENERIC, "MenuSceneMgr");
	m_pSceneMgr->setAmbientLight(Ogre::ColourValue(0.7f, 0.7f, 0.7f));

	m_pCamera = m_pSceneMgr->createCamera("MenuCam");
	m_pCamera->setPosition(Vector3(0, 25, -50));
	m_pCamera->lookAt(Vector3(0, 0, 0));
	m_pCamera->setNearClipDistance(1);

	m_pCamera->setAspectRatio(Real(COgreFramework::getSingletonPtr()->m_pViewport->getActualWidth())/
		Real(COgreFramework::getSingletonPtr()->m_pViewport->getActualHeight()));

	COgreFramework::getSingletonPtr()->m_pViewport->setCamera(m_pCamera);

	COgreFramework::getSingletonPtr()->m_pTrayMgr->destroyAllWidgets();
	COgreFramework::getSingletonPtr()->m_pTrayMgr->showFrameStats(OgreBites::TL_BOTTOMLEFT);
	COgreFramework::getSingletonPtr()->m_pTrayMgr->showLogo(OgreBites::TL_BOTTOMRIGHT);
	COgreFramework::getSingletonPtr()->m_pTrayMgr->showCursor();
	COgreFramework::getSingletonPtr()->m_pTrayMgr->createButton(OgreBites::TL_CENTER, "EnterBtn", "Enter GameState", 250);
	COgreFramework::getSingletonPtr()->m_pTrayMgr->createButton(OgreBites::TL_CENTER, "ExitBtn", "Exit OgreFramework", 250);
	COgreFramework::getSingletonPtr()->m_pTrayMgr->createLabel(OgreBites::TL_TOP, "MenuLbl","Menu mode", 250);

	CreateScene();
}

void CMenuState::CreateScene()
{

}

void CMenuState::Exit()
{
	COgreFramework::getSingletonPtr()->m_pLog->logMessage("Leaving MenuState...");

	m_pSceneMgr->destroyCamera(m_pCamera);

	if (m_pSceneMgr)
		COgreFramework::getSingletonPtr()->m_pRoot->destroySceneManager(m_pSceneMgr);

	COgreFramework::getSingletonPtr()->m_pTrayMgr->clearAllTrays();
	COgreFramework::getSingletonPtr()->m_pTrayMgr->destroyAllWidgets();
	COgreFramework::getSingletonPtr()->m_pTrayMgr->setListener(NULL);
}

bool CMenuState::keyPressed(const OIS::KeyEvent &evt)
{
	if (COgreFramework::getSingletonPtr()->m_pKeyboard->isKeyDown(OIS::KC_ESCAPE))
	{
		m_bQuit = true;
		return true;
	}

	COgreFramework::getSingletonPtr()->keyPressed(evt);

	return true;
}

bool CMenuState::keyReleased(const OIS::KeyEvent &evt)
{
	COgreFramework::getSingletonPtr()->keyReleased(evt);

	return true;
}

bool CMenuState::mouseMoved(const OIS::MouseEvent &evt)
{
	if (COgreFramework::getSingletonPtr()->m_pTrayMgr->injectMouseMove(evt))
		return true;

	return true;
}

bool CMenuState::mousePressed( const OIS::MouseEvent &evt, OIS::MouseButtonID id )
{
	if (COgreFramework::getSingletonPtr()->m_pTrayMgr->injectMouseDown(evt, id))
		return true;

	return true;
}

bool CMenuState::mouseReleased( const OIS::MouseEvent &evt, OIS::MouseButtonID id )
{
	if (COgreFramework::getSingleton().m_pTrayMgr->injectMouseUp(evt, id))
		return true;

	return true;
}

void CMenuState::Update(double timeSinceLastFrame)
{
	m_FrameEvent.timeSinceLastFrame = timeSinceLastFrame;
	COgreFramework::getSingletonPtr()->m_pTrayMgr->frameRenderingQueued(m_FrameEvent);

	if (m_bQuit == true)
	{
		Shutdown();
		return;
	}
}

void CMenuState::buttonHit(OgreBites::Button* button)
{
	if (button->getName() == "ExitBtn")
		m_bQuit = true;
	else if (button->getName() == "EnterBtn")
		ChangeGameState(FindByName("RunState"));
}