#include "AppDocumentWindow.h"

AppDocumentWindow::AppDocumentWindow()
        : juce::DocumentWindow("Sand Physics App",
                juce::Colours::black,
                juce::DocumentWindow::TitleBarButtons::minimiseButton +
                juce::DocumentWindow::TitleBarButtons::closeButton)
{
    setUsingNativeTitleBar(true);
}

void AppDocumentWindow::closeButtonPressed()
{
    juce::JUCEApplicationBase::quit();
}
