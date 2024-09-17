#include "Controller.h"
#include <Windows.h>

Controller::Controller()
{
	for (int i = 0; i < 256; i++) {
		mkey[i] = KeyState::None;
	}
}

Controller::~Controller()
{
}

void Controller::Update()
{
	for (int i = 0; i < 256; i++) {
		bool currentstate = GetAsyncKeyState(i) < 0;
		if (currentstate ) {
			if (mkey[i] == KeyState::None) {
				mkey[i] = KeyState::Pressed;
			}
			else if ( mkey[i] == KeyState::Pressed) {
				mkey[i] = KeyState::Down;
			}
			
		}
		
		else {
			mkey[i] = KeyState::None;
		}
	}

}

bool Controller::IsKey(int key)
{
	return mkey[key] == KeyState::Pressed;
}


