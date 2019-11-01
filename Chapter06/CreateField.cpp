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
//    const float start = -500.0f;    //正六面体のとき、FieldHeightとFieldWidthが500増えるごとに-500
    const float size = 1000.0f;
//    const int widthCount = 2;    //床はZ軸、壁はそれぞれX軸Y軸に並べる枚数
//    const int heightCount = 3;    //壁はZ軸（高さ）、床はY軸に並べる枚数
//
//    floorCount = (float)((int)_gameInstance->GetFieldWidth() % 1000 + 1);
//    wallCount = (float)((int)_gameInstance->GetFieldHeight() % 1000 + 1);
    
    
    
    Quaternion q(Vector3::UnitY, -Math::PiOver2);
    //床と天井
    for (int i = 0; i < mWallCount; i++)
    {
        for (int j = 0; j < mWallCount; j++)
        {
            Wall* wall = new Wall();
            wall->SetPosition(Vector3(-mStart + i * size + (size/2.0f), -mStart + j * size + (size/2.0f), -mStart));
            
            wall = new Wall();
            wall->SetPosition(Vector3(-mStart + i * size + (size/2.0f), -mStart + j * size + (size/2.0f), mStart));
        }
    }
    //左右壁
    q = Quaternion(Vector3::UnitX, Math::PiOver2);
    for (int i = 0; i < mWallCount; i++)
    {
        for(int j = 0; j < mWallCount; j++){
            Wall* wall = new Wall();
            wall->SetPosition(Vector3(-mStart + i * size + (size / 2.0f), mStart, -mStart + j * size + (size / 2.0f)));
            wall->SetRotation(q);
            
            wall = new Wall();
            wall->SetPosition(Vector3(-mStart + i * size + (size / 2.0f), -mStart, -mStart + j * size + (size / 2.0f)));
            wall->SetRotation(q);
        }
    }
    
    //上下壁
    q = Quaternion::Concatenate(q,Quaternion(Vector3::UnitZ, Math::PiOver2));
    for (int i = 0; i < mWallCount; i++)
    {
        for (int j = 0; j < mWallCount; j++){
            Wall* wall = new Wall();
            wall->SetPosition(Vector3(_gameInstance->GetFieldWidth(), -mStart + i * size + (size / 2.0f), -mStart + j * size + (size / 2.0f)));
            wall->SetRotation(q);
        
            wall = new Wall();
            wall->SetPosition(Vector3(-(_gameInstance->GetFieldWidth()), -mStart + i * size + (size / 2.0f), -mStart + j * size + (size / 2.0f)));
            wall->SetRotation(q);
        }
    }
}
