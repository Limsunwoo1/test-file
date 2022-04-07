#pragma once

#define SINGLE(type) \
private: \
	type(); \
	~type(); \
public: \
	static type* GetInstance() \
	{ \
		static type* Instance; \
		if(Instance == nullptr) \
			Instance = new type(); \
		return Instance; \
	}

#define KEY_STATE(InKey) CKeyManager::GetInstance()->GetKeyState(InKey)

