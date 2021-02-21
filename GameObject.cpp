#include "GameObject.h"

GameObject::GameObject(Position2D position, int id)
	: mPosition(position)
	, mID(id)
{

}

int GameObject::GetID()
{
	return mID;
}