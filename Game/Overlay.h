#pragma once
#include <irrlicht.h>
#include "MMenu.h"

class Overlay{

private:
	irr::IrrlichtDevice* device;
	irr::gui::IGUIEnvironment* env;
	irr::video::IVideoDriver* driver;
	irr::u32 stime,
			currentTime,
			lastTime;
	irr::gui::IGUISkin* skin;
	irr::gui::IGUIFont* font2;
	irr::gui::IGUIFont* font;
	irr::video::ITexture* image1;
	irr::video::ITexture* image2;
	irr::video::ITexture* image3;
	irr::gui::IGUIWindow* window;
	irr::video::SColor* col;
	irr::gui::IGUIStaticText* score_text;
	irr::gui::IGUIStaticText* time_text;
    irr::gui::IGUIListBox* pause_listBox;
	irr::gui::IGUIListBox* go_listBox;
	irr::gui::IGUIStaticText* text;

	int sel,
		score,
		last_score;
	irr::s32 width,
		height;
	bool gameHasStarted;

public:
	//pause menu buttons
	enum{
		RESTART_BUTTON = 6,
	};

	Overlay(irr::IrrlichtDevice*);
	~Overlay(void);

	void move_select_up();
	void move_select_down();
	void setTime(int);
	int getTime();
	irr::s32 return_selected();
	void display_menu();
	void display_go_text(int);
	void display_hud();
	int getScore();
	void setScore(int);
	void remove();
};