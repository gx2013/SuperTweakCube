#include"RunStateEnemy.h"

RunStateEnemy::RunStateEnemy(Ogre::SceneManager* m_pSceneMgr)
{
	this->m_pSceneMgr = m_pSceneMgr;
}

void RunStateEnemy::CreateEnemy()
{
	Ogre::SceneNode* node = m_pSceneMgr->createSceneNode("NodeE");
	_EnemyEnt = m_pSceneMgr->createEntity("Enemy","Sinbad.mesh");
	_EnemyNode = node->createChildSceneNode("EnemyNode");
	_EnemyNode->setScale(3.0f,3.0f,3.0f);
	_EnemyNode->setPosition(Ogre::Vector3(0.0f,4.0f,0.0f));
	_EnemyNode->attachObject(_EnemyEnt);
}