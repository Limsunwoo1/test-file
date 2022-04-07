#pragma once
#include "Array.h"
#include "Object.h"
#include "Define.h"
#include "Player.h"
#include <vector>
#define USER = 0;
#define BULLET = 1;
#define HURDLE = 2;


class ObjectManager
{
	SINGLE(ObjectManager);
private:
	std::vector<CObject*> OBJvector;
	//CArray<CObject*> BulletArray;
	CObject* Player;
	CPlayer* testPobj;
public:
	void Init();
	void Update(float InDeltaTime);
	void Render(HDC Inhdc);

	void SetPlayer(CObject* InPlayer);
	void AddObject(CObject* InObject);

	CObject* GetPlayer();
	std::vector<CObject*>Get_Object();
	void SetVectorSize(std::vector<CObject*> InVC);
	bool Player_Hit();

	void Dynamic_Cast();
};

