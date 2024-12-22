#pragma once

#include <iostream>
#include <utility>

class LoaderParams
{
public:
    /**
     * @param x x position
     * @param y y position
     * @param width
     * @param height
     * @param textureID name of sprite sheet
     * @param startColumn in the sprite sheet
     * @param startRow in the sprite sheet
     */
    LoaderParams(int x, int y, int width, int height, std::string textureID, int startColumn = 0, int startRow = 0)
        : m_x(x),
          m_y(y),
          m_width(width),
          m_height(height),
          m_textureID(std::move(textureID)),
          m_startColumn(startColumn),
          m_startRow(startRow) {}

    int getX() const { return m_x; }

    int getY() const { return m_y; }

    int getWidth() const { return m_width; }

    int getHeight() const { return m_height; }

    std::string getTextureID() const { return m_textureID; }

    int getStartColumn() const { return m_startColumn; }

    int getStartRow() const { return m_startRow; }

private:
    int m_x;
    int m_y;
    int m_width;
    int m_height;

    std::string m_textureID;
    int m_startColumn;
    int m_startRow;
};
