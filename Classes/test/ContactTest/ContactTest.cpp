#include "ContactTest.h"
ContactTest::ContactTest()
{

}

ContactTest::~ContactTest()
{

}

Scene* ContactTest::createScene()
{
	ContactTest* pRet = ContactTest::create();
	Scene* ptrScene = Scene::create();
	ptrScene->addChild(pRet);
	return ptrScene;
}

bool ContactTest::init()
{
	if (!HelloWorld::init())
		return false;

	return true;
}

void ContactTest::initPhysics()
{
	HelloWorld::initPhysics();

	m_ptrPhysicsWorld->SetContactListener(&m_customListener);

	Size visibleSize = Director::getInstance()->getVisibleSize();

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(visibleSize.width / 2 / PTM_RATIO, 9);



	b2PolygonShape shape;
	shape.SetAsBox(0.3f, 0.3f);

	b2FixtureDef fixturedef;
	fixturedef.shape = &shape;
	fixturedef.density = 1;


	bodyDef.type = b2_staticBody;
	bodyDef.position.Set(0, 2);
	b2Body* staticBody = m_ptrPhysicsWorld->CreateBody(&bodyDef);



	shape.SetAsBox(5, 0.1f, b2Vec2(visibleSize.width / 2 / PTM_RATIO, 0), 0);//ground
	staticBody->CreateFixture(&fixturedef);
	shape.SetAsBox(5, 0.1f, b2Vec2(visibleSize.width / 2 / PTM_RATIO, 10), 0);//ceiling
	staticBody->CreateFixture(&fixturedef);
	shape.SetAsBox(0.1f, 5, b2Vec2(visibleSize.width / 2 / PTM_RATIO - 5, 5), 0);//left wall
	staticBody->CreateFixture(&fixturedef);
	shape.SetAsBox(0.1f, 5, b2Vec2(visibleSize.width / 2 / PTM_RATIO + 5, 5), 0);//right wall
	staticBody->CreateFixture(&fixturedef);

	Ball* ball = new Ball(m_ptrPhysicsWorld, 0.5);
	m_vecBalls.push_back(ball);

}

void ContactTest::addNewSpriteAtPosition(cocos2d::Point p)
{

}

void ContactTest::update(float dt)
{
	
	HelloWorld::update(dt);
	for (unsigned int i = 0; i < m_vecBalls.size(); i++)
	{
		m_vecBalls[i]->renderAtBodyPosition();
	}
}



void CustomContactListener::BeginContact(b2Contact* contact)
{
	void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
	if (bodyUserData)
		static_cast<Ball*>(bodyUserData)->startContact();

	bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
	if (bodyUserData)
		static_cast<Ball*>(bodyUserData)->startContact();
}

void CustomContactListener::EndContact(b2Contact* contact)
{
	void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
	if (bodyUserData)
		static_cast<Ball*>(bodyUserData)->endContact();

	bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
	if (bodyUserData)
		static_cast<Ball*>(bodyUserData)->endContact();
}

void Ball::render()
{
	if (m_bContacting)
		log("Contact true");
	else
		log("Contact false");
// 	glPointSize(4);
// 	glBegin(GL_POINTS);
// 	glVertex2f(-0.5, 0.5);
// 	glVertex2f(0.5, 0.f);
// 	glVertex2f(0.5, 0.5);
// 	glEnd();
// 
// 	//mouth
// 	glBegin(GL_LINES);
// 	glVertex2f(-0.5f, -0.5f);
// 	glVertex2f(-0.16f, -0.6f);
// 	glVertex2f(0.16f, -0.6f);
// 	glVertex2f(0.5f, -0.5f);
// 	glEnd();
// 
// 	//circle outline
// 	glBegin(GL_LINE_LOOP);
// 	for (float a = 0; a < 360 * DEGTORAD; a += 30 * DEGTORAD)
// 		glVertex2f(sinf(a), cosf(a));
// 	glEnd();

}

void Ball::renderAtBodyPosition()
{
	//get current position from Box2D
	b2Vec2 pos = m_ptrBody->GetPosition();
	float angle = m_ptrBody->GetAngle();

	//call normal render at different position/rotation
//	glPushMatrix();
//	glTranslatef(pos.x, pos.y, 0);
//	glRotatef(angle * RADTODEG, 0, 0, 1);//OpenGL uses degrees here
	render();//normal render at (0,0)
	//glPopMatrix();
}
