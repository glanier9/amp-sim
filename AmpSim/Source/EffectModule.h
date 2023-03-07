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
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class EffectModule  : public juce::Component
//                      public juce::Slider::Listener
{
public:
    EffectModule();
//    EffectModule(AmpSimAudioProcessor&);
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
    FxKnob1 knob4;
//    juce::TextButton advancedMenu { "Advanced Menu" };
//    std::unique_ptr<FxKnob1> menuKnob1;
    
//    FxKnob1 menuKnob1;
//    std::unique_ptr<FxKnob1> menuKnobPtr(new FxKnob1(std::move(menuKnob1)));
    
//    std::shared_ptr<FxKnob1> menuKnob1 = std::make_shared<FxKnob1>();
//    FxKnob1 menuKnob;
//    std::unique_ptr<FxKnob1> menuKnob1;
//    juce::Slider::Listener menuKnobListener;
//    std::unique_ptr<FxKnob1> menuKnob1 = std::make_unique<FxKnob1>();
//    juce::CallOutBox& myBox;
//    juce::AudioProcessorValueTreeState apvts;
//    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> menuKnobAtt;

    
//    void sliderValueChanged (juce::Slider* slider) override
//    {
//    }


private:
    /* Referenced audio processor */
//    AmpSimAudioProcessor& audioProcessor;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EffectModule)
};
