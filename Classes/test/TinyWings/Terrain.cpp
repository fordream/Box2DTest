#include "Terrain.h"
Terrain::Terrain()
{
	_spripes = NULL;
}

Terrain::~Terrain()
{
	_spripes = NULL;
}


Terrain* Terrain::create(b2World* world)
{
	Terrain* pRet = new Terrain();
	pRet->setWorld(world);
	{
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
}


bool Terrain::init()
{
	if (!Node::init())
		return false;

	generateHills();
	resetHillVertices();

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("TinySeal.plist");

	_batchNode = SpriteBatchNode::create("TinySeal.png");
	_batchNode->setPosition(Point(0, 0));
	addChild(_batchNode);

	return true;
}

void Terrain::draw()
{
	if (nullptr!=_spripes)
	{
// 		glBindTexture(GL_TEXTURE_2D, _spripes->getTexture()->getName());
// 		glDisableClientState(GL_COLOR_ARRAY);
// 
// 		ccDrawColor4B(255, 255, 255, 255);
// 		glVertexPointer(2, GL_FLOAT, 0, _hillVertices);
// 		glTexCoordPointer(2, GL_FLOAT, 0, _hillTexCoords);
// 		glDrawArrays(GL_TRIANGLE_STRIP, 0, (GLsizei)_nHillVertices);
	}


	for (int i = MAX(_fromKeyPointI, 1); i <=_toKeyPointI; ++i)
	{

		ccDrawColor4B(255, 255, 255, 255);

		ccDrawLine(_hillKeyPoints[i - 1], _hillKeyPoints[i]);

		ccDrawColor4B(255, 0, 0, 255);

		Point p0 = _hillKeyPoints[i - 1];
		Point p1 = _hillKeyPoints[i];
		int hSegments = floorf((p1.x - p0.x) / kHillSegmentWidth);
		float dx = (p1.x - p0.x) / hSegments;
		float da = M_PI / hSegments;
		float ymid = (p0.y + p1.y) / 2;
		float ampl = (p0.y - p1.y) / 2;

		Point pt0, pt1;
		pt0 = p0;
		for (int j = 0; j < hSegments + 1; ++j) {

			pt1.x = p0.x + j*dx;
			pt1.y = ymid + ampl * cosf(da*j);

			ccDrawLine(pt0, pt1);

			pt0 = pt1;

		}
	}

// 	glDisable(GL_TEXTURE_2D);
// 	glDisableClientState(GL_COLOR_ARRAY);
// 	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	_world->DrawDebugData();

// 	glEnable(GL_TEXTURE_2D);
// 	glEnableClientState(GL_COLOR_ARRAY);
// 	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
}

void Terrain::generateHills()
{
	Size winSize = Director::getInstance()->getWinSize();

	float minDX = 160;
	float minDY = 60;
	int rangeDX = 80;
	int rangeDY = 40;

	float x = -minDX;
	float y = winSize.height / 2 - minDY;


	float dy, ny;
	float sign = 1; // +1 - going up, -1 - going down
	float paddingTop = 20;
	float paddingBottom = 20;

	for (int i = 0; i < kMaxHillKeyPoints; i++) {
		_hillKeyPoints[i] = Point(x, y);
		if (i == 0) {
			x = 0;
			y = winSize.height / 2;
		}
		else {
			x += rand() % rangeDX + minDX;
			while (true) {
				dy = rand() % rangeDY + minDY;
				ny = y + dy*sign;
				if (ny < winSize.height - paddingTop && ny > paddingBottom) {
					break;
				}
			}
			y = ny;
		}
		sign *= -1;
	}
}

void Terrain::resetHillVertices()
{
	Size winSize = Director::getInstance()->getWinSize();

	static int prevFromKeyPointI = -1;
	static int prevToKeyPointI = -1;

	resetBody();

	// key points interval for drawing
	while (_hillKeyPoints[_fromKeyPointI + 1].x <= (m_nOffsetX - winSize.width) /2/getScale()) {
		_fromKeyPointI++;
	}
	while (_hillKeyPoints[_toKeyPointI].x <= (m_nOffsetX + winSize.width * 8)/2/getScale() ) {
		_toKeyPointI++;
	}

	if (prevFromKeyPointI != _fromKeyPointI || prevToKeyPointI != _toKeyPointI) {

		// vertices for visible area
		_nHillVertices = 0;
		_nBorderVertices = 0;
		Point p0, p1, pt0, pt1;
		p0 = _hillKeyPoints[_fromKeyPointI];
		for (int i = _fromKeyPointI + 1; i < _toKeyPointI + 1; i++) {
			p1 = _hillKeyPoints[i];

			// triangle strip between p0 and p1
			int hSegments = floorf((p1.x - p0.x) / kHillSegmentWidth);
			float dx = (p1.x - p0.x) / hSegments;
			float da = M_PI / hSegments;
			float ymid = (p0.y + p1.y) / 2;
			float ampl = (p0.y - p1.y) / 2;
			pt0 = p0;
			_borderVertices[_nBorderVertices++] = pt0;
			for (int j = 1; j < hSegments + 1; j++) {
				pt1.x = p0.x + j*dx;
				pt1.y = ymid + ampl * cosf(da*j);
				_borderVertices[_nBorderVertices++] = pt1;

				_hillVertices[_nHillVertices] = Point(pt0.x, 0);
				_hillTexCoords[_nHillVertices++] = Point(pt0.x / 512, 1.0f);
				_hillVertices[_nHillVertices] = Point(pt1.x, 0);
				_hillTexCoords[_nHillVertices++] = Point(pt1.x / 512, 1.0f);

				_hillVertices[_nHillVertices] = Point(pt0.x, pt0.y);
				_hillTexCoords[_nHillVertices++] = Point(pt0.x / 512, 0);
				_hillVertices[_nHillVertices] = Point(pt1.x, pt1.y);
				_hillTexCoords[_nHillVertices++] = Point(pt1.x / 512, 0);

				pt0 = pt1;
			}

			p0 = p1;
		}

		prevFromKeyPointI = _fromKeyPointI;
		prevToKeyPointI = _toKeyPointI;
	}

}

void Terrain::resetBody()
{
	if (_body)
	{
		_world->DestroyBody(_body);
	}



	b2BodyDef bd;
	bd.position.Set(0, 0);

	_body = _world->CreateBody(&bd);

	b2EdgeShape shape;

	b2Vec2 p1, p2;
	for (int i = 0; i < _nBorderVertices - 1; i++) {
		p1 = b2Vec2(_borderVertices[i].x / PTM_RATIO, _borderVertices[i].y / PTM_RATIO);
		p2 = b2Vec2(_borderVertices[i + 1].x / PTM_RATIO, _borderVertices[i + 1].y / PTM_RATIO);
		shape.Set(p1, p2);
		_body->CreateFixture(&shape, 0);
	}
}

void Terrain::setWorld(b2World* world)
{
	_world = world;

	Point p0 = _hillKeyPoints[0];
	Point p1 = _hillKeyPoints[kMaxHillKeyPoints - 1];

	b2BodyDef bodydef;
	bodydef.position.SetZero();
	_body = _world->CreateBody(&bodydef);

	b2EdgeShape shape;
	b2Vec2 ep1 = b2Vec2(p0.x / PTM_RATIO, 0);
	b2Vec2 ep2 = b2Vec2(p1.x / PTM_RATIO, 0);
	shape.Set(ep1, ep2);
	_body->CreateFixture(&shape, 0);
}

