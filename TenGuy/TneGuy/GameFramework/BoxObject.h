#pragma once
#include "Object.h"
class BoxObject : public CObject
{
protected:
	int speed;
public:
	BoxObject();
	BoxObject(POINT InPoint, POINT InScale, int Speed);
	~BoxObject();

	virtual void Update(float InDeltaTime) override;
	void BoxRemove();
	void Hit();

};

