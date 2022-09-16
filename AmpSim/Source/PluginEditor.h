/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

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
    juce::Slider preGainSlider;
    juce::Label preGainLabel;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> preGainAtt;

    /* Filter sliders */
    juce::Slider bassSlider;
    juce::Label bassLabel;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> bassAtt;
    juce::Slider midSlider;
    juce::Label midLabel;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> midAtt;
    juce::Slider trebleSlider;
    juce::Label trebleLabel;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> trebleAtt;

    /* Waveshaper combo box */
    juce::ComboBox waveShaperCombo;
    juce::Label waveBoxLabel;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> waveShaperAtt;
    
    /* Master volume slider */
    juce::Slider masterVolSlider;
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
    juce::ComboBox convolutionCombo;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> convolutionAtt;
    void convolutionChanged();

    /* Referenced audio processor */
    AmpSimAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AmpSimAudioProcessorEditor)
};
