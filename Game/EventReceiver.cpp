#include "EventReceiver.h"

EventReceiver::EventReceiver(){

	//sets all the values in the keys to false - all keys are up
	for(int i = 0; i < KEY_KEY_CODES_COUNT; i++){
		KeyDown[i] = false;
	}

	for(int i = 0; i < MMenu::NUM_MMENU_BUTTONS + MMenu::NUM_OVRLY_BUTTONS;i++){
		buttonPressed[i] = false;
	}

}

bool EventReceiver::OnEvent(const SEvent& event){

	switch(event.EventType){

		case EET_KEY_INPUT_EVENT:
			KeyDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
			break;

		case EET_GUI_EVENT:
			switch (event.GUIEvent.EventType){
			case irr::gui::EGET_BUTTON_CLICKED:
				buttonPressed[event.GUIEvent.Caller->getID()] = true;
			}
			break;
		default:
			break;  

	}
	return false;
	
}

bool EventReceiver::isKeyDown(EKEY_CODE keyCode) const{
	return KeyDown[keyCode];
}

bool EventReceiver::isKeyUp(EKEY_CODE keyCode) const{
	return !KeyDown[keyCode];
}

bool EventReceiver::isButtonPressed(int button){
	return buttonPressed[button];
}

void EventReceiver::resetButtons(void){
	for(int i = 0; i < MMenu::NUM_MMENU_BUTTONS + MMenu::NUM_OVRLY_BUTTONS;i++){
		buttonPressed[i] = false;
	}
}