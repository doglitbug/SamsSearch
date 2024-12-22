#include <iostream>

#include "AssetManager.h"

// region Fonts
bool AssetManager::loadFont(const std::string &filename, const std::string &fontID, int size) {
    if (m_fontMap.find(fontID) != m_fontMap.end()) {
        return true;
    }

    if (TTF_Init() == -1) {
        std::cout << "SDL_ttf could not initialize! SDL_ttf Error: " << TTF_GetError() << std::endl;
        return false;
    }

    TTF_Font *pFont = TTF_OpenFont(("assets/fonts/" + filename).c_str(), size);
    if (pFont == nullptr) {
        std::cout << "Failed to load font! SDL_ttf Error: " << TTF_GetError() << std::endl;
        return false;
    }

    m_fontMap[fontID] = pFont;
    return true;
}

bool AssetManager::createTextTexture(int width, int height, const std::string &text, const std::string &fontID,
                                     const std::string &textureID) {
    // Check to see if we have no text to write
    // if (text.size() != 0)

    //If we have already made this, just return it?
    if (m_textureMap.find(textureID) != m_textureMap.end()) return true;

    // TODO check font exists?
    TTF_Font *gFont = m_fontMap[fontID];

    SDL_Texture *backgroundTexture = SDL_CreateTexture(m_pRenderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET,
                                                       width, height);
    SDL_SetRenderTarget(m_pRenderer, backgroundTexture);

    // Create the text item
    //TODO Make this a parameter
    auto textColor = SDL_Color{0xFF, 0xFF, 0xFF};
    SDL_Surface *pTextSurface = TTF_RenderText_Blended(gFont, text.c_str(), textColor);
    SDL_Texture *pTextTexture = SDL_CreateTextureFromSurface(m_pRenderer, pTextSurface);
    SDL_FreeSurface(pTextSurface);

    // Get size of the text texture
    int textWidth, textHeight;
    SDL_QueryTexture(pTextTexture, nullptr, nullptr, &textWidth, &textHeight);

    SDL_Rect dstRect;

    // Center the text
    // TODO Alignment as a parameter?
    dstRect.x = width / 2 - textWidth / 2;
    dstRect.y = height / 2 - textHeight / 2;
    dstRect.w = textWidth;
    dstRect.h = textHeight;

    // Draw text
    SDL_RenderCopy(m_pRenderer, pTextTexture, nullptr, &dstRect);

    // Save to Textures
    m_textureMap[textureID] = backgroundTexture;

    // Reset renderer
    SDL_SetRenderTarget(m_pRenderer, nullptr);

    return true;
}
// endregion

// region Images
bool AssetManager::loadTexture(const std::string &filename, const std::string &id) {
    if (m_textureMap.find(id) != m_textureMap.end()) {
        return true;
    }

    SDL_Surface *pTempSurface = IMG_Load((filename).c_str());
    if (!pTempSurface) {
        std::cout << "Could not load image " << id << " from " << filename << std::endl;
        return false;
    }

    SDL_Texture *pTexture = SDL_CreateTextureFromSurface(m_pRenderer, pTempSurface);
    SDL_FreeSurface(pTempSurface);

    if (!pTexture) {
        std::cout << "Could not create texture " << std::endl;
        return false;
    }

    // TODO Ensure we don't already have this texture ID, or should we just overwrite it after freeing the previous one?
    m_textureMap[id] = pTexture;
    return true;
}

void AssetManager::addBorderToExistingTexture(const std::string &textureID, int size) {
    //TODO Refactor this mess to use SDL_RenderFillRects

    //Check texture exists
    if (m_textureMap.find(textureID) != m_textureMap.end()) {
        //TPanic
    }

    //Get texture details
    int width;
    int height;
    SDL_QueryTexture(m_textureMap[textureID], nullptr, nullptr, &width, &height);

    //Set as destination
    SDL_SetRenderTarget(m_pRenderer, m_textureMap[textureID]);

    SDL_SetRenderDrawColor(m_pRenderer, 255, 255, 255, 255);

    //Add 4 rectangles to it
    auto top = new SDL_Rect{0, 0, width, size};
    SDL_RenderFillRect(m_pRenderer, top);
    auto bottom = new SDL_Rect{0, height - size, width, height};
    SDL_RenderFillRect(m_pRenderer, bottom);
    auto left = new SDL_Rect{0, size, size, height - size};
    SDL_RenderFillRect(m_pRenderer, left);
    auto right = new SDL_Rect{width - size, size, width, height - size};
    SDL_RenderFillRect(m_pRenderer, right);
    //Reset render target
    SDL_SetRenderTarget(m_pRenderer, nullptr);
}


void AssetManager::drawTexture(const std::string &id, int x, int y, int width, int height, SDL_RendererFlip flip) {
    if (width==0) {
        SDL_QueryTexture(m_textureMap[id], nullptr, nullptr, &width, &height);
    }
    SDL_Rect srcRect;
    SDL_Rect destRect;
    srcRect.x = 0;
    srcRect.y = 0;
    srcRect.w = destRect.w = width;
    srcRect.h = destRect.h = height;
    destRect.x = x;
    destRect.y = y;
    SDL_RenderCopyEx(m_pRenderer, m_textureMap[id], &srcRect, &destRect, 0, nullptr, flip);
}

void AssetManager::drawTextureFrame(const std::string &id, int x, int y, int width, int height, int currentRow,
                                    int currentFrame, SDL_RendererFlip flip) {
    SDL_Rect srcRect;
    SDL_Rect destRect;
    srcRect.x = width * currentFrame;
    srcRect.y = height * currentRow;
    srcRect.w = destRect.w = width;
    srcRect.h = destRect.h = height;
    destRect.x = x;
    destRect.y = y;
    SDL_RenderCopyEx(m_pRenderer, m_textureMap[id], &srcRect, &destRect, 0, nullptr, flip);
}

void AssetManager::drawTile(const std::string &id, int margin, int spacing, int x, int y, int width, int height,
                            int currentRow,
                            int currentFrame) {
    SDL_Rect srcRect;
    SDL_Rect destRect;
    srcRect.x = margin + (spacing + width) * currentFrame;
    srcRect.y = margin + (spacing + height) * currentRow;
    srcRect.w = destRect.w = width;
    srcRect.h = destRect.h = height;
    destRect.x = x;
    destRect.y = y;
    SDL_RenderCopyEx(m_pRenderer, m_textureMap[id], &srcRect, &destRect, 0, nullptr, SDL_FLIP_NONE);
}

void AssetManager::deleteTexture(const std::string &id) {
    SDL_DestroyTexture(m_textureMap[id]);
    m_textureMap.erase(id);
}

// endregion

// region Audio
bool AssetManager::loadMusic(const std::string &filename, const std::string &id) {
    //Check to see if this has been loaded already
    if (m_music.find(id) != m_music.end()) {
        return true;
    }

    Mix_Music *pMusic = Mix_LoadMUS(filename.c_str());
    if (pMusic) {
        m_music[id] = pMusic;
        return true;
    }
    std::cout << "Could not load music: " << Mix_GetError() << std::endl;
    return false;
}

void AssetManager::playMusic(const std::string &id, int loop) {
    Mix_PlayMusic(m_music[id], loop);
    m_currentMusic = id;
}

void AssetManager::stopMusic() {
    Mix_HaltMusic();
}

// endregion
void AssetManager::clean() {
    //Textures
    for (auto &[id, texture]: m_textureMap) {
        SDL_DestroyTexture(m_textureMap[id]);
    }

    //Fonts
    //TTF_CloseFont
    TTF_Quit();

    //Audio
    //Mix_FreeMusic
    //Mix_FreeChunk
    Mix_CloseAudio();
}

AssetManager::AssetManager() {
    Mix_OpenAudio(22050, AUDIO_S16, 2, 4096);
    //Set volumes!
    //TODO Load from Settings?
    Mix_Volume(-1, 4);
    Mix_VolumeMusic(10);
}

void AssetManager::stopMenuMusic() {
    if (m_currentMusic == "main_menu") {
        stopMusic();
    }
}

void AssetManager::setMusicVolume(int volume) {
    int newVolume = (volume / 100.0f) * MIX_MAX_VOLUME;
    Mix_VolumeMusic(newVolume);
}

void AssetManager::setGameVolume(int volume) {
    int newVolume = (volume / 100.0f) * MIX_MAX_VOLUME;
    Mix_Volume(-1, newVolume);
}

bool AssetManager::loadSound(const std::string &filename, const std::string &id) {
      //Check to see if this has been loaded already
    if (m_sound.find(id) != m_sound.end()) {
        return true;
    }

    auto *pSound = Mix_LoadWAV(filename.c_str());
    if (pSound) {
        m_sound[id] = pSound;
        return true;
    }
    std::cout << "Could not load sound: " << id <<" : " << Mix_GetError() << std::endl;
    return false;
}

void AssetManager::playSound(const std::string &id, int loops, int channel) {
    if (m_sound.find(id) == m_sound.end()) {
        std::cout << "Could not find sound: " << id << std::endl;
        return;
    }
    Mix_PlayChannel(channel, m_sound[id], loops);
}
