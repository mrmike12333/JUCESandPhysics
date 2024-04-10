#include "MainComponent.h"

/**
 * @brief The top level juce application
 * 
 */
class SandPhysicsApp final 
    : public juce::JUCEApplication
{
    public:
    explicit SandPhysicsApp() = default;

    const juce::String getApplicationName() override       { return JUCE_APPLICATION_NAME_STRING; }
    
    const juce::String getApplicationVersion() override    { return JUCE_APPLICATION_VERSION_STRING; }
    
    bool moreThanOneInstanceAllowed() override             { return true; }

    void initialise(const juce::String&) override
    {
        mainWindow.reset(new juce::DocumentWindow(
            "Window", 
            juce::Colours::black, 
            juce::DocumentWindow::TitleBarButtons::minimiseButton + 
            juce::DocumentWindow::TitleBarButtons::closeButton));
        
        mainWindow->setBounds(100, 100, 400, 500);
        mainWindow->setVisible(true);
        mainWindow->setContentOwned(new MainComponent(), true);
    }

    void shutdown() override
    {
        mainWindow = nullptr;
    }

    private:
    std::unique_ptr<juce::DocumentWindow> mainWindow;
};

START_JUCE_APPLICATION(SandPhysicsApp)