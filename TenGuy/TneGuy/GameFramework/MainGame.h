#pragma once
#include "framework.h"
#include "Object.h"
#include "Array.h"
#include "BulletObject.h"
#include "BoxObject.h"
#include "Define.h"
#include <random>
//#include "ObjectManager.h"

class CMainGame
{
	SINGLE(CMainGame);
private:
	HDC Hdc;
	HDC BackHdc;

	HBITMAP BitMap;
	HBITMAP BackBitMap;

	HWND Hwnd;
	HINSTANCE HInstance;

	CArray<CObject*> ObjectArray;
	CObject* Player;
	CObject* Bullet;
	CObject* Box;
	CObject* BoxAttack;

	POINT BoxAttackObjectPosition;

	float	BoxSpawnCoolTimeMax;
	float	BoxSpawnCoolTimeCurrent;

	float	BoxAttackObjectSpawnCoolTimeMax;
	float	BoxAttackObjectSpawnCoolTimeCurrent;
	float	BoxAttackObjectSpawnTimeCurrent;

public:
	void Init(HWND InHwnd, HINSTANCE InHInstance);
	void Logic();

	virtual void Update(float InDeltaTime);
	void Render();
	void AddBox(float InDeltaTime);
	void BoxAttackObject(float InDeltaTime);
	bool MainGameRun();

	HWND GetHwnd() {return Hwnd;}
};

