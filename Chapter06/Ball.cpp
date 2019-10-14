//
//  Ball.cpp
//  Game-mac
//
//  Created by hw17a042 on 2019/10/14.
//  Copyright © 2019 Sanjay Madhav. All rights reserved.
//

#include "Ball.hpp"
#include "Renderer.h"
#include "MeshComponent.h"
#include "MoveComponent.h"
#include "Game.h"

Ball::Ball()
    :Actor()
{
    mMoveComp = new MoveComponent(this);
    mMeshComp = new MeshComponent(this);
    mMeshComp->SetMesh(_gameInstance -> GetRenderer() ->GetMesh("Assets/Cube.gpmesh"));
}

void Ball::UpdateActor(float deltaTime)
{
    
}

void Ball::ActorInput(const uint8_t* keyState)
{
}
