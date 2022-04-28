#include "Overlay.h"
#include <iostream>

using namespace std;

Overlay::Overlay(irr::IrrlichtDevice* dev){
	device = dev;
	env = device->getGUIEnvironment();
	driver = device->getVideoDriver();
	sel = 0;
	score = 0;
	last_score = 0;
	stime = 30;
	cout << score;
	cout << stime;
	gameHasStarted = false;
	currentTime = device->getTimer()->getTime();
	lastTime = device->getTimer()->getTime();
	col = &(irr::video::SColor(255, 255, 255, 255));
	width = device->getVideoDriver()->getScreenSize().Width;
	height = device->getVideoDriver()->getScreenSize().Height;
	irr::gui::IGUISkin* skin = env->getSkin();
	font = env->getFont("big_text.bmp");
	if(font)
		skin->setFont(font);
}


Overlay::~Overlay(void){

}

void Overlay::setTime(int newtime){
	stime = newtime;
}

int Overlay::getTime(){
	return stime;
}

void Overlay::display_hud(){
	
	if(gameHasStarted){

		currentTime = device->getTimer()->getTime();

		if(score != last_score){
			last_score = score;
		}
			text = env->addStaticText(irr::core::stringw(score).c_str(),
					irr::core::rect<irr::s32>(70, 20, 110, 70), true);
			text->setOverrideColor(irr::video::SColor(255, 255, 0, 0));
	
		if((currentTime - lastTime) >= 1000){
			if(stime != 0 && score != 10){
				--stime;
				lastTime = currentTime;
			}
		}
		text = env->addStaticText(irr::core::stringw(stime).c_str(),
					irr::core::rect<irr::s32>(width / 2, 20, (width / 2) + 40, 70), true);
		text->setOverrideColor(irr::video::SColor(255, 255, 0, 0));
	}else{
		text = env->addStaticText(irr::core::stringw(score).c_str(),
				irr::core::rect<irr::s32>(70, 20, 200, 70), true);
		text->setOverrideColor(irr::video::SColor(255, 255, 0, 0));
		text = env->addStaticText(irr::core::stringw(stime).c_str(),
				irr::core::rect<irr::s32>(width / 2, 20, (width / 2) + 200, 70), true);
		text->setOverrideColor(irr::video::SColor(255, 255, 0, 0));

		gameHasStarted = true;
	}
}

void Overlay::display_go_text(int wol){

	switch(wol){
	case 0:
		text = env->addStaticText(L"YOU LOSE\nGAME OVER",
			irr::core::rect<irr::s32>(0, 0, 0, 0), true);
		text->setRelativePosition(irr::core::rect<irr::s32>((width - text->getTextWidth()) / 2, (height - text->getTextHeight()) / 2,
										((width - text->getTextWidth()) / 2) + 200, ((height - text->getTextHeight()) / 2) + 70));
		text->setOverrideColor(irr::video::SColor(255, 255, 0, 0));
		break;
	case 1:
		text = env->addStaticText(L"YOU WIN\nGAME OVER",
			irr::core::rect<irr::s32>(0, 0, 0, 0), true);
		text->setRelativePosition(irr::core::rect<irr::s32>((width - text->getTextWidth()) / 2, (height - text->getTextHeight()) / 2,
										((width - text->getTextWidth()) / 2) + 200, ((height - text->getTextHeight()) / 2) + 70));
		text->setOverrideColor(irr::video::SColor(255, 255, 0, 0));
		break;
	}

	/*//this uses the win or lose and game over jpg. 
	switch(wol){
	case 0:
		//loser text :(
		image1 = 
			driver->getTexture("you_lose.jpg");

		driver->makeColorKeyTexture(image1, 
			irr::core::vector2d<irr::s32>(0, 0), false);

		driver->draw2DImage(image1, 
			irr::core::rect<irr::s32>(100, 100, 700, 245), 
			irr::core::rect<irr::s32>(0, 0, 795, 145), 0, 
			col, true);

		image3 = 
			driver->getTexture("gameOver.jpg");

		driver->makeColorKeyTexture(image3, 
			irr::core::vector2d<irr::s32>(0, 0), false);

		driver->draw2DImage(image3, 
			irr::core::rect<irr::s32>(250, 100, 700, 395), 
			irr::core::rect<irr::s32>(0, 0, 888, 145), 0, 
			col, true);
		break;
	case 1:
		//winner text :)
		image2 = 
			driver->getTexture("you_win.jpg");

		driver->makeColorKeyTexture(image2, 
			irr::core::vector2d<irr::s32>(0, 0), false);

		driver->draw2DImage(image2, 
			irr::core::rect<irr::s32>(100, 100, 700, 245), 
			irr::core::rect<irr::s32>(0, 0, 743, 145), 0, 
			col, true);

		image3 = 
			driver->getTexture("gameOver.jpg");

		driver->makeColorKeyTexture(image3, 
			irr::core::vector2d<irr::s32>(0, 0), false);

		driver->draw2DImage(image3, 
			irr::core::rect<irr::s32>(250, 100, 700, 395), 
			irr::core::rect<irr::s32>(0, 0, 888, 145), 0, 
			col, true);
		break;
	}
	*/
}

void Overlay::display_menu(){

	window = env->addWindow(irr::core::rect<irr::s32>(100, 100, 300, 200), 
			false, L"Pause");

	pause_listBox = env->addListBox(irr::core::rect<irr::s32>
										(0, 20, 200, 100), window);

	pause_listBox->addItem(L"Restart");
	pause_listBox->addItem(L"Quit");
	pause_listBox->setSelected(sel);
	
}

void Overlay::setScore(int s){
	score = s;
}

int Overlay::getScore(){
	return score;
}

void Overlay::move_select_down(){
	++sel;
	if(sel > 1)
		sel = 0;
	pause_listBox->setSelected(sel);
}

void Overlay::move_select_up(){
	--sel;
	if(sel < 0)
		sel = 1;
	pause_listBox->setSelected(sel);
}

irr::s32 Overlay::return_selected(){
	return sel;
}

void Overlay::remove(){
	env->clear();
}