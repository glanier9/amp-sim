/*
  ==============================================================================

    PopupKnob.h
    Created: 17 Nov 2022 11:03:16pm
    Author:  School

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

struct CustomComponent  : public juce::PopupMenu::CustomComponent
{
    CustomComponent (int widthIn, int heightIn, juce::Colour backgroundIn)
        : juce::PopupMenu::CustomComponent (false),
          idealWidth (widthIn),
          idealHeight (heightIn),
          background (backgroundIn)
    {}

    void getIdealSize (int& width, int& height) override
    {
        width = idealWidth;
        height = idealHeight;
    }

    void paint (juce::Graphics& g) override { g.fillAll (background); }

    int idealWidth = 0;
    int idealHeight = 0;
    juce::Colour background;
};
