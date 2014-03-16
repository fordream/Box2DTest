#include "FixtureTest.h"

FixtureTest::FixtureTest()
{

}

FixtureTest::~FixtureTest()
{

}

Scene* FixtureTest::createScene()
{
	FixtureTest* pRet = FixtureTest::create();
	Scene* ptrScene = Scene::create();
	ptrScene->addChild(pRet);
	return ptrScene;
}

bool FixtureTest::init()
{
	if (!HelloWorld::init())
		return false;

	return true;
}

