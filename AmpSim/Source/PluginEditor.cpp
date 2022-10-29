/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
AmpSimAudioProcessorEditor::AmpSimAudioProcessorEditor (AmpSimAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    /* Labels for components */
    preGainSlider.labels.add({0.f, "Gain"});
    bassSlider.labels.add({0.f, "Bass"});
    midSlider.labels.add({0.f, "Mid"});
    trebleSlider.labels.add({0.f, "Treble"});
    masterVolSlider.labels.add({0.f, "Volume"});
    waveShaperCombo.lnf.outsideLabels.add({0.f, "Amp Model"});
    convolutionCombo.lnf.outsideLabels.add({0.f, "Cabinet"});
    noiseGate.labels.add({0.f, "Noise Gate"});
    reverb.labels.add({0.f, "Reverb"});
    
    /* Amp section sliders */
    preGainAtt = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>
        (audioProcessor.apvts, "GAIN", preGainSlider);
    bassAtt = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>
        (audioProcessor.apvts, "BASS", bassSlider);
    midAtt = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>
        (audioProcessor.apvts, "MID", midSlider);
    trebleAtt = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>
        (audioProcessor.apvts, "TREBLE", trebleSlider);
    masterVolAtt = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>
        (audioProcessor.apvts, "MASTERVOL", masterVolSlider);
    
    /* Amp (waveshaper) combo box */
    addAndMakeVisible(waveShaperCombo);
    waveShaperCombo.addSectionHeading("Low Gain");
    waveShaperCombo.addItemList(LowGainAmps, 1);
    waveShaperCombo.addSeparator();
    waveShaperCombo.addSectionHeading("High Gain");
    waveShaperCombo.addItemList(HighGainAmps, sizeof(LowGainAmps) + 1);
    waveShaperCombo.onChange = [this] { waveshaperChanged(); };
    waveShaperAtt = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>
        (audioProcessor.apvts, "WAVESHAPER", waveShaperCombo);
    
    /* Cabinet (convolution) comobo box */
    addAndMakeVisible(convolutionCombo);
    convolutionCombo.addSectionHeading("Amp Cabinets");
    convolutionCombo.addItem("Cabinet", 1);
    convolutionCombo.addSectionHeading("Special");
    convolutionCombo.addItem("Cassette", 2);
    convolutionCombo.onChange = [this] { convolutionChanged(); };
    convolutionAtt = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>
        (audioProcessor.apvts, "CONVOLUTION", convolutionCombo);
    
    /* Noise Gate */
    noiseGateThresholdAtt = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>
        (audioProcessor.apvts, "GATETHRESH", noiseGate.knob);
    noiseGateToggleAtt = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>
        (audioProcessor.apvts, "GATE", noiseGate.button);
    
    /* Reverb */
//    reverbWidthAtt = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>
//        (audioProcessor.apvts, "VERBWIDTH", reverbWidth);
    reverbLevelAtt = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>
        (audioProcessor.apvts, "VERBMIX", reverb.knob);
//    reverbDampingAtt = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>
//        (audioProcessor.apvts, "VERBDAMPING", reverbDamping);
//    reverbRoomAtt = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>
//        (audioProcessor.apvts, "VERBROOM", reverbRoomSize);
    // Toggle Button TODO
//    addAndMakeVisible(reverbButton);
//    addAndMakeVisible(reverbBypassedLabel);
//    reverbBypassedLabel.setFont(bypassedFont);
//    reverbBypassedLabel.setText("Bypassed:", juce::dontSendNotification);
//    reverbBypassedLabel.attachToComponent(&reverbButton, true);
    reverbToggleAtt = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>
        (audioProcessor.apvts, "REVERB", reverb.button);
    
    /* Effect 1 */
    fxLabel1.setFont(bypassedFont);
    fxLabel1.setText("Effect 1", juce::dontSendNotification);
    // TODO
    
    /* Effect 2 */
    fxLabel2.setFont(bypassedFont);
    fxLabel2.setText("Effect 2", juce::dontSendNotification);
    // TODO

    /* Generate all components */
    for( auto* comp : getComps() )
    {
        addAndMakeVisible(comp);
    }
    
    /* Set plugin window size */
    setSize (getInitialWindowSize().getX(), getInitialWindowSize().getY());
}

AmpSimAudioProcessorEditor::~AmpSimAudioProcessorEditor()
{
}

//==============================================================================
void AmpSimAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.setGradientFill(juce::ColourGradient(juce::Colours::yellow, 0, 0,
                                           juce::Colours::black, getInitialWindowSize().getX(),
                                           getInitialWindowSize().getY(),
                                           true));
    g.fillAll();
}

void AmpSimAudioProcessorEditor::resized()
{
    /* Area of whole window */
    auto windowBounds = getLocalBounds();
    
    /* Divide window into different sections */
    auto ampArea = windowBounds.removeFromBottom(windowBounds.getHeight()/3.f);
    auto fxArea1 = windowBounds.removeFromLeft(windowBounds.getWidth()/5.f);
    auto fxArea2 = windowBounds.removeFromRight(windowBounds.getWidth()/4.f);
    auto comboArea = windowBounds.removeFromBottom(windowBounds.getHeight()/7.f);
    auto singleKnobFxArea = windowBounds.removeFromBottom(windowBounds.getHeight()/3.f);
    
    /* Amp slider section */
    preGainSlider.setBounds(ampArea.removeFromLeft(ampArea.getWidth()/5.f));
    bassSlider.setBounds(ampArea.removeFromLeft(ampArea.getWidth()/4.f));
    midSlider.setBounds(ampArea.removeFromLeft(ampArea.getWidth()/3.f));
    trebleSlider.setBounds(ampArea.removeFromLeft(ampArea.getWidth()/2.f));
    masterVolSlider.setBounds(ampArea.removeFromLeft(ampArea.getWidth()));
    
    /* Combo box section */
    waveShaperCombo.setBounds(comboArea.removeFromLeft(comboArea.getWidth()/2.f));
    convolutionCombo.setBounds(comboArea.removeFromLeft(comboArea.getWidth()));
    
    /* Noise gate section */
//    noiseGateToggle.setBounds(singleKnobFxArea.removeFromLeft(singleKnobFxArea.getWidth()/10.f));
//    gateThresholdSlider.setBounds(singleKnobFxArea.removeFromLeft(singleKnobFxArea.getWidth()*(4.f/9.f)));
    noiseGate.setBounds(singleKnobFxArea.removeFromLeft(singleKnobFxArea.getWidth()/2.f));
    
    /* Reverb section */
//    reverbButton.setBounds(singleKnobFxArea.removeFromLeft(singleKnobFxArea.getWidth()/5));
    reverb.setBounds(singleKnobFxArea);
    
    /* Effect 1 section */
    fxLabel1.setBounds(fxArea1.removeFromTop(fxArea1.getHeight()/10.f));
    // TODO
    
    /* Effect 2 section */
    fxLabel2.setBounds(fxArea2.removeFromTop(fxArea2.getHeight()/10.f));
    // TODO
    
}

/* 
    FUNCTIONS NOT CURRENTLY USED

    This was for testing the combo boxes, showing how changing a selection
    can adjust visual things. Leaving in for future expansion
*/
void AmpSimAudioProcessorEditor::waveshaperChanged()
{
    switch (waveShaperCombo.getSelectedId())
    {
    case stylePlain:
        // Nothing for now
        //comboBox.setStyleFlags(juce::Font::plain);
        break;
    case styleBold:
        // Nothing for now
        //waveBoxFont.setStyleFlags(juce::Font::bold);
        break;
    case styleItalic:
        // Nothing for now
        //waveBoxFont.setStyleFlags(juce::Font::italic);
        break;
    default: 
        break;
    }

    //waveBoxLabel.setFont(waveBoxFont);
}
void AmpSimAudioProcessorEditor::convolutionChanged()
{
    switch (convolutionCombo.getSelectedId())
    {
    case stylePlain:
        //convoBoxFont.setStyleFlags(juce::Font::plain);
        break;
    case styleBold:
        //convoBoxFont.setStyleFlags(juce::Font::bold);
        break;
    case styleItalic:
        //convoBoxFont.setStyleFlags(juce::Font::italic);
        break;
    default:
        break;
    }

    //convoBoxLabel.setFont(convoBoxFont);
}

std::vector<juce::Component*> AmpSimAudioProcessorEditor::getComps()
{
    return
    {
        /* Amp Sliders */
        &preGainSlider,
        &bassSlider,
        &midSlider,
        &trebleSlider,
        &masterVolSlider,
        
        /* Combo Boxes */
        &waveShaperCombo,
        &convolutionCombo,
        
        /* FX sections with multiple components */
        &noiseGate,
        &reverb,
        
        /* Fx 1 */
        &fxLabel1,
        
        /* Fx 2 */
        &fxLabel2
    };
}
