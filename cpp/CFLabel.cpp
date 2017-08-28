#include "CFLabel.h"

CFLabel::CFLabel():text(NULL),font(NULL),ttf(NULL),bmfnt(NULL){

}

CFLabel::~CFLabel(){

}

CFLabel* CFLabel::create(const char *text, const char* font, float size,const ccColor3B color){
    return CFLabel::create(text, font, size, color, 0, 0);
}

CFLabel* CFLabel::create(const char *text, const char* font, float size, const ccColor3B color, float width, float height){
    CFLabel* label = new CFLabel();
    label->text = text;
    label->font = font;
    label->size = size;
    label->width = width;
    label->height = height;
    label->color = color;
    label->init();
    label->autorelease();
    return label;
}

bool CFLabel::init(){
    ccLanguageType lang = CCApplication::sharedApplication()->getCurrentLanguage();
    if(lang == kLanguageChinese||lang == kLanguageFrench||lang == kLanguageKorean||lang == kLanguageJapanese){
        if(width == 0||height == 0){
            this->ttf = CCLabelTTF::create(this->text, this->getFont(), this->size);
            this->ttf->setColor(this->color);
            this->addChild(this->ttf);
        }else{
            this->ttf = CCLabelTTF::create(this->text, this->getFont(), this->size, CCSize(width, 300), kCCTextAlignmentLeft, kCCVerticalTextAlignmentCenter);
            this->ttf->setColor(this->color);
            this->addChild(this->ttf);
        }
    }else{
        this->bmfnt = CCLabelBMFont::create(this->text, this->font, this->width);
        this->addChild(this->bmfnt);
    }
    return true;
}

void CFLabel::setString(const char *text){
    if(this->bmfnt != NULL){
        this->bmfnt->setString(text);
    }
    if(this->ttf!=NULL){
        this->ttf->setString(text);
    }
}

const char* CFLabel::getFont(){
    ccLanguageType lang = CCApplication::sharedApplication()->getCurrentLanguage();
    switch (lang) {
        case cocos2d::kLanguageChinese:
            return "Heiti SC";
        case cocos2d::kLanguageFrench:
            return "Arial";
        case cocos2d::kLanguageKorean:
            return "Heiti K";
        case cocos2d::kLanguageJapanese:
            return "Heiti J";
        default:
            return "Arial";
    }
}