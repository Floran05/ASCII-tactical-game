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

int Controller::WaitForKey()
{
	while (true)
	{
		int key = -1;
		for (int i = 0; i < 256; i++)
		{
			bool currentstate = GetAsyncKeyState(i) < 0;
			if (currentstate) {
				if (mkey[i] == KeyState::None) {
					mkey[i] = KeyState::Pressed;
					key = i;
				}
				else if (mkey[i] == KeyState::Pressed) {
					mkey[i] = KeyState::Down;
				}
			}
			else {
				mkey[i] = KeyState::None;
			}
		}
		if (key >= 0) return key;
	}
	return 0;
}


