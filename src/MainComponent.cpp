#include "MainComponent.h"

MainComponent::MainComponent()
{
    setSize(Sizes::Width, Sizes::Height);

    addAndMakeVisible(sandGrid);
}

void MainComponent::paint(juce::Graphics& g)
{
    juce::Component::paint(g);
}

void MainComponent::resized()
{
    sandGrid.setBounds(getLocalBounds().reduced(50));
}