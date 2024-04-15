#pragma once
#include <juce_gui_extra/juce_gui_extra.h>

enum GridSettings
{
    Columns = 10,
    Rows = 10
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

    std::array<std::array<uint8_t, GridSettings::Columns>, GridSettings::Rows> grid;
    float cellWidth, cellHeight;
};