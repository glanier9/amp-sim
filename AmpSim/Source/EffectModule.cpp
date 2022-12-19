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
//    addAndMakeVisible(knob4);
    
    addAndMakeVisible(advancedMenu);
    advancedMenu.onClick = [&]
    {
        juce::PopupMenu menu;

        menu.addCustomItem (-1, std::make_unique<CustomComponent> (100,  20, juce::Colours::darkred));
        menu.addCustomItem (-1, std::make_unique<CustomComponent> (20,  100, juce::Colours::darkgreen));
        menu.addCustomItem (-1, std::make_unique<CustomComponent> (100, 100, juce::Colours::darkblue));
        menu.addCustomItem (-1, std::make_unique<CustomComponent> (100,  50, juce::Colours::darkcyan));
        menu.addCustomItem (-1, std::make_unique<CustomComponent> (50,  100, juce::Colours::darkmagenta));

        menu.showMenuAsync (juce::PopupMenu::Options{}.withTargetComponent (advancedMenu)
                                                .withMinimumNumColumns (5));
    };
}

EffectModule::~EffectModule()
{
}

void EffectModule::paint (juce::Graphics& g)
{
    auto localBounds = getLocalBounds();
    juce::Rectangle<float> textBox;
    
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
//    knob4.setBounds(localBounds.removeFromTop(localBounds.getHeight()/1.f));
    advancedMenu.setBounds(localBounds.removeFromTop(localBounds.getHeight()/1.f));
}
