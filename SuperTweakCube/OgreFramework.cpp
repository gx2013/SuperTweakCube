#include "OgreFramework.h"

using namespace Ogre;

template<> COgreFramework* Ogre::Singleton<COgreFramework>::msSingleton = NULL;

COgreFramework::COgreFramework()
{
	m_pRoot = NULL;
	m_pRenderWnd = NULL;
	m_pViewport = NULL;
	m_pLog = NULL;
	m_pTimer = NULL;

	m_pInputMgr = NULL;
	m_pKeyboard = NULL;
	m_pMouse = NULL;
	m_pTrayMgr = NULL;
}

COgreFramework::~COgreFramework()
{
	COgreFramework::getSingletonPtr()->m_pLog->logMessage("Shutdown OGRE...");
	if (m_pTrayMgr)
		delete m_pTrayMgr;
	if (m_pInputMgr)
		OIS::InputManager::destroyInputSystem(m_pInputMgr);
	if (m_pRoot)
		delete m_pRoot;
}

bool COgreFramework::InitOgre(Ogre::String wndTitle, OIS::KeyListener* pKeyListener /* = 0 */, OIS::MouseListener* pMouseListener /* = 0 */)
{
	Ogre::LogManager* logMgr = new Ogre::LogManager();

	m_pLog = Ogre::LogManager::getSingleton().createLog("OgreLogfile.log", true, true, false);
	m_pLog->setDebugOutputEnabled(true);

	m_pRoot = new Ogre::Root("plugins_d.cfg");

	if (!m_pRoot->showConfigDialog())
		return false;

	m_pRenderWnd = m_pRoot->initialise(true, wndTitle);

	m_pViewport = m_pRenderWnd->addViewport(0);
	m_pViewport->setBackgroundColour(ColourValue(0.5f, 0.5f, 0.5f, 1.0f));

	m_pViewport->setCamera(0);

	size_t hWnd = 0;
	OIS::ParamList paramList;
	m_pRenderWnd->getCustomAttribute("WINDOW", &hWnd);

	paramList.insert(OIS::ParamList::value_type("WINDOW", Ogre::StringConverter::toString(hWnd)));

	m_pInputMgr = OIS::InputManager::createInputSystem(paramList);

	m_pKeyboard = static_cast<OIS::Keyboard*>(m_pInputMgr->createInputObject(OIS::OISKeyboard, true));
	m_pMouse = static_cast<OIS::Mouse*>(m_pInputMgr->createInputObject(OIS::OISMouse, true));

	m_pMouse->getMouseState().height = m_pRenderWnd->getHeight();
	m_pMouse->getMouseState().width = m_pRenderWnd->getWidth();

	if (pKeyListener == NULL)
		m_pKeyboard->setEventCallback(this);
	else
		m_pKeyboard->setEventCallback(pKeyListener);

	if (pMouseListener == NULL)
		m_pMouse->setEventCallback(this);
	else
		m_pMouse->setEventCallback(pMouseListener);

	// load resources
	Ogre::String secName, typeName, archName;
	Ogre::ConfigFile cf;
	cf.load("resources_d.cfg");

	Ogre::ConfigFile::SectionIterator seci = cf.getSectionIterator();
	while (seci.hasMoreElements())
	{
		secName = seci.peekNextKey();
		Ogre::ConfigFile::SettingsMultiMap* settings = seci.getNext();
		Ogre::ConfigFile::SettingsMultiMap::iterator i;
		for (i = settings->begin(); i != settings->end(); ++i)
		{
			typeName = i->first;
			archName = i->second;
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(archName, typeName, secName);
		}
	}
	Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);
	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

	m_pTrayMgr = new OgreBites::SdkTrayManager("OFTrayMgr", m_pRenderWnd, m_pMouse, 0);

	m_pTimer = new Ogre::Timer();
	m_pTimer->reset();

	m_pRenderWnd->setActive(true);

	return true;
}

bool COgreFramework::keyPressed(const OIS::KeyEvent& evt)
{
	if (m_pKeyboard->isKeyDown(OIS::KC_SYSRQ))
	{
		m_pRenderWnd->writeContentsToTimestampedFile("OF_Screenshot_", ".jpg");
		return true;
	}

	if (m_pKeyboard->isKeyDown(OIS::KC_0))
	{
		if (m_pTrayMgr->isLogoVisible())
		{
			m_pTrayMgr->hideFrameStats();
			m_pTrayMgr->hideLogo();
		}
		else
		{
			m_pTrayMgr->showFrameStats(OgreBites::TL_BOTTOMLEFT);
			m_pTrayMgr->showLogo(OgreBites::TL_BOTTOMRIGHT);
		}
	}

	return true;
}

bool COgreFramework::keyReleased(const OIS::KeyEvent& evt)
{
	return true;
}

bool COgreFramework::mouseMoved(const OIS::MouseEvent& evt)
{
	return true;
}

bool COgreFramework::mousePressed(const OIS::MouseEvent& evt, OIS::MouseButtonID id)
{
	return true;
}

bool COgreFramework::mouseReleased(const OIS::MouseEvent& evt, OIS::MouseButtonID id)
{
	return true;
}

void COgreFramework::UpdateOgre(double timeSinceLastFrame)
{

}