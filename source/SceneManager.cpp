#include "SceneManager.h"

using namespace std;

SceneManager *SceneManager::ms_Instance = NULL;

SceneManager::SceneManager()
{
	m_iTargetId = -1;
}

SceneManager::~SceneManager()
{
	m_vObjects.clear();
}

void SceneManager::CreateInstance()
{
	if (ms_Instance == NULL)
		ms_Instance = new SceneManager;
}

SceneManager * SceneManager::GetInstance()
{
	return ms_Instance;
}

void SceneManager::DestroyInstance()
{
	if (ms_Instance)
	{
		delete ms_Instance;
		ms_Instance = NULL;
	}
}

void SceneManager::Init()
{
	string line;
	char str[80];
	int input0 = 0;

	ifstream file("./Resources/SM.txt");
	while (getline(file, line)) {

		sscanf(line.c_str(), "%s ", str);
		string header(str);
		if (header == "#OBJECT_NUM\0")
		{
			cout << "start" <<endl;
		}

		if (header == "#ID")
		{
			cout << "-" << endl;

			char keyword[20];
			char acInput[20];

			int iInput0;
			int iInput1;
			int iInput2;
			int iInput3;

			getline(file, line);
			sscanf(line.c_str(), "%s %s", keyword, acInput);

			if (string(keyword) == "#ID")
			{
				getline(file, line);
				sscanf(line.c_str(), "%s %s", keyword, acInput);
			}

			if (string(keyword) != "TYPE:") cout << "can not find keyword: TYPE " << endl;

			if (string(acInput) == "RECT")
			{
				getline(file, line);
				sscanf(line.c_str(), "%s %d, %d, %d, %d", keyword, &iInput0, &iInput1, &iInput2, &iInput3);
				if (string(keyword) != "POSITION:") cout << "can not find keyword: POSITION" << endl;
				Rect* obj = new Rect(Vector2(iInput0, iInput1), Vector2(iInput2, iInput3));

				getline(file, line);
				sscanf(line.c_str(), "%s %d", keyword, &iInput0);
				if (string(keyword) != "VELOCITY:") cout << "can not find keyword: VELOCITY" << endl;
				obj->SetVelocity(Vector2(0, iInput0));

				AddObject(obj);

				cout << "success" << endl;
			}
			else if (string(acInput) == "CIRCLE")
			{
				getline(file, line);
				sscanf(line.c_str(), "%s %d, %d, %d", keyword, &iInput0, &iInput1, &iInput2);
				if (string(keyword) != "POSITION:") cout << "can not find keyword: POSITION" << endl;
				Circle* obj = new Circle(Vector2(iInput0, iInput1), iInput2);

				getline(file, line);
				sscanf(line.c_str(), "%s %d", keyword, &iInput0);
				if (string(keyword) != "VELOCITY:") cout << "can not find keyword: VELOCITY" << endl;
				obj->SetVelocity(Vector2(0, iInput0));

				AddObject(obj);

				cout << "success" << endl;
			}
			else if (string(acInput) == "PLANE")
			{
				getline(file, line);
				sscanf(line.c_str(), "%s %d, %d, %d, %d", keyword, &iInput0, &iInput1, &iInput2, &iInput3);
				if (string(keyword) != "POSITION:") cout << "can not find keyword: POSITION" << endl;
				Plane* obj = new Plane(Vector2(iInput0, iInput1), Vector2(iInput2, iInput3));

				AddObject(obj);

				cout << "success" << endl;
			}
			else {
				cout << "WARNING: SM.txt" << endl;
			}
		}
	}

	file.close();
}

void SceneManager::Update(float frameTime)
{
	for (int i = 0; i < m_vObjects.size(); i++)
	{
		m_vObjects.at(i)->Update(frameTime);
	}

	CheckCollision();
}

void SceneManager::Render()
{
	for (auto it = m_vObjects.begin(); it != m_vObjects.end(); it++)
	{
		(*it)->Render();
	}
}

void SceneManager::AddObject(Object * object)
{
	 m_vObjects.push_back(object);
}

void SceneManager::OnMouseDown(Vector2 mousePosition)
{
	m_previousMousePositionX = mousePosition.x;
	m_previousMousePositionY = mousePosition.y;

	double minDistance = 10000;
	for (int i = 0; i < m_vObjects.size(); i++)
	{
		Object* obj = m_vObjects.at(i);
		Vector2 direction = mousePosition - obj->GetPosition();
		double distance = direction.length();

		if (distance > minDistance) continue;

		if (obj->GetName() == "Circle") {
			Circle* circle = (Circle*)obj;
			if (circle->ContainPoint(mousePosition))
			{
				m_iTargetId = i;
				minDistance = distance;
			}
		}
		else if (obj->GetName() == "Rect") {
			Rect* rect = (Rect*)obj;
			if (rect->ContainPoint(mousePosition))
			{
				m_iTargetId = i;
				minDistance = distance;
			}
		}
	}

	if (m_iTargetId != -1)
	{
		m_vObjects.at(m_iTargetId)->Lock();
		cout << m_iTargetId;
	}

	//if (m_iTargetId != -1)
	//{
	//	m_vObjects.at(m_iTargetId)->AddForce(Vector2(3, 0));
	//	m_iTargetId = -1;
	//}
}

//void SceneManager::OnMouseMove()
//{
//	if (m_iTargetId != -1)
//	{
//		double deltaX = m_previousMousePositionX - m_previousMousePositionX;
//		double deltaY = m_previousMousePositionY - m_previousMousePositionY;
//
//		m_vObjects.at(m_iTargetId)->Move(Vector2(deltaX, deltaY));
//
//		m_previousMousePositionX = m_previousMousePositionX;
//		m_previousMousePositionY = m_previousMousePositionY;
//	}
//}

void SceneManager::OnMouseMove(Vector2 mousePosition)
{
	if (m_iTargetId != -1)
	{
		double deltaX = mousePosition.x - m_previousMousePositionX;
		double deltaY = mousePosition.y - m_previousMousePositionY;

		m_vObjects.at(m_iTargetId)->Move(Vector2(deltaX, deltaY));

		m_previousMousePositionX = mousePosition.x;
		m_previousMousePositionY = mousePosition.y;
	}
}

void SceneManager::OnMouseUp()
{
	if (m_iTargetId != -1)
	{
		m_vObjects.at(m_iTargetId)->Unlock();
	}

	m_iTargetId = -1;
}

std::vector<Object*> SceneManager::GetObjectsList()
{
	return m_vObjects;
}

void SceneManager::CheckCollision()
{
	for (int i = 0; i < m_vObjects.size() - 1; i++)
	{ 
		for (int j = i + 1; j < m_vObjects.size(); j++)
		{
			CheckCollider(m_vObjects.at(i), m_vObjects.at(j));
		}
	}
}

void SceneManager::CheckCollider(Object * first, Object* second)
{
	if (first->GetName() == "Circle") 
	{
		Circle* main = (Circle*) first;
		if (second->GetName() == "Circle")
		{
			Circle* other = (Circle*) second;

			main->CheckCollider(other);
		}

		if (second->GetName() == "Plane")
		{
			Plane* other = (Plane*) second;

			main->CheckCollider(other);
		}
		
		if (second->GetName() == "Rect")
		{
			Rect* other = (Rect*) second;

			other->CheckCollider(main);
		}
	}
	else if (first->GetName() == "Rect")
	{
		Rect* main = (Rect*) first;

		if (second->GetName() == "Rect")
		{
			Rect* other = (Rect*) second;
			main->CheckCollider(other);
		}

		if (second->GetName() == "Circle")
		{
			Circle* other = (Circle*)second;

			main->CheckCollider(other);
		}

		if (second->GetName() == "Plane")
		{
			Plane* other = (Plane*)second;

			main->CheckCollider(other);
		}
	}
	else if (first->GetName() == "Plane") 
	{
		Plane* main = (Plane*) first;

		if (second->GetName() == "Circle")
		{
			Circle* other = (Circle*) second;

			other->CheckCollider(main);
		}

		if (second->GetName() == "Rect")
		{
			Rect* other = (Rect*)second;
			other->CheckCollider(main);
		}
	}
}


