/*
  ==============================================================================

    Switch.h
    Created: 28 Oct 2022 9:15:32pm
    Author:  School

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

struct SwitchLookAndFeel : juce::LookAndFeel_V4
{
    juce::Font getTextButtonFont(juce::TextButton&, int buttonHeight) override;
    void drawButtonBackground (juce::Graphics& g,
                               juce::Button& button,
                               const juce::Colour& backgroundColour,
                               bool shouldDrawButtonAsHighlighted,
                               bool shouldDrawButtonAsDown) override;
    void drawToggleButton (juce::Graphics& g, juce::ToggleButton& button,
                           bool shouldDrawButtonAsHighlighted,
                           bool shouldDrawButtonAsDown) override;
    void drawTickBox (juce::Graphics& g, juce::Component& component,
                      float x, float y, float w, float h,
                      const bool ticked,
                      const bool isEnabled,
                      const bool shouldDrawButtonAsHighlighted,
                      const bool shouldDrawButtonAsDown) override;
    void changeToggleButtonWidthToFitText (juce::ToggleButton& button) override;
};

struct Switch : juce::ToggleButton
{
public:
    Switch() : juce::ToggleButton("Bypass")
    {
        setLookAndFeel(&lnf);
    }
    ~Switch()
    {
        setLookAndFeel(nullptr);
    }
    
private:
    SwitchLookAndFeel lnf;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Switch)
};
