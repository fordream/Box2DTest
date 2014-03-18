#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Utils/GLES-Render.h"
#include "cocos-ext.h"
#include <vector>

#define PTM_RATIO 32

#define RADTODEG 57.29577951f
#define DEGTORAD 0.017453293f


class HelloWorld : public cocos2d::Layer
{
public:
	HelloWorld();
	~HelloWorld();
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init() override;  
    
    // a selector callback
    void menuCloseCallback(Object* pSender);
	void menuClosePhysicDebugDraw(Object* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

	virtual void onEnter() override;

	virtual void initPhysics();

	virtual void draw() override;

	virtual void addNewSpriteAtPosition(cocos2d::Point p);
	virtual void update(float dt) override;
	void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);

protected:
	kmMat4 _modelViewMV;
	void onDraw();
	cocos2d::CustomCommand _customCommand;

	b2World* m_ptrPhysicsWorld;
	GLESDebugDraw* m_ptrDebugDraw;

	bool m_bIsDebugOpen;
	
private:
	
};

#endif // __HELLOWORLD_SCENE_H__
