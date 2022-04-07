#pragma once
#include "Object.h"
#include "ObjectManager.h"
class BulletObject :public CObject
{
	
public:

	BulletObject();
	BulletObject(POINT InPosition, POINT InScale);
	~BulletObject();

	virtual void Update(float InDeltaTime) override;
	/*virtual void Render(HDC InHdc) override;*/

	void BulletRemove();
	//void BulletInterSet();

};



