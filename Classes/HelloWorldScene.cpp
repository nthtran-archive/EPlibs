#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "eplibs\EPNotificationCenter.h"
#include "eplibs\EPResourceManager.h"

using namespace cocos2d;
using namespace CocosDenshion;

CCScene* HelloWorld::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::node();

	// 'layer' is an autorelease object
	HelloWorld *layer = HelloWorld::node();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
	if ( !EPGestureRecognizerLayer::init() )
	{
		return false;
	}

	EPNotificationCenter::sharedNotifCenter()->addObserver(this, 
		callfuncO_selector(HelloWorld::completedCallback),
		kResourceLoadedNotif, 
		NULL);

	CCSize size = CCDirector::sharedDirector()->getWinSize();

	CCMenuItem *item1 = CCMenuItemFont::itemFromString("loaded", 
		this, 
		callfuncO_selector(HelloWorld::loadedCallback));

	CCMenuItem *item2 = CCMenuItemFont::itemFromString("completed", 
		this, 
		callfuncO_selector(HelloWorld::completedCallback));

	CCMenu *m = CCMenu::menuWithItems(item1, item2, NULL);
	m->alignItemsVerticallyWithPadding(10.0f);
	m->setPosition(ccp_CENTER());
	this->addChild(m);

	return true;
}

void HelloWorld::loadedCallback(CCObject* pSender)
{  
	// Need to use shared Manager here, otherwise this won't work
	EPResourceManager::sharedResourceManager()->addPngResourceAsync("HelloWorld",false);
	EPResourceManager::sharedResourceManager()->addPngResourceAsync("4444_pics",true);
	EPResourceManager::sharedResourceManager()->loadResourceAsync();    
}

void HelloWorld::completedCallback(CCObject* pSender)
{
	CCLOG("completedCallback\n");

	CCSprite *sp = CCSprite::spriteWithSpriteFrameName("blocks.png");
	sp->setPosition(ccp_CENTER());
	sp->setTag(123);
	this->addChild(sp);

	this->addTapRecognizer(sp);

	this->addRotationRecognizer(sp);

	this->addPinchRecognizer(sp);

	this->addPanRecognizer(sp);

	this->addLongPressRecognizer(sp);
	this->setLongPressInterval(0.5f);
}

bool HelloWorld::gestureRecognizer(GestureRecognizer *gestureRecognizer)
{
	//    if (gestureRecognizer->getRecognizerType() == kTapGestureRecognizer)
	//        return true;
	return true;
}

void HelloWorld::performTap(TapGestureRecognizer *recognizer ,CCNode *node)
{
	if (node->getTag() == 123)
	{
		this->pressButton(node, callfuncN_selector(HelloWorld::pressAction));
		CCLOG("performTap");
	}
}

void HelloWorld::performLongPress(LongPressGestureRecognizer *recognizer ,CCNode *node)
{
	if (node->getTag() == 123)
	{
		CCLOG("performLongPress");
	}
}

void HelloWorld::performPan(PanGestureRecognizer *recognizer ,CCNode *node)
{
	if (node->getTag() == 123)
	{
		CCPoint pt = recognizer->getTranslationView();

		if (recognizer->getGestureRecognizerState() == kGestureRecognizerStateBegan)
			m_from = pt;
		else if (recognizer->getGestureRecognizerState() == kGestureRecognizerStateChanged)
		{
			CCPoint distance = ccpSub(pt, m_from);

			node->setPosition(ccpAdd(node->getPosition(),distance));
			m_from = pt;
		}        
	}
}

void HelloWorld::performPinch(PinchGestureRecognizer *recognizer ,CCNode *node)
{
	if (node->getTag() == 123)
	{
		CCLOG("performPinch : %f\n",recognizer->getPinchScale());
		node->setScale(recognizer->getPinchScale());
	}
}

void HelloWorld::performRotation(RotationGestureRecognizer *recognizer ,CCNode *node)
{
	if (node->getTag() == 123)
	{
		CCLOG("performRotation : %f\n",recognizer->getGestureRotation());
		node->setRotation(recognizer->getGestureRotation() + node->getRotation());
	}
}


void HelloWorld::pressAction(CCNode* node)
{
	CCLOG("pressAction");
}
