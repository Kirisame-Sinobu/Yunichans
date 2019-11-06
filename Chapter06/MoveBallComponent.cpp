//
//  MoveBall.cpp
//  Game-mac
//
//  Created by hw17a042 on 2019/10/14.
//  Copyright © 2019 Sanjay Madhav. All rights reserved.
//

#include "MoveBallComponent.hpp"
#include "Actor.h"
#include <stdio.h>
#include "Game.h"

MoveBallComponent::MoveBallComponent(class Actor* owner, int updateOrder)
:Component(owner, updateOrder)
,mAngularSpeed(0.0f)
,mForwardSpeed(0.0f)
{
    mSpeed = Vector3(1,1,2) * 30;
}

Vector3 x_direction = Vector3(-1,1,1);
Vector3 y_direction = Vector3(1,-1,1);
Vector3 z_direction = Vector3(1,1,-1);

void MoveBallComponent::Update(float deltaTime)
{
//    int baund_under_pos = 200;
//    int side_pos = 500;
    Vector3 my_pos = mOwner -> GetPosition();
    if(my_pos.x > /*side_pos*/_gameInstance->GetFieldWidth() - (mOwner->GetState()) && mSpeed.x > 0){
        mSpeed = x_direction * mSpeed;
//        printf("x:");
//        printf("mspeed = %f,%f,%f\n",mSpeed.x,mSpeed.y,mSpeed.z);
    }else if(my_pos.x < /*-side_pos*/-(_gameInstance->GetFieldWidth()) + (mOwner->GetScale()) && mSpeed.x < 0){
        mSpeed = x_direction * mSpeed;
//        printf("-x:");
//        printf("mspeed = %f,%f,%f\n",mSpeed.x,mSpeed.y,mSpeed.z);
    }
    if(my_pos.y > /*baund_under_pos*/_gameInstance->GetFieldWidth() - (mOwner->GetScale()) && mSpeed.y > 0){
        mSpeed = y_direction * mSpeed;
//        printf("y:");
    }else if(my_pos.y < /*-baund_under_pos*/-(_gameInstance->GetFieldWidth()) + (mOwner->GetScale()) && mSpeed.y < 0){
        mSpeed = y_direction * mSpeed;
//        printf("-y:");
//        printf("mspeed = %f,%f,%f\n",mSpeed.x,mSpeed.y,mSpeed.z);
    }
    if(my_pos.z > /*side_pos*/_gameInstance->GetFieldWidth() - (mOwner->GetScale()) && mSpeed.z > 0){
        mSpeed = z_direction * mSpeed;
//        printf("z:");
//        printf("mspeed = %f,%f,%f\n",mSpeed.x,mSpeed.y,mSpeed.z);
    }else if(my_pos.z < /*-side_pos*/-(_gameInstance->GetFieldWidth()) + (mOwner->GetScale()) && mSpeed.z < 0){
        mSpeed = z_direction * mSpeed;
//        printf("-z:");
//        printf("mspeed = %f,%f,%f\n",mSpeed.x,mSpeed.y,mSpeed.z);
    }
//    printf("my_pos.x = %f\n",my_pos.x);
//    printf("my_pos.y = %f\n",my_pos.y);
//    printf("my_pos.z = %f\n",my_pos.z);
    mOwner -> SetPosition(mOwner -> GetPosition() + mSpeed);
}

void MoveBallComponent::Hit_block(int pos){
    
    if(pos == 1){
        mSpeed = x_direction * mSpeed;
    }else{
        mSpeed = z_direction * mSpeed;
    }
    
    
    
    
    
}
