#pragma once
#include <juce_gui_extra/juce_gui_extra.h>

enum GridSettings
{
    Columns = 10,
    Rows = 10
};

/**
 * @brief Handy class for getting the grid position
 */
struct GridPosition
{
    GridPosition()
        : row(0)
        , col(0)
        , isValid(false)
    {
    }

    // TODO: Make integer types more consistent.
    unsigned int row, col;
    bool isValid;
};

/**
 * @brief The component grid which handles user input and drawing the "sand" to screen.
 */
class SandGrid final
    : public juce::Component
{
public:
    explicit SandGrid();

    ~SandGrid() override = default;

    void paint(juce::Graphics &g) override;

    void resized() override;

    void mouseUp(const juce::MouseEvent &event) override;

    void resetGrid();

    private:
    /**
     * @brief Draw a grid to display each "pixel" the sand can be drawn to.
     * @param g the juce graphics context to draw to.
     */
    void drawDebugGrid(juce::Graphics& g) const;

    /**
     * @brief Draw the "sand" to screen
     * @param g the juce graphics context to draw to.
     */
    void drawSand(juce::Graphics& g) const;

    /**
     * @brief   Convert a pixel, screen position to a point on a grid.
     *          NOTE: if outside grid bounds, the position is marked invalid.
     * @param location The position on the screen as a juce float point.
     * @return  A GridPosition object detailing the row and column which the point
     *          exists in
     */
    [[nodiscard]] GridPosition convertPointToGridPosition(juce::Point<float> location) const;

    std::array<std::array<bool, GridSettings::Columns>, GridSettings::Rows> grid;
    float cellWidth, cellHeight;
};