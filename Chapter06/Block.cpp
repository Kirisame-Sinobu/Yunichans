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

Block::Block()
    :Actor()
{
    mMeshComp = new MeshComponent(this);
    mMeshComp->SetMesh(_gameInstance -> GetRenderer() ->GetMesh("Assets/Cube.fbx"));
}

void Block::UpdateActor(float deltaTime)
{
    
}

void Block::ActorInput(const uint8_t* keyState)
{
}
