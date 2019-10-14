//
//  Block.hpp
//  Game-mac
//
//  Created by hw17a042 on 2019/10/14.
//  Copyright © 2019 Sanjay Madhav. All rights reserved.
//

#pragma once
#include "Actor.h"


class Block : public Actor
{
public:
    Block();

    void UpdateActor(float deltaTime) override;
    void ActorInput(const uint8_t* keyState) override;
private:
    class MeshComponent* mMeshComp;
};
