#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#endif

#ifndef EVENTRECEIVER_H
#define EVENTRECEIVER_H

#include <irrlicht.h>
#include "MMenu.h"
#include "Objective.h"

using namespace irr;
using namespace core;
using namespace video;
using namespace scene;
using namespace gui;

class EventReceiver:public IEventReceiver
{
	private:
		bool KeyDown[KEY_KEY_CODES_COUNT];
		bool buttonPressed[MMenu::NUM_MMENU_BUTTONS + MMenu::NUM_OVRLY_BUTTONS];

	public:
		EventReceiver();
		virtual bool OnEvent(const SEvent& event);
		virtual bool isKeyDown(EKEY_CODE keyCode) const;  //const means thsi function can not modify private members
		virtual bool isKeyUp(EKEY_CODE keyCode) const;
		bool isButtonPressed(int);
		void resetButtons(void);
};
#endif

