#pragma once

#include <string>
#include <map>

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3_mixer/SDL_mixer.h>

class AssetManager {
public:
    static AssetManager *get() {
        static AssetManager me;
        return &me;
    };

    // Singleton
    AssetManager(AssetManager &other) = delete;
    void operator=(const AssetManager &) = delete;

    /// @brief Attach renderer to static instance
    /// @param pRenderer
    void setRenderer(SDL_Renderer *pRenderer) {
        m_pRenderer = pRenderer;
    }

    // Fonts/text
    bool loadFont(const std::string &filename, const std::string &fontID, int size);

    /// @brief Create a texture with the specified text on it
    /// @param width
    /// @param height
    /// @param text text to write
    /// @param fontID font to use
    /// @param textureID textureID to save as
    /// @return Creation success
    /// @note ToDo text alignment, multiline, background colour, background image optional, text colour, size from xml file?
    bool createTextTexture(int width, int height, const std::string &text, const std::string &fontID,
                           const std::string &textureID);

    // region Images
    bool loadTexture(const std::string &filename, const std::string &id);

    /// @brief Add a border to an existing texture
    /// @param textureID texture
    /// @param size width of border
    /// @param pRenderer renderer to use
    void addBorderToExistingTexture(const std::string &textureID, float size);

    /// @brief
    /// @param id
    /// @param x position on screen
    /// @param y position on screen
    /// @param width
    /// @param height
    void drawTexture(const std::string &id, float x, float y, float width, float height);

    /// @brief
    /// @param id
    /// @param x position on screen
    /// @param y position on screen
    /// @param width
    /// @param height
    /// @param currentRow
    /// @param currentColumn
    void drawTextureFrame(const std::string &id, float x, float y, float width, float height, int currentRow, int currentColumn);

    /// @brief Draw a tile from a sprite sheet
    /// @param id texture ID
    /// @param margin in sprite sheet
    /// @param spacing in sprite sheet
    /// @param x position on screen
    /// @param y position on screen
    /// @param width
    /// @param height
    /// @param currentRow
    /// @param currentFrame
    void drawTile(const std::string &id, int margin, int spacing, int x, int y, int width, int height, int currentRow,
                  int currentFrame);

    /// @brief Delete a texture
    /// @param id
    void deleteTexture(const std::string &id);
    /// endregion

    ///region Audio

    /// @brief Load a music file
    /// @param filename
    /// @param id
    /// @return success
    bool loadMusic(const std::string &filename, const std::string &id);

    /// @brief Play music
    /// @param id musicID to play
    /// @param loop Number of loops to play the music for: 0 for once, -1 for repeat (default)
    void playMusic(const std::string &id, int loop = -1);

    /// @brief Stop all music
    /// @note TODO Only stop if not menu music?
    static void stopMusic();

    /// @brief Stop playing menu music
    void stopMenuMusic();

    /// @brief Set music volume
    /// @param volume as a percentage
    static void setMusicVolume(int volume);

    /// @brief Set game volume
    /// @param volume as a percentage
    static void setGameVolume(int volume);

    bool loadSound(const std::string &filename, const std::string &id);

    /// @brief Play a loaded sound
    /// @param id of sound to play
    /// @param loops how many times to loop, defaults to no extra loops (once)
    /// @param channel to play on, defaults to -1 for next available channel
    void playSound(const std::string &id, int loops = 0, int channel = -1);
    ///endregion

    // End game
    void clean();

private:
    AssetManager();

    ~AssetManager() = default;

    SDL_Renderer *m_pRenderer;
    std::map<std::string, SDL_Texture *> m_textureMap;
    std::map<std::string, TTF_Font *> m_fontMap;
    std::map<std::string, Mix_Music *> m_music;
    std::string m_currentMusic;

    std::map<std::string, Mix_Chunk *> m_sound;
};