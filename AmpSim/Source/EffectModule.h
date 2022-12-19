/*
  ==============================================================================

    EffectModule.h
    Created: 8 Nov 2022 12:06:21pm
    Author:  Greg Lanier

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "FxKnob1.h"
#include "PopupKnob.h"

//==============================================================================
/*
*/
class EffectModule  : public juce::Component
{
public:
    EffectModule();
    ~EffectModule() override;

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
    FxKnob1 knob1;
    FxKnob1 knob2;
    FxKnob1 knob3;
//    FxKnob1 knob4;
    juce::TextButton advancedMenu { "Advanced Menu" };

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EffectModule)
};
