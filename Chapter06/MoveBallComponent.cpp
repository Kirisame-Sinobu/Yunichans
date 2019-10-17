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

MoveBallComponent::MoveBallComponent(class Actor* owner, int updateOrder)
:Component(owner, updateOrder)
,mAngularSpeed(0.0f)
,mForwardSpeed(0.0f)
{
    mSpeed = Vector3(1,1,2) * 60;
}

Vector3 x_direction = Vector3(-1,1,1);
Vector3 y_direction = Vector3(1,-1,1);
Vector3 z_direction = Vector3(1,1,-1);
int hit_pos = 7;

void MoveBallComponent::Update(float deltaTime)
{
    Vector3 my_pos = mOwner -> GetPosition();
    if(my_pos.x > 500 && hit_pos != 0){
        mSpeed = x_direction * mSpeed;
        hit_pos = 0;
        printf("x:");
        printf("mspeed = %f,%f,%f\n",mSpeed.x,mSpeed.y,mSpeed.z);
    }else if(my_pos.x < -500 && hit_pos != 1){
        mSpeed = x_direction * mSpeed;
        hit_pos = 1;
        printf("-x:");
        printf("mspeed = %f,%f,%f\n",mSpeed.x,mSpeed.y,mSpeed.z);
    }
    if(my_pos.y > 500 && hit_pos != 2){
        mSpeed = y_direction * mSpeed;
        hit_pos = 2;
        printf("y:");
    }else if(my_pos.y < -500 && hit_pos != 3){
        mSpeed = y_direction * mSpeed;
        hit_pos = 3;
        printf("-y:");
        printf("mspeed = %f,%f,%f\n",mSpeed.x,mSpeed.y,mSpeed.z);
    }
    if(my_pos.z > 500 && hit_pos != 4){
        mSpeed = z_direction * mSpeed;
        hit_pos = 4;
        printf("z:");
        printf("mspeed = %f,%f,%f\n",mSpeed.x,mSpeed.y,mSpeed.z);
    }else if(my_pos.z < -500 && hit_pos != 5){
        mSpeed = z_direction * mSpeed;
        hit_pos = 5;
        printf("-z:");
        printf("mspeed = %f,%f,%f\n",mSpeed.x,mSpeed.y,mSpeed.z);
    }
//    printf("my_pos.x = %f\n",my_pos.x);
//    printf("my_pos.y = %f\n",my_pos.y);
//    printf("my_pos.z = %f\n",my_pos.z);
    mOwner -> SetPosition(mOwner -> GetPosition() + mSpeed);
}