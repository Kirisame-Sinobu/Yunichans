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
//    mMeshComp->SetMesh(_gameInstance -> GetRenderer() ->GetMesh("Assets/Sphere.gpmesh"));
    mMeshComp->SetMesh(_gameInstance -> GetRenderer() ->GetMesh("Assets/Sphere.gpmesh"));
}

void Ball::UpdateActor(float deltaTime)
{
    
}

void Ball::ActorInput(const uint8_t* keys)
{
    float forwardSpeed = 0.0f;
    float angularSpeed = 0.0f;
    // wasd movement
    if (keys[SDL_SCANCODE_W])
    {
        forwardSpeed += 300.0f;
    }
    if (keys[SDL_SCANCODE_S])
    {
        forwardSpeed -= 300.0f;
    }
    if (keys[SDL_SCANCODE_A])
    {
        angularSpeed -= Math::TwoPi;
    }
    if (keys[SDL_SCANCODE_D])
    {
        angularSpeed += Math::TwoPi;
    }

    mMoveComp->SetForwardSpeed(forwardSpeed);
    mMoveComp->SetAngularSpeed(angularSpeed);
}
