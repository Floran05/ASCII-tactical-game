#pragma once
enum KeyState {
	None,
	Pressed ,
	Down
};
class Controller
{
public :
	Controller();
	virtual ~Controller();
protected : 
	unsigned char mkey[256];
public : 
	void Update();
	bool IsKey(int key);
	
};

