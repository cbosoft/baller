#include "textrenderer.hpp"
#include <iostream>

template<> TextRenderer* Ogre::Singleton<TextRenderer>::msSingleton = 0;

TextRenderer::TextRenderer()
{
    this->_overlayMgr = Ogre::OverlayManager::getSingletonPtr();

    this->_overlay = this->_overlayMgr->create("overlay1");
    //this->_overlay->setZOrder(500);

    this->_panel = static_cast<Ogre::OverlayContainer*>(_overlayMgr->createOverlayElement("Panel", "container1"));
    this->_panel->setDimensions(1, 1);
    this->_panel->setPosition(0, 0);

    this->_overlay->add2D(_panel);

    this->_overlay->show();
    this->_panel->show();
}

void TextRenderer::addTextBox(const std::string& ID,
                const std::string& text,
                Ogre::Real x, Ogre::Real y,
                Ogre::Real width, Ogre::Real height,
                const Ogre::ColourValue& color)
{
    Ogre::TextAreaOverlayElement* textBox = static_cast<Ogre::TextAreaOverlayElement *>(this->_overlayMgr->createOverlayElement("TextArea", ID));
    textBox->setDimensions(width, height);
    textBox->setMetricsMode(Ogre::GMM_PIXELS);
    textBox->setPosition(x, y);
    textBox->setWidth(width);
    textBox->setHeight(height);
    textBox->setFontName("MyFont");
    textBox->setCharHeight(20);
    textBox->setColour(color);

    textBox->setCaption(text);
    textBox->show();

    this->_panel->addChild(textBox);
}

void TextRenderer::removeTextBox(const std::string& ID)
{
    _panel->removeChild(ID);
    _overlayMgr->destroyOverlayElement(ID);
}

void TextRenderer::setText(const std::string& ID, const std::string& Text)
{
    Ogre::OverlayElement* textBox = _overlayMgr->getOverlayElement(ID);
    textBox->setCaption(Text);
}

// const std::string& TextRenderer::getText(const std::string& ID)
// {
//     Ogre::OverlayElement* textBox = _overlayMgr->getOverlayElement(ID);
//     return textBox->getCaption();
// }
