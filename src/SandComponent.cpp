#include "SandComponent.h"

SandGrid::SandGrid()
    : physicsGrid()
    , renderGrid()
    , cellWidth(0)
    , cellHeight(0)
    , isMouseDown(false)
    , lastMouseDownPosition()
{
    startTimerHz(30);
    resetGrid(physicsGrid);
    resetGrid(renderGrid);
}

void SandGrid::paint(juce::Graphics &g)
{
    juce::ScopedLock lock(gridLock);
    drawSand(g);
    g.setColour(juce::Colours::white);
    g.drawRect(getLocalBounds().toFloat());

    physicsGrid = renderGrid;
}

void SandGrid::resized()
{
    const juce::Rectangle<float> bounds = getLocalBounds().toFloat();

    cellHeight = bounds.getHeight() / static_cast<float>(GridSettings::Rows);
    cellWidth = bounds.getWidth() / static_cast<float>(GridSettings::Columns);
}

void SandGrid::mouseDown(const juce::MouseEvent &event)
{
    setMouseHeldDown(true);
    lastMouseDownPosition = convertPointToGridPosition(event.getPosition().toFloat());
}

void SandGrid::mouseUp(const juce::MouseEvent &event)
{
    const GridPosition clickPos = convertPointToGridPosition(event.getPosition().toFloat());

    queueNewSandPlacement(clickPos);

    setMouseHeldDown(false);
}

void SandGrid::mouseDrag(const juce::MouseEvent &event)
{
    // Leverage the same holding code, makes for better visual consistency.
    lastMouseDownPosition = convertPointToGridPosition(event.getPosition().toFloat());
}

void SandGrid::timerCallback()
{
    juce::ScopedTryLock lock(gridLock);

    if (getMouseHeldDown())
    {
        queueNewSandPlacement(lastMouseDownPosition);
    }

    // Handle next update
    if (!updateQueue.empty())
    {
        const GridPosition nextPos = updateQueue.front();
        physicsGrid[nextPos.row][nextPos.col] = true;
        updateQueue.erase(updateQueue.begin());
        repaint();
    }

    // Apply Physics
    applyPhysicsToGrid();

    // Draw
    repaint();
}

void SandGrid::resetGrid(std::array<std::array<bool, GridSettings::Columns>, GridSettings::Rows>& grid)
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
            if (renderGrid[row][col] == false)
                continue;

            g.setColour(juce::Colours::sandybrown);
            g.fillRect(static_cast<float>(col) * cellWidth
                , static_cast<float>(row) * cellHeight
                , cellWidth
                , cellHeight);
        }
    }
}

void SandGrid::applyPhysicsToGrid()
{
    juce::ScopedLock lock(gridLock);
    for (size_t row = 0; row < GridSettings::Rows; ++row)
    {
        for (size_t col = 0; col < GridSettings::Columns; ++col)
        {
            // Move each block down
            if (physicsGrid[row][col] == true
                && row < GridSettings::Rows - 1
                && physicsGrid[row + 1][col] == false)
            {
                renderGrid[row][col] = false;
                renderGrid[row + 1][col] = true;
            }
        }
    }
}

void SandGrid::queueNewSandPlacement(const GridPosition position)
{
    if (position.isValid)
    {
        updateQueue.emplace_back(position);
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
