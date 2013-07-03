
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