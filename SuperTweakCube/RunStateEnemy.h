#include<Ogre.h>

class RunStateEnemy {
public:
	RunStateEnemy(Ogre::SceneManager* m_pSceneMgr);
	void CreateEnemy();

private:
	Ogre::SceneManager* m_pSceneMgr;
	Ogre::Entity* _EnemyEnt;
	Ogre::SceneNode* _EnemyNode;
};