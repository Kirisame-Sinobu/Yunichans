//
//  Bar.cpp
//  Game-mac
//
//  Created by hw17a042 on 2019/10/21.
//  Copyright © 2019 Sanjay Madhav. All rights reserved.
//

#include "Bar.hpp"
#include "Renderer.h"
#include "MeshComponent.h"
#include "Key_move.hpp"
#include "Game.h"

Bar::Bar()
    :Actor()
{
    mKey_move = new Key_move(this);
    
    mMeshComp = new MeshComponent(this);
    mMeshComp->SetMesh(_gameInstance -> GetRenderer() ->GetMesh("Assets/Cube.gpmesh"));
}

void Bar::UpdateActor(float deltaTime)
{
    
}

void Bar::ActorInput(const uint8_t* keys)
{
    float forward_speed = 0.0f;
    float Left_speed = 0.0f;
    // wasd movement
    if (keys[SDL_SCANCODE_L])
    {
        forward_speed += 1000.0f;
    }
    if (keys[SDL_SCANCODE_J])
    {
        forward_speed -= 1000.0f;
    }
    if (keys[SDL_SCANCODE_I])
    {
        Left_speed -= 1000.0f;
    }
    if (keys[SDL_SCANCODE_K])
    {
        Left_speed += 1000.0f;
    }

    mKey_move->SetForwardSpeed(forward_speed);
    mKey_move -> SetLight_speed(Left_speed);
}
