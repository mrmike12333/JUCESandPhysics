#include "MainComponent.h"

MainComponent::MainComponent()
{
    setSize(Sizes::Width, Sizes::Height);

    addAndMakeVisible(sandGrid);
    addAndMakeVisible(resetButton);

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

    bounds.removeFromLeft(reduction);
    bounds.removeFromRight(reduction);
    bounds.removeFromTop(reduction);

    resetButton.setBounds(bounds.removeFromBottom(reduction));
    sandGrid.setBounds(bounds);
}