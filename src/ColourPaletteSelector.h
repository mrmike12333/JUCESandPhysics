#pragma once
#include <juce_gui_extra/juce_gui_extra.h>
#include <juce_events/juce_events.h>

/**
 * @brief A custom made colour selector to select a point across the grid.
 * TODO: Made a proper 2D gradient, like a colour wheel
 */
class ColourPaletteSelector final
    : public juce::Component
    , public juce::ChangeBroadcaster
{
public:
    ColourPaletteSelector();

    void mouseDown(const juce::MouseEvent &event) override;

    void mouseDrag(const juce::MouseEvent &event) override;

    void paint(juce::Graphics &g) override;

    void resized() override;

    /**
     * @brief Get the colour currently selected by the user.
     * @return The selected juce::Colour
     */
    [[nodiscard]] juce::Colour getSelectedColour() const;

private:
    /**
     * Generate the colour gradient to render
     * @return The new colour gradient
     */
    [[nodiscard]] juce::ColourGradient regenerateColourGradient() const;

    void updateLastSelectedPosition(juce::Point<int> position);

    juce::ColourGradient grad;
    juce::Point<int> lastSelectedPosition;
};