/*
  ==============================================================================

    KnobWithToggle.cpp
    Created: 22 Oct 2022 3:35:57pm
    Author:  School

  ==============================================================================
*/

#include <JuceHeader.h>
#include "KnobWithToggle.h"

//==============================================================================
KnobWithToggle::KnobWithToggle()
{
    /* Make child components visible */
    addAndMakeVisible(knob);
    addAndMakeVisible(button);
}

KnobWithToggle::~KnobWithToggle()
{
}

void KnobWithToggle::paint (juce::Graphics& g)
{
    auto localBounds = getLocalBounds();
    juce::Rectangle<float> textBox;
    
    /* Background Fill */
//    g.fillAll (getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId)); // clear the background
    
    /* Area border */
    g.setColour (juce::Colours::black);
    g.drawRect (localBounds, 1);   // draw an outline around the component
    
    /* Section label */
    g.setColour (juce::Colours::white);
    g.setFont(getFontSettings());
    textBox.setSize(g.getCurrentFont().getStringWidth(labels[0].label),
                    g.getCurrentFont().getHeight());
    textBox.setCentre(localBounds.getX() + localBounds.getWidth()/2.f,
                      localBounds.getY() + g.getCurrentFont().getHeight());
    g.drawFittedText(labels[0].label, textBox.toNearestInt(),
                     juce::Justification::centred, 1);
}

void KnobWithToggle::resized()
{
    auto localBounds = getLocalBounds();
    
    /* Knob */
    knob.setBounds(localBounds.removeFromRight(localBounds.getWidth()/2.f));
    
    /* Toggle Button */
    button.setBounds(localBounds);
}
