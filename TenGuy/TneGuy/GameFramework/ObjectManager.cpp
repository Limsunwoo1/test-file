#include "ObjectManager.h"
#include <iostream>
#include "framework.h"
#include "Func.h"
#include "Player.h"
#include <windows.h>

 HBRUSH BLACK = CreateSolidBrush(RGB(0, 0, 0));
 HBRUSH RED = CreateSolidBrush(RGB(255, 0, 0));
 HBRUSH GREEN = CreateSolidBrush(RGB(0, 128, 0));
 HBRUSH BACKGROUND = CreateSolidBrush(RGB(255, 255, 255));

ObjectManager::ObjectManager()
{

}

ObjectManager::~ObjectManager()
{

}

void ObjectManager::Init()
{

}

void ObjectManager::Update(float InDeltaTime)
{

	for (int i = 0; i < OBJvector.size(); ++i)
	{
		OBJvector[i]->Update(InDeltaTime);
		
	}
	
	if (Player)
		Player->Update(InDeltaTime);
}

void ObjectManager::Render(HDC Inhdc)
{
	for (int i = 0; i < OBJvector.size(); ++i)
	{
		if (OBJvector[i]->GetObjectType() == EOBJ_TYPE::RECTANGLE)
		{
			SelectObject(Inhdc, BLACK);
		}
		else if (OBJvector[i]->GetObjectType() == EOBJ_TYPE::ELLIPSE)
		{
			SelectObject(Inhdc, RED);
		}
		else if (OBJvector[i]->GetObjectType() == EOBJ_TYPE::Bullet)
		{
			SelectObject(Inhdc, BLACK);
		}
		OBJvector[i]->Render(Inhdc);
	}
	
	SelectObject(Inhdc, GREEN);
	if (Player)
		Player->Render(Inhdc);

	wchar_t buffer[100] = {};
	swprintf_s(buffer, L"%d", testPobj->GetPlayerLIfe());

	SelectObject(Inhdc, BLACK);
	TextOut(Inhdc, Player->GetPosition().x  , Player->GetPosition().y  , buffer, 1); // 플레이어의 라이프 표시


	SelectObject(Inhdc, BACKGROUND);
}

void ObjectManager::SetPlayer(CObject* InPayer)
{
	Player = InPayer;
	Dynamic_Cast();
}

void ObjectManager::AddObject(CObject* InObject)
{
	OBJvector.push_back(InObject);
}

CObject* ObjectManager::GetPlayer()
{
	return Player;
}

std::vector<CObject*> ObjectManager::Get_Object()
{
	return OBJvector;
}

void ObjectManager::SetVectorSize(std::vector<CObject*> InVC)
{
	OBJvector.swap(InVC);
}


bool ObjectManager::Player_Hit()
{
	for(int i = 0 ;i < OBJvector.size(); ++i)
	{
		if (OBJvector[i]->GetObjectType() == EOBJ_TYPE::RECTANGLE || OBJvector[i]->GetObjectType() == EOBJ_TYPE::Bullet)
		{
			if(!CheckCollision(Player->GetPosition(), Player->GetScale(), OBJvector[i]->GetPosition(), OBJvector[i]->GetScale()))
				continue;

			OBJvector.erase(OBJvector.begin() + i);
			return true;
		}

	}
	return false;
}

void ObjectManager:: Dynamic_Cast()
{
	testPobj = static_cast<CPlayer*>(Player);
}

