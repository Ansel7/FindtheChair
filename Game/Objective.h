#pragma once
#include <irrlicht.h>
#include <cstdlib>
#include <ctime>

class Objective{

private:
	irr::IrrlichtDevice* device;
	irr::video::IVideoDriver* driver;
	irr::scene::IAnimatedMesh* mesh;
	irr::scene::IAnimatedMeshSceneNode* node;
	irr::scene::ISceneManager* smgr;
	
	irr::f32 width,
			length,
			height;
	int lastInt,
		randomInt;
	irr::core::vector3d<irr::f32> min;

	irr::core::vector3d<irr::f32> getNextSpawnPoint();
public:

	enum{
        // I use this ISceneNode ID to indicate a scene node that is
        // not pickable by getSceneNodeAndCollisionPointFromRay()
        ID_IsNotPickable = 0,

        // I use this flag in ISceneNode IDs to indicate that the
        // scene node can be picked by ray selection.
        IDFlag_IsPickable = 1 << 0,

        // I use this flag in ISceneNode IDs to indicate that the
        // scene node can be highlighted.  In this example, the
        // homonids can be highlighted, but the level mesh can't.
        IDFlag_IsHighlightable = 1 << 1
	};

	Objective(irr::IrrlichtDevice*);
	~Objective(void);

	void drawObjective(void);
	void setNewSpawnPoint(void);

};

