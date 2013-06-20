#include<Ogre.h>

class RunStateEnemy {
public:
	RunStateEnemy(Ogre::SceneManager* SceneMgr);
	void CreateEnemy();

private:
	Ogre::Entity* _EnemyEnt;
	Ogre::SceneNode* _EnemyNode;
	Ogre::SceneManager* m_pSceneMgr;
};