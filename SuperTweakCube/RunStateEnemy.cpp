#include"RunStateEnemy.h"

RunStateEnemy::RunStateEnemy(Ogre::SceneManager* SceneMgr)
{
	m_pSceneMgr=SceneMgr;
}

void RunStateEnemy::CreateEnemy()
{

	_EnemyEnt = m_pSceneMgr->createEntity("Enemy","sinbad.mesh");
	_EnemyNode = m_pSceneMgr->createSceneNode("ENode");
	m_pSceneMgr->getRootSceneNode()->addChild(_EnemyNode);
	_EnemyNode->setScale(3.0f,3.0f,3.0f);
	_EnemyNode->setPosition(Ogre::Vector3(10.0f,4.0f,0.0f));
	_EnemyNode->attachObject(_EnemyEnt);
}