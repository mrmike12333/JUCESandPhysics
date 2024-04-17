#pragma once

#include <juce_gui_extra/juce_gui_extra.h>
#include "SandComponent.h"
#include "ColourPaletteSelector.h"

/**
 * @brief The main component which holds everything within the app.
 * 
 */
class MainComponent final
    : public juce::Component
    , public juce::ChangeListener
{
public:
    /**
    * @brief Construct a new Main Component object
    * 
    */
    explicit MainComponent();

    enum Sizes
    {
        Width = 800,
        Height = 800
    };

    void paint (juce::Graphics&) override;
    
    void resized() override;

    void changeListenerCallback(juce::ChangeBroadcaster *source) override;

private:
    SandGrid sandGrid;
    juce::TextButton resetButton;
    ColourPaletteSelector colourSelector;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
