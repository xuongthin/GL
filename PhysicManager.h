#pragma once

#include "SceneManager.h"
//#include "Object.h"
//#include "Circle.h"
//#include "Rect.h"
//#include "Plane.h"
//#include "Vector2.h"

class PhysicManager
{
public:
	PhysicManager();
	~PhysicManager();

	static void CreateInstance();
	static PhysicManager* GetInstance();
	static void DestroyInstance();

	void CheckCollider(SceneManager* scene);
protected:
	static PhysicManager* ms_Instance;
};

