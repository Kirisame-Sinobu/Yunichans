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
#include "MoveBallComponent.hpp"
#include "Game.h"

Ball::Ball()
    :Actor()
{
    mMoveBallComp = new MoveBallComponent(this);
    mMeshComp = new MeshComponent(this);
//    mMeshComp->SetMesh(_gameInstance -> GetRenderer() ->GetMesh("Assets/Sphere.gpmesh"));
    mMeshComp->SetMesh(_gameInstance -> GetRenderer() ->GetMesh("Assets/Sphere.gpmesh"));
}

void Ball::UpdateActor(float deltaTime)
{
    
}

void Ball::ActorInput(const uint8_t* keys)
{
    
}
