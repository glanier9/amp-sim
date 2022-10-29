/*
  ==============================================================================

    KnobWithToggle.h
    Created: 22 Oct 2022 3:35:57pm
    Author:  School

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "FxKnob1.h"
#include "Switch.h"

//==============================================================================
/*
*/
class KnobWithToggle  : public juce::Component
{
public:
    KnobWithToggle();
    ~KnobWithToggle() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    juce::Font getFontSettings() const {return juce::Font(16, juce::Font::italic);}
    
    /* Labels for use in component */
    struct LabelPosition
    {
        float pos;
        juce::String label;
    };
    juce::Array<LabelPosition> labels;
    
    /* Components */
    FxKnob1 knob;
    Switch button;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (KnobWithToggle)
};
