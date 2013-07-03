#include "RunState.h"

using namespace Ogre;

CRunState::CRunState()
{
	m_bQuit = false;
	translate=Ogre::Vector3(0,0,0);
	m_FrameEvent = Ogre::FrameEvent();
	mousewheeltime=0;
	CampivotNode = NULL;
}

void CRunState::Enter()
{
	COgreFramework::getSingletonPtr()->m_pLog->logMessage("Entering GameState...");

	m_pSceneMgr = COgreFramework::getSingletonPtr()->m_pRoot->createSceneManager(ST_GENERIC, "RunSceneMgr");
	m_pSceneMgr->setAmbientLight(Ogre::ColourValue(0.6f, 0.6f, 0.6f));

	CampivotNode = m_pSceneMgr->getRootSceneNode()->createChildSceneNode("Campivot");
	CampivotNode->setPosition(Ogre::Vector3(120.0f,2.0f,280.0f));			//摄像机支点
	m_pCamera = m_pSceneMgr->createCamera("RunCam");
	SceneNode* CamNode = CampivotNode->createChildSceneNode();
	CamNode->setPosition(Vector3(0.0f, 0.0f, 40.0f));						//摄像机相对支点位置
	CamNode->attachObject(m_pCamera);
	
	m_pCamera->setAutoTracking(true,CampivotNode);							//摄像机自动跟踪支点
	m_pCamera->setNearClipDistance(5.0f);
	m_pCamera->setFarClipDistance(20.0f);			//设定摄像机最远与最近距离
	m_pCamera->setAspectRatio(Real(COgreFramework::getSingletonPtr()->m_pViewport->getActualWidth())/
		Real(COgreFramework::getSingletonPtr()->m_pViewport->getActualHeight()));
	COgreFramework::getSingletonPtr()->m_pViewport->setCamera(m_pCamera);

	//COgreFramework::getSingletonPtr()->m_pTrayMgr->showCursor();
	COgreFramework::getSingletonPtr()->m_pTrayMgr->hideCursor();
	CreateScene();
}

void CRunState::CreateScene()
{
	//m_pSceneMgr->setSkyBox(true, "town_sky.MESH", 5000, false);			//绘制天空
	//Sky
	Ogre::Entity * sky_ent = m_pSceneMgr->createEntity("town_sky.MESH");
	Ogre::SceneNode* sky_node = m_pSceneMgr->getRootSceneNode()->createChildSceneNode("sky_node",Ogre::Vector3(0.0,0.0,0.0));
	sky_node->scale(1000,1000,1000);
	sky_node->roll(Ogre::Radian(3.14f));
	sky_node->attachObject(sky_ent);
	//m_pSceneMgr->setFog(Ogre::FOG_EXP, Ogre::ColourValue(0.5f, 0.5f, 0.5f), 0.0001,0.4f);		//fog

	Ogre::Plane plane(Vector3::UNIT_Y, -10);
	Ogre::MeshManager::getSingleton().createPlane("plane",ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, plane,1500,1500,200,200,true,1,5,5,Vector3::UNIT_Z);
	Ogre::Entity* ent = m_pSceneMgr->createEntity("GrassPlane", "plane");
	m_pSceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(ent);
	ent->setMaterialName("Examples/GrassFloor");

	/*Ogre::Light* light = m_pSceneMgr->createLight("Light100");			//设置全局光照
	light->setDiffuseColour(Ogre::ColourValue(0.5f,0.3f,0.3f));
	light->setType(Ogre::Light::LT_DIRECTIONAL);
	light->setDirection(Ogre::Vector3(1,-2,0));*/
	m_pSceneMgr->setShadowTechnique(Ogre:: SHADOWTYPE_STENCIL_ADDITIVE);

	Ogre::ManualObject* manual = m_pSceneMgr->createManualObject("grass");
	manual->begin("Examples/GrassBlades", RenderOperation::OT_TRIANGLE_LIST);

	manual->position(5.0, 0.0, 0.0); manual->textureCoord(1,1); 
	manual->position(-5.0, 10.0, 0.0); manual->textureCoord(0,0); 
	manual->position(-5.0, 0.0, 0.0); manual->textureCoord(0,1); 
	manual->position(5.0, 10.0, 0.0); manual->textureCoord(1,0); 
	manual->position(2.5, 0.0, 4.3); manual->textureCoord(1,1); 
	manual->position(-2.5, 10.0, -4.3); manual->textureCoord(0,0); 
	manual->position(-2.0, 0.0, -4.3); manual->textureCoord(0,1); 
	manual->position(2.5, 10.0, 4.3); manual->textureCoord(1,0); 
	manual->position(2.5, 0.0, -4.3); manual->textureCoord(1,1); 
	manual->position(-2.5, 10.0, 4.3); manual->textureCoord(0,0); 
	manual->position(-2.0, 0.0, 4.3); manual->textureCoord(0,1); 
	manual->position(2.5, 10.0, -4.3); manual->textureCoord(1,0);

	manual->index(0); manual->index(1); manual->index(2); manual->index(0); manual->index(3); manual->index(1);
	manual->index(4); manual->index(5); manual->index(6); manual->index(4); manual->index(7); manual->index(5); 
	manual->index(8); manual->index(9); manual->index(10); manual->index(8); manual->index(11); manual->index(9);

	manual->end();

	//Ogre::SceneNode* grassNode = m_pSceneMgr->getRootSceneNode()->createChildSceneNode("GrassNode2");
	//grassNode->attachObject(manual);

	manual->convertToMesh("BladesOfGrass");
	Ogre::StaticGeometry* field = m_pSceneMgr->createStaticGeometry("FieldOfGrass");

	for(int i=0;i<25;i++) { 
		for(int j=0;j<25;j++) {
			Ogre::Entity * ent = m_pSceneMgr->createEntity("BladesOfGrass");
			//Ogre::SceneNode* node = m_pSceneMgr->getRootSceneNode()->createChildSceneNode(Ogre::Vector3(i*3,-10,j*3));
			//node->attachObject(ent);
			field->addEntity(ent,Ogre::Vector3(i*6,-10,j*6));
		}
	}
	field->build();

	Ogre::ManualObject* manual2 = m_pSceneMgr->createManualObject("Quad");
	manual2->begin("WaterFlow", RenderOperation::OT_TRIANGLE_LIST); 

	manual2->position(20, 0.0, 0.0); manual2->textureCoord(0.0,1.0); 
	manual2->position(-20, 1500, 0.0); manual2->textureCoord(1.0,0.0); 
	manual2->position(-20, 0.0, 0.0); manual2->textureCoord(1.0,1.0); 
	manual2->position(20, 1500, 0.0); manual2->textureCoord(0.0,0.0);

	manual2->index(0); manual2->index(1); manual2->index(2); 
	manual2->index(0); manual2->index(3); manual2->index(1); 
	manual2->end();
	manual2->convertToMesh("Quad");

	Ogre::ManualObject* manual3 = m_pSceneMgr->createManualObject("SmallQuad");
	manual3->begin("DirtRoad", RenderOperation::OT_TRIANGLE_LIST); 

	manual3->position(10, 0.0, 0.0); manual3->textureCoord(0.0,1.0); 
	manual3->position(-10, 0, -20); manual3->textureCoord(1.0,0.0); 
	manual3->position(-10, 0.0, 0.0); manual3->textureCoord(1.0,1.0); 
	manual3->position(10, 0, -20); manual3->textureCoord(0.0,0.0);

	manual3->index(0); manual3->index(1); manual3->index(2); 
	manual3->index(0); manual3->index(3); manual3->index(1); 
	manual3->end();
	manual3->convertToMesh("SmallQuad");

	//River Entity
	Ogre::Entity * water_ent = m_pSceneMgr->createEntity("Quad");
	Ogre::SceneNode* water_node = m_pSceneMgr->getRootSceneNode()->createChildSceneNode("water_node",Ogre::Vector3(-70,-9.5,750));
	water_node->pitch(Ogre::Radian(-Ogre::Math::HALF_PI));
	water_node->attachObject(water_ent);

	//Dirt Entity
	/*
	Ogre::Entity * dirt_ent = m_pSceneMgr->createEntity("SmallQuad");
	Ogre::SceneNode* dirt_node = m_pSceneMgr->getRootSceneNode()->createChildSceneNode("dirt_node",Ogre::Vector3(270,5,300));
	//dirt_node->pitch(Ogre::Radian(-Ogre::Math::HALF_PI));
	//dirt_node->scale(10,10,10);
	dirt_node->attachObject(dirt_ent);
	*/

	Ogre::StaticGeometry* road = m_pSceneMgr->createStaticGeometry("road_geo");
	for(int i=0;i<2;i++) { 
		for(int j=0;j<30;j++) {
			Ogre::Entity * ent = m_pSceneMgr->createEntity("SmallQuad");
			road->addEntity(ent,Ogre::Vector3(270 + i*20,-9.5,j*20 - 240));
		}
	}
	road->build();

	Ogre::StaticGeometry* road2 = m_pSceneMgr->createStaticGeometry("road_geo2");
	for(int i=0;i<30;i++) { 
		for(int j=0;j<2;j++) {
			Ogre::Entity * ent = m_pSceneMgr->createEntity("SmallQuad");
			road2->addEntity(ent,Ogre::Vector3(i*20 - 290,-9.4,j*20 - 250));
		}
	}
	road2->build();

	//House Entitities
	Ogre::Entity* house = m_pSceneMgr->createEntity("tudorhouse","tudorhouse.mesh"); 
	Ogre::SceneNode* house_node = m_pSceneMgr->getRootSceneNode()->createChildSceneNode("house");
	house_node->setPosition(200,47,75);
	house_node->scale(0.1,0.1,0.1);
	house_node->attachObject(house);

	Ogre::Entity* house2 = m_pSceneMgr->createEntity("blacksmith_house","building_blacksmith.Mesh"); 
	Ogre::SceneNode* house_node2 = m_pSceneMgr->getRootSceneNode()->createChildSceneNode("house2");
	house_node2->setPosition(310,-9,670);
	house_node2->yaw(Ogre::Degree(15.0f)); 
	house_node2->scale(6,6,6);
	house_node2->attachObject(house2);


	Ogre::Light* light1 = m_pSceneMgr->createLight("Light1"); light1->setType(Ogre::Light::LT_POINT);
	light1->setPosition(66,2,322); light1->setDiffuseColour(1.0f,0.0f,0.0f);
	light1->setAttenuation(100,0,0.007,0);


	Ogre::Entity* house3 = m_pSceneMgr->createEntity("watchtower","building_guardtower.Mesh"); 
	Ogre::SceneNode* house_node3 = m_pSceneMgr->getRootSceneNode()->createChildSceneNode("house3");
	house_node3->yaw(Ogre::Degree(75.0f));
	house_node3->setPosition(325,-10,50);
	house_node3->scale(6,6,6);
	house_node3->attachObject(house3);

	Ogre::Light* light4 = m_pSceneMgr->createLight("Light4"); light4->setType(Ogre::Light::LT_POINT);
	light4->setPosition(0,40,-330); light4->setDiffuseColour(1.0f,0.5f,0.5f);
	light4->setAttenuation(100,0,0.007,0);

	Ogre::Entity* house4 = m_pSceneMgr->createEntity("inn","building_inn.Mesh"); 
	Ogre::SceneNode* house_node4 = m_pSceneMgr->getRootSceneNode()->createChildSceneNode("house4");
	house_node4->yaw(Ogre::Degree(45.0f));
	house_node4->setPosition(350,-10,35);
	house_node4->scale(6,6,6);
	house_node4->attachObject(house4);

	Ogre::Entity* house5 = m_pSceneMgr->createEntity("tudorhouse5","tudorhouse.mesh"); 
	Ogre::SceneNode* house_node5 = m_pSceneMgr->getRootSceneNode()->createChildSceneNode("house5");
	house_node5->setPosition(200,17,-310);
	house_node5->scale(0.05,0.05,0.05);
	house_node5->attachObject(house5);

	Ogre::Entity* house6 = m_pSceneMgr->createEntity("tudorhouse6","tudorhouse.mesh"); 
	Ogre::SceneNode* house_node6 = m_pSceneMgr->getRootSceneNode()->createChildSceneNode("house6");
	house_node6->setPosition(230,17,-310);
	house_node6->scale(0.05,0.05,0.05);
	house_node6->attachObject(house6);

	Ogre::Entity* column = m_pSceneMgr->createEntity("column","column.mesh");
	column->setMaterialName("MyMaterial8");
	Ogre::SceneNode* column_node = m_pSceneMgr->getRootSceneNode()->createChildSceneNode("column");
	column_node->setPosition(65,-5,275);
	column_node->scale(0.03,0.05,0.03);
	column_node->attachObject(column);

	Ogre::Entity* column2 = m_pSceneMgr->createEntity("column2","column.mesh");
	column2->setMaterialName("MyMaterial8");
	Ogre::SceneNode* column_node2 = m_pSceneMgr->getRootSceneNode()->createChildSceneNode("column2");
	column_node2->setPosition(35,-5,275);
	column_node2->scale(0.03,0.05,0.03);
	column_node2->attachObject(column2);

	Ogre::Entity* column3 = m_pSceneMgr->createEntity("column3","column.mesh");
	column3->setMaterialName("MyMaterial8");
	Ogre::SceneNode* column_node3 = m_pSceneMgr->getRootSceneNode()->createChildSceneNode("column3");
	column_node3->setPosition(65,-5,255);
	column_node3->scale(0.03,0.05,0.03);
	column_node3->attachObject(column3);

	Ogre::Entity* column4 = m_pSceneMgr->createEntity("column4","column.mesh");
	column4->setMaterialName("MyMaterial8");
	Ogre::SceneNode* column_node4 = m_pSceneMgr->getRootSceneNode()->createChildSceneNode("column4");
	column_node4->setPosition(35,-5,255);
	column_node4->scale(0.03,0.05,0.03);
	column_node4->attachObject(column4);

	Ogre::Entity* column5 = m_pSceneMgr->createEntity("column5","column.mesh");
	column5->setMaterialName("MyMaterial8");
	Ogre::SceneNode* column_node5 = m_pSceneMgr->getRootSceneNode()->createChildSceneNode("column5");
	column_node5->setPosition(55,-9,233);
	column_node5->roll(Ogre::Degree(90.0f));
	column_node5->scale(0.03,0.05,0.03);
	column_node5->attachObject(column5);

	Ogre::Entity* column6 = m_pSceneMgr->createEntity("column6","column.mesh");
	column6->setMaterialName("MyMaterial8");
	Ogre::SceneNode* column_node6 = m_pSceneMgr->getRootSceneNode()->createChildSceneNode("column6");
	column_node6->setPosition(55,-9,232);
	column_node6->roll(Ogre::Degree(90.0f));
	column_node6->scale(0.03,0.05,0.03);
	column_node6->attachObject(column6);

	Ogre::Entity* column7 = m_pSceneMgr->createEntity("column7","column.mesh");
	column7->setMaterialName("MyMaterial8");
	Ogre::SceneNode* column_node7 = m_pSceneMgr->getRootSceneNode()->createChildSceneNode("column7");
	column_node7->setPosition(55,-8,232.5);
	column_node7->roll(Ogre::Degree(90.0f));
	column_node7->scale(0.03,0.05,0.03);
	column_node7->attachObject(column7);

	//for(int i=-3;i<55;i++) {
		//South Fence
		Ogre::Entity * isouth_fence_ent = m_pSceneMgr->createEntity("WoodPallet.mesh");
		Ogre::SceneNode* isouth_fence_node = m_pSceneMgr->getRootSceneNode()->createChildSceneNode("south_fence2",Ogre::Vector3(114.0f,-8.0f,175.0f));
		isouth_fence_node->pitch(Ogre::Radian(Ogre::Math::HALF_PI)); 
		isouth_fence_node->scale(35,0.5,2.5);
		isouth_fence_node->attachObject(isouth_fence_ent);

		//North Fence
		Ogre::Entity * inorth_fence_ent = m_pSceneMgr->createEntity("WoodPallet.mesh");
		Ogre::SceneNode* inorth_fence_node = m_pSceneMgr->getRootSceneNode()->createChildSceneNode("north_fence2",Ogre::Vector3(114.0f,-8.0f,-10.0f));
		inorth_fence_node->pitch(Ogre::Radian(-(Ogre::Math::HALF_PI)));
		inorth_fence_node->scale(35,0.5,2.5);
		inorth_fence_node->attachObject(inorth_fence_ent);
	//}

	//for(int i=-2;i<56;i++)	{
		//West Fence
		Ogre::Entity * iwest_fence_ent = m_pSceneMgr->createEntity("WoodPallet.mesh");
		Ogre::SceneNode* iwest_fence_node = m_pSceneMgr->getRootSceneNode()->createChildSceneNode("west_fence2",Ogre::Vector3(240.0f,-8.0f,68.0f));
		iwest_fence_node->pitch(-(Ogre::Radian(Ogre::Math::HALF_PI)));
		iwest_fence_node->roll(Ogre::Radian(Ogre::Math::HALF_PI)); 
		iwest_fence_node->scale(20,0.5,2.5);
		iwest_fence_node->attachObject(iwest_fence_ent);

		//East Fence
		//if(i < 25 || i > 29)
		//{
			Ogre::Entity * ieast_fence_ent = m_pSceneMgr->createEntity("WoodPallet.mesh");
			Ogre::SceneNode* ieast_fence_node = m_pSceneMgr->getRootSceneNode()->createChildSceneNode("east_fence2",Ogre::Vector3(-15,-8,85.0f));
			ieast_fence_node->pitch(Ogre::Radian(Ogre::Math::HALF_PI));
			ieast_fence_node->roll(Ogre::Radian(Ogre::Math::HALF_PI)); 
			ieast_fence_node->scale(27,0.5,2.5);
			ieast_fence_node->attachObject(ieast_fence_ent);
		//}
	//}

	//Outer Fences
	Ogre::Entity * north_fence_ent = m_pSceneMgr->createEntity("WoodPallet.mesh");
	Ogre::SceneNode* north_fence_node = m_pSceneMgr->getRootSceneNode()->createChildSceneNode("north_fence",Ogre::Vector3(160,-8,-375));
	north_fence_node->pitch(Ogre::Radian(Ogre::Math::HALF_PI)); 
	north_fence_node->scale(71,0.5,2.5);
	north_fence_node->attachObject(north_fence_ent);

	Ogre::Entity * south_fence_ent = m_pSceneMgr->createEntity("WoodPallet.mesh");
	Ogre::SceneNode* south_fence_node = m_pSceneMgr->getRootSceneNode()->createChildSceneNode("south_fence",Ogre::Vector3(100,-8,375));
	south_fence_node->pitch(Ogre::Radian(Ogre::Math::HALF_PI)); 
	south_fence_node->scale(55,0.5,2.5);
	south_fence_node->attachObject(south_fence_ent);

	Ogre::Entity * east_fence_ent = m_pSceneMgr->createEntity("WoodPallet.mesh");
	Ogre::SceneNode* east_fence_node = m_pSceneMgr->getRootSceneNode()->createChildSceneNode("east_fence",Ogre::Vector3(410,-8,0));
	east_fence_node->pitch(Ogre::Radian(Ogre::Math::HALF_PI));
	east_fence_node->roll(Ogre::Radian(Ogre::Math::HALF_PI));
	east_fence_node->scale(105,0.5,2.5);
	east_fence_node->attachObject(east_fence_ent);

	Ogre::Entity * west_fence_ent = m_pSceneMgr->createEntity("WoodPallet.mesh");
	Ogre::SceneNode* west_fence_node = m_pSceneMgr->getRootSceneNode()->createChildSceneNode("west_fence",Ogre::Vector3(-98,-8,82));
	west_fence_node->pitch(Ogre::Radian(Ogre::Math::HALF_PI));
	west_fence_node->roll(Ogre::Radian(Ogre::Math::HALF_PI));
	west_fence_node->scale(83,0.5,2.5);
	west_fence_node->attachObject(west_fence_ent);

	Ogre::Entity * swest_fence_ent = m_pSceneMgr->createEntity("WoodPallet.mesh");
	Ogre::SceneNode* swest_fence_node = m_pSceneMgr->getRootSceneNode()->createChildSceneNode("swest_fence",Ogre::Vector3(-98,-8,-325));
	swest_fence_node->pitch(Ogre::Radian(Ogre::Math::HALF_PI));
	swest_fence_node->roll(Ogre::Radian(Ogre::Math::HALF_PI));
	swest_fence_node->scale(15,0.5,2.5);
	swest_fence_node->attachObject(swest_fence_ent);

	Ogre::Entity * Blacksmith_ent = m_pSceneMgr->createEntity("Blacksmith.Mesh");
	Ogre::SceneNode* Blacksmith_node = m_pSceneMgr->getRootSceneNode()->createChildSceneNode("blacksmith",Ogre::Vector3(85,-10,325));
	Blacksmith_node->scale(6,6,6);
	Blacksmith_node->yaw(Ogre::Radian(Ogre::Math::HALF_PI));
	Blacksmith_node->attachObject(Blacksmith_ent);
	_aniStateNPC =Blacksmith_ent->getAnimationState("Idle");
	_aniStateNPC->setEnabled(true);
	_aniStateNPC->setLoop(true);

	Ogre::Entity * town_center_ent = m_pSceneMgr->createEntity("collision_towncenter.Mesh");
	Ogre::SceneNode* town_center_node = m_pSceneMgr->getRootSceneNode()->createChildSceneNode("town_center",Ogre::Vector3(350,-10,-100));
	town_center_node->scale(4,4,4);
	town_center_node->yaw(Ogre::Radian(Ogre::Math::HALF_PI));
	town_center_node->attachObject(town_center_ent);

	Ogre::Entity * lamp_ent = m_pSceneMgr->createEntity("object_lampposts08.Mesh");
	Ogre::SceneNode* lamp_node = m_pSceneMgr->getRootSceneNode()->createChildSceneNode("lamp",Ogre::Vector3(300,-10,-75));
	lamp_node->scale(6,6,6);
	lamp_node->yaw(Ogre::Radian(Ogre::Math::HALF_PI));
	lamp_node->attachObject(lamp_ent);

	Ogre::Light* light2 = m_pSceneMgr->createLight("Light2"); light2->setType(Ogre::Light::LT_POINT);
	light2->setPosition(27,10,-55); light2->setDiffuseColour(0.5f,0.5f,0.5f);
	light2->setAttenuation(100,0,0.007,0);

	Ogre::Entity * lamp_ent2 = m_pSceneMgr->createEntity("object_lampposts08.Mesh");
	Ogre::SceneNode* lamp_node2 = m_pSceneMgr->getRootSceneNode()->createChildSceneNode("lamp2",Ogre::Vector3(300,-10,-164));
	lamp_node2->scale(6,6,6);
	lamp_node2->yaw(Ogre::Radian(Ogre::Math::HALF_PI));
	lamp_node2->attachObject(lamp_ent2);

	Ogre::Light* light3 = m_pSceneMgr->createLight("Light3"); light3->setType(Ogre::Light::LT_POINT);
	light3->setPosition(27,10,-145); light3->setDiffuseColour(0.5f,0.5f,0.5f);
	light3->setAttenuation(100,0,0.007,0);

	Ogre::Entity * gem_ent = m_pSceneMgr->createEntity("gems.Mesh");
	Ogre::SceneNode* gem_node = m_pSceneMgr->getRootSceneNode()->createChildSceneNode("gem",Ogre::Vector3(0,-30,500));
	gem_node->scale(15,15,15);
	gem_node->attachObject(gem_ent);

	Ogre::Light* light5 = m_pSceneMgr->createLight("Light5"); light5->setType(Ogre::Light::LT_POINT);
	light5->setPosition(-330,5,-338); light5->setDiffuseColour(0.0f,0.0f,1.0f);
	light5->setAttenuation(100,0,0.007,0);

	Ogre::Entity * gem_ent2 = m_pSceneMgr->createEntity("gems.Mesh");
	Ogre::SceneNode* gem_node2 = m_pSceneMgr->getRootSceneNode()->createChildSceneNode("gem2",Ogre::Vector3(250,-30,-475));
	gem_node2->scale(15,15,15);
	gem_node2->yaw(Ogre::Degree(90.0f));
	gem_node2->attachObject(gem_ent2);

	Ogre::Light* light6 = m_pSceneMgr->createLight("Light6"); light6->setType(Ogre::Light::LT_POINT);
	light6->setPosition(-595,5,-145); light6->setDiffuseColour(0.0f,0.0f,1.0f);
	light6->setAttenuation(100,0,0.007,0);

	Ogre::Entity * gem_ent3 = m_pSceneMgr->createEntity("gems.Mesh");
	Ogre::SceneNode* gem_node3 = m_pSceneMgr->getRootSceneNode()->createChildSceneNode("gem3",Ogre::Vector3(150,-30,800));
	gem_node3->scale(15,15,15);
	gem_node3->attachObject(gem_ent3);

	Ogre::Light* light7 = m_pSceneMgr->createLight("Light7"); light7->setType(Ogre::Light::LT_POINT);
	light7->setPosition(-190,5,-50); light7->setDiffuseColour(0.0f,0.0f,1.0f);
	light7->setAttenuation(100,0,0.007,0);

	Ogre::Entity * gem_ent4 = m_pSceneMgr->createEntity("gems.Mesh");
	Ogre::SceneNode* gem_node4 = m_pSceneMgr->getRootSceneNode()->createChildSceneNode("gem4",Ogre::Vector3(375,-30,-225));
	gem_node4->scale(15,15,15);
	gem_node4->yaw(Ogre::Degree(90.0f));
	gem_node4->attachObject(gem_ent4);

	Ogre::Light* light8 = m_pSceneMgr->createLight("Light8"); light8->setType(Ogre::Light::LT_POINT);
	light8->setPosition(-465,5,100); light8->setDiffuseColour(0.0f,0.0f,1.0f);
	light8->setAttenuation(100,0,0.007,0);

	Ogre::Entity * gem_ent5 = m_pSceneMgr->createEntity("gems.Mesh");
	Ogre::SceneNode* gem_node5 = m_pSceneMgr->getRootSceneNode()->createChildSceneNode("gem5",Ogre::Vector3(600,-30,-100));
	gem_node5->scale(15,15,15);
	gem_node5->yaw(Ogre::Degree(90.0f));
	gem_node5->attachObject(gem_ent5);

	Ogre::Light* light9 = m_pSceneMgr->createLight("Light9"); light8->setType(Ogre::Light::LT_POINT);
	light9->setPosition(-250,5,225); light9->setDiffuseColour(0.0f,0.0f,1.0f);
	light9->setAttenuation(100,0,0.007,0);

	Ogre::Entity * gem_ent6 = m_pSceneMgr->createEntity("gems.Mesh");
	Ogre::SceneNode* gem_node6 = m_pSceneMgr->getRootSceneNode()->createChildSceneNode("gem6",Ogre::Vector3(-10,-30,1375));
	gem_node6->scale(15,15,15);
	gem_node6->attachObject(gem_ent6);

	Ogre::Light* light10 = m_pSceneMgr->createLight("Light10"); light10->setType(Ogre::Light::LT_POINT);
	light10->setPosition(-350,5,525); light10->setDiffuseColour(0.0f,0.0f,1.0f);
	light10->setAttenuation(100,0,0.007,0);

	player = new Player(m_pSceneMgr,m_pCamera);			//创建人物

	Enemy[0]=new RunStateEnemy(m_pSceneMgr,m_pCamera,Ogre::Vector3(-140.0f,-10.0f,-40.0f));
	Enemy[0]->Create(player);
	Enemy[1]=new RunStateEnemy(m_pSceneMgr,m_pCamera,Ogre::Vector3(-200.0f,-10.0f,-200.0f));
	Enemy[1]->Create(player);
	Enemy[2]=new RunStateEnemy(m_pSceneMgr,m_pCamera,Ogre::Vector3(-320.0f,-10.0f,-120.0f));
	Enemy[2]->Create(player);					//创建怪物
	createoverlay();							//创建界面
}

void CRunState::Exit()
{
	COgreFramework::getSingletonPtr()->m_pLog->logMessage("Leaving MenuState...");

	m_pSceneMgr->destroyCamera(m_pCamera);

	if (m_pSceneMgr)
		COgreFramework::getSingletonPtr()->m_pRoot->destroySceneManager(m_pSceneMgr);
}

bool CRunState::Pause()
{
	return true;
}

void CRunState::Resume()
{

}

bool CRunState::keyPressed(const OIS::KeyEvent &evt)
{
	
	if (evt.key==OIS::KC_ESCAPE)
	{
		m_bQuit = true;
		return true;
	}
	if(evt.key==OIS::KC_W)
	{
		translate += Ogre::Vector3(0,0,-1);		//摄像机移动方向
	}
	if(evt.key==OIS::KC_S)
	{
		translate += Ogre::Vector3(0,0,1);

	}
	if(evt.key==OIS::KC_A)
	{
		translate += Ogre::Vector3(-1,0,0);
	}
	if(evt.key==OIS::KC_D)
	{
		translate += Ogre::Vector3(1,0,0);
	}
	player->keyPressed(evt);
	COgreFramework::getSingletonPtr()->keyPressed(evt);

	return true;
}

bool CRunState::keyReleased(const OIS::KeyEvent &evt)
{
	if(evt.key==OIS::KC_W)
	{
		translate -= Ogre::Vector3(0,0,-1);
	}
	if(evt.key==OIS::KC_S)
	{
		translate -= Ogre::Vector3(0,0,1);
	}
	if(evt.key==OIS::KC_A)
	{
		translate -= Ogre::Vector3(-1,0,0);
	}
	if(evt.key==OIS::KC_D)
	{
		translate -= Ogre::Vector3(1,0,0);
	}
	player->keyReleased(evt);
	COgreFramework::getSingletonPtr()->keyPressed(evt);
	return true;
}

bool CRunState::mouseMoved(const OIS::MouseEvent &evt)
{
	COgreFramework::getSingletonPtr()->m_pTrayMgr->injectMouseMove(evt);
	mousewheeltime+=evt.state.Z.rel*0.05;			//滚动时间
	float rotX = evt.state.X.rel * -1;
	float rotY = evt.state.Y.rel * -1;
	CampivotNode->yaw(Ogre::Radian(rotX)/300);		//转动摄像机支点
	CampivotNode->pitch(Ogre::Radian(rotY)/300);
	
	return true;
}

bool CRunState::mousePressed( const OIS::MouseEvent &evt, OIS::MouseButtonID id )
{
	player->mousePressed(id);
	return true;
}

bool CRunState::mouseReleased( const OIS::MouseEvent &evt, OIS::MouseButtonID id )
{

	return true;
}

void CRunState::Update(double timeSinceLastFrame)
{

	m_FrameEvent.timeSinceLastFrame = timeSinceLastFrame;
	COgreFramework::getSingletonPtr()->m_pTrayMgr->frameRenderingQueued(m_FrameEvent);

	m_pSceneMgr->getSceneNode("sky_node")->yaw(timeSinceLastFrame*Ogre::Radian(0.00001f));				//天空旋转

	if (m_bQuit == true)
	{
		Shutdown();
		return;
	}
	player->addTime(timeSinceLastFrame);
	_aniStateNPC->addTime(timeSinceLastFrame/1000);
	for(int i=0;i<3;i++)
		Enemy[i]->addTime(timeSinceLastFrame);
	//_newaniState->addTime(timeSinceLastFrame/1000);
	//CampivotNode->translate(translate*timeSinceLastFrame/30);
	CampivotNode->setPosition(m_pSceneMgr->getSceneNode("PNode")->getPosition()+Ogre::Vector3(0.0f,5.0f,0.0f));
	if(mousewheeltime>0)
	{
		m_pCamera->moveRelative(Ogre::Vector3(0,0,-0.1f)*timeSinceLastFrame);//根据滚轮向父坐标系的z轴移动
		mousewheeltime--;
	}
	else if(mousewheeltime<0)
	{
		m_pCamera->moveRelative(Ogre::Vector3(0,0,0.1f)*timeSinceLastFrame);//根据滚轮向父坐标系的z轴移动
		mousewheeltime++;
	}
	scaleoverlay();

	/*if (player->Health  == 0)
	{
		OverlayManager::getSingleton().destroyAllOverlayElements();
		ChangeGameState(FindByName("MenuState"));
	}*/
}

//overlay
void CRunState::createoverlay(){	
	mOverlay = OverlayManager::getSingleton().create("borderoverlay");
	mpicture = OverlayManager::getSingleton().createOverlayElement("Panel","border");
	mOverlay->setZOrder(200);
	mpicture->setParameter("metrics_mode","pixels");
	mpicture->setParameter("left","150");
	mpicture->setParameter("top","440");
	mpicture->setParameter("width","400");
	mpicture->setParameter("height","144");
	mpicture->setMaterialName("overlay/border");
	mOverlay->add2D((OverlayContainer*)mpicture);
	mOverlay->show();
	//blood
	bOverlay = OverlayManager::getSingleton().create("bloodoverlay");
	bOverlay->setZOrder(100);
	bpicture = OverlayManager::getSingleton().createOverlayElement("Panel","blood");
	bpicture->setParameter("metrics_mode","pixels");
	bpicture->setParameter("left","260");
	bpicture->setParameter("top","520");
	bpicture->setParameter("width","280");
	bpicture->setParameter("height","25");
	bpicture->setMaterialName("overlay/blood");
	bOverlay->add2D((OverlayContainer*)bpicture);
	bOverlay->show();
	//bg
	gOverlay = OverlayManager::getSingleton().create("bgoverlay");
	gOverlay->setZOrder(50);
	gpicture = OverlayManager::getSingleton().createOverlayElement("Panel","bg");
	gpicture->setParameter("metrics_mode","pixels");
	gpicture->setParameter("left","260");
	gpicture->setParameter("top","520");
	gpicture->setParameter("width","280");
	gpicture->setParameter("height","25");
	gpicture->setMaterialName("overlay/bg");
	gOverlay->add2D((OverlayContainer*)gpicture);
	gOverlay->show();
	
}
//overlay scale
void  CRunState::scaleoverlay(){
		bOverlay->setScale(player->Health*1.0/100,1);
}