//
//  Ball.hpp
//  Game-mac
//
//  Created by hw17a042 on 2019/10/14.
//  Copyright © 2019 Sanjay Madhav. All rights reserved.
//

#pragma once
#include "Actor.h"


class Ball : public Actor
{
public:
    Ball(const Vector3& pos = Vector3(0,0,0));

    void UpdateActor(float deltaTime) override;
    void ActorInput(const uint8_t* keyState) override;
    void Hit_Actor(int pos) override;
    std::string Get_Name(){return mName;}
private:
    class MeshComponent *mMeshComp;
    class MoveBallComponent *mMoveBallComp;
    std::string mName = "Ball";
};
