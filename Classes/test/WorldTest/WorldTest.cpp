#include "WorldTest.h"
WorldTest::WorldTest()
{

}

WorldTest::~WorldTest()
{

}

Scene* WorldTest::createScene()
{
	WorldTest* pRet = WorldTest::create();
	Scene* ptrScene = Scene::create();
	ptrScene->addChild(pRet);
	return ptrScene;
}

bool WorldTest::init()
{
	if (!HelloWorld::init())
		return false;

	return true;
}

void WorldTest::initPhysics()
{
	HelloWorld::initPhysics();
	// 	b2Vec2 gravity(0, -10.0f);
	// 	m_ptrPhysicsWorld = new b2World(gravity);
	// 	m_ptrPhysicsWorld->SetDebugDraw(m_ptrDebugDraw);
	// 	m_ptrPhysicsWorld->SetAllowSleeping(true);
	// 	m_ptrPhysicsWorld->SetContinuousPhysics(true);

	b2BodyDef bodydef;
	bodydef.type = b2_dynamicBody;

	b2PolygonShape polygonshape;
	polygonshape.SetAsBox(1, 1);

	b2FixtureDef fixturedef;
	fixturedef.shape = &polygonshape;
	fixturedef.density = 1;

	for (int i = 0; i < 3; i++)
	{
		bodydef.position.Set(10 + i * 4, 20);
		bodies[i] = m_ptrPhysicsWorld->CreateBody(&bodydef);
		bodies[i]->CreateFixture(&fixturedef);
		sprites[i] = PhysicsSprite::create("sprite.png");
		sprites[i]->setTag(i);
		sprites[i]->setB2Body(bodies[i]);
		sprites[i]->setPTMRatio(PTM_RATIO);
		sprites[i]->setPosition(Point(bodydef.position.x*PTM_RATIO, bodydef.position.y*PTM_RATIO));
		this->addChild(sprites[i]); 
	}

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [](Touch* touch, Event* event){
		auto sprite = static_cast<Sprite*>(event->getCurrentTarget());

		Point locationInNode = sprite->convertToNodeSpace(touch->getLocation());
		Size s = sprite->getContentSize();
		Rect rect = Rect(0, 0, s.width, s.height);
		if (rect.containsPoint(locationInNode))
		{
			return true;
		}
		return false;
		
	};
	listener->onTouchMoved = [](Touch* touch, Event* event){

	};
	listener->onTouchEnded = [](Touch* touch, Event* event){
		auto sprite = static_cast<PhysicsSprite*>(event->getCurrentTarget());
		log("sprite index = %d", sprite->getTag());
		b2Body* body = sprite->getB2Body();
		switch (sprite->getTag())
		{
		case 0:
// 			for (int i = 0; i < 50; i++)
// 			{
// 				//力是需要不断的去累加到后面才有效果
// 				body->ApplyForce(b2Vec2(0, 50), body->GetWorldCenter(), true);
// 			}
			for (int i = 0; i < 20;i++)
				//正数为逆时针旋转， 负数为顺时针旋转
				body->ApplyTorque(-40, true);

				break;

		case 1:
			//冲量是瞬间的效果
			//GetWorldCenter()获得质心的重点，这里是施加的力的位置
			body->ApplyLinearImpulse(b2Vec2(0, 50), /*body->GetWorldCenter()*/body->GetWorldPoint(b2Vec2(1,1)), true);
			break;

		case 2:
			body->SetTransform(b2Vec2(10, 20), 45);
			break;
		default:
			break;
		}
	};
	listener->setSwallowTouches(true);

	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, sprites[0]);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener->clone(), sprites[1]);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener->clone(), sprites[2]);

	bodydef.type = b2_staticBody;
	bodydef.position.Set(0, 0);
	b2EdgeShape edgeShape;
	edgeShape.Set(b2Vec2(-15, 0), b2Vec2(15, 0));
	fixturedef.shape = &edgeShape;
	m_ptrPhysicsWorld->CreateBody(&bodydef)->CreateFixture(&fixturedef);
}

void WorldTest::addNewSpriteAtPosition(cocos2d::Point p)
{

}



void WorldTest::onEnter()
{
	Layer::onEnter();
}



