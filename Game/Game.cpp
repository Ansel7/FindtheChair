#include "Game.h"

Game::Game(void){
}

int Game::run(){

	device = createDevice( video::EDT_DIRECT3D9, 
	core::dimension2d<u32>(800, 600));

	if(device == 0)return 1;//could not create device driver.

	device->setWindowCaption(L"Pancakes");
	device->setResizable(true);

	engine = createIrrKlangDevice();
	driver = device->getVideoDriver();
	smgr = device->getSceneManager();
	guienv = device->getGUIEnvironment();

	MMenu menu(device);
	Overlay hud(device);
	Objective fridge(device);
	EventReceiver receiver;
	
	device->setEventReceiver(&receiver);
	gamePaused = false;
	gameOver = false;
	main_menu = true;
	been_default = false;
	instruc_menu = false;

	node = 0;

	int lastplay = 1001;
	bool pauseplay = false;
	bool pUp_flag = false;
	bool pDown_flag = false;
	bool action_flag = false;
	bool list_flag = false;
	int wol_flag = 0;

	material.setTexture(0,0);
	material.Lighting = false;

	sound_init(device);
	background_music("01 - Menu Theme.mp3");

	highlightedSceneNode = 0;

	device->getFileSystem()->addZipFileArchive("cod_map.pk3");

	while(device->run())

		if(device->isWindowActive()){
//---------------------------------------------------------------------------------
			//quick exit for debugging
			/*if(receiver.isKeyDown(KEY_ESCAPE)){
				sound_shutdown();
				return 0;
			}*/
//---------------------------------------------------------------------------------
			//check for win
			if(hud.getScore() >= 10 && !gameOver){
				engine->play2D("victory.ogg");//victory song
				background_music("");
				wol_flag = 1;
				gameOver = true;
			}
//---------------------------------------------------------------------------------
			//check hud timer
			if(hud.getTime() <= 0 && !gameOver){
				engine->play2D("menu_cancel(1).mp3");
				wol_flag = 0;
				gameOver = true;
			}
//---------------------------------------------------------------------------------
			if(receiver.isKeyDown(KEY_KEY_Q) && (gamePaused || gameOver)){
				 if(!list_flag)
				switch(hud.return_selected()){
                case 0:
						engine->stopAllSounds();
						background_music("06 - Demolition Soviet Holdline.mp3");
						//engine->play2D("rain.mp3", true);
						engine->play2D("menu3.wav");
						fridge.setNewSpawnPoint();
						hud.setScore(0);
						hud.setTime(30);
						gamePaused = false;
						gameOver = false;
						list_flag = true;
                        break;
                case 1:
						return 0;
                        break;
                }
			}else{
				list_flag = false;
			}
//---------------------------------------------------------------------------------
			//pause menu button
			if(receiver.isKeyDown(irr::KEY_TAB) && (gamePaused || gameOver || !gamePaused) && !main_menu){

				if(!pauseplay){

					engine->play2D("menu_ready(1).mp3");

					if(gamePaused)
						gamePaused = false;
					else
						gamePaused = true;

					pauseplay = true;

				}
				
			}else{
				pauseplay = false;
			}
//------------------------------------------------------------------------------
			//pause menu controlls
			//move up the pause menu list
			if(receiver.isKeyDown(KEY_UP) && (gamePaused ||gameOver)){
				if(!pUp_flag){
					engine->play2D("cursor_move(1).mp3");
					hud.move_select_up();
					pUp_flag = true;
				}
			}else{
				pUp_flag = false;
			}
//------------------------------------------------------------------------------
			//move down the pause menu list
			if(receiver.isKeyDown(KEY_DOWN) && (gamePaused ||gameOver)){
				if(!pDown_flag){
					engine->play2D("cursor_move(1).mp3");
					hud.move_select_down();
					pDown_flag = true;
				}
			}else{
				pDown_flag = false;
			}
//-----------------------------------------------------------------------------
			//action button
			if(receiver.isKeyDown(irr::KEY_KEY_E) && (gamePaused || !gamePaused) && !gameOver){
				if(!action_flag && highlightedSceneNode){
					engine->play2D("menu_ok(1).mp3");
					hud.setScore(hud.getScore() + 1);
					hud.setTime(30);
					fridge.setNewSpawnPoint();
					action_flag = true;
				}
			}else{
				action_flag = false;
			}
//----------------------------------------------------------------------------
			//start button
			if(receiver.isButtonPressed(MMenu::START_BUTTON)){
				
				engine->play2D("menu_sound(1).mp3");
				background_music("06 - Demolition Soviet Holdline.mp3");
				//engine->play2D("rain.mp3", true);
				engine->play2D("findthechair.wav");
				menu.remove();
				main_menu = false;
				fridge.drawObjective();
				loadMap();
				receiver.resetButtons();
			}
//--------------------------------------------------------------------------
			//instruction button
			if(receiver.isButtonPressed(MMenu::INSTRUCTIONS_BUTTON)){

				engine->play2D("menu_sound(1).mp3");
				menu.remove();
				main_menu = false;
				instruc_menu = true;
				receiver.resetButtons();
			}
//-------------------------------------------------------------------------		
			//back to main menu button
			//!(only when you are at the instructions screen)!
			if(receiver.isButtonPressed(MMenu::BACK_TO_MAIN_BUTTON)){

				engine->play2D("menu_sound(1).mp3");
				menu.remove();
				main_menu = true;
				instruc_menu = false;
				receiver.resetButtons();
			}
//-------------------------------------------------------------------------
			//space bar(jump)
			if(receiver.isKeyDown(KEY_SPACE) && lastplay > 1000){
				engine->play2D("jump1.mp3");
				lastplay = 0;
			}else if(receiver.isKeyDown(KEY_SPACE)){
				lastplay++;
			}else{
				lastplay = 1001;
			}
//------------------------------------------------------------------------
			//quit button
			if(receiver.isButtonPressed(MMenu::QUIT_BUTTON)){
				return 0;
			}
			
			if(main_menu){
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				//Main Menu     //
				//////////////////
				driver->beginScene(true, true, 
					video::SColor(255, 255, 255, 255));

				menu.Display();
				smgr->drawAll();
				guienv->drawAll();

				driver->endScene();

			}else if(!main_menu && instruc_menu){
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				//Instruction Menu //
				/////////////////////
				driver->beginScene(true, true, 
					video::SColor(255, 255, 255, 255));

				menu.instructions_display();
				smgr->drawAll();
				guienv->drawAll();

				driver->endScene();

			}else if(!gamePaused && !gameOver){
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				//Game Screen  //
				//////////////////
				driver->beginScene(true, true, 
					0);


				if (highlightedSceneNode)
                {
						highlightedSceneNode->setMaterialFlag(video::EMF_LIGHTING, true);
                        highlightedSceneNode = 0;
                }

				core::line3d<f32> ray;
                ray.start = camera->getPosition();
                ray.end = ray.start + (camera->getTarget() - ray.start).normalize() * 1000.0f;
				
                core::vector3df intersection;
                core::triangle3df hitTriangle;

				scene::ISceneNode * selectedSceneNode =
				collMan->getSceneNodeAndCollisionPointFromRay(
						ray, intersection, hitTriangle, 0, 0);
				if(selectedSceneNode){
					bill->setPosition(intersection);
					
					driver->setTransform(video::ETS_WORLD, core::matrix4());
                    driver->setMaterial(material);
                   
					if((selectedSceneNode->getID() & Objective::IDFlag_IsHighlightable) == Objective::IDFlag_IsHighlightable)
                        {
                                highlightedSceneNode = selectedSceneNode;

								highlightedSceneNode->setMaterialFlag(video::EMF_LIGHTING, false);
                        }
				
				}
				guienv->clear();
				hud.display_hud();
				smgr->drawAll();
				guienv->drawAll();
				driver->endScene();

			}else if(gameOver){
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				//Game Over Screen//
				////////////////////
				driver->beginScene(true, true, 
					0);


				if (highlightedSceneNode)
                {
						highlightedSceneNode->setMaterialFlag(video::EMF_LIGHTING, true);
                        highlightedSceneNode = 0;
                }

				core::line3d<f32> ray;
                ray.start = camera->getPosition();
                ray.end = ray.start + (camera->getTarget() - ray.start).normalize() * 1000.0f;
				
                core::vector3df intersection;
                core::triangle3df hitTriangle;

				scene::ISceneNode * selectedSceneNode =
				collMan->getSceneNodeAndCollisionPointFromRay(
						ray, intersection, hitTriangle, 0, 0);
				if(selectedSceneNode){
					bill->setPosition(intersection);
					
					driver->setTransform(video::ETS_WORLD, core::matrix4());
                    driver->setMaterial(material);
                   
					if((selectedSceneNode->getID() & Objective::IDFlag_IsHighlightable) == Objective::IDFlag_IsHighlightable)
                        {
                                highlightedSceneNode = selectedSceneNode;

								highlightedSceneNode->setMaterialFlag(video::EMF_LIGHTING, false);
                        }
				
				}
				guienv->clear();
				hud.display_menu();
				hud.display_go_text(wol_flag);
				hud.display_hud();
				smgr->drawAll();
				guienv->drawAll();
				driver->endScene();

			}else{
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				//Pause Screen  //
				//////////////////
				driver->beginScene(true, true, 
					0);


				if (highlightedSceneNode)
                {
						highlightedSceneNode->setMaterialFlag(video::EMF_LIGHTING, true);
                        highlightedSceneNode = 0;
                }

				core::line3d<f32> ray;
                ray.start = camera->getPosition();
                ray.end = ray.start + (camera->getTarget() - ray.start).normalize() * 1000.0f;
				
                core::vector3df intersection;
                core::triangle3df hitTriangle;

				scene::ISceneNode * selectedSceneNode =
				collMan->getSceneNodeAndCollisionPointFromRay(
						ray, intersection, hitTriangle, 0, 0);
				if(selectedSceneNode){
					bill->setPosition(intersection);
					
					driver->setTransform(video::ETS_WORLD, core::matrix4());
                    driver->setMaterial(material);
                   
					if((selectedSceneNode->getID() & Objective::IDFlag_IsHighlightable) == Objective::IDFlag_IsHighlightable)
                        {
                                highlightedSceneNode = selectedSceneNode;

								highlightedSceneNode->setMaterialFlag(video::EMF_LIGHTING, false);
                        }
				
				}
				guienv->clear();
				hud.display_hud();
				hud.display_menu();
				smgr->drawAll();
				guienv->drawAll();
				driver->endScene();

			}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////			
		}else{
			device->yield();
		}
	device->drop();
	engine->drop();
	return 0;
}

void Game::loadMap(){
	device->getFileSystem()->addZipFileArchive("cod_map.pk3");
		

	scene::IQ3LevelMesh* q3levelmesh = 
		(scene::IQ3LevelMesh*)smgr->getMesh("firing_range.bsp");

	smgr->getParameters()->setAttribute(scene::ALLOW_ZWRITE_ON_TRANSPARENT, true);
	//scene::ISceneNode* q3node = 0;
	scene::IMeshSceneNode* q3node = 0;
	scene::IMesh* geometry = 0;

	if(q3levelmesh){
		
		geometry = 
			q3levelmesh->getMesh(scene::quake3::E_Q3_MESH_GEOMETRY);
		
		q3node = 
			smgr->addOctreeSceneNode(geometry, 0, Objective::IDFlag_IsPickable, 1024);
/*		q3node->setMaterialType(video::EMT_NORMAL_MAP_SOLID);
		driver->setTextureCreationFlag(video::ETCF_ALWAYS_32_BIT, true);
		q3node = smgr->addMeshSceneNode(geometry);

		if(col_list)
			col_list->addTriangleSelector(
				smgr->createOctreeTriangleSelector(geometry, q3node));
	
		q3node->setMaterialFlag(EMF_FOG_ENABLE,true);
		
		driver->setFog(
			SColor(0,125,125,125), video::EFT_FOG_LINEAR, 0, 4000, 0.09F, true, false);
	*/	
		const scene::IMesh* const additional_mesh = 
			q3levelmesh->getMesh(quake3::E_Q3_MESH_ITEMS);

		for(u32 i = 0; i != additional_mesh->getMeshBufferCount(); ++i){
			IMeshBuffer* meshBuffer = additional_mesh->getMeshBuffer(i);
			const video::SMaterial& material = meshBuffer->getMaterial();

			//The Shader Index is stored in the material parameter
			const s32 shaderIndex = (s32)material.MaterialTypeParam2;

			//the meshbuffer can be rendered without additional support, or it has no shader
			const quake3::IShader *shader = q3levelmesh->getShader(shaderIndex);
			if(0 == shader){
				continue;
			}
			
			node = smgr->addQuake3SceneNode(meshBuffer, shader);
	/*	
			if(col_list){
				scene::SMesh *model_mesh = new scene::SMesh;
				model_mesh->addMeshBuffer(meshBuffer);
				
				col_list->addTriangleSelector(
					smgr->createTriangleSelector(model_mesh, node));
				
				delete model_mesh;
			}
			*/
			//q3levelmesh->releaseMesh(quake3::E_Q3_MESH_ITEMS);
			
			
		}
		scene::quake3::tQ3EntityList &entityList = 
			q3levelmesh->getEntityList();

		scene::quake3::IEntity search;
		search.name = "info_player_start";

		//KeyCodes//
		SKeyMap keyMap[6];
		//move foward
		keyMap[0].Action = EKA_MOVE_FORWARD;
		keyMap[0].KeyCode = KEY_KEY_W;
		//move backward
		keyMap[1].Action = EKA_MOVE_BACKWARD;
		keyMap[1].KeyCode = KEY_KEY_S;
		//strafe to the left
		keyMap[2].Action = EKA_STRAFE_LEFT;
		keyMap[2].KeyCode = KEY_KEY_A;
		//strage to the right
		keyMap[3].Action = EKA_STRAFE_RIGHT;
		keyMap[3].KeyCode = KEY_KEY_D;
		//jump
		keyMap[4].Action = EKA_JUMP_UP;
		keyMap[4].KeyCode = KEY_SPACE;
		//crouch
		keyMap[5].Action = EKA_CROUCH;
		keyMap[5].KeyCode = KEY_KEY_Q;

		camera =
			smgr->addCameraSceneNodeFPS(0, 100.0f, .3f,
				Objective::ID_IsNotPickable, keyMap, 6, true, 3.f);

		s32 index = entityList.binary_search(search);
		if (index >= 0)
		{
			s32 notEndList;
			do
			{
				const scene::quake3::SVarGroup *group = entityList[index].getGroup(1);

				u32 parsepos = 0;
				const core::vector3df pos =
					scene::quake3::getAsVector3df(group->get("origin"), parsepos);

				parsepos = 0;
				const f32 yaw = scene::quake3::getAsFloat(group->get("angle"), parsepos);
		
				camera->setPosition(pos);
				camera->setRotation(core::vector3df(0, yaw, 0));
				camera->setTarget(core::vector3df(-10, -15, 300));
				camera->setMaterialFlag(video::EMF_LIGHTING, false);
				camera->setMaterialFlag(video::EMF_NORMALIZE_NORMALS, true);

				++index;

				notEndList = (   index < (s32) entityList.size () &&
							entityList[index].name == search.name &&
							(device->getTimer()->getRealTime() >> 3 ) & 1
							);

				notEndList = index == 2;
			} while ( notEndList );
	
		}

	}

	scene::ITriangleSelector* selector = 0;

	if(q3node){

		q3node->setPosition(core::vector3df(core::vector3df(0, 0, 0)));
		//selector = smgr->createOctreeTriangleSelector(
        //        q3node->getMesh(), q3node, 128);
		selector = smgr->createOctreeTriangleSelector(
				geometry, q3node);
        q3node->setTriangleSelector(selector);
		
	}

    if (selector)
    {
		
            scene::ISceneNodeAnimator* anim = smgr->createCollisionResponseAnimator(
                    selector, camera, core::vector3df(10, 15, 10),
                    core::vector3df(0,-10,0), core::vector3df(0,30,0));
            selector->drop(); 
            camera->addAnimator(anim);
            anim->drop();
    }

	device->getCursorControl()->setVisible(false);
	
	bill = smgr->addBillboardSceneNode();
	bill->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);
	bill->setMaterialTexture(0, driver->getTexture("portal6.bmp"));
	bill->setMaterialFlag(video::EMF_LIGHTING, false);
	bill->setMaterialFlag(video::EMF_ZBUFFER, false);
	bill->setSize(core::dimension2d<f32>(20.0f, 20.0f));
	bill->setID(Objective::ID_IsNotPickable);
	collMan = smgr->getSceneCollisionManager();
	
	//scene::IParticleSystemSceneNode* ps = 0;
	//ps = smgr->addParticleSystemSceneNode(false);
	//ps->setPosition(core::vector3df(0, 0, 0));
	//ps->setScale(core::vector3df(1, 1, 1));

	//ps->setParticleSize(core::dimension2d<f32>(5.0f, 5.0f));

	//scene::IParticleEmitter* em = ps->createBoxEmitter(
	//	core::aabbox3d<f32>(-270, -200, -270, 270, 300, 300),
	//	core::vector3df(0.00f, 0.00f, 0.0f),
	//	400, 800, video::SColor(0, 255, 255, 255), video::SColor(0, 255, 255, 255), 
	//	8000, 10000);

	//ps->setEmitter(em);
	//em->drop();

	//scene::IParticleAffector* paf = 
	//	ps->createGravityAffector(core::vector3df(0.00f, -0.45f, 0.00f), 1000);

	//ps->addAffector(paf);
	//paf->drop();

	//ps->setMaterialFlag(video::EMF_LIGHTING, false);
	//ps->setMaterialType(EMT_TRANSPARENT_ADD_COLOR);
	//irr::video::ITexture* image = driver->getTexture("portal6.bmp");
	////driver->makeColorKeyTexture(image, irr::core::vector2d<irr::s32>(0, 0), false);
	//ps->setMaterialTexture(0, driver->getTexture(image->getName()));
	//ps->setMaterialType(video::EMT_TRANSPARENT_VERTEX_ALPHA);

	//ps->setParent(camera);
	
}