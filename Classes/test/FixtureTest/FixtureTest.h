#ifndef  _FIXTURE_TEST_H

#define  _FIXTURE_TEST_H

#include "../../HelloWorldScene.h"
USING_NS_CC;

class FixtureTest : public HelloWorld
{
public:
	FixtureTest();
	~FixtureTest();

	CREATE_FUNC(FixtureTest);
	static Scene* createScene();

	virtual bool init() override;




};
#endif