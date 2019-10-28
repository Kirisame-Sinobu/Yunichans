//
//  Wall.cpp
//  Chapter06-mac
//
//  Created by hw17a036 on 2019/10/24.
//  Copyright © 2019年 Sanjay Madhav. All rights reserved.
//

#include "Wall.hpp"
#include "MeshComponent.h"
#include "Game.h"
#include "Renderer.h"

Wall::Wall()
    :Actor()
{
    SetScale(10.0f);
    mMeshComp = new MeshComponent(this);
    mMeshComp->SetMesh(_gameInstance -> GetRenderer() ->GetMesh("Assets/Plane.gpmesh"));
}
