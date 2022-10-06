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
    convolutionCombo.outsideLabel.label = "Cabinet";
//    /*
//
//        Amp section Setup
//
//    */
//    addAndMakeVisible(ampSectionLabel);
//    ampSectionLabel.setFont(ampSectionFont);
//
//    /*
//
//        Noise gate setup
//
//    */
//    addAndMakeVisible(gateSectionLabel);
//    gateSectionLabel.setFont(noiseGateFont);
//    gateSectionLabel.setText("Noise Gate", juce::dontSendNotification);
//
//    /* Noise gate toggle */
//    addAndMakeVisible(noiseGateToggle);
//    addAndMakeVisible(gateBypassedLabel);
//    gateBypassedLabel.setFont(bypassedFont);
//    gateBypassedLabel.setText("Bypassed:", juce::dontSendNotification);
//    gateBypassedLabel.attachToComponent(&noiseGateToggle, true);
//    noiseGateToggleAtt = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>
//        (audioProcessor.apvts, "GATE", noiseGateToggle);
//
//    /* Noise gate attack */
//    addAndMakeVisible(gateAttackSlider);
//    gateAttackSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
//    gateAttackSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 100, 50);
//    addAndMakeVisible(gateAttackLabel);
//    gateAttackLabel.setFont(noiseGateFont);
//    gateAttackLabel.setText("Attack", juce::dontSendNotification);
//    gateAttackLabel.attachToComponent(&gateAttackSlider, true);
//    gateAttackAtt = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>
//        (audioProcessor.apvts, "GATEATT", gateAttackSlider);
//
//    /* Noise gate release */
//    addAndMakeVisible(gateReleaseSlider);
//    gateReleaseSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
//    gateReleaseSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 100, 50);
//    addAndMakeVisible(gateReleaseLabel);
//    gateReleaseLabel.setFont(noiseGateFont);
//    gateReleaseLabel.setText("Release", juce::dontSendNotification);
//    gateReleaseLabel.attachToComponent(&gateReleaseSlider, true);
//    gateReleaseAtt = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>
//        (audioProcessor.apvts, "GATEREL", gateReleaseSlider);
//
//    /* Noise gate threshold */
//    addAndMakeVisible(gateThresholdSlider);
//    gateThresholdSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
//    gateThresholdSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 100, 50);
//    addAndMakeVisible(gateThresholdLabel);
//    gateThresholdLabel.setFont(noiseGateFont);
//    gateThresholdLabel.setText("Threshold", juce::dontSendNotification);
//    gateThresholdLabel.attachToComponent(&gateThresholdSlider, true);
//    gateThresholdAtt = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>
//        (audioProcessor.apvts, "GATETHRESH", gateThresholdSlider);
//
//    /*
//
//        Gain slider setup
//
//    */
//    addAndMakeVisible(preGainSlider);
//    preGainSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
//    preGainSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 100, 50);
//    addAndMakeVisible(preGainLabel);
//    preGainLabel.setFont(ampSliderFont);
//    preGainLabel.setText("Gain", juce::dontSendNotification);
//    preGainLabel.attachToComponent(&preGainSlider, false);
    preGainAtt = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>
        (audioProcessor.apvts, "GAIN", preGainSlider);
//
//    /*
//
//        Filter sliders
//
//    */
//
//    /* Bass slider */
//    addAndMakeVisible(bassSlider);
//    bassSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
//    bassSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 100, 50);
//    addAndMakeVisible(bassLabel);
//    bassLabel.setFont(ampSliderFont);
//    bassLabel.setText("Bass", juce::dontSendNotification);
//    bassLabel.attachToComponent(&bassSlider, false);
    bassAtt = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>
        (audioProcessor.apvts, "BASS", bassSlider);
//
//    /* Mid slider */
//    addAndMakeVisible(midSlider);
//    midSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
//    midSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 100, 50);
//    addAndMakeVisible(midLabel);
//    midLabel.setFont(ampSliderFont);
//    midLabel.setText("Mid", juce::dontSendNotification);
//    midLabel.attachToComponent(&midSlider, false);
    midAtt = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>
        (audioProcessor.apvts, "MID", midSlider);
//
//    /* Treble slider */
//    addAndMakeVisible(trebleSlider);
//    trebleSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
//    trebleSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 100, 50);
//    addAndMakeVisible(trebleLabel);
//    trebleLabel.setFont(ampSliderFont);
//    trebleLabel.setText("Treble", juce::dontSendNotification);
//    trebleLabel.attachToComponent(&trebleSlider, false);
    trebleAtt = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>
        (audioProcessor.apvts, "TREBLE", trebleSlider);
//
//    /*
//
//        Master volume slider setup
//
//    */
//    addAndMakeVisible(masterVolSlider);
//    masterVolSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
//    masterVolSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 100, 50);
//    addAndMakeVisible(masterVolLabel);
//    masterVolLabel.setFont(ampSliderFont);
//    masterVolLabel.setText("Volume", juce::dontSendNotification);
//    masterVolLabel.attachToComponent(&masterVolSlider, false);
    masterVolAtt = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>
        (audioProcessor.apvts, "MASTERVOL", masterVolSlider);
//
//    /*
//
//        Waveshaper comobo box
//
//    */
    addAndMakeVisible(waveShaperCombo);
    waveShaperCombo.addItem("Squeaky Clean", Clean);
    waveShaperCombo.addSectionHeading("Low Gain");
    waveShaperCombo.addItem("Asinine", Asinine);
    waveShaperCombo.addItem("Reptile", Reptile);
    waveShaperCombo.addItem("Geeky", Geeky);
    waveShaperCombo.addItem("Smol Cronch", SmolCronch);
    waveShaperCombo.addSectionHeading("High Gain");
    waveShaperCombo.addItem("Fat Man", FatMan);
    waveShaperCombo.addItem("Circle 7", Circle7);
    waveShaperCombo.addItem("Fork in Toaster", ForkInToaster);
    waveShaperCombo.onChange = [this] { waveshaperChanged(); };
    addAndMakeVisible(waveBoxLabel);    // Waveshaper label
//    waveBoxLabel.setFont(comboBoxFont);
//    waveBoxLabel.setText("Amp:", juce::dontSendNotification);
//    waveBoxLabel.attachToComponent(&waveShaperCombo, true);
    waveShaperAtt = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>
        (audioProcessor.apvts, "WAVESHAPER", waveShaperCombo);
//
//    /*
//
//        Reverb setup
//
//    */
//    addAndMakeVisible(reverbSectionLabel);
//    reverbSectionLabel.setFont(reverbFont);
//    reverbSectionLabel.setText("Reverb", juce::dontSendNotification);
//
//    /* Reverb toggle */
//    addAndMakeVisible(reverbButton);
//    addAndMakeVisible(reverbBypassedLabel);
//    reverbBypassedLabel.setFont(bypassedFont);
//    reverbBypassedLabel.setText("Bypassed:", juce::dontSendNotification);
//    reverbBypassedLabel.attachToComponent(&reverbButton, true);
//    reverbButtonAtt = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>
//        (audioProcessor.apvts, "REVERB", reverbButton);
//
//    /* Reverb room size*/
//    addAndMakeVisible(reverbRoomSize);
//    reverbRoomSize.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
//    reverbRoomSize.setTextBoxStyle(juce::Slider::NoTextBox, true, 100, 50);
//    addAndMakeVisible(reverbRoomLabel);
//    reverbRoomLabel.setFont(reverbFont);
//    reverbRoomLabel.setText("Room", juce::dontSendNotification);
//    reverbRoomLabel.attachToComponent(&reverbRoomSize, true);
//    reverbRoomAtt = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>
//        (audioProcessor.apvts, "VERBROOM", reverbRoomSize);
//
//    /* Reverb damping */
//    addAndMakeVisible(reverbDamping);
//    reverbDamping.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
//    reverbDamping.setTextBoxStyle(juce::Slider::NoTextBox, true, 100, 50);
//    addAndMakeVisible(reverbDampingLabel);
//    reverbDampingLabel.setFont(reverbFont);
//    reverbDampingLabel.setText("Damping", juce::dontSendNotification);
//    reverbDampingLabel.attachToComponent(&reverbDamping, true);
//    reverbDampingAtt = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>
//        (audioProcessor.apvts, "VERBDAMPING", reverbDamping);
//
//    /* Reverb mix knob */
//    addAndMakeVisible(reverbMix);
//    reverbMix.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
//    reverbMix.setTextBoxStyle(juce::Slider::NoTextBox, true, 100, 50);
//    addAndMakeVisible(reverbMixLabel);
//    reverbMixLabel.setFont(reverbFont);
//    reverbMixLabel.setText("Mix", juce::dontSendNotification);
//    reverbMixLabel.attachToComponent(&reverbMix, true);
//    reverbMixAtt = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>
//        (audioProcessor.apvts, "VERBMIX", reverbMix);
//
//    /* Reverb width */
//    addAndMakeVisible(reverbWidth);
//    reverbWidth.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
//    reverbWidth.setTextBoxStyle(juce::Slider::NoTextBox, true, 100, 50);
//    addAndMakeVisible(reverbWidthLabel);
//    reverbWidthLabel.setFont(reverbFont);
//    reverbWidthLabel.setText("Width", juce::dontSendNotification);
//    reverbWidthLabel.attachToComponent(&reverbWidth, true);
//    reverbWidthAtt = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>
//        (audioProcessor.apvts, "VERBWIDTH", reverbWidth);
//
//    /*
//
//        Convolution comobo box
//
//    */
    addAndMakeVisible(convolutionCombo);
    convolutionCombo.addSectionHeading("Amp Cabinets");
    convolutionCombo.addItem("Cabinet", 1);
    convolutionCombo.addSectionHeading("Special");
    convolutionCombo.addItem("Cassette", 2);
    convolutionCombo.onChange = [this] { convolutionChanged(); };
    addAndMakeVisible(convoBoxLabel);    // Convolution label
//    convoBoxLabel.setFont(comboBoxFont);
//    convoBoxLabel.setText("Cabinet:", juce::dontSendNotification);
//    convoBoxLabel.attachToComponent(&convolutionCombo, true);
    convolutionAtt = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>
        (audioProcessor.apvts, "CONVOLUTION", convolutionCombo);

    /*
        Generate Knobs
     */
    for( auto* comp : getComps() )
    {
        addAndMakeVisible(comp);
    }
    
    /*
        Set plugin size
    */
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
    /* Define window sections */
//    auto windowBounds = getLocalBounds();   // Full window area
//    auto ampSection = windowBounds.removeFromBottom(windowBounds.getHeight()*0.33); // Amp takes up 1/3
//    auto effectsSection = windowBounds.removeFromTop(windowBounds.getHeight()); // Effects take up 2/3
//
//    /* Narrow down effects section */
//    auto effectsTopSpacer = effectsSection.removeFromTop(5);
//    auto effectsBottomSpacer = effectsSection.removeFromBottom(40);
//    auto effectsLeftSpacer = effectsSection.removeFromLeft(effectsSection.getWidth()*0.1);
//    auto effectsRightSpacer = effectsSection.removeFromRight(effectsSection.getWidth()*0.1);
//    auto effectsLabels = effectsSection.removeFromTop(effectsSection.getHeight() * 0.1);
//    auto effectsToggles = effectsSection.removeFromBottom(effectsSection.getHeight() * 0.1);
//
//    /* Narrow down each effects areas */
//    auto gateSection = effectsSection.removeFromLeft( effectsSection.getWidth() * 0.2 );
//    auto reverbSection = effectsSection.removeFromRight( effectsSection.getWidth() * 0.3333 );
//
//    /* Narrow down amp section */
//    auto ampSliderSection = ampSection.removeFromTop(ampSection.getHeight() * 0.66);
//    auto leftAmpSliderSpacer = ampSliderSection.removeFromLeft(50);
//    auto rightAmpSliderSpacer = ampSliderSection.removeFromRight(50);
//    auto bottomAmpSliderSpacer = ampSliderSection.removeFromBottom(5);
//    auto leftAmpComboSpacer = ampSection.removeFromLeft( getWidth() * 0.25 );
//    auto rightAmpComboSpacer = ampSection.removeFromRight( getWidth() * 0.25 );
//    auto bottomAmpComboSpacer = ampSection.removeFromBottom(35);
//    auto gainSecSpacer = windowBounds.removeFromLeft( windowBounds.getWidth()*0.1 );
//
//    /* Amp section positioning */
//    preGainSlider.setBounds(ampSliderSection.removeFromLeft( ampSliderSection.getWidth() * 0.2 ));
//    bassSlider.setBounds(ampSliderSection.removeFromLeft(ampSliderSection.getWidth() * 0.25));
//    midSlider.setBounds(ampSliderSection.removeFromLeft(ampSliderSection.getWidth() * 0.33));
//    trebleSlider.setBounds(ampSliderSection.removeFromLeft(ampSliderSection.getWidth() * 0.5));
//    masterVolSlider.setBounds(ampSliderSection);
//    waveShaperCombo.setBounds(ampSection.removeFromLeft(ampSection.getWidth() * 0.33));
//    auto comboBoxSpacer = ampSection.removeFromLeft(ampSection.getWidth() * 0.5);
//    convolutionCombo.setBounds(ampSection);
//
//    /* Noise gate section */
//    gateSectionLabel.setBounds(effectsLabels.removeFromLeft(effectsLabels.getWidth() * 0.2f));
//    noiseGateToggle.setBounds(effectsToggles.removeFromLeft(effectsToggles.getWidth() * 0.2f));
//    gateThresholdSlider.setBounds(gateSection.removeFromBottom(gateSection.getHeight() * 0.33f));
//    gateAttackSlider.setBounds(gateSection.removeFromBottom(gateSection.getHeight() * 0.5f));
//    gateReleaseSlider.setBounds(gateSection);
//
//    /* Reverb section */
//    reverbSectionLabel.setBounds(effectsLabels.removeFromRight(effectsLabels.getWidth() * 0.2f));
//    reverbButton.setBounds(effectsToggles.removeFromRight(effectsToggles.getWidth() * 0.2f));
//    reverbMix.setBounds(reverbSection.removeFromBottom(reverbSection.getHeight() * 0.25f));
//    reverbRoomSize.setBounds(reverbSection.removeFromBottom(reverbSection.getHeight() * 0.33f));
//    reverbDamping.setBounds(reverbSection.removeFromBottom(reverbSection.getHeight() * 0.5f));
//    reverbWidth.setBounds(reverbSection);
    
    /* Area of whole window */
    auto windowBounds = getLocalBounds();
    
    /* Divide area into different sections */
    auto ampArea = windowBounds.removeFromBottom(windowBounds.getHeight()/3.f);
    auto effectArea1 = windowBounds.removeFromLeft(windowBounds.getWidth()/5.f);
    auto effectArea2 = windowBounds.removeFromRight(windowBounds.getWidth()/4.f);
    auto comboArea = windowBounds.removeFromBottom(windowBounds.getHeight()/7.f);
    
    /* Amp slider section */
    preGainSlider.setBounds(ampArea.removeFromLeft(ampArea.getWidth()/5.f));
    bassSlider.setBounds(ampArea.removeFromLeft(ampArea.getWidth()/4.f));
    midSlider.setBounds(ampArea.removeFromLeft(ampArea.getWidth()/3.f));
    trebleSlider.setBounds(ampArea.removeFromLeft(ampArea.getWidth()/2.f));
    masterVolSlider.setBounds(ampArea.removeFromLeft(ampArea.getWidth()));
    
    /* Combo box section */
    waveShaperCombo.setBounds(comboArea.removeFromLeft(comboArea.getWidth()/2.f));
    convolutionCombo.setBounds(comboArea.removeFromLeft(comboArea.getWidth()));
    
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
        &convolutionCombo
    };
}
