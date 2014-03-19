#include "MainGame.h"
#include "Terrain.h"

MainGame::MainGame()
{
	m_LayerColor = Color4B(10, 10, 10, 100);
	m_ptrGround = nullptr;
}

MainGame::~MainGame()
{

}


Scene* MainGame::createScene()
{
	MainGame* pRet = MainGame::create();

	Scene* ptrScene = Scene::create();

	ptrScene->addChild(pRet);

	return ptrScene;
}


bool MainGame::init()
{
	if (!LayerColor::initWithColor(m_LayerColor))
		return false;



	

	_debugDraw = new GLESDebugDraw(PTM_RATIO);
	uint32 flags = 0;
	flags += b2Draw::e_shapeBit;
	flags += b2Draw::e_jointBit;
	flags += b2Draw::e_aabbBit;
	flags += b2Draw::e_pairBit;
	flags += b2Draw::e_centerOfMassBit;
	_debugDraw->SetFlags(flags);


	initPhysics();

	_terrain = Terrain::create(_world);
	_terrain->setDebugDraw(_debugDraw);
	_terrain->setPosition(Point(0, 40));
	this->addChild(_terrain, 1);

	genBackground();

	scheduleUpdate();


	return true;
}

void MainGame::onEnter()
{
	LayerColor::onEnter();
	auto listener = EventListenerTouchAllAtOnce::create();
	listener->onTouchesBegan = CC_CALLBACK_2(MainGame::onTouchesBegan, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

void MainGame::onExit()
{
	LayerColor::onExit();
}

cocos2d::Color4F MainGame::randomBrightColor()
{
	while (true)
	{
		float requiredBrightness = 192;
		Color4B randomColor = Color4B(rand() % 255, rand() % 255, rand() % 255, 255);

		if (randomColor.r > requiredBrightness ||
			randomColor.g > requiredBrightness ||
			randomColor.b > requiredBrightness)
		{
			return Color4F(randomColor);
		}

	}
}

void MainGame::genBackground()
{
	if (m_ptrGround&&m_ptrGround->getParent())
		m_ptrGround->removeFromParentAndCleanup(true);

	Color4F bgColor = randomBrightColor();
	Color4F color2 = randomBrightColor();
	int nStripes = ((rand() % 4) + 1) * 2;

// 	m_ptrGround = stripedSpriteWithColor1(bgColor, color2, 1024, nStripes);
// 	Size winSize = Director::getInstance()->getWinSize();
// 	m_ptrGround->setPosition(Point(winSize.width / 2, winSize.height / 2));
// 	Texture2D::TexParams  tx;
// 	tx.magFilter = GL_LINEAR;
// 	tx.minFilter = GL_LINEAR;
// 	tx.wrapS = GL_REPEAT;
// 	tx.wrapT = GL_REPEAT;
// 	m_ptrGround->getTexture()->setTexParameters(tx);
// 	addChild(m_ptrGround, 100);

	Color4F color3 = randomBrightColor();
	Color4F color4 = randomBrightColor();
	auto stripes = stripedSpriteWithColor1(color3, color4, 512, 4);
	Texture2D::TexParams tx1 = { GL_LINEAR, GL_LINEAR, GL_REPEAT, GL_CLAMP_TO_EDGE };

	stripes->getTexture()->setTexParameters(tx1);

	_terrain->setStripes(stripes);



}


Sprite* MainGame::spriteWithColor(Color4F color, float textureSize)
{
	RenderTexture* rt = RenderTexture::create(textureSize, textureSize);



	

	rt->beginWithClear(color.r, color.g, color.b, color.a);
// 
// 	auto noise = Sprite::create("Noise.png");
// 	//GL_DST_COLOR指定如何乘以输入图像/原图像的颜色
// 	//GL_ZERO指定如何乘以已经存在的图像/目标图像的颜色数据
// 	noise->setBlendFunc(BlendFunc{ GL_DST_COLOR, GL_ZERO });
// 	Size winSize = Director::getInstance()->getWinSize();
// 	noise->setPosition(Point(textureSize/2,textureSize/ 2));
// 	noise->setScale(2.0f);
// 	noise->visit();

	rt->end();

	return Sprite::createWithTexture(rt->getSprite()->getTexture());


}


void MainGame::onDraw()
{
	LayerColor::onDraw();
// 	kmMat4 oldMV;
// 	kmGLGetMatrix(KM_GL_MODELVIEW, &oldMV);
// 	kmGLLoadMatrix(&_modelViewMV);
// 	_world->DrawDebugData();
// 	kmGLLoadMatrix(&oldMV);
}

Sprite* MainGame::stripedSpriteWithColor1(Color4F color1, Color4F color2, float textureSize, int nStripes)
{
	RenderTexture* rt = RenderTexture::create(textureSize, textureSize);
	rt->beginWithClear(color1.r, color1.g, color1.b, color1.a);

// 	glDisable(GL_TEXTURE_2D);
// 	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
// 	glDisableClientState(GL_COLOR_ARRAY);

// 	Point*  vertices = new Point[nStripes*6];
// 	int nVertices = 0;
// 	float x1 = -textureSize;
// 	float x2;
// 	float y1 = textureSize;
// 	float y2 = 0;
// 	float dx = textureSize / nStripes * 2;
// 	float stripeWidth = dx / 2;
// 	for (int i = 0; i < nStripes; i++)
// 	{
// 		x2 = x1 + textureSize;
// 		vertices[nVertices++] = Point(x1, y1);
// 		vertices[nVertices++] = Point(x1 + stripeWidth, y1);
// 		vertices[nVertices++] = Point(x2, y2);
// 		vertices[nVertices++] = vertices[nVertices - 2];
// 		vertices[nVertices++] = vertices[nVertices - 2];
// 		vertices[nVertices++] = Point(x2 + stripeWidth, y2);
// 		x1 += dx;
// 	}
// 
// 	glColor4f(color2.r, color2.g, color2.b, color2.a);
// 	glVertexPointer(2, GL_FLOAT, 0, vertices);
// 	glDrawArrays(GL_TRIANGLES, 0, (GLsizei)nVertices);
// 
// 	glEnableClientState(GL_COLOR_ARRAY);
// 	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
// 	glEnable(GL_TEXTURE_2D);

	rt->end();

	return Sprite::createWithTexture(rt->getSprite()->getTexture());
}

void MainGame::update(float dt)
{
	_terrain->setOffset(1);

	static double UPDATE_INTERVAL = 1.0f / 60.0f;
	static double MAX_CYCLES_PER_FRAME = 5;
	static double timeAccumulator = 0;

	timeAccumulator += dt;

	timeAccumulator += dt;
	if (timeAccumulator > (MAX_CYCLES_PER_FRAME * UPDATE_INTERVAL)) {
		timeAccumulator = UPDATE_INTERVAL;
	}

	int32 velocityIterations = 3;
	int32 positionIterations = 2;

	while (timeAccumulator >= UPDATE_INTERVAL) {
		timeAccumulator -= UPDATE_INTERVAL;
		_world->Step(UPDATE_INTERVAL,
			velocityIterations, positionIterations);
		_world->ClearForces();
	}
// 	int velocityIterations = 8;
// 	int positionIterations = 3;
// 
// 	// Instruct the world to perform a single step of simulation. It is
// 	// generally best to keep the time step and iterations fixed.
// 	_world->Step(dt, velocityIterations, positionIterations);

}

void MainGame::initPhysics()
{
	b2Vec2 gravity(0.0f, -10.0f);
	_world = new b2World(gravity);
	_world->SetAllowSleeping(true);
	_world->SetContinuousPhysics(true);
	_world->SetDebugDraw(_debugDraw);

}

void MainGame::createTestBodyAtPosition(Point p)
{
	b2BodyDef bodydef;
	bodydef.type = b2_dynamicBody;
	bodydef.position.Set(p.x / PTM_RATIO, p.y / PTM_RATIO);

	b2Body* body = _world->CreateBody(&bodydef);

	b2CircleShape circleShape;
	circleShape.m_radius = 25.0 / PTM_RATIO;

	b2FixtureDef fixturedef;
	fixturedef.shape = &circleShape;
	fixturedef.density = 1.0f;
	fixturedef.friction = 0.2f;
	fixturedef.restitution = 0.6f;
	body->CreateFixture(&fixturedef);
}

void MainGame::onTouchesBegan(const std::vector<Touch*>& touches, Event *unused_event)
{
	for (auto& touch : touches)
	{
		if (!touch)
			break;

		auto location = _terrain->convertTouchToNodeSpace(touch);

		createTestBodyAtPosition(location);
	}
}


