/********************************************************************
	created:	2012/02/27
	created:	27:2:2012   15:44
	filename: 	E:\Ogre\Project\Ogre_Project\Game_Demo\RunState.h
	file path:	E:\Ogre\Project\Ogre_Project\Game_Demo
	file base:	RunState
	file ext:	h
	author:		Star
	
	purpose:	run state of game
*********************************************************************/

#include "GameState.h"
#include "RunStateEnemy.h"
#include "Player.h"

class CRunState : public CGameState
{
public:
	CRunState();
	Ogre::Overlay* mOverlay;
	Ogre::Overlay* bOverlay;
	Ogre::Overlay* gOverlay;
	Ogre::OverlayElement* mpicture;
	Ogre::OverlayElement* bpicture;
	Ogre::OverlayElement* gpicture;

	DECLARE_GAMESTATE_CLASS(CRunState)

	void Enter();
	void CreateScene();
	void Exit();
	bool Pause();
	void Resume();

	bool keyPressed(const OIS::KeyEvent &evt);
	bool keyReleased(const OIS::KeyEvent &evt);

	bool mouseMoved( const OIS::MouseEvent &evt);
	bool mousePressed( const OIS::MouseEvent &evt, OIS::MouseButtonID id );
	bool mouseReleased( const OIS::MouseEvent &evt, OIS::MouseButtonID id );

	void Update(double timeSinceLastFrame);

	void createoverlay();
	void scaleoverlay();
private:
	bool m_bQuit;
	Ogre::Vector3 translate;
	RunStateEnemy* Enemy[3];
	Player* player;
	Ogre::SceneNode* CampivotNode;
	int mousewheeltime;			//鼠标滚轮滚动时间
	Ogre::AnimationState* _aniStateNPC;
};