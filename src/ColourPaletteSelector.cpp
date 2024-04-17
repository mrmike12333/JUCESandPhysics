#include "ColourPaletteSelector.h"

ColourPaletteSelector::ColourPaletteSelector()
    : grad()
    , lastSelectedPosition(0, 0)
{
}

void ColourPaletteSelector::mouseDown(const juce::MouseEvent &event)
{
    updateLastSelectedPosition(event.getPosition());
}

void ColourPaletteSelector::mouseDrag(const juce::MouseEvent &event)
{
    updateLastSelectedPosition(event.getPosition());
}

void ColourPaletteSelector::paint(juce::Graphics &g)
{
    g.setGradientFill(grad);
    g.fillAll();

    g.setColour(juce::Colours::black);
    g.drawRect(lastSelectedPosition.x, 0, 8, getHeight(), 1);
}

void ColourPaletteSelector::resized()
{
    // Need to reset the colour gradient on resized callback.
    grad = regenerateColourGradient();

    repaint();
}

juce::Colour ColourPaletteSelector::getSelectedColour() const
{
    return grad.getColourAtPosition(static_cast<float>(lastSelectedPosition.x) / static_cast<float>(getWidth()));
}

juce::ColourGradient ColourPaletteSelector::regenerateColourGradient() const
{
    const auto bounds = getLocalBounds().toFloat();
    juce::ColourGradient gradientToReturn(juce::Colours::orange, 0.0f, 0.0f,
        juce::Colours::blue, bounds.getWidth(), bounds.getHeight(), true);

    // TODO: Refactor this so it's not regenerated each time.
    const std::vector<juce::Colour> colours =
    {
        // TODO: Make colours look nicer.
        juce::Colours::sandybrown,
        juce::Colours::lightblue,
        juce::Colours::green,
        juce::Colours::yellow,
        juce::Colours::red
    };

    int i = 0;
    auto sizeOfEachIndex = 1.0f / static_cast<float>(colours.size());

    for (const auto& col : colours)
        gradientToReturn.addColour(static_cast<float>(i++) * sizeOfEachIndex, col);

    return gradientToReturn;
}

void ColourPaletteSelector::updateLastSelectedPosition(const juce::Point<int> position)
{
    lastSelectedPosition = position;
    repaint();
    sendChangeMessage();
}
