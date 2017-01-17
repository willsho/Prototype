#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Ball.hpp"

class HelloWorld : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
    
    //物理引擎所需的入口
    virtual void onEnter();
    
    Sprite *ballOfPoint(Point *point);
    
    //物理引擎添加物理元素
    void addBall(int a);
    
    void addTriangle();
    
    void addRect();
    
    int ballNumber = 20;
    
    
    
    virtual bool onTouchBegan(Touch *touch, Event *unused) override;
    
    virtual void onTouchMoved(Touch *touch, Event *event) override;
    
    virtual void onTouchEnded(Touch *touch, Event *unused) override;
    
private:
    
    cocos2d::Size visibleSize;
    
    Vec2 origin;
    
    Sprite **b_matrix;
    
    // bool b_isTouchEnable;// is need to deal with touch event
    
    Sprite *b_srcBall;// 用户移动的寿司
    Sprite *b_destBall;
    
};

#endif // __HELLOWORLD_SCENE_H__


