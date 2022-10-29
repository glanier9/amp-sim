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
const float heightOffset = 0.5f;

struct SelectionLookAndFeel : juce::LookAndFeel_V4
{
    /* Public Fucntions*/
    void drawComboBox(juce::Graphics& g,
                      int width, int height,
                      bool isButtonDown,
                      int buttonX, int buttonY, int buttonW, int buttonH,
                      juce::ComboBox& box) override;
    void positionComboBoxText (juce::ComboBox& box,
                               juce::Label& label) override;
    juce::Font getLabelFontSettings() const {return juce::Font(16, juce::Font::italic);}
    
    /* Public Variables*/
    struct LabelPosition
    {
        float pos;
        juce::String label;
    };
    juce::Array<LabelPosition> outsideLabels;
};

struct SelectionBox : juce::ComboBox
{
    /* Public Functions */
    SelectionBox() : juce::ComboBox()
    {
        setLookAndFeel(&lnf);
    }
    ~SelectionBox()
    {
        setLookAndFeel(nullptr);
    }
    
    /* Public Variables */
    SelectionLookAndFeel lnf;
    
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SelectionBox)
};
