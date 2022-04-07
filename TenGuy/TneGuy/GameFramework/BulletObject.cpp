#include "BulletObject.h"
#include <iostream>

BulletObject::BulletObject()
	:CObject()
{

}
BulletObject::BulletObject(POINT InPosition, POINT InScale)
	: CObject(InPosition, InScale) 
{
	
}

BulletObject::~BulletObject()
{
	
}


void BulletObject::Update(float InDeltaTime)
{
	Position.x += 2100 * InDeltaTime;
	//BulletInterSet();
	BulletRemove();
 }


void BulletObject::BulletRemove()
{
	for (int i = 0; i < ObjectManager::GetInstance()->Get_Object().size(); ++i)
	{
		std::vector<CObject*> InVecotr = ObjectManager::GetInstance()->Get_Object();

		if (InVecotr[i]->GetObjectType() == EOBJ_TYPE::ELLIPSE)
		{
			if (InVecotr[i]->GetPosition().x >= 980)
			{
				InVecotr.erase(InVecotr.begin() + i);
				ObjectManager::GetInstance()->SetVectorSize(InVecotr);
				InVecotr.clear();

				//std::cout << "총알 삭제"  << std::endl;
				continue;
			}
		}
		else
		{

		}
		
		// List 
		// 배열 1 2 3 4(x) 5 
		// 
	}
}

//void  BulletObject::BulletInterSet()
//{
//	for (int i = 0; i < ObjectManager::GetInstance()->Get_Object().size(); ++i)
//	{
//		std::vector<CObject*> InVecotr = ObjectManager::GetInstance()->Get_Object();
//
//		if (InVecotr[i]->GetObjectType() == EOBJ_TYPE::RECTANGLE)
//		{
//			/*if (Position.x - (Scale.x * 0.5) < AB[i]->GetPosition().x || Position.y - (Scale.y * 0.5) < AB[i]->GetPosition().y ||
//				Position.x + (Scale.x * 0.5) > AB[i]->GetPosition().x || Position.y + (Scale.y * 0.5) > AB[i]->GetPosition().y)
//				continue;*/
//			if (Position.x + (Scale.x * 0.3) > InVecotr[i]->GetPosition().x - (Scale.x * 0.5) ||
//				Position.x - (Scale.x * 0.3) < InVecotr[i]->GetPosition().x + (Scale.x * 0.5))
//			{
//				//delete AB[i];
//
//				continue;
//
//				/*std::cout << AB[i]->GetPosition().x + (AB[i]->GetScale().x * 0.5) << std::endl;
//				std::cout << "충돌" << std::endl;*/
//				//delete ObjectManager::GetInstance()->Get_Object()[i];
//
//			}
//			else if (Position.y + (Scale.y * 0.5) < InVecotr[i]->GetPosition().y - (Scale.y * 0.5) ||
//				Position.y - (Scale.y * 0.5) > InVecotr[i]->GetPosition().y + (Scale.y * 0.5))
//			{
//				continue;
//			}
//			else
//			{
//				static int A = 0;
//				//delete InVecotr[i];
//
//				InVecotr.erase(InVecotr.begin() + i);
//				ObjectManager::GetInstance()->SetVectorSize(InVecotr);
//				InVecotr.clear();
//
//				//std::cout << Position.x << std::endl;
//				std::cout << "충돌" << A++ << std::endl;
//			}
//			
//		}
//		else
//		{
//
//		}
//	}
//}
//void BulletObject::Render(HDC InHdc)
//{
// 	/*Ellipse(InHdc,
//		Position.x - (Scale.x * 0.3f),
//		Position.y - (Scale.y * 0.3f),
//		Position.x + (Scale.x * 0.3f),
//		Position.y + (Scale.y * 0.3f));*/
//}