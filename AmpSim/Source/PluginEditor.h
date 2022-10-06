/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "AmpKnob.h"
#include "SelectionBox.h"

//==============================================================================
/**
*/
class AmpSimAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    AmpSimAudioProcessorEditor (AmpSimAudioProcessor&);
    ~AmpSimAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    
    /* Helper Functions */
    std::vector<juce::Component*> getComps();
    std::vector<juce::Component*> getKnobs();
    juce::Point<float> getInitialWindowSize () const { return juce::Point<float>(1000, 600); }

    /* Font assets */
    juce::Font ampSectionFont{ 12.0f };
    juce::Font ampSliderFont{ 16.0f };
    juce::Font comboBoxFont{ 16.0f };
    juce::Font noiseGateFont{ 16.0f };
    juce::Font reverbFont{ 16.0f };
    juce::Font bypassedFont{ 16.0f };
    enum FontStyles
    {
        stylePlain = 1,
        styleBold,
        styleItalic,
        numberOfStyles
    };

    /* Section labels */
    juce::Label ampSectionLabel{ {}, "Amplifier" };
    juce::Label gateSectionLabel;
    juce::Label reverbSectionLabel;

    /* Noise gate assets */
    juce::ToggleButton noiseGateToggle;
    juce::Label gateBypassedLabel;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> noiseGateToggleAtt;
    juce::Slider gateThresholdSlider;
    juce::Label gateThresholdLabel;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> gateThresholdAtt;
    juce::Slider gateRatioSlider;
    juce::Label gateRatioLabel;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> gateRatioAtt;
    juce::Slider gateAttackSlider;
    juce::Label gateAttackLabel;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> gateAttackAtt;
    juce::Slider gateReleaseSlider;
    juce::Label gateReleaseLabel;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> gateReleaseAtt;
    
    /* Gain slider */
    AmpKnobRotarySlider preGainSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> preGainAtt;
    juce::Label preGainLabel;

    /* Filter sliders */
    AmpKnobRotarySlider bassSlider;
    juce::Label bassLabel;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> bassAtt;
    AmpKnobRotarySlider midSlider;
    juce::Label midLabel;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> midAtt;
    AmpKnobRotarySlider trebleSlider;
    juce::Label trebleLabel;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> trebleAtt;

    /* Waveshaper combo box */
    SelectionBox waveShaperCombo;
    juce::Label waveBoxLabel;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> waveShaperAtt;
    
    /* Master volume slider */
    AmpKnobRotarySlider masterVolSlider;
    juce::Label masterVolLabel;
    juce::Font masterVolFont;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> masterVolAtt;
    void waveshaperChanged();
    
    /* Reverb */
    juce::ToggleButton reverbButton;
    juce::Label reverbBypassedLabel;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> reverbButtonAtt;
    juce::Slider reverbRoomSize;
    juce::Label reverbRoomLabel;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> reverbRoomAtt;
    juce::Slider reverbDamping;
    juce::Label reverbDampingLabel;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> reverbDampingAtt;
    juce::Slider reverbMix;
    juce::Label reverbMixLabel;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> reverbMixAtt;
    juce::Slider reverbWidth;
    juce::Label reverbWidthLabel;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> reverbWidthAtt;

    /* Convolution combo box */
    juce::Label convoBoxLabel;
    SelectionBox convolutionCombo;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> convolutionAtt;
    void convolutionChanged();

    /* Referenced audio processor */
    AmpSimAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AmpSimAudioProcessorEditor)
};
