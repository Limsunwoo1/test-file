#include "MainGame.h"
#include "TimerManager.h"
#include "KeyManager.h"
#include "Player.h"
#include <iostream>
#include <windows.h>
std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<int> dis(0, 980);
std::uniform_int_distribution<int> Dis(50, 150);

// 과제
// 총알에 공격속도를 가지게해서 주기적으로 발사할수있도록
// 박스 오브젝트도 주기적으로 총알을 발사하도록
// Life 를 추가해서 일정 체력이 소모되면 게임이 종료되게 할것
// 시작화면 만들어보기

// 다음에는 Scene, Layer의 개념, UI, 마우스 입력이벤트 를 할것

CMainGame::CMainGame()
{

}

CMainGame::~CMainGame()
{
	SelectObject(BackHdc, BitMap);
	DeleteObject(BackBitMap);
	DeleteDC(BackHdc);

	delete Player;
}

void CMainGame::Init(HWND InHwnd, HINSTANCE InHInstance)
{
	HInstance = InHInstance;
	Hwnd = InHwnd;
	Hdc = GetDC(Hwnd);

	// 싱글턴들 초기화 구간
	ObjectManager::GetInstance()->Init();
	CTimerManager::GetInstance()->Init();
	CKeyManager::GetInstance()->Init();
	//

	// 더블버퍼링
	BackHdc = CreateCompatibleDC(Hdc);
	BackBitMap = CreateCompatibleBitmap(Hdc, 1920, 1080);
	BitMap = (HBITMAP)SelectObject(BackHdc, BackBitMap);     // 이부분 이해안감

	Player = new CPlayer();
	Player->SetObjectType(EOBJ_TYPE::Player);
	ObjectManager::GetInstance()->SetPlayer(Player);

	BoxSpawnCoolTimeMax = 0.3f;
	BoxSpawnCoolTimeCurrent = 0.f;

	BoxAttackObjectSpawnCoolTimeMax = 0.1f;
	BoxAttackObjectSpawnCoolTimeCurrent = 0.f;
}

void CMainGame::Logic()
{
	CTimerManager::GetInstance()->Update();
	float deltaTime = CTimerManager::GetInstance()->GetDeltaTime();
	Update(deltaTime);
	Render();
}

void CMainGame::Update(float InDeltaTime)
{
	CObject* test_Obj = ObjectManager::GetInstance()->GetPlayer();        //형 변환
	CPlayer* testPobj = static_cast<CPlayer*>(test_Obj);

	CKeyManager::GetInstance()->Update(InDeltaTime);
	ObjectManager::GetInstance()->Update(InDeltaTime);

	static float currdelta;

	if (testPobj->GetPlayerLIfe() == 0)
		DestroyWindow(Hwnd);

	currdelta += InDeltaTime;
	
	if (ObjectManager::GetInstance()->Player_Hit() == true)
	{
		if (currdelta > 1.0f)
		{
			testPobj->SetPlayerLIfe(testPobj->GetPlayerLIfe() - 1);
			currdelta = 0.f;
		}
	}
	

	BoxSpawnCoolTimeCurrent += InDeltaTime;

	if (BoxSpawnCoolTimeCurrent > BoxSpawnCoolTimeMax)
	{
		BoxSpawnCoolTimeCurrent = 0.f;
		AddBox(InDeltaTime);
	}

	BoxAttackObject(InDeltaTime);           //루프를 돌면서 좌표값 체크	 및 이전에 생성된 박스오브젝트가 지속적인 공격을 할수 있게해야함
}

void CMainGame::Render()
{
	Rectangle(BackHdc, 0, 0, 980, 680);

	ObjectManager::GetInstance()->Render(BackHdc);

	BitBlt(Hdc, 0, 0, 980, 680, BackHdc, 0, 0, SRCCOPY);
}

void CMainGame::AddBox(float InDeltaTime)
{
	int rand = Dis(gen);
	Box = new BoxObject(POINT{ 980 ,dis(gen) }, POINT{ rand ,rand }, 600);
	Box->SetObjectType(EOBJ_TYPE::RECTANGLE);
	Box->SetDeltaTime(InDeltaTime);
	ObjectManager::GetInstance()->AddObject(Box);
}

void CMainGame::BoxAttackObject(float InDeltaTime)
{
	vector<CObject*> InVect = ObjectManager::GetInstance()->Get_Object();
	for (int i = 0; i < InVect.size(); ++i)
	{
		if (InVect[i]->GetObjectType() != EOBJ_TYPE::RECTANGLE)
			continue;

		BoxAttackObjectSpawnCoolTimeCurrent = InVect[i]->GetDeltaTime();
		BoxAttackObjectSpawnCoolTimeCurrent += InDeltaTime;

		if (BoxAttackObjectSpawnCoolTimeCurrent < BoxAttackObjectSpawnCoolTimeMax)
		{
			InVect[i]->SetDeltaTime(BoxAttackObjectSpawnCoolTimeCurrent);
			continue;
		}

		if (BoxAttackObjectSpawnCoolTimeCurrent > BoxAttackObjectSpawnCoolTimeMax)
		{
			BoxAttack = new BoxObject(POINT{ InVect[i]->GetPosition().x, InVect[i]->GetPosition().y }, POINT{ 20,20 }, 1200);
			BoxAttack->SetObjectType(EOBJ_TYPE::Bullet);
			InVect[i]->SetDeltaTime(0.f);

			ObjectManager::GetInstance()->AddObject(BoxAttack);
		}
	}
}

bool CMainGame::MainGameRun()
{
	float deltaTime = CTimerManager::GetInstance()->GetDeltaTime();

	static POINT holdpoint;
	static POINT tappoint;

	static int exit = 0;

	if (exit == 1)
		return true;
	POINT Position{490,340};
	POINT Scale{200,100};
	Rectangle(Hdc,
		Position.x - (Scale.x * 0.5f),
		Position.y - (Scale.y * 0.5f),
		Position.x + (Scale.x * 0.5f),
		Position.y + (Scale.y * 0.5f));

	while (1)
	{
		CKeyManager::GetInstance()->Update(deltaTime);
		if (KEY_STATE(KEY::LBUTTON) == KEY_STATE::HOLD)
		{
			exit = 1;
			GetCursorPos(&holdpoint);
			

		}

		if (KEY_STATE(KEY::LBUTTON) == KEY_STATE::TAP)
		{
			exit = 1;
			GetCursorPos(&tappoint);

			break;
		}
		
		TextOut(Hdc, 450, 10 , L"TEST GAME!!", 11);
		TextOut(Hdc, 450, 340, L"GAME START", 10);
	}

	return true;
}