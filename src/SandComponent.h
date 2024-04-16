#pragma once
#include <juce_gui_extra/juce_gui_extra.h>
#include <juce_events/juce_events.h>

enum GridSettings
{
    Columns = 80,
    Rows = 80
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
    , public juce::Timer
{
public:
    explicit SandGrid();

    ~SandGrid() override = default;

    void paint(juce::Graphics &g) override;

    void resized() override;

    void mouseDown(const juce::MouseEvent &event) override;

    void mouseUp(const juce::MouseEvent &event) override;

    void mouseDrag(const juce::MouseEvent &event) override;

    void timerCallback() override;

    /**
     * @brief Reset the entire grid
     */
    void resetGrid();

    private:
    /**
     * Re-initialise a grid to be all zeros
     * @param grid The grid to reset
     */
    static void resetGrid(std::array<std::array<bool, GridSettings::Columns>, GridSettings::Rows>& grid);

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
     * @brief Apply some physics to give the sand "gravity"
     */
    void applyPhysicsToGrid();

    /**
     * @brief Post a new sand position to the queue.
     *        NOTE: invalid grid positions will not be queued.
     * @param position The grid position to place.
     */
    void queueNewSandPlacement(GridPosition position);

    /**
     * @brief   Convert a pixel, screen position to a point on a grid.
     *          NOTE: if outside grid bounds, the position is marked invalid.
     * @param location The position on the screen as a juce float point.
     * @return  A GridPosition object detailing the row and column which the point
     *          exists in
     */
    [[nodiscard]] GridPosition convertPointToGridPosition(juce::Point<float> location) const;

    void setMouseHeldDown(const bool mouseDown) { isMouseDown = mouseDown; }

    [[nodiscard]] bool getMouseHeldDown() const { return isMouseDown; }

    std::array<std::array<bool, GridSettings::Columns>, GridSettings::Rows> physicsGrid, renderGrid;
    float cellWidth, cellHeight;

    std::vector<GridPosition> updateQueue;

    juce::CriticalSection gridLock;

    bool isMouseDown;
    GridPosition lastMouseDownPosition;
};