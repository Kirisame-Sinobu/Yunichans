//
//  MoveBall.hpp
//  Game-mac
//
//  Created by hw17a042 on 2019/10/14.
//  Copyright © 2019 Sanjay Madhav. All rights reserved.
//

#pragma once
#include "Component.h"


class MoveBallComponent : public Component
{
public:
    // Lower update order to update first
    MoveBallComponent(class Actor* owner, int updateOrder = 10);
    void Update(float deltaTime) override;
    
    void Hit_block(int pos);
    
    float GetAngularSpeed() const { return mAngularSpeed; }
    float GetForwardSpeed() const { return mForwardSpeed; }
    void SetAngularSpeed(float speed) { mAngularSpeed = speed; }
    void SetForwardSpeed(float speed) { mForwardSpeed = speed; }
private:
    float mAngularSpeed;
    float mForwardSpeed;
    
    Vector3 mSpeed;
};
