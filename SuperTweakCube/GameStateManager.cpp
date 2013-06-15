#include "GameStateManager.h"

CGameStateManager::CGameStateManager()
{
	m_bShutdown = false;
}

CGameStateManager::~CGameStateManager()
{
	SState_info si;

	while (!m_ActiveStateStack.empty())
	{
		m_ActiveStateStack.back()->Exit();
		m_ActiveStateStack.pop_back();
	}

	while (!m_States.empty())
	{
		si = m_States.back();
		si.state->destroy();
		m_States.pop_back();
	}
}

void CGameStateManager::ManageGameState(Ogre::String stateName, CGameState* state)
{
	try
	{
		SState_info new_state_info;
		new_state_info.name = stateName;
		new_state_info.state = state;
		m_States.push_back(new_state_info);
	}
	catch (std::exception& e)
	{
		delete state;
		throw Ogre::Exception(Ogre::Exception::ERR_INTERNAL_ERROR, "Error while trying to manage a new GameState\n" + Ogre::String(e.what()), "GamestateManager.cpp(38)");
	}
}

CGameState* CGameStateManager::FindByName(Ogre::String stateName)
{
	std::vector<SState_info>::iterator itr;

	for (itr = m_States.begin(); itr != m_States.end(); itr++)
	{
		if (itr->name == stateName)
			return itr->state;
	}

	return NULL;
}

void CGameStateManager::Start(CGameState* state)
{
	ChangeGameState(state);

	int timeSinceLastFrame = 1;
	int startTime = 0;

	while (!m_bShutdown)
	{
		if (COgreFramework::getSingletonPtr()->m_pRenderWnd->isClosed())
			m_bShutdown = true;

		Ogre::WindowEventUtilities::messagePump();

		if (COgreFramework::getSingletonPtr()->m_pRenderWnd->isActive())
		{
			startTime = COgreFramework::getSingletonPtr()->m_pTimer->getMillisecondsCPU();

			COgreFramework::getSingletonPtr()->m_pKeyboard->capture();
			COgreFramework::getSingletonPtr()->m_pMouse->capture();

			m_ActiveStateStack.back()->Update(timeSinceLastFrame);

			COgreFramework::getSingletonPtr()->UpdateOgre(timeSinceLastFrame);
			COgreFramework::getSingletonPtr()->m_pRoot->renderOneFrame();

			timeSinceLastFrame = COgreFramework::getSingletonPtr()->m_pTimer->getMillisecondsCPU() - startTime;
		}
		else
		{
			Sleep(1000);
		}

		COgreFramework::getSingletonPtr()->m_pLog->logMessage("Main loop quit");
	}
}

void CGameStateManager::ChangeGameState(CGameState* state)
{
	if (!m_ActiveStateStack.empty())
	{
		m_ActiveStateStack.back()->Exit();
		m_ActiveStateStack.pop_back();
	}

	m_ActiveStateStack.push_back(state);
	Init(state);
	m_ActiveStateStack.back()->Enter();
}

bool CGameStateManager::PushGameState(CGameState* state)
{
	if (!m_ActiveStateStack.empty())
	{
		if (!m_ActiveStateStack.back()->Pause())
		{
			return false;
		}
	}

	m_ActiveStateStack.push_back(state);
	Init(state);
	m_ActiveStateStack.back()->Enter();

	return true;
}

void CGameStateManager::PopGameState()
{
	if (!m_ActiveStateStack.empty())
	{
		m_ActiveStateStack.back()->Exit();
		m_ActiveStateStack.pop_back();
	}

	if (!m_ActiveStateStack.empty())
	{
		Init(m_ActiveStateStack.back());
	}
}

void CGameStateManager::PopAllAndPushGameState(CGameState* state)
{
	while (!m_ActiveStateStack.empty())
	{
		m_ActiveStateStack.back()->Exit();
		m_ActiveStateStack.pop_back();
	}

	PushGameState(state);
}

void CGameStateManager::PauseCurGameState()
{
	if (!m_ActiveStateStack.empty())
	{
		m_ActiveStateStack.back()->Pause();
	}

	if (m_ActiveStateStack.size() > 2)
	{
		Init(m_ActiveStateStack.at(m_ActiveStateStack.size() - 2));
		m_ActiveStateStack.at(m_ActiveStateStack.size() - 2)->Resume();
	}
}

void CGameStateManager::Shutdown()
{
	m_bShutdown = true;
}

void CGameStateManager::Init(CGameState* state)
{
	COgreFramework::getSingletonPtr()->m_pKeyboard->setEventCallback(state);
	COgreFramework::getSingletonPtr()->m_pMouse->setEventCallback(state);
	COgreFramework::getSingletonPtr()->m_pTrayMgr->setListener(state);

	COgreFramework::getSingletonPtr()->m_pRenderWnd->resetStatistics();
}