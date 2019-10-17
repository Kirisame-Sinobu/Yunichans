//
//  Grid_obj.cpp
//  Game-mac
//
//  Created by hw17a042 on 2019/10/17.
//  Copyright © 2019 Sanjay Madhav. All rights reserved.
//

#include "Grid_obj.hpp"
#include "Game.h"
#include "Block.hpp"
//#include "Renderer.h"
//#include "MeshComponent.h"

Grid::Grid()
    :Actor()
{
    int grid_num = 201;
    //x軸のグリット制作
    for(int x = 0; x < grid_num; x++){
        Block* block = new Block();
        block->SetPosition(Vector3((-(grid_num/2 * 100) + 100.0f * x), 0, 0.0f));
        block->SetScale(10.0f);
//        Quaternion q(Vector3::UnitY, -Math::Pi);
//        q = Quaternion::Concatenate(q, Quaternion(Vector3::UnitZ, Math::Pi));
//        block->SetRotation(q);
    }
       //y軸のグリット制作
    for(int y = 0; y < grid_num; y++){
        Block* block = new Block();
        block->SetPosition(Vector3(0.0f,(-(grid_num/2 * 100) + 100.0f * y), 0.0f));
        block->SetScale(10.0f);
    }
    //z軸のグリット制作
     for(int z = 0; z < grid_num; z++){
         Block* block = new Block();
         block->SetPosition(Vector3(0.0f, 0.0f,(-(grid_num/2 * 100) + 100.0f * z)));
         block->SetScale(10.0f);
     }
}

void Grid::UpdateActor(float deltaTime)
{
    
}

void Grid::ActorInput(const uint8_t* keyState)
{
}
