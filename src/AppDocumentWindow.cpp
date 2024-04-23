#include "AppDocumentWindow.h"

AppDocumentWindow::AppDocumentWindow()
        : juce::DocumentWindow("Sand Physics App",
                juce::Colours::black,
                juce::DocumentWindow::TitleBarButtons::minimiseButton +
                juce::DocumentWindow::TitleBarButtons::closeButton)
{
    setUsingNativeTitleBar(true);
    setResizable(true, false);

    /*
    *   Potentially hacky solution which may fail on multi-desktop.
    *   TODO: Refactor for finding the display which the component is in.
    */
    const juce::Displays activeDisplays = juce::Desktop::getInstance().getDisplays();
    const auto displayArea = activeDisplays.getPrimaryDisplay()->userArea;
    setResizeLimits(400, 400,
        displayArea.getWidth(), displayArea.getHeight());
}

void AppDocumentWindow::closeButtonPressed()
{
    juce::JUCEApplicationBase::quit();
}
