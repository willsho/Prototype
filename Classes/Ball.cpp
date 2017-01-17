//
//  Ball.cpp
//  GamePrototype
//
//  Created by Will Wang on 2017/1/10.
//
//

#include "Ball.hpp"

bool Ball::init(){
    
    Sprite::initWithFile("res/yellow.png");
    
    visibleSize = Director::getInstance()->getVisibleSize();
    
    speedX = CCRANDOM_0_1()*2 - 1;
    
    speedY = 1;
    
    scheduleUpdate();
    
    return true;
    
}

void Ball::update(float dt){
    
    setPosition(getPositionX()+ speedX,getPositionY()+ speedY);
    
    if (getPositionX()<getContentSize().width/2) {
        speedX = fabs(speedX);
    }
    if (getPositionX()>visibleSize.width - getContentSize().width/2) {
        speedX = -fabs(speedX);
    }
    if (getPositionY()<getContentSize().height/2 + 20) {
        speedY = fabs(speedY);
    }
    if (getPositionY()>visibleSize.height + getContentSize().height/2) {
        speedY = -fabs(speedY);
    }
    
    
}
