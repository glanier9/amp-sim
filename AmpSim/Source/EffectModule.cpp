/*
  ==============================================================================

    EffectModule.cpp
    Created: 8 Nov 2022 12:06:21pm
    Author:  School

  ==============================================================================
*/

#include <JuceHeader.h>
#include "EffectModule.h"
#include "PluginEditor.h"

//==============================================================================
//EffectModule::EffectModule(AmpSimAudioProcessor& p) : audioProcessor (p)
EffectModule::EffectModule()

{
    addAndMakeVisible(knob1);
    addAndMakeVisible(knob2);
    addAndMakeVisible(knob3);
    addAndMakeVisible(knob4);
    
//    addAndMakeVisible(advancedMenu);
//    advancedMenu.onClick = [&]
//    {
//        auto menuKnob1 = std::make_unique<FxKnob1>();
//        menuKnob1->setSize (knob1.getWidth(), knob1.getHeight());
//        auto& myBox = juce::CallOutBox::launchAsynchronously (std::move(menuKnob1),
//                                                           getScreenBounds(),
//                                                           nullptr);
        
//        auto menuKnob1 = std::make_unique<FxKnob1>();
        
        /* Most likely scenario */
//        menuKnob1.release();
//        menuKnob1 = std::make_unique<FxKnob1>();
//        menuKnob1->setSize (knob1.getWidth(), knob1.getHeight());
//        auto& myBox = juce::CallOutBox::launchAsynchronously (std::move(menuKnob1),
//                                                                       getScreenBounds(),
//                                                                       nullptr);
        
//        menuKnob1.release();
//        menuKnob1 = std::make_unique<FxKnob1>();
//        menuKnob1->setSize (knob1.getWidth(), knob1.getHeight());
//        auto& myBox = juce::CallOutBox::launchAsynchronously (std::move(menuKnob1),
//                                                                       getScreenBounds(),
//                                                                       nullptr);
        
        
        
//        auto menuKnob1 = std::make_unique<FxKnob1>();
//        menuKnob1->addListener(this);
//        menuKnob1->setSize (knob1.getWidth(), knob1.getHeight());
//        menuKnobAtt = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>
//                (apvts,"PHASERFC", menuKnob1);
//                (mengetParentComponent()->audioProcessor.apvts, "PHASERFC", menuKnob1);
//        menuKnob1->onValueChange = [this]
//        {
//            menuKnob.setValue(, juce::dontSendNotification);
//        };
//        std::shared_ptr<juce::Label> menuKnobLabel = std::make_shared<juce::Label>();
//        menuKnobLabel->setText("BPM", juce::dontSendNotification);
//        menuKnobLabel->attachToComponent(menuKnob1.get(), true);
//        auto& myBox = juce::CallOutBox::launchAsynchronously (std::move(menuKnob1),
//                                                           getScreenBounds(),
//                                                           nullptr);
//    };
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
    textBox.setCentre(localBounds.getX() + g.getCurrentFont().getStringWidth(labels[0].label)*0.75f,
                      localBounds.getY() + g.getCurrentFont().getHeight() - 5);
    g.drawFittedText(labels[0].label, textBox.toNearestInt(),
                     juce::Justification::centred, 1);
    
    /* Knob Labels */
    auto knobLabelOffset = 10;
    g.setColour (juce::Colours::white);
    g.setFont(getFontSettings());
    textBox.setSize(g.getCurrentFont().getStringWidth(labels[1].label),
                    g.getCurrentFont().getHeight());
    textBox.setCentre(localBounds.getX() + localBounds.getWidth()/2.f,
//                      localBounds.getY() + localBounds.getHeight()*0.2 + 5);
                      knob1.getBottom() - knobLabelOffset);
    g.drawFittedText(labels[1].label, textBox.toNearestInt(),
                     juce::Justification::centred, 1);
    textBox.setSize(g.getCurrentFont().getStringWidth(labels[2].label),
                    g.getCurrentFont().getHeight());
    textBox.setCentre(localBounds.getX() + localBounds.getWidth()/2.f,
                      knob2.getBottom() - knobLabelOffset);
    g.drawFittedText(labels[2].label, textBox.toNearestInt(),
                     juce::Justification::centred, 1);
    textBox.setSize(g.getCurrentFont().getStringWidth(labels[3].label),
                    g.getCurrentFont().getHeight());
    textBox.setCentre(localBounds.getX() + localBounds.getWidth()/2.f,
                      knob3.getBottom() - knobLabelOffset);
    g.drawFittedText(labels[3].label, textBox.toNearestInt(),
                     juce::Justification::centred, 1);
    textBox.setSize(g.getCurrentFont().getStringWidth(labels[4].label),
                    g.getCurrentFont().getHeight());
    textBox.setCentre(localBounds.getX() + localBounds.getWidth()/2.f,
                      knob4.getBottom() - knobLabelOffset);
    g.drawFittedText(labels[4].label, textBox.toNearestInt(),
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
