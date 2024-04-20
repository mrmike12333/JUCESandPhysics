#include "MainComponent.h"

MainComponent::MainComponent()
    : colourSelector()
{
    setSize(Sizes::Width, Sizes::Height);

    addAndMakeVisible(sandGrid);
    addAndMakeVisible(resetButton);
    addAndMakeVisible(colourSelector);
    addAndMakeVisible(speedControl);

    colourSelector.addChangeListener(this);
    sandGrid.setActiveColour(colourSelector.getSelectedColour());

    setupSpeedControl();

    resetButton.setButtonText("Reset Grid");
    resetButton.setColour(juce::TextButton::ColourIds::textColourOnId,
        juce::Colours::white);
    resetButton.setColour(juce::TextButton::ColourIds::textColourOffId,
    juce::Colours::white);
    resetButton.setColour(juce::TextButton::ColourIds::buttonColourId,
    juce::Colours::black);
    resetButton.setColour(juce::TextButton::ColourIds::buttonOnColourId,
    juce::Colours::black);

    resetButton.onClick = [this]()
    {
        sandGrid.resetGrid();
    };
}

void MainComponent::paint(juce::Graphics& g)
{
    juce::Component::paint(g);
}

void MainComponent::resized()
{
    constexpr int reduction = 50;
    auto bounds = getLocalBounds();
    auto bottomBounds = bounds.removeFromBottom(reduction);

    sandGrid.setBounds(bounds);

    constexpr int numCols = 3;
    const int componentWidth = bottomBounds.getWidth() / numCols;

    // Bottom Panel
    colourSelector.setBounds(bottomBounds.removeFromLeft(componentWidth));
    resetButton.setBounds(bottomBounds.removeFromLeft(componentWidth));
    speedControl.setBounds(bottomBounds.removeFromLeft(componentWidth));
}

void MainComponent::changeListenerCallback(juce::ChangeBroadcaster *source)
{
    if (source == &colourSelector)
    {
        sandGrid.setActiveColour(colourSelector.getSelectedColour());
    }
}

void MainComponent::setupSpeedControl()
{
    speedControl.setSliderStyle(juce::Slider::LinearBarVertical);
    speedControl.textFromValueFunction = [](const double val)
    {
        const double normalisedValue = ((val - UpdateRate::min) / (UpdateRate::max - UpdateRate::min)) * 100.0;
        return juce::String("Speed: ") + juce::String(static_cast<int>(normalisedValue));
    };
    speedControl.setRange(UpdateRate::min, UpdateRate::max);
    speedControl.setTextValueSuffix("%");
    speedControl.setTextBoxIsEditable(false);
    speedControl.onValueChange = [this](){ sandGrid.setUpdateRate(static_cast<int>(speedControl.getValue())); };
    speedControl.setSkewFactor(0.5);
}
