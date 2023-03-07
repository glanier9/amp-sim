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
#include "KnobWithToggle.h"
#include "EffectModule.h"

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
    const int pluginW = 1000;
    const int pluginH = 600;
    juce::Point<float> getInitialWindowSize () const { return juce::Point<float>(pluginW, pluginH); }

    /* Section Labels */
    juce::Label fxLabel1;
    juce::Label fxLabel2;
    
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
    
    /* Gain slider */
    AmpKnobRotarySlider preGainSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> preGainAtt;

    /* Filter sliders */
    AmpKnobRotarySlider bassSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> bassAtt;
    AmpKnobRotarySlider midSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> midAtt;
    AmpKnobRotarySlider trebleSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> trebleAtt;

    /* Noise gate assets */
    KnobWithToggle noiseGate;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> noiseGateToggleAtt;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> noiseGateThresholdAtt;

    /* Waveshaper combo box */
    SelectionBox waveShaperCombo;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> waveShaperAtt;
    
    /* Master volume slider */
    AmpKnobRotarySlider masterVolSlider;
    juce::Font masterVolFont;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> masterVolAtt;
    void waveshaperChanged();
    
    /* Reverb */
    KnobWithToggle reverb;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> reverbToggleAtt;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> reverbLevelAtt;
    
    /* Effect 1 */
    EffectModule effect1;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> chorusMixAtt;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> chorusRateAtt;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> chorusDepthAtt;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> chorusDelayAtt;
    
    /* Effect 2 */
    EffectModule effect2;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> phaserMixAtt;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> phaserRateAtt;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> phaserDepthAtt;
//    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> phaserFcAtt;

    /* Convolution combo box */
    SelectionBox convolutionCombo;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> convolutionAtt;
    void convolutionChanged();
    
    /* Image */
    juce::ImageComponent ampImage;
    int imageCheck;
    
    /* Referenced audio processor */
    AmpSimAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AmpSimAudioProcessorEditor)
};
