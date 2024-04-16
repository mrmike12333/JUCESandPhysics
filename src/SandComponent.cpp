#include "SandComponent.h"

SandGrid::SandGrid()
    : grid()
    , cellWidth(0)
    , cellHeight(0)
{
    resetGrid();
}

void SandGrid::paint(juce::Graphics &g)
{
    drawSand(g);
    drawDebugGrid(g);
}

void SandGrid::resized()
{
    const juce::Rectangle<float> bounds = getLocalBounds().toFloat();

    cellHeight = bounds.getHeight() / static_cast<float>(GridSettings::Rows);
    cellWidth = bounds.getWidth() / static_cast<float>(GridSettings::Columns);
}

void SandGrid::mouseUp(const juce::MouseEvent &event)
{
    const GridPosition clickPos = convertPointToGridPosition(event.getPosition().toFloat());

    if (clickPos.isValid)
    {
        grid[clickPos.row][clickPos.col] = true;
        repaint();
    }
}

void SandGrid::resetGrid()
{
    for (auto&  row : grid)
        for (auto& cell : row)
            cell = false;
}

void SandGrid::drawDebugGrid(juce::Graphics &g) const
{
    const juce::Colour gridColour = juce::Colours::white;
    g.setColour(gridColour);

    for (auto row = 0; row < GridSettings::Rows; ++row)
    {
        const float cellXPosition = static_cast<float>(row) * cellWidth;
        for (auto col = 0; col < GridSettings::Columns; ++col)
        {
            const float cellYPosition = static_cast<float>(col) * cellHeight;

            g.drawRect(cellXPosition,
                cellYPosition,
                cellWidth,
                cellHeight);
        }
    }
}

void SandGrid::drawSand(juce::Graphics &g) const
{
    for (size_t row = 0; row < GridSettings::Rows; ++row)
    {
        for (size_t col = 0; col < GridSettings::Columns; ++col)
        {
            if (grid[row][col] == false)
                continue;

            g.setColour(juce::Colours::sandybrown);
            g.fillRect(static_cast<float>(col) * cellWidth
                , static_cast<float>(row) * cellHeight
                , cellWidth
                , cellHeight);
        }
    }
}

GridPosition SandGrid::convertPointToGridPosition(const juce::Point<float> location) const
{
    GridPosition position;

    position.col = static_cast<unsigned int>(location.getX() / cellWidth);
    position.row = static_cast<unsigned int>(location.getY() / cellHeight);

    if (location.getX() >= 0 && location.getY() >= 0)
        position.isValid = true;

    return position;
}
