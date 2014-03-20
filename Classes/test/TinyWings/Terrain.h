#ifndef _TERRAIN_H

#define _TERRAIN_H

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Box2D/Box2D.h"
#include "../../Utils/GLES-Render.h"
USING_NS_CC;
USING_NS_CC_EXT;

#define PTM_RATIO 32

#define kMaxHillKeyPoints 2000
#define kHillSegmentWidth 10
#define kMaxHillVertices 4000
#define kMaxBorderVertices 800 



class Terrain : public cocos2d::Node{
public:
	Terrain();
	virtual ~Terrain();

	CREATE_FUNC(Terrain);
	static Terrain* create(b2World* world);

	virtual bool init() override;

	virtual void draw() override;

	void setOffset(float offsetX){
		m_nOffsetX = offsetX;
		Size size = Director::getInstance()->getWinSize();
		this->setPosition(Point(m_nOffsetX*this->getScale(), 0));
		resetHillVertices();
	}

	void setStripes(Sprite* sprite)
	{
		_spripes = sprite;
	}

	void generateHills();
	void resetHillVertices();

	void resetBody();

	void setWorld(b2World* world);
	CC_SYNTHESIZE(GLESDebugDraw*, _debugDraw, DebugDraw);
	CC_SYNTHESIZE(b2Body*, _body, Body);
	SpriteBatchNode* getBatchNode(){ return this->_batchNode; }

private:
	float m_nOffsetX = 0.0f;

	Point _hillKeyPoints[kMaxHillKeyPoints];

	Sprite* _spripes;

	int _fromKeyPointI = -1;
	int _toKeyPointI = -1;
	b2World* _world;

	int _nHillVertices;
	Point _hillVertices[kMaxHillVertices];
	Point _hillTexCoords[kMaxHillVertices];
	int _nBorderVertices;
	Point _borderVertices[kMaxBorderVertices];

	SpriteBatchNode* _batchNode;

};
#endif // !_TERRAIN_H
