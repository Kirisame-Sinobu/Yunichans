//
//  Key_move.hpp
//  Game-mac
//
//  Created by hw17a042 on 2019/10/21.
//  Copyright © 2019 Sanjay Madhav. All rights reserved.
//

#pragma once
#include "Component.h"

class Key_move : public Component
{
public:
    // Lower update order to update first
    Key_move(class Actor* owner, int updateOrder = 10);
    void Update(float deltaTime) override;
    
    float GetForwardSpeed() const { return mForwardSpeed; }
    void SetForwardSpeed(float speed) { mForwardSpeed = speed; }
    float GetLight_speed() const {return mLeft_speed;}
    void SetLight_speed(float speed) {mLeft_speed = speed;}
    
private:
    float mForwardSpeed;
    float mLeft_speed;
};
