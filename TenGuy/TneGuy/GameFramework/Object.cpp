#include "Object.h"

CObject::CObject()
	: Position()
	, Scale()
	, ObjType(EOBJ_TYPE::RECTANGLE)
{

}
CObject::CObject(POINT InPosition, POINT InScale)
	: Position(InPosition)
	, Scale(InScale)
	, ObjType(EOBJ_TYPE::RECTANGLE)
{
	
}
CObject::~CObject()
{

}


void CObject::Update(float InDeltaTime)
{

}

 void CObject::Render(HDC InHdc)
{
	if (ObjType == EOBJ_TYPE::RECTANGLE || ObjType == EOBJ_TYPE::Player)
	{
		Rectangle(InHdc, 
			Position.x - (Scale.x * 0.5f),
			Position.y - (Scale.y * 0.5f),
			Position.x + (Scale.x * 0.5f),
			Position.y + (Scale.y * 0.5f));
	}
	if (ObjType == EOBJ_TYPE::ELLIPSE || ObjType == EOBJ_TYPE::Bullet)
	{
		Ellipse(InHdc,
			Position.x - (Scale.x * 0.5f),
			Position.y - (Scale.y * 0.5f),
			Position.x + (Scale.x * 0.5f),
			Position.y + (Scale.y * 0.5f));
	}
}

 /*bool CObject::InTerSect(const CObject* InPosition)
 {

	 if (Position.x + (Scale.x * 0.5f) >= InPosition->Position.x - (InPosition->Scale.x * 0.5f) ||
		 Position.x - (Scale.x * 0.5f) <= InPosition->Position.x + (InPosition->Scale.x * 0.5f))
		 return true;

	 if (Position.y + (Scale.x * 0.5f) >= InPosition->Position.y - (InPosition->Scale.x * 0.5f) ||
		 Position.y - (Scale.x * 0.5f) <= InPosition->Position.y + (InPosition->Scale.x * 0.5f));
		return true;


	 return false;
 }*/

 void CObject::SetObjectType(EOBJ_TYPE objType)
 {
	 ObjType = objType;
 }

 EOBJ_TYPE CObject::GetObjectType()
 {
	 return ObjType;
 }

 void CObject::SetDeltaTime(float InDeltaTime)
 {
	 ObjDeletaTime = InDeltaTime;
 }
 float CObject::GetDeltaTime()
 {
	 return ObjDeletaTime;
 }