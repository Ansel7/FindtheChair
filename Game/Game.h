#pragma once
#include <irrlicht.h>
#include "MMenu.h"
#include "Overlay.h"
#include "Objective.h"
#include "EventReceiver.h"
#include "sound.h"
#include <irrKlang.h>

using namespace irr;
using namespace irrklang;

#if defined(_MSC_VER)
	#pragma comment(lib, "Irrlicht.lib")
	#pragma comment(lib, "irrKlang.lib")
#endif

class Game{

private:
	bool gameOver;
	bool gamePaused;
	bool result;
	bool instruc_menu;
	bool main_menu;
	bool been_default;
	u32 beforeTime,
		deltaTime,
		sleepTime,
		period;
	
	IrrlichtDevice* device;
	ISoundEngine* engine;
	scene::ISceneManager* smgr;
	video::IVideoDriver* driver;
	gui::IGUIEnvironment* guienv;
	scene::IMetaTriangleSelector* col_list;
	
	//scene::IAnimatedMeshSceneNode* node;
	irr::core::vector3d<irr::f32> pos;
	
	//for map
	scene::ISceneNode* node;
	scene::ISceneNode* highlightedSceneNode;

	scene::ICameraSceneNode* camera;
	scene::ISceneCollisionManager* collMan;
	scene::IBillboardSceneNode* bill;
	video::SMaterial material;

public:

	Game(void);
	int run(void);
	void loadMap();

};