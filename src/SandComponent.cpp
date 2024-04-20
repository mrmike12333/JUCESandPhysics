#include "SandComponent.h"

SandGrid::SandGrid()
    : physicsGrid()
    , renderGrid()
    , cellWidth(0)
    , cellHeight(0)
    , sandColour(juce::Colours::sandybrown)
    , backgroundColour(juce::Colours::black)
    , isMouseDown(false)
    , lastMouseDownPosition()
    , engineSpeed(UpdateRate::min)
{
    startTimerHz(UpdateRate::min);
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
        physicsGrid[nextPos.row][nextPos.col] = sandColour.brighter(randomNumberGenerator.nextFloat());
        updateQueue.erase(updateQueue.begin());
        repaint();
    }

    // Apply Physics
    applyPhysicsToGrid();

    // Draw
    repaint();
}

void SandGrid::resetGrid()
{
    juce::ScopedLock lock(gridLock);
    resetGrid(physicsGrid);
    resetGrid(renderGrid);
}

void SandGrid::setUpdateRate(const int speed)
{
    engineSpeed.store(speed);
    triggerAsyncUpdate();
}

void SandGrid::handleAsyncUpdate()
{
    stopTimer();
    startTimerHz(engineSpeed.load());
}

void SandGrid::resetGrid(SandArray& grid) const
{
    for (auto&  row : grid)
        for (auto& cell : row)
            cell = backgroundColour;
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
            if (renderGrid[row][col] == backgroundColour)
                continue;

            g.setColour(renderGrid[row][col]);
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
            if (physicsGrid[row][col] != backgroundColour
                && row < GridSettings::Rows - 1)
            {
                const juce::Colour currentColour = physicsGrid[row][col];
                // Fall to next block
                if (physicsGrid[row + 1][col] == backgroundColour)
                {
                    renderGrid[row + 1][col] = currentColour;
                    renderGrid[row][col] = backgroundColour;
                    continue;
                }

                // Offset to the left or right
                int offset = 0;
                if (col == 0)
                    offset = 1;
                else if (col == GridSettings::Columns - 1)
                    offset = -1;
                else
                    offset = randomNumberGenerator.nextBool() ? -1 : 1;

                if (physicsGrid[row + 1][col + offset] == backgroundColour)
                {
                    renderGrid[row + 1][col + offset] = currentColour;
                    renderGrid[row][col] = backgroundColour;
                }
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

    if (getLocalBounds().toFloat().contains(location))
        position.isValid = true;

    position.col = static_cast<unsigned int>(location.getX() / cellWidth);
    position.row = static_cast<unsigned int>(location.getY() / cellHeight);

    return position;
}
