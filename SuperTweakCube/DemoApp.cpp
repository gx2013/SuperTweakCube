#include "DemoApp.h"

#include "MenuState.h"
#include "RunState.h"

CDemoApp::CDemoApp()
{
	m_pGameStateMgr = NULL;
}

CDemoApp::~CDemoApp()
{
	delete m_pGameStateMgr;
	delete COgreFramework::getSingletonPtr();
}

void CDemoApp::StartDemo()
{
	new COgreFramework();
	if (COgreFramework::getSingletonPtr()->InitOgre("GameDemo"), NULL, NULL)
		return;

	COgreFramework::getSingletonPtr()->m_pLog->logMessage("Demo Initialized");
	
	m_pGameStateMgr = new CGameStateManager();

	CMenuState::Create(m_pGameStateMgr, "MenuState");
	CRunState::Create(m_pGameStateMgr, "RunState");

	m_pGameStateMgr->Start(m_pGameStateMgr->FindByName("MenuState"));

}

