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
    Component::mouseUp(event);
}

void SandGrid::resetGrid()
{
    for (auto&  row : grid)
        for (auto& cell : row)
            cell = 0;
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
