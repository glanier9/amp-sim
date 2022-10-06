/*
  ==============================================================================

    SelectionBox.h
    Created: 28 Sep 2022 9:46:08pm
    Author:  Greg Lanier

  ==============================================================================
*/

#pragma once

#include<JuceHeader.h>

const float widthOffset = 0.8f;
const float heightOffset = 0.6f;

struct SelectionLookAndFeel : juce::LookAndFeel_V4
{
    void drawComboBox(juce::Graphics& g,
                      int width, int height,
                      bool isButtonDown,
                      int buttonX, int buttonY, int buttonW, int buttonH,
                      juce::ComboBox& box) override;
    
    void positionComboBoxText (juce::ComboBox& box,
                               juce::Label& label) override;
    
    juce::Font getLabelFontSettings() const {return juce::Font(16, juce::Font::italic);}
};

struct SelectionBox : juce::ComboBox
{
    SelectionBox() : juce::ComboBox()
    {
        setLookAndFeel(&lnf);
    }
    
    ~SelectionBox()
    {
        setLookAndFeel(nullptr);
    }
    
    struct LabelPosition
    {
        float pos;
        juce::String label;
    };
    LabelPosition outsideLabel;
    
private:
    SelectionLookAndFeel lnf;
};
