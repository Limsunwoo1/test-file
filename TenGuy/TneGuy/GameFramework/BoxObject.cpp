#include "BoxObject.h"
#include "ObjectManager.h" 
#include <iostream>
#include <vector>
#include "Func.h"

BoxObject::BoxObject()
{

}

BoxObject::BoxObject(POINT InPoint, POINT InScale,int Speed) :
	CObject(InPoint, InScale)
{
	this->speed = Speed;
}

BoxObject::~BoxObject()
{

}

void BoxObject::Update(float InDeltaTime)
{
	Position.x -= speed * InDeltaTime;
	BoxRemove();
	Hit();
}

void BoxObject::BoxRemove()
{
	std::vector<CObject*> InVecotr = ObjectManager::GetInstance()->Get_Object();

	for (int i = 0; i < InVecotr.size(); ++i)
	{
		if (InVecotr[i]->GetObjectType() == EOBJ_TYPE::ELLIPSE)
			continue;

		if (InVecotr[i]->GetPosition().x <= 0)
		{
			InVecotr.erase(InVecotr.begin() + i);
			ObjectManager::GetInstance()->SetVectorSize(InVecotr);
			InVecotr.clear();

			//std::cout << "박스 삭제" << std::endl;
			continue;
		}
	}
}

void BoxObject::Hit()
{
	for (int i = 0; i < ObjectManager::GetInstance()->Get_Object().size(); ++i)
	{
		std::vector<CObject*> InVecotr = ObjectManager::GetInstance()->Get_Object();

		if (InVecotr[i]->GetObjectType() != EOBJ_TYPE::ELLIPSE)
			continue;
		//if (InVecotr[i]->GetObjectType() != EOBJ_TYPE::Bullet)
			
		if (!CheckCollision(Position, Scale, InVecotr[i]->GetPosition(), InVecotr[i]->GetScale()))
				continue;

		InVecotr.erase(InVecotr.begin() + i);
		ObjectManager::GetInstance()->SetVectorSize(InVecotr);
		InVecotr.clear();

		int cnt = 0;
		std::vector<CObject*> InVecotr2 = ObjectManager::GetInstance()->Get_Object();

		for (int i = 0; i < InVecotr2.size(); ++i)
		{
			if (Position.x == InVecotr2[i]->GetPosition().x && Position.y == InVecotr2[i]->GetPosition().y && InVecotr2[i]->GetObjectType() == EOBJ_TYPE::ELLIPSE)
			{
				cnt = i;
				break;
			}
		}
		std::cout << "충돌" << std::endl;
		InVecotr2.erase(InVecotr2.begin() + cnt);
		ObjectManager::GetInstance()->SetVectorSize(InVecotr2);
		InVecotr2.clear();
	}
}