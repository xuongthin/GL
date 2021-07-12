#pragma once

#include "Object.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include "Plane.h"
#include "Circle.h"
#include "Rect.h"
#include "Vector2.h"
#include <typeinfo>

class SceneManager
{
protected:
	int m_iMaxObjectsAmount;
	int m_iCurrentObjectsAmount;
	std::vector<Object*> m_vObjects;

	int m_iTargetId;
	double m_previousMousePositionX;
	double m_previousMousePositionY;
	double m_pressTimer;
public:
	SceneManager();
	~SceneManager();

	static void CreateInstance();
	static SceneManager* GetInstance();
	static void DestroyInstance();

	void Init();
	void Update(float frameTime);
	void Render();
	void AddObject(Object* object);

	void OnMouseDown(Vector2 mousePosition);
	/*void OnMouseMove();*/
	void OnMouseMove(Vector2 mousePosition);
	void OnMouseUp();

	std::vector<Object*> GetObjectsList();
	void CheckCollision();
	void CheckCollider(Object* first, Object* second);
protected:
	static SceneManager* ms_Instance;
};

