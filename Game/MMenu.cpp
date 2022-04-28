#include "MMenu.h"

using namespace irr;

MMenu::MMenu(irr::IrrlichtDevice* dev){
	
	device = dev;
	driver = device->getVideoDriver();
	env = device->getGUIEnvironment();
	backgroundPic = driver->getTexture("Pancakes.jpg");
	area = irr::core::rect<irr::s32>(0,0,800,600);
	col = &(irr::video::SColor(255, 255, 255, 255));
		
	b_ht = 40;
	b_wid = 150;

	x = (device->getVideoDriver()->getScreenSize().Width - b_wid) / 2;
	y = (device->getVideoDriver()->getScreenSize().Height) / 2;
}

void MMenu::Display(){

	s32 v_spacing = 5;

	driver->draw2DImage(backgroundPic, area, irr::core::rect<irr::s32>(0, 0, 497, 335), 0, col, false);

	irr::video::ITexture* image = driver->getTexture("title.jpg");
	driver->makeColorKeyTexture(image, irr::core::vector2d<irr::s32>(0, 0), false);
	driver->draw2DImage(image, irr::core::rect<irr::s32>(250, 0, 543, 322), irr::core::rect<irr::s32>(0, 0, 843, 502), 0, col, true);
	
	env->addButton(core::rect<s32>(x, y, x + b_wid, y + b_ht), 0, START_BUTTON,
			L"START", L"Start Game");

	env->addButton(core::rect<s32>(x, (y + (b_ht * 1)) + v_spacing, x + b_wid, (y + (b_ht * 2)) + v_spacing), 0, INSTRUCTIONS_BUTTON,
			L"ABOUT", L"learn how to play");
	
	env->addButton(core::rect<s32>(x, (y + (b_ht * 3)) + (2 * v_spacing), x + b_wid, (y + (b_ht * 4)) + (2 * v_spacing)), 0, QUIT_BUTTON,
		L"QUIT", L"Terminate Program");
}

void MMenu::remove(){
	env->clear();
}

void MMenu::instructions_display(){

	driver->draw2DImage(backgroundPic, area, irr::core::rect<irr::s32>(0, 0, 497, 335), 0, col, false);

	irr::video::ITexture* image = driver->getTexture("keyboard.jpg");
	driver->makeColorKeyTexture(image, irr::core::vector2d<irr::s32>(0, 0), false);
	driver->draw2DImage(image, irr::core::rect<irr::s32>(250, 10, 650, 561), irr::core::rect<irr::s32>(0, 0, 399, 411), 0, col, true);
	

	env->addButton(core::rect<s32>(x - (b_wid * 2), y + (b_ht * 3), (x - (b_wid * 2)) + b_wid, (y + (b_ht * 3)) + b_ht), 0, BACK_TO_MAIN_BUTTON,
		L"RETURN", L"return to previous menu");

}

void MMenu::setBackgroundPic(irr::video::ITexture* bkgrnd_pic){
	backgroundPic = bkgrnd_pic;
}

irr::video::ITexture* MMenu::getBackgroundPic(){
	return backgroundPic;
}