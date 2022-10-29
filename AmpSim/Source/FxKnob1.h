/*
  ==============================================================================

    FxKnob1.h
    Created: 28 Oct 2022 8:50:57pm
    Author:  School

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

/*
    Design for Amp Knobs
 */
struct FxKnob1LookAndFeel : juce::LookAndFeel_V4
{
    void drawRotarySlider (juce::Graphics&,
                           int x, int y, int width, int height,
                           float sliderPosProportional,
                           float rotaryStartAngle,
                           float rotaryEndAngle,
                           juce::Slider&) override;
};

//==============================================================================
/*
*/
struct FxKnob1  : juce::Slider
{
public:
    FxKnob1() : juce::Slider(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag,
                             juce::Slider::TextEntryBoxPosition::NoTextBox)
    {
        setLookAndFeel(&lnf);
    }
    ~FxKnob1()
    {
        setLookAndFeel(nullptr);
    }

    void paint (juce::Graphics&) override;
    
    struct LabelPosition
    {
        float pos;
        juce::String label;
    };
    juce::Array<LabelPosition> labels;
    
    juce::Rectangle<int> getSliderBounds() const;
    juce::Font getFontSettings() const {return juce::Font(16, juce::Font::italic);}

private:
    FxKnob1LookAndFeel lnf;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FxKnob1)
};
