#include "Assets.h"

#include "Settings.h"
#include "App.h"

Assets::Assets(App* pSDLApplication) : m_pApplication(pSDLApplication)
{
    //Cache this for brevity
    m_pRenderer = m_pApplication->getRenderer();
    //TODO Cancel using Audio or quit if this fails?
    if (!MIX_Init())
    {
        SDL_Log("MIX_Init failed: %s", SDL_GetError());
    }

    m_pMixer = MIX_CreateMixerDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, nullptr);
    //Create music track
    m_pMusicTrack = MIX_CreateTrack(m_pMixer);
    //Create sound track
    //TODO Pool this for overlapping sounds in future
    m_pSoundTrack = MIX_CreateTrack(m_pMixer);

    //Set volumes!
    MIX_SetTrackGain(m_pMusicTrack, m_pApplication->getSettings()->getMusicVolume());
    //TODO Load from Settings
    MIX_SetTrackGain(m_pSoundTrack, 1.0f);
}

// region Fonts

void Assets::loadFont(const std::string& filename, const std::string& fontID, const int size)
{
    if (m_fontMap.find(fontID) != m_fontMap.end())
    {
        return;
    }

    if (!TTF_Init())
    {
        std::cout << "SDL_ttf could not initialize! SDL_ttf Error: " << SDL_GetError() << std::endl;
        return;
    }

    TTF_Font* pFont = TTF_OpenFont(("assets/fonts/" + filename).c_str(), size);
    if (pFont == nullptr)
    {
        std::cout << "Failed to load font! SDL_ttf Error: " << SDL_GetError() << std::endl;
        return;
    }

    m_fontMap[fontID] = pFont;
}

// endregion

// region Text
void Assets::createTextTexture(const int width, const int height, const std::string& text,
                               const std::string& fontID,
                               const std::string& textureID)
{
    // Check to see if we have no text to write
    // if (text.size() != 0)

    //If we have already made this, just return it?
    if (m_textureMap.find(textureID) != m_textureMap.end()) return;

    // TODO check font exists?
    TTF_Font* gFont = m_fontMap[fontID];

    SDL_Texture* backgroundTexture = SDL_CreateTexture(m_pRenderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET,
                                                       width, height);
    SDL_SetRenderTarget(m_pRenderer, backgroundTexture);

    // Create the text item
    //TODO Make this a parameter
    constexpr auto textColor = SDL_Color{0xFF, 0xFF, 0xFF};
    SDL_Surface* pTextSurface = TTF_RenderText_Blended(gFont, text.c_str(), 0, textColor);
    SDL_Texture* pTextTexture = SDL_CreateTextureFromSurface(m_pRenderer, pTextSurface);
    SDL_DestroySurface(pTextSurface);

    // Get size of the text texture
    float textWidth, textHeight;
    SDL_GetTextureSize(pTextTexture, &textWidth, &textHeight);

    SDL_FRect dstRect;

    // Center the text
    // TODO Alignment as a parameter?
    dstRect.x = width / 2 - textWidth / 2;
    dstRect.y = height / 2 - textHeight / 2;
    dstRect.w = textWidth;
    dstRect.h = textHeight;

    // Draw text
    SDL_RenderTexture(m_pRenderer, pTextTexture, nullptr, &dstRect);

    // Save to Textures
    m_textureMap[textureID] = backgroundTexture;

    // Reset renderer
    SDL_SetRenderTarget(m_pRenderer, nullptr);
}

SDL_Texture* Assets::createDialogue(const std::string& characterName, const Sprite& face,
                                    const std::vector<std::string>& dialog, const std::string& fontID)
{
    constexpr int border = 5;
    //TODO Make this a set height always?
    const int height = face.height + 2 * border;
    int offset = border * 2;


    //Decide texture size:
    int width;
    m_pApplication->getWindowSize(&width, nullptr);

    TTF_Font* gFont = m_fontMap[fontID];

    SDL_Texture* dialogTexture = SDL_CreateTexture(m_pRenderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET,
                                                   width, height);
    SDL_SetRenderTarget(m_pRenderer, dialogTexture);

    //Set background color
    SDL_SetRenderDrawColor(m_pRenderer, 0x65, 0x73, 0x79, 0xff);
    SDL_RenderClear(m_pRenderer);

    //Check we have a face image
    if (face.textureID != "")
    {
        offset += face.width;
        //Draw face
        SDL_FRect dstRect;
        SDL_FRect srcRect;

        srcRect.x = face.column * face.width;
        srcRect.y = face.row * face.height;
        srcRect.w = face.width;
        srcRect.h = face.height;


        dstRect.x = border;
        dstRect.y = border;
        dstRect.w = face.width;
        dstRect.h = face.height;

        SDL_RenderTexture(m_pRenderer, m_textureMap[face.textureID], &srcRect, &dstRect);
    }

    constexpr auto textColor = SDL_Color{0xFF, 0xFF, 0xFF};

    int linePosition = border + 5;
    for (const auto line : dialog)
    {
        SDL_Surface* pTextSurface = TTF_RenderText_Blended(gFont, line.c_str(), 0, textColor);
        SDL_Texture* pTextTexture = SDL_CreateTextureFromSurface(m_pRenderer, pTextSurface);
        SDL_DestroySurface(pTextSurface);

        // Get the size of the text texture
        float textWidth, textHeight;
        SDL_GetTextureSize(pTextTexture, &textWidth, &textHeight);

        SDL_FRect dstRect;

        dstRect.x = offset;;
        dstRect.y = linePosition;
        dstRect.w = textWidth;
        dstRect.h = textHeight;

        // Draw text
        SDL_RenderTexture(m_pRenderer, pTextTexture, nullptr, &dstRect);

        //Go to next line
        linePosition += textHeight;
        linePosition += 10; //Line gap
    }

    // Reset renderer
    SDL_SetRenderTarget(m_pRenderer, nullptr);

    // Save to Textures
    m_textureMap["dialog"] = dialogTexture;
    addBorderToExistingTexture("dialog", border);

    return dialogTexture;
}

void Assets::getTextureSize(const std::string& textureID, float* width, float* height)
{
    if (m_textureMap.find(textureID) == m_textureMap.end())
    {
        SDL_Log("Texture not found: %s", textureID.c_str());
        return;
    }

    //Get texture details
    SDL_GetTextureSize(m_textureMap[textureID], width, height);
}

// endregion

// region Images
void Assets::loadTexture(const std::string& filename, const std::string& id)
{
    if (m_textureMap.find(id) != m_textureMap.end())
    {
        return;
    }

    SDL_Surface* pTempSurface = IMG_Load((filename).c_str());
    if (!pTempSurface)
    {
        std::cout << "Could not load image " << id << " from " << filename << std::endl;
        return;
    }

    SDL_Texture* pTexture = SDL_CreateTextureFromSurface(m_pRenderer, pTempSurface);
    SDL_DestroySurface(pTempSurface);

    if (!pTexture)
    {
        std::cout << "Could not create texture " << std::endl;
        return;
    }

    m_textureMap[id] = pTexture;
}

void Assets::addBorderToExistingTexture(const std::string& textureID, const float size)
{
    //TODO Refactor this mess to use SDL_RenderFillRects

    //Check texture exists
    if (m_textureMap.find(textureID) == m_textureMap.end())
    {
        SDL_Log("Texture not found: %s", textureID.c_str());
        return;
    }

    //Get texture details
    float width;
    float height;
    SDL_GetTextureSize(m_textureMap[textureID], &width, &height);

    //Set as destination
    SDL_SetRenderTarget(m_pRenderer, m_textureMap[textureID]);

    SDL_SetRenderDrawColor(m_pRenderer, 255, 255, 255, 255);

    //Add 4 rectangles to it
    const SDL_FRect top{0, 0, width, size};
    SDL_RenderFillRect(m_pRenderer, &top);
    const SDL_FRect bottom{0, height - size, width, size};
    SDL_RenderFillRect(m_pRenderer, &bottom);

    const SDL_FRect left{0, size, size, height - size};
    SDL_RenderFillRect(m_pRenderer, &left);
    const SDL_FRect right{width - size, size, width, height - size};
    SDL_RenderFillRect(m_pRenderer, &right);

    //Reset render target
    SDL_SetRenderTarget(m_pRenderer, nullptr);
}

void Assets::drawTexture(const std::string& id, const float x, const float y, float width, float height)
{
    if (width == 0.0f)
    {
        getTextureSize(id, &width, &height);
    }

    SDL_FRect srcRect;
    SDL_FRect destRect;
    srcRect.x = 0;
    srcRect.y = 0;
    srcRect.w = destRect.w = width;
    srcRect.h = destRect.h = height;
    destRect.x = x;
    destRect.y = y;
    SDL_RenderTexture(m_pRenderer, m_textureMap[id], &srcRect, &destRect);
}

void Assets::drawSprite(const Sprite& sprite,
                        const float x, const float y,
                        const int extraRow,
                        const int extraColumn)
{
    SDL_FRect srcRect;
    SDL_FRect destRect;
    srcRect.x = sprite.width * static_cast<float>(sprite.column + extraColumn);
    srcRect.y = sprite.height * static_cast<float>(sprite.row + extraRow);
    srcRect.w = destRect.w = sprite.width;
    srcRect.h = destRect.h = sprite.height;
    destRect.x = x;
    destRect.y = y;
    SDL_RenderTexture(m_pRenderer, m_textureMap[sprite.textureID], &srcRect, &destRect);
}

void Assets::drawTile(const std::string& id, int margin, int spacing, int x, int y, int width, int height,
                      const int currentRow,
                      const int currentFrame)
{
    SDL_FRect srcRect;
    SDL_FRect destRect;
    srcRect.x = margin + (spacing + width) * currentFrame;
    srcRect.y = margin + (spacing + height) * currentRow;
    srcRect.w = destRect.w = width;
    srcRect.h = destRect.h = height;
    destRect.x = x;
    destRect.y = y;
    SDL_RenderTexture(m_pRenderer, m_textureMap[id], &srcRect, &destRect);
}

void Assets::deleteTexture(const std::string& id)
{
    SDL_DestroyTexture(m_textureMap[id]);
    m_textureMap.erase(id);
}

// endregion

// region Audio
bool Assets::loadMusic(const std::string& filename, const std::string& id)
{
    //Check to see if this has been loaded already
    if (m_music.find(id) != m_music.end())
    {
        return true;
    }

    if (MIX_Audio* pMusic = MIX_LoadAudio(m_pMixer, filename.c_str(), true))
    {
        m_music[id] = pMusic;
        return true;
    }
    std::cout << "Could not load music: " << SDL_GetError() << std::endl;
    return false;
}

void Assets::playMusic(const std::string& id, int loop)
{
    MIX_SetTrackAudio(m_pMusicTrack, m_music[id]);
    MIX_PlayTrack(m_pMusicTrack, -1);
    m_currentMusic = id;
}

void Assets::stopMusic()
{
    MIX_StopTrack(m_pMusicTrack, 0);
}

void Assets::stopTitleMusic()
{
    if (m_currentMusic == "main_menu")
    {
        stopMusic();
    }
}

void Assets::setMusicVolume(const int volume)
{
    MIX_SetTrackGain(m_pMusicTrack, static_cast<float>(volume) / 100.0f);
}

void Assets::setGameVolume(const int volume)
{
    MIX_SetTrackGain(m_pSoundTrack, static_cast<float>(volume) / 100.0f);
}

bool Assets::loadSound(const std::string& filename, const std::string& id)
{
    //Check to see if this has been loaded already
    if (m_sound.find(id) != m_sound.end())
    {
        return true;
    }

    if (auto* pSound = MIX_LoadAudio(m_pMixer, filename.c_str(), true))
    {
        m_sound[id] = pSound;
        return true;
    }
    std::cout << "Could not load sound: " << id << " : " << SDL_GetError() << std::endl;
    return false;
}

void Assets::playSound(const std::string& id, int loops, int channel)
{
    if (m_sound.find(id) == m_sound.end())
    {
        std::cout << "Could not find sound: " << id << std::endl;
        return;
    }

    MIX_SetTrackAudio(m_pSoundTrack, m_sound[id]);
    MIX_PlayTrack(m_pSoundTrack, 0);
}

// endregion

Assets::~Assets()
{
    //Textures
    for (auto& [id, texture] : m_textureMap)
    {
        SDL_DestroyTexture(m_textureMap[id]);
    }

    //Fonts
    //TTF_CloseFont
    TTF_Quit();

    //Audio
    for (auto& [id, music] : m_music)
    {
        MIX_DestroyAudio(m_music[id]);
    }
    for (auto& [id, chunk] : m_sound)
    {
        MIX_DestroyAudio(m_sound[id]);
    }
    MIX_DestroyMixer(m_pMixer);
    MIX_Quit();
}
