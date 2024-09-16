#pragma once

class GameObject;

class Cell
{
public:

	Cell();
	virtual ~Cell();

private:

	GameObject* mContent;

public:

	void SetContent(GameObject* content) { mContent = content; }

};

