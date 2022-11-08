/*
  ==============================================================================

    EffectModule.cpp
    Created: 8 Nov 2022 12:06:21pm
    Author:  School

  ==============================================================================
*/

#include <JuceHeader.h>
#include "EffectModule.h"

//==============================================================================
EffectModule::EffectModule()
{
    addAndMakeVisible(knob1);
    addAndMakeVisible(knob2);
    addAndMakeVisible(knob3);
    addAndMakeVisible(knob4);
}

EffectModule::~EffectModule()
{
}

void EffectModule::paint (juce::Graphics& g)
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

void EffectModule::resized()
{
    auto localBounds = getLocalBounds();
    
    /* Knobs */
    knob1.setBounds(localBounds.removeFromTop(localBounds.getHeight()/4.f));
    knob2.setBounds(localBounds.removeFromTop(localBounds.getHeight()/3.f));
    knob3.setBounds(localBounds.removeFromTop(localBounds.getHeight()/2.f));
    knob4.setBounds(localBounds.removeFromTop(localBounds.getHeight()/1.f));
    
}
