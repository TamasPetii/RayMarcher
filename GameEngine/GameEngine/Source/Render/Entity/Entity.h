#pragma once
#define _USE_MATH_DEFINES
#include <cmath>
#include <typeindex>
#include <unordered_set>
#include <map>
#include <vector>
#include <algorithm>
#include "../../Engine/Engine.h"

class Entity
{
public:
    Entity();
    ~Entity();
    static Entity* GetEntity(int id);
    static void DeleteEntity(int id);

    template<typename T>
    T* GetComponent();

    template<typename T>
    void AddComponent(T* componenet);

    template<typename T>
    bool HasComponent();

    //Getter
    inline int& GetId() { return mId; }
    inline std::string& GetText() { return mText; }
    inline static std::map<int, Entity*>& Entities() { return mEntities; }
private:
    int mId;
    std::string mText;
	std::unordered_map<std::type_index, Component*> mComponents;

    static std::map<int, Entity*> mEntities;
};

#include "Entity.inl"
