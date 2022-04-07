#include "KeyManager.h"
#include <windows.h>

int KeyArr[(int)KEY::MAX] =
{
	VK_SPACE,
	VK_LBUTTON,
	'W',
	'A',
	'S',
	'D'
};

CKeyManager::CKeyManager()
{

}

CKeyManager::~CKeyManager()
{

}

void CKeyManager::Init()
{
	for (int i = 0; i < (int)KEY::MAX; ++i)
	{
		KeyInfoArr.push_back(KeyInfo{KEY_STATE::NONE, false});
	}

}

void CKeyManager::Update(float InDeltaTime)
{
	for (int i = 0; i < (int)KEY::MAX; ++i)
	{
		if (GetAsyncKeyState(KeyArr[i]) & 0x8000)
		{
			if (KeyInfoArr[i].PrevPush)
			{
				KeyInfoArr[i].KeyState = KEY_STATE::HOLD;
			}
			else
			{
				KeyInfoArr[i].KeyState = KEY_STATE::TAP;
			}

			KeyInfoArr[i].PrevPush = true;
		}
		else
		{
			if (KeyInfoArr[i].PrevPush)
			{
				KeyInfoArr[i].KeyState = KEY_STATE::AWAY;
			}
			else
			{
				KeyInfoArr[i].KeyState = KEY_STATE::NONE;
			}

			KeyInfoArr[i].PrevPush = false;
		}
	}
}

KEY_STATE CKeyManager::GetKeyState(KEY InKey)
{
	return KeyInfoArr[(int)InKey].KeyState;
}