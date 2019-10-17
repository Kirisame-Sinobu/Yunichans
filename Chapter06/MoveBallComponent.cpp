//
//  MoveBall.cpp
//  Game-mac
//
//  Created by hw17a042 on 2019/10/14.
//  Copyright © 2019 Sanjay Madhav. All rights reserved.
//

#include "MoveBallComponent.hpp"
#include "Actor.h"

MoveBallComponent::MoveBallComponent(class Actor* owner, int updateOrder)
:Component(owner, updateOrder)
,mAngularSpeed(0.0f)
,mForwardSpeed(0.0f)
{
    
}

void MoveBallComponent::Update(float deltaTime)
{
    Vector3 now_pos = mOwner -> GetForward();
//    if(now_pos > )
    
    
    if (!Math::NearZero(mAngularSpeed))
    {
        Quaternion rot = mOwner->GetRotation();
        float angle = mAngularSpeed * deltaTime;
        // Create quaternion for incremental rotation
        // (Rotate about up axis)
        Quaternion inc(Vector3::UnitZ, angle);
        // Concatenate old and new quaternion
        rot = Quaternion::Concatenate(rot, inc);
        mOwner->SetRotation(rot);
    }
    
    if (!Math::NearZero(mForwardSpeed))
    {
        Vector3 pos = mOwner->GetPosition();
        pos += mOwner->GetForward() * mForwardSpeed * deltaTime;
        mOwner->SetPosition(pos);
    }
}
