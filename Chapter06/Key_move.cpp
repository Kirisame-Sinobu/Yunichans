//
//  Key_move.cpp
//  Game-mac
//
//  Created by hw17a042 on 2019/10/21.
//  Copyright © 2019 Sanjay Madhav. All rights reserved.
//

#include "Key_move.hpp"
#include "Actor.h"
#include <stdio.h>

Key_move::Key_move(class Actor* owner, int updateOrder)
:Component(owner, updateOrder)
,mForwardSpeed(0.0f)
,mLeft_speed(0.0f)
{
    
}

void Key_move::Update(float deltaTime)
{
//    printf("mforward = %f",mForwardSpeed);
    if (!Math::NearZero(mForwardSpeed))
    {
        Vector3 pos = mOwner->GetPosition();
        pos += Vector3(1,0,0) * mForwardSpeed * deltaTime;
        mOwner->SetPosition(pos);
    }
    if(!Math::NearZero(mLeft_speed)){
        Vector3 pos = mOwner -> GetPosition();
        pos += Vector3(0,1,0) * mLeft_speed * deltaTime;
        mOwner -> SetPosition(pos);
    }
}
