#pragma once
#include <juce_gui_basics/juce_gui_basics.h>

/**
 * The window surrounding the application, containing the app
 * name, minimise and maximuse functionality.
 */
class AppDocumentWindow final
    : public juce::DocumentWindow
{
public:
    explicit AppDocumentWindow();
private:
    void closeButtonPressed() override;
};
