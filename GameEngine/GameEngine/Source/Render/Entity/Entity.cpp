#include "Entity.h"

std::map<int, Entity*> Entity::mEntities;

Entity* Entity::GetEntity(int id)
{
	if (mEntities.find(id) != mEntities.end())
		return mEntities[id];
	return nullptr;
}

void Entity::DeleteEntity(int id)
{
	if (mEntities.find(id) != mEntities.end())
	{
		delete mEntities[id];
		mEntities.erase(id);
	}
}

Entity::Entity()
{
	static int id = 0;
	mId = id++;
	mText = "Entity" + std::to_string(mId);
	mEntities[mId] = this;
}

Entity::~Entity()
{
	for (auto& component : mComponents)
	{
		delete component.second;
	}
}