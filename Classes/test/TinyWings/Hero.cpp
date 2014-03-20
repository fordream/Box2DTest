#include "Hero.h"
Hero::Hero()
{
	_bIsAwake = false;
}

Hero::~Hero()
{

}

Hero* Hero::create(b2World* world)
{
	Hero* pRet = new Hero();
	pRet->setWorld(world);
	if (pRet&&pRet->init())
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = nullptr;
		return nullptr;
	}
}

bool Hero::init()
{
	if (!Sprite::init())
		return false;


	initWithSpriteFrameName("seal1.png");

	createBody();

	scheduleUpdate();

	return true;
}

void Hero::update(float dt)
{
	this->setPosition(Point(_body->GetPosition().x*PTM_RATIO, _body->GetPosition().y*PTM_RATIO));
	b2Vec2 vel = _body->GetLinearVelocity();
	b2Vec2 weightedVel = vel;
	float angle = ccpToAngle(Point(vel.x, vel.y));
	if (_bIsAwake)
	{
		this->setRotation(-1 * CC_RADIANS_TO_DEGREES(angle));
	}
}

void Hero::createBody()
{
	float radius = 16.0f;

	Size size = Director::getInstance()->getWinSize();
	int screenH = size.height;

	Point startPosition = ccp(0, screenH / 2 + radius);

	b2BodyDef bd;
	bd.type = b2_dynamicBody;
	bd.linearDamping = 0.1f;
	bd.fixedRotation = true;
	bd.position.Set(startPosition.x / PTM_RATIO, startPosition.y/PTM_RATIO);
	_body = _world->CreateBody(&bd);

	b2CircleShape circleshape;
	circleshape.m_radius = radius / PTM_RATIO;

	b2FixtureDef fixturedef;
	fixturedef.shape = &circleshape;
	fixturedef.density = 1.0f;
	fixturedef.restitution = 0.0f;
	fixturedef.friction = 0.2f;

	_body->CreateFixture(&fixturedef);
}

void Hero::wake()
{
	_bIsAwake = true;
	_body->SetActive(true);
	_body->ApplyLinearImpulse(b2Vec2(1, 10), _body->GetPosition(), _bIsAwake);
}

void Hero::dive()
{
	_bIsAwake = false;
	_body->ApplyForce(b2Vec2(1, -1), _body->GetPosition(), _bIsAwake);
}

void Hero::limitVelocity()
{
	if (!_bIsAwake) return;

	const float minVelocityX = 5;
	const float minVelocityY = -40;
	b2Vec2 vel = _body->GetLinearVelocity();
	if (vel.x < minVelocityX) {
		vel.x = minVelocityX;
	}
	if (vel.y < minVelocityY) {
		vel.y = minVelocityY;
	}
	_body->SetLinearVelocity(vel);
}

