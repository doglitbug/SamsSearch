#include "UIObject.h"
#include "App.h"

void UIObject::load(const LoaderParams &pParams) {
    m_ScreenPosition = Vector2D(pParams.getX(), pParams.getY());
    m_width = pParams.getWidth();
    m_height = pParams.getHeight();
    m_textureID = pParams.getTextureID();
}

void UIObject::draw() {
    App::get()->getAssets()->drawTexture(m_textureID, m_ScreenPosition.getX(), m_ScreenPosition.getY());
}