#include "UIObject.h"

void UIObject::load(const LoaderParams *pParams) {
    m_position = Vector2D(pParams->getX(), pParams->getY());
    m_width = pParams->getWidth();
    m_height = pParams->getHeight();
    m_textureID = pParams->getTextureID();
}

void UIObject::draw() {
    AssetManager::get()->drawTexture(m_textureID, (int) m_position.getX(), (int) m_position.getY(), m_width, m_height);
}