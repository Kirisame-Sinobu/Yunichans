// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
//
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "Block.hpp"
#include "MeshComponent.h"
#include "Game.h"
#include "Renderer.h"
#include "Ball.hpp"

Block::Block()
    :Actor()
{
    mMeshComp = new MeshComponent(this);
    mMeshComp->SetMesh(_gameInstance -> GetRenderer() ->GetMesh("Assets/Cube.gpmesh"));
    SetName("Block");
//    printf("hogehoge");
}

Block::~Block(){
    Ball* ball = new Ball(Vector3(GetPosition()));
//    ball->SetPosition(GetPosition());
//    ball->SetScale(3.0f);
}

void Block::UpdateActor(float deltaTime)
{
    
}

void Block::ActorInput(const uint8_t* keyState)
{
    
}

void Block::Hit_Actor(int pos)
{
    SetState(EDead);
}
