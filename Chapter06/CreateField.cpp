//
//  CreateField.cpp
//  Chapter06-mac
//
//  Created by hw17a036 on 2019/10/28.
//  Copyright © 2019年 Sanjay Madhav. All rights reserved.
//

#include "CreateField.hpp"
#include "Game.h"
#include "Wall.hpp"

CreateField::CreateField()
    :Actor()
{
    const float start = -500.0f;
    const float size = 1000.0f;
//    float floorCount;    //床並べる枚数
//    float wallCount;    //壁並べる枚数
//    
//    floorCount = (float)((int)_gameInstance->GetFieldWidth() % 1000 + 1);
//    wallCount = (float)((int)_gameInstance->GetFieldHeight() % 1000 + 1);
    
    
    
    Quaternion q(Vector3::UnitY, -Math::PiOver2);
    //床
    for (int i = 0; i < 5/*(int)floorCount*/; i++)
    {
        for (int j = 0; j < 5/*(int)floorCount*/; j++)
        {
            Wall* wall = new Wall();
            wall->SetPosition(Vector3(start + i * size, start + j * size, -(_gameInstance->GetFieldHeight())));
            
            wall = new Wall();
            wall->SetPosition(Vector3(start + i * size, start + j * size, _gameInstance->GetFieldHeight()));
        }
    }
    //左右壁
//    q = Quaternion(Vector3::UnitX, Math::PiOver2);
    q = Quaternion(Vector3::UnitX, Math::PiOver2);
    for (int i = 0; i < 5/*(int)wallCount*/; i++)
    {
        Wall* wall = new Wall();
        wall->SetPosition(Vector3(start + i * size, /*start - size*/_gameInstance->GetFieldWidth(), 0.0f));
        wall->SetRotation(q);
        
        wall = new Wall();
        wall->SetPosition(Vector3(start + i * size, /*-start + size*/-(_gameInstance->GetFieldWidth()), 0.0f));
        wall->SetRotation(q);
    }
    
    //上下壁
    q = Quaternion::Concatenate(q,Quaternion(Vector3::UnitZ, Math::PiOver2));
    for (int i = 0; i < 5/*(int)wallCount*/; i++)
    {
        Wall* wall = new Wall();
        wall->SetPosition(Vector3(/*start - size*/_gameInstance->GetFieldWidth(), start + i * size, 0.0f));
        wall->SetRotation(q);
        
        wall = new Wall();
        wall->SetPosition(Vector3(/*-start + size*/-(_gameInstance->GetFieldWidth()), start + i * size, 0.0f));
        wall->SetRotation(q);
    }
}
