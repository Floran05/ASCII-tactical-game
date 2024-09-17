#pragma once
enum KeyState {
	None,
	Pressed 
};
class Controller
{
public :
	Controller();
	virtual ~Controller();
protected : 
	unsigned char mkey[255];
public : 
	void Update();
	bool IsKey(int key);
	
};

