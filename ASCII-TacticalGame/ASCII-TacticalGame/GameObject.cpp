#include "GameObject.h"

int GameObject::sObjectGlobalId = 0;

GameObject::GameObject()
	: mPosition({0, 0})
	, mSymbol('?')
{
	mId = ++GameObject::sObjectGlobalId;
}

GameObject::~GameObject()
{
}

void GameObject::Update()
{
}

void GameObject::Render()
{
}
