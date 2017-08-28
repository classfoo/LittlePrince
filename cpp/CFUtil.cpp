#include "CFUtil.h"

b2Body* CFUtil::createBody(const char* shape, CFNode* node, b2World* world){
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    //CCLog("bodypos:x=%f&y=%f",this->getPositionX(), this->getPositionY());
    bodyDef.position.Set(node->getPositionX()/(PTM_RATIO), node->getPositionY()/(PTM_RATIO));
    bodyDef.fixedRotation = true;
    //bodyDef.linearVelocity = linearvec;
    bodyDef.userData = node;
    bodyDef.linearDamping=0.0f;
    bodyDef.angularDamping=0.0f;
    b2Body* body = world->CreateBody(&bodyDef);
    gbox2d::GB2ShapeCache::sharedGB2ShapeCache()->addFixturesToBody(body, shape);//把生成的刚体和形状绑在一起
    node->setAnchorPoint(gbox2d::GB2ShapeCache::sharedGB2ShapeCache()->anchorPointForShape(shape));//设置锚点
    return body;
}

void CFUtil::updateBody(b2Body* body, CCNode* node, CFGameContext* context){
    if(body == NULL){
        return;
    }
    CFGameSpaceContext* space = context->getSpaceContext();
    float zoom = space->getPlanetZoom();
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    float basex = size.width/2;
    float basey = context->getCurrentLevel()->getPlanetTop();
    b2Vec2 pos = b2Vec2((node->getPositionX()-basex)/(PTM_RATIO*zoom),(node->getPositionY()-basey)/(PTM_RATIO*zoom));
    body->SetTransform(pos, -node->getRotation()*PI_/180);
}
