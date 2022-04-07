#pragma once
#include "Object.h"
class CPlayer :
    public CObject
{
    int Speed;
    int life;

    float	BulletSpawnCoolTimeMax;
    float   BulletSpawnCollTimeCurrent;
public:
    CPlayer();
    ~CPlayer();

    virtual void Update(float InDeltaTime) override;
    void SetPlayerLIfe(int SetLife);
    int GetPlayerLIfe();
};

