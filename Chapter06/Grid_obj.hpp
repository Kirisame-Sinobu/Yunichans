//
//  Grid_obj.hpp
//  Game-mac
//
//  Created by hw17a042 on 2019/10/17.
//  Copyright © 2019 Sanjay Madhav. All rights reserved.
//

#pragma once
#include "Actor.h"


class Grid : public Actor
{
public:
    Grid();

    void UpdateActor(float deltaTime) override;
    void ActorInput(const uint8_t* keyState) override;
private:
//    class MeshComponent* mMeshComp;
    std::string mName = "Grid";
};
