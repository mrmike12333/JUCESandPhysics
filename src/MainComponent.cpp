#include "MainComponent.h"

MainComponent::MainComponent()
{

}

void MainComponent::paint(juce::Graphics& g)
{
    const auto bounds = getLocalBounds();
    g.setColour(juce::Colours::white);
    g.drawText("Hello World!", bounds, juce::Justification::centred);
}

void MainComponent::resized()
{
    
}