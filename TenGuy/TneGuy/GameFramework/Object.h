#pragma once
#include "framework.h"

enum class EOBJ_TYPE {
	RECTANGLE,
	ELLIPSE,
	Player,
	Bullet,
	Max,
};

class CObject
{
protected:
	POINT Position;
	POINT Scale;
	EOBJ_TYPE ObjType;
	
	float ObjDeletaTime = 0.f;
public:
	CObject();
	CObject(POINT InPosition, POINT InScale);
	~CObject();

	void SetPosition(POINT InPosition) { Position = InPosition; }
	POINT GetPosition() { return Position; }

	void SetScale(POINT InScale) { Scale = InScale; }
	POINT GetScale() { return Scale; }

	void SetType(EOBJ_TYPE InType) { ObjType = InType; }

	virtual void Update(float InDeltaTime);
	void Render(HDC InHdc);
	//bool InTerSect(const CObject* InPosition);

	void SetObjectType(EOBJ_TYPE objType);
	EOBJ_TYPE GetObjectType();

	void SetDeltaTime(float InDeltaTime);
	float GetDeltaTime();	
};

