#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "Ball.hpp"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    // auto scene = Scene::create();
    auto scene = Scene::createWithPhysics();
    
    // scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    
    scene->getPhysicsWorld()->setGravity(Vec2(0, 0));
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    log("sprite began... x = %f, y = %f", visibleSize.width, visibleSize.height);
    
    
    auto background = Sprite::create("res/background.png");
    
    background->setPosition(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y);
    
    this->addChild(background);
    
    auto edgeSp = Sprite::create();
    
    // 创建一个静态四边形刚体，表示屏幕四边
    auto body = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 3);
    
    edgeSp->setPosition(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y);
    
    PhysicsShape* es = body->getShape(0);
    
    es->setFriction(0.0f);
    
    es->setRestitution(1.0f);
    
    edgeSp->setPhysicsBody(body);
    
    this->addChild(edgeSp);
    
    auto touchListener = EventListenerTouchOneByOne::create();
    // 设置是否吞没事件，在 onTouchBegan 方法返回 true 时吞没
    // listener1->setSwallowTouches(true);
    
    // 使用 lambda 实现 onTouchBegan 事件回调函数
    
    touchListener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);// 触摸开始时触发
    touchListener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);// 触摸移动时触发
    touchListener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);// 触摸移动时触发
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    int arraySize = sizeof(Sprite *) * ballNumber;//数组尺寸大小
    b_matrix = (Sprite **)malloc(arraySize);//为m_matrix分配内存，这里m_matrix是指向指针类型的指针，其定义为：SushiSprite **m_matrix。所以可以理解为m_matrix是一个指针数组
    memset((void*)b_matrix, 0, arraySize);//初始化数组m_matrix
    
    
    for (int i=0; i<ballNumber; i++) {
        
        addBall(i);
        
    }
    
    for (int i=0; i<10; i++) {
        
        addTriangle();
        
    }
    
    for (int i=0; i<10; i++) {
        
        addRect();
        
    }
    
    return true;
}


//物理引擎  应用程序入口
void HelloWorld::onEnter(){
    
    //父类onEnter
    Layer::onEnter();
    
    //添加一个物理元素
    //addBall(visibleSize.width / 2, visibleSize.height / 2);

}

Sprite *HelloWorld::ballOfPoint(Point *point)
{
    Sprite *ball = NULL;
    Rect rect = Rect(0, 0, 0, 0);
    
    for (int i = 0; i < ballNumber; i++) {
        ball = b_matrix[i];
        if (ball) {
            rect.origin.x = ball->getPositionX() - (ball->getContentSize().width / 2);
            rect.origin.y = ball->getPositionY() - (ball->getContentSize().height / 2);
            rect.size = ball->getContentSize();
            if (rect.containsPoint(*point)) {
                return ball;
            }
        }
    }
    return NULL;
}

bool HelloWorld::onTouchBegan(Touch *touch, Event *unused)
{
    b_srcBall = NULL;
        
    auto location = touch->getLocation();//获取触摸屏幕时对应的坐标
    
    log("sprite began... x = %f, y = %f", location.x, location.y);
            
    b_srcBall= ballOfPoint(&location);
    
    if(b_srcBall){
        
    auto body = PhysicsBody::createCircle(b_srcBall->getContentSize().width / 2);
    
    //body->setVelocity(Vect(0, 0));
        
    body->setDynamic(false);
    
    b_srcBall->setPhysicsBody(body);
    }

    //this->removeChild(b_srcBall);
    
    return true;
}

void HelloWorld::onTouchMoved(Touch *touch, Event *event)
{
    b_destBall = NULL;
    
    log("onTouchMoved");
    
    if (!b_srcBall) {
        
        return;
    }
    
    auto location = touch->getLocation();
    
    b_destBall= ballOfPoint(&location);
    
    if(b_destBall){
        
        auto body = PhysicsBody::createCircle(b_destBall->getContentSize().width / 2);
        
        body->setVelocity(Vect(0, 0));
        
        b_destBall->setPhysicsBody(body);
    }


}


void HelloWorld::onTouchEnded(Touch *touch, Event *unused)
{

    this->removeChild(b_srcBall);
    
    this->removeChild(b_destBall);
}

void HelloWorld::addBall(int a){
    
    //创建一个Sprite对象
    
    auto ball = Sprite::create("res/yellow.png");
    
    // b->setScale(0.2);
    //设置物理Body
    // b->setPhysicsBody(PhysicsBody::createBox(b->getContentSize()));
    
    auto body = PhysicsBody::createCircle(ball->getContentSize().width / 2);
    
    body->setVelocity(Vect(CCRANDOM_0_1()*100, CCRANDOM_0_1()*100));
    
    PhysicsShape* ps = body->getShape(0);
    
    ps->setMoment(0);
    
    ps->setMass(1.0f);
    
    ps->setDensity(0.2f);
    
    ps->setFriction(0.0f);
    
    ps->setRestitution(1);
    
    ball->setPhysicsBody(body);
    
    ball->setPosition(CCRANDOM_0_1()*100+100 + origin.x ,300 + origin.y);
    
    this->addChild(ball);
    
    b_matrix[a] = ball;
    
}

void HelloWorld::addTriangle(){
    
    //创建一个Sprite对象
    
    auto triangle = Sprite::create("res/triangle.png");
    
    // b->setScale(0.2);
    //设置物理Body
    // b->setPhysicsBody(PhysicsBody::createBox(b->getContentSize()));
    
    auto body = PhysicsBody::createCircle(triangle->getContentSize().width / 2);
    
    body->setVelocity(Vect(CCRANDOM_0_1()*100, CCRANDOM_0_1()*100));
    
    PhysicsShape* ps = body->getShape(0);
    
    ps->setMoment(0);
    
    ps->setMass(1.0f);
    
    ps->setDensity(0.2f);
    
    ps->setFriction(0.0f);
    
    ps->setRestitution(1);
    
    triangle->setPhysicsBody(body);
    
    triangle->setPosition(CCRANDOM_0_1()*100+100 + origin.x ,300 + origin.y);
    
    this->addChild(triangle);
    
}

void HelloWorld::addRect(){
    
    //创建一个Sprite对象
    
    auto rect = Sprite::create("res/rect.png");
    
    // b->setScale(0.2);
    //设置物理Body
    // b->setPhysicsBody(PhysicsBody::createBox(b->getContentSize()));
    
    auto body = PhysicsBody::createCircle(rect->getContentSize().width / 2);
    
    body->setVelocity(Vect(CCRANDOM_0_1()*100, CCRANDOM_0_1()*100));
    
    PhysicsShape* ps = body->getShape(0);
    
    ps->setMoment(0);
    
    ps->setMass(1.0f);
    
    ps->setDensity(0.2f);
    
    ps->setFriction(0.0f);
    
    ps->setRestitution(1);
    
    rect->setPhysicsBody(body);
    
    rect->setPosition(CCRANDOM_0_1()*100+100 + origin.x ,300 + origin.y);
    
    this->addChild(rect);
    
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
    
    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/
    
    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
    
    
}
