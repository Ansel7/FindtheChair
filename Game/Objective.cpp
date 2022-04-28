#include "Objective.h"

Objective::Objective(irr::IrrlichtDevice* dev){
	device = dev;
	driver = device->getVideoDriver();
	smgr = device->getSceneManager();
	srand(time(NULL));
	min = getNextSpawnPoint();
	node = 0;
	randomInt = 0;
	lastInt = 0;
	length = 150;
	height = 150;
	width = 150;
	mesh = smgr->getMesh("a3dchr3.3ds");
}

Objective::~Objective(void){}

void Objective::drawObjective(void){

	smgr->getMeshManipulator()->makePlanarTextureMapping(mesh->getMesh(0), 0.004f);

	irr::scene::ITriangleSelector* selector = 0;

	node = smgr->addAnimatedMeshSceneNode(mesh);
	node->setMaterialTexture(0, driver->getTexture("dchrfab.tga"));
	node->setID(IDFlag_IsPickable | IDFlag_IsHighlightable);
	node->setMaterialFlag(irr::video::EMF_LIGHTING, true);
	node->getMaterial(0).NormalizeNormals = true;
	node->setPosition(min);
	
	selector = smgr->createTriangleSelector(node);
	node->setTriangleSelector(selector);
	selector->drop();
}

void Objective::setNewSpawnPoint(){
	min = getNextSpawnPoint();
	node->setPosition(min);
}

irr::core::vector3d<irr::f32> Objective::getNextSpawnPoint(){
	do{
		randomInt = rand() % 5;
	}while(lastInt == randomInt);
	lastInt = randomInt;
	
	switch(randomInt){
	case 0:
		return irr::core::vector3d<irr::f32>(-10, -7, 300);
	case 1:
		return irr::core::vector3d<irr::f32>(-1050, 15, -150);
	case 2:
		return irr::core::vector3d<irr::f32>(-1490, 17, 500);
	case 3:
		return irr::core::vector3d<irr::f32>(-1100, 217, 230);
	case 4:
		return irr::core::vector3d<irr::f32>(-900, 147, 930);
	default:
		return irr::core::vector3d<irr::f32>(-900, 147, 930);
	}
}