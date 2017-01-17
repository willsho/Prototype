//
//  Ball.hpp
//  GamePrototype
//
//  Created by Will Wang on 2017/1/10.
//
//

#ifndef Ball_hpp
#define Ball_hpp

#include <stdio.h>
#include "cocos2d.h"

using namespace cocos2d;

class Ball:public Sprite{
    
public:
    
    virtual bool init();
    
    virtual void update(float dt);
    
    CREATE_FUNC(Ball);
    
private:
    
    float speedX,speedY;
    
    Size visibleSize;
};

#endif /* Ball_hpp */
