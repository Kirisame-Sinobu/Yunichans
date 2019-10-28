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

class CreateField : public Actor
{
public:
    CreateField();
    
    void CreateSideWall();
    void CreateUpWall();
    
    
};

#endif /* CreateField_hpp */
