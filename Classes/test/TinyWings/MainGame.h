#ifndef _TINY_WINGS_H

#define _TINY_WINGS_H

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "../../Utils/GLES-Render.h"
USING_NS_CC;

class Terrain;
class Hero;

#define kMaxHillKeyPoints 1000

class MainGame : public LayerColor
{
public:
	MainGame();
	virtual ~MainGame();

	CREATE_FUNC(MainGame);
	static Scene* createScene();

	virtual bool init() override;

	virtual void onEnter() override;
	virtual void onExit() override;

	virtual void update(float dt) override;

	void initPhysics();

	void createTestBodyAtPosition(Point p);

	virtual void onTouchesBegan(const std::vector<Touch*>& touches, Event *unused_event) override;
	virtual void onTouchesEnded(const std::vector<Touch*>& touches, Event *unused_event) override;
	virtual void onTouchesCancelled(const std::vector<Touch*>&touches, Event *unused_event) override;

protected:
	Color4B m_LayerColor;

private:
	Sprite* m_ptrGround;
	int m_nOffsetX;

	Point m_hillKeyPoints[1000];

	Color4F randomBrightColor();
	void genBackground();
	Sprite* spriteWithColor(Color4F color, float textureSize);
	Sprite* stripedSpriteWithColor1(Color4F color1, Color4F color2, float textureSize, int nStripes);

	Terrain* _terrain;

	b2World* _world;
	GLESDebugDraw* _debugDraw;
	kmMat4 _modelViewMV;

	Hero* _hero;
	bool _tapDown;

};
#endif