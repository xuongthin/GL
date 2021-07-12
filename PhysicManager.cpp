#include "PhysicManager.h"

PhysicManager* PhysicManager::ms_Instance = 0;

PhysicManager::PhysicManager()
{
}


PhysicManager::~PhysicManager()
{
}

void PhysicManager::CreateInstance()
{
	if (ms_Instance == 0)
		ms_Instance = new PhysicManager;
}

PhysicManager * PhysicManager::GetInstance()
{
	return ms_Instance;
}

void PhysicManager::DestroyInstance()
{
	if (ms_Instance)
	{
		delete ms_Instance;
		ms_Instance = 0;
	}
}

void PhysicManager::CheckCollider(SceneManager* scene)
{

}
