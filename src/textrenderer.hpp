#pragma once
#include <Ogre.h>
#include <OgreOverlay.h>
#include <OgreOverlayManager.h>
#include <OgreOverlayContainer.h>
#include <OgreTextAreaOverlayElement.h>
#include <OgreSingleton.h>

// http://wiki.ogre3d.org/Simple+Text+Output

class TextRenderer : public Ogre::Singleton<TextRenderer>
{
private:

    Ogre::OverlayManager*    _overlayMgr;
    Ogre::Overlay*           _overlay;
    Ogre::OverlayContainer*  _panel;

public:

    TextRenderer();
    ~TextRenderer() =default;

    void addTextBox(
        const std::string& ID,
        const std::string& text,
        Ogre::Real x, Ogre::Real y,
        Ogre::Real width, Ogre::Real height,
        const Ogre::ColourValue& color = Ogre::ColourValue(1.0, 1.0, 1.0, 1.0));

    void removeTextBox(const std::string& ID);

    void setText(const std::string& ID, const std::string& Text);
    const std::string& getText(const std::string& ID);
};
