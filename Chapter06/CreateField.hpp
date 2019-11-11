//
//  CreateField.hpp
//  Chapter06-mac
//
//  Created by hw17a036 on 2019/10/28.
//  Copyright © 2019年 Sanjay Madhav. All rights reserved.
//

#ifndef CreateField_hpp
#define CreateField_hpp

#include <stdio.h>
#include "Actor.h"
#include "Game.h"

class CreateField : public Actor
{
public:
    CreateField();
    
    void CreateSideWall();
    void CreateUpWall();
    
private:
//    float mWidthStart = -500.0f * (_gameInstance->GetFieldWidth() / 500.0f );
//    float mHeightStart = -500.0f * (_gameInstance->GetFieldHeight() / 500.0f) - 1.0f;
//    int mWidthCount = _gameInstance->GetFieldWidth() / 500;
//    int mHeightCount = _gameInstance->GetFieldHeight() / 500;
    float mStart = _gameInstance->GetFieldWidth();
    int mWallCount = (_gameInstance->GetFieldWidth()) / 500;
    
};

#endif /* CreateField_hpp */
