#ifndef _CONTACT_TEST_h

#define _CONTACT_TEST_H

#include "../../HelloWorldScene.h"
#include <vector>
USING_NS_CC;



class CustomContactListener : public b2ContactListener
{
	virtual void BeginContact(b2Contact* contact) override;

	virtual void EndContact(b2Contact* contact) override;
};

class Ball
{
public:
	b2Body* m_ptrBody;
	float m_fradius;


public:
	Ball(b2World* world, float radius)
	{
		m_ptrBody = nullptr;
		m_fradius = radius;

		b2BodyDef bodydef;
		bodydef.type = b2_dynamicBody;
		bodydef.position.Set(4, 10);
		m_ptrBody = world->CreateBody(&bodydef);
		m_ptrBody->SetUserData(this);

		b2CircleShape shape;
		shape.m_p.Set(0, 0);
		shape.m_radius = m_fradius;

		b2FixtureDef fixturedef;
		fixturedef.shape = &shape;
		fixturedef.density = 1;
		m_ptrBody->CreateFixture(&fixturedef);


	}

	Ball(b2World* world, float radius, b2Color color, uint16 categoryBits, uint16 maskBits)
	{
		m_ptrBody = nullptr;
		m_fradius = radius;
		m_color = color;

		b2BodyDef bodydef;
		bodydef.type = b2_dynamicBody;
		bodydef.position.Set(10, 10);
		m_ptrBody = world->CreateBody(&bodydef);
		m_ptrBody->SetUserData(this);

		b2CircleShape shape;
		shape.m_p.Set(0, 0);
		shape.m_radius = m_fradius;

		b2FixtureDef fixturedef;
		fixturedef.shape = &shape;
		fixturedef.density = 1;
		fixturedef.filter.categoryBits = categoryBits;
		fixturedef.filter.maskBits = maskBits;
		m_ptrBody->CreateFixture(&fixturedef);


	}



	virtual ~Ball(){}

	void render();

	void renderAtBodyPosition();

	void startContact(){ m_bContacting = true; }
	void endContact(){ m_bContacting = false; }

private:
	bool m_bContacting = false;

	b2Color m_color;

};





class ContactTest : public HelloWorld
{
public:
	ContactTest();
	virtual ~ContactTest();

	CREATE_FUNC(ContactTest);

	static Scene* createScene();

	virtual bool init() override;

	virtual void initPhysics() override;

	virtual void update(float dt) override;
	
	virtual void addNewSpriteAtPosition(cocos2d::Point p) override;

private:
	CustomContactListener m_customListener;
	std::vector<Ball*> m_vecBalls;

};


#endif