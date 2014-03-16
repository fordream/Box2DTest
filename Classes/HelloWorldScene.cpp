#include "HelloWorldScene.h"
#include <string>
using namespace std;

USING_NS_CC;
USING_NS_CC_EXT;



HelloWorld::HelloWorld()
{
	m_bIsDebugOpen = true;
}

HelloWorld::~HelloWorld()
{
	CC_SAFE_DELETE(m_ptrPhysicsWorld);
	delete m_ptrDebugDraw;
}

Scene* HelloWorld::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();


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
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();

	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.

	// add a "close" icon to exit the progress. it's an autorelease object

	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

	closeItem->setPosition(Point(origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
		origin.y + closeItem->getContentSize().height / 2));


	auto closeDebugItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(HelloWorld::menuClosePhysicDebugDraw, this));

	closeDebugItem->setPosition(Point(origin.x + visibleSize.width - closeDebugItem->getContentSize().width / 2,
		visibleSize.height/2));


	// create menu, it's an autorelease object
	auto menu = Menu::create(closeItem, closeDebugItem, nullptr);
	menu->setPosition(Point::ZERO);
	this->addChild(menu, 2);

	/////////////////////////////
	// 3. add your codes below...

	// add a label shows "Hello World"
	// create and initialize a label

	auto label = LabelTTF::create("Hello World", "Arial", 24);

	// position the label on the center of the screen
	label->setPosition(Point(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - label->getContentSize().height));

	//add the label as a child to this layer
	this->addChild(label, 1);

	// add "HelloWorld" splash screen"
	/*auto sprite = Sprite::create("HelloWorld.png");*/

	// position the sprite on the center of the screen
	/*sprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));*/

	// add the sprite as a child to this layer
	/*this->addChild(sprite, 0);*/
	m_ptrDebugDraw = new GLESDebugDraw(PTM_RATIO);
	uint32 flags = 0;
	flags += b2Draw::e_shapeBit;
	flags += b2Draw::e_jointBit;
	flags += b2Draw::e_aabbBit;
	flags += b2Draw::e_pairBit;
	flags += b2Draw::e_centerOfMassBit;
	m_ptrDebugDraw->SetFlags(flags);


	initPhysics();

	scheduleUpdate();

	return true;
}


void HelloWorld::menuCloseCallback(Object* pSender)
{
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

void HelloWorld::menuClosePhysicDebugDraw(Object* pSender)
{
	m_bIsDebugOpen = !m_bIsDebugOpen;
}

void HelloWorld::initPhysics()
{
	b2Vec2 gravity;
	gravity.Set(0.0f, -10.0f);
	m_ptrPhysicsWorld = new b2World(gravity);

	m_ptrPhysicsWorld->SetAllowSleeping(true);
	m_ptrPhysicsWorld->SetContinuousPhysics(true);



	m_ptrPhysicsWorld->SetDebugDraw(m_ptrDebugDraw);

	Size visibleSize = Director::getInstance()->getVisibleSize();

	//创建地面
	//默认的type是static
	b2BodyDef groundDef;
	groundDef.position.Set(0, 0);
	b2Body* groundBody = m_ptrPhysicsWorld->CreateBody(&groundDef);

	b2EdgeShape groundBox;

	//bottom
	groundBox.Set(b2Vec2(0, 0), b2Vec2(visibleSize.width / PTM_RATIO, 0));
	groundBody->CreateFixture(&groundBox, 0);

	//top
	groundBox.Set(b2Vec2(0, visibleSize.height / PTM_RATIO), b2Vec2(visibleSize.width / PTM_RATIO, visibleSize.height / PTM_RATIO));
	groundBody->CreateFixture(&groundBox, 0);

	//left
	groundBox.Set(b2Vec2(0, 0), b2Vec2(0, visibleSize.height / PTM_RATIO));
	groundBody->CreateFixture(&groundBox, 0);

	//right
	groundBox.Set(b2Vec2((visibleSize.width) / PTM_RATIO, 0), b2Vec2(visibleSize.width / PTM_RATIO, visibleSize.height / PTM_RATIO));
	groundBody->CreateFixture(&groundBox, 0);

// 	b2BodyDef kbodyDef;
// 	kbodyDef.type = b2_kinematicBody;
// 	kbodyDef.position.Set(visibleSize.width/2/PTM_RATIO, visibleSize.height/4/PTM_RATIO);
// 	b2Body* kbody = m_ptrPhysicsWorld->CreateBody(&kbodyDef);
// 
// 	b2PolygonShape kbodyshape;
// 	kbodyshape.SetAsBox(4.0f, 1.0f);
// 
// 	b2FixtureDef kfixdef;
// 	kfixdef.shape = &kbodyshape;
// 	
// 	kbody->CreateFixture(&kfixdef);
// 	kbody->SetLinearVelocity(b2Vec2(0.0f, 0.1f));
}

void HelloWorld::draw()
{
	Layer::draw();

	if (!m_bIsDebugOpen)
		return
	GL::enableVertexAttribs(cocos2d::GL::VERTEX_ATTRIB_FLAG_POSITION);

	kmGLPushMatrix();
	kmGLGetMatrix(KM_GL_MODELVIEW, &_modelViewMV);

	_customCommand.init(_globalZOrder);
	_customCommand.func = CC_CALLBACK_0(HelloWorld::onDraw, this);
	Director::getInstance()->getRenderer()->addCommand(&_customCommand);
	kmGLPopMatrix();
}

void HelloWorld::onDraw()
{
	kmMat4 oldMV;
	kmGLGetMatrix(KM_GL_MODELVIEW, &oldMV);
	kmGLLoadMatrix(&_modelViewMV);
	m_ptrPhysicsWorld->DrawDebugData();
	kmGLLoadMatrix(&oldMV);
}

void HelloWorld::update(float dt)
{
	//It is recommended that a fixed time step is used with Box2D for stability
	//of the simulation, however, we are using a variable time step here.
	//You need to make an informed choice, the following URL is useful
	//http://gafferongames.com/game-physics/fix-your-timestep/

	int velocityIterations = 8;
	int positionIterations = 3;

	// Instruct the world to perform a single step of simulation. It is
	// generally best to keep the time step and iterations fixed.
	m_ptrPhysicsWorld->Step(dt, velocityIterations, positionIterations);
}

void HelloWorld::addNewSpriteAtPosition(Point p)
{
	//Create dynmaic body
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(p.x / PTM_RATIO, p.y / PTM_RATIO);

	b2Body* body = m_ptrPhysicsWorld->CreateBody(&bodyDef);

	b2PolygonShape dynmaicBox;
// 	b2Vec2 vectices[5];
// 	vectices[0].Set(0.5f, -1.0f);
// 	vectices[1].Set(1.0f, 0.0f);
// 	vectices[2].Set(0.0f, 1.0f);
// 	vectices[3].Set(-1.0f, 0.0f);
// 	vectices[4].Set(-0.5f, -1.0f);
// 	dynmaicBox.Set(vectices, 5);
	dynmaicBox.SetAsBox(0.5f, 1.0f);

// 	b2CircleShape circleShape;
// 	circleShape.m_radius = 1.0f;

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynmaicBox;
	fixtureDef.density = 2.0f;
	fixtureDef.friction = 1.0f;
	fixtureDef.restitution = 0.5f;

	/*body->SetLinearVelocity(b2Vec2(5, 5));*/
	//让物体不会自旋转
	/*body->SetFixedRotation(true);*/
	body->CreateFixture(&fixtureDef);

// 	auto sprite = PhysicsSprite::create("CloseNormal.png");
// 	addChild(sprite);
// 	sprite->setB2Body(body);
// 	sprite->setPTMRatio(PTM_RATIO);
// 	sprite->setPosition(p);
}

void HelloWorld::onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event)
{
	for (auto& touch : touches)
	{
		if (!touch)
			break;

		auto location = touch->getLocation();

		addNewSpriteAtPosition(location);
	}
}

void HelloWorld::onEnter()
{
	Layer::onEnter();
	auto touchListener = EventListenerTouchAllAtOnce::create();
	touchListener->onTouchesEnded = CC_CALLBACK_2(HelloWorld::onTouchesEnded, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
}


