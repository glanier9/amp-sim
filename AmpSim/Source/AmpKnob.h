//
//  AmpKnob.hpp
//  AmpSim - VST3
//
//  Created by Greg Lanier on 9/28/22.
//  Copyright © 2022 GAEamps. All rights reserved.
//

#pragma once

#include <JuceHeader.h>

/*
    Design for Amp Knobs
 */
struct AmpKnobLookAndFeel : juce::LookAndFeel_V4
{
    void drawRotarySlider (juce::Graphics&,
                           int x, int y, int width, int height,
                           float sliderPosProportional,
                           float rotaryStartAngle,
                           float rotaryEndAngle,
                           juce::Slider&) override;
};

/*
    Custom Knobs for Amp
 */
struct AmpKnobRotarySlider : juce::Slider
{
    AmpKnobRotarySlider() : juce::Slider(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag,
                                        juce::Slider::TextEntryBoxPosition::NoTextBox)
    {
        setLookAndFeel(&lnf);
    }
    
    ~AmpKnobRotarySlider()
    {
        setLookAndFeel(nullptr);
    }
    
    struct LabelPosition
    {
        float pos;
        juce::String label;
    };
    juce::Array<LabelPosition> labels;
    
    void paint(juce::Graphics& g) override;
    juce::Rectangle<int> getSliderBounds() const;
    juce::Font getFontSettings() const {return juce::Font(16, juce::Font::italic);}
    
private:
    AmpKnobLookAndFeel lnf;
};
