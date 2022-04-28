#pragma once
#include <irrlicht.h>

class MMenu{

private:
	irr::video::ITexture* backgroundPic;
	irr::IrrlichtDevice* device;
	irr::gui::IGUIEnvironment* env;
	irr::video::IVideoDriver* driver;
	irr::core::rect<irr::s32> area;
	const irr::video::SColor* col;

	irr::s32 x, y, b_wid, b_ht;

public:
	//Main Menu Buttons
	enum{
		QUIT_BUTTON = 0,
		START_BUTTON,
		NUM_OVRLY_BUTTONS,
		INSTRUCTIONS_BUTTON,
		BACK_TO_MAIN_BUTTON,
		NUM_MMENU_BUTTONS
	};

	MMenu(irr::IrrlichtDevice*);
	void Display();
	void setBackgroundPic(irr::video::ITexture*);
	irr::video::ITexture* getBackgroundPic();
	void instructions_display(void);
	void remove();

};

