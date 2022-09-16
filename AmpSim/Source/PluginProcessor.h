/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

/* Plugin settings for connecting to UI */
struct ChainSettings
{
    bool gateToggle{ true };
    float gateThreshold{ 0.0 }, gateAttack{ 0.0 }, gateRelease{ 0.0 };
    float preGain{ 0.5 };
    float bassFreq{ 0 }, midGain{ 0 }, trebleFreq{ 0 };
    float waveshaper{ 1 };
    float reverbToggle {1};
    float verbMix {0}, verbRoom {0}, verbDamping {0}, verbWidth {0};
    float masterVol{ 0.5 };
    float convolution{ 1 };
};
ChainSettings getChainSettings(juce::AudioProcessorValueTreeState& apvts);

/* Chain stage types */
using NoiseGate = juce::dsp::NoiseGate<float>;
using Gain = juce::dsp::Gain<float>;
using WaveShaper = juce::dsp::WaveShaper<float>;\
using Filter = juce::dsp::IIR::Filter<float>;
using FilterCoefs = juce::dsp::IIR::Coefficients<float>;
using Reverb = juce::dsp::Reverb;
using ReverbParams = juce::Reverb::Parameters;
using Convolution = juce::dsp::Convolution;

/* Pregain chain setup */
using InputChain = juce::dsp::ProcessorChain
<
    NoiseGate,  // Noise gate
    Gain        // Pregain
>;
enum InputChainPositions
{
    Gate,
    PreGain
};

/* Tone stack setup */
using ToneStack = juce::dsp::ProcessorChain
<
    Filter,
    Filter,
    Filter
>;
enum ToneStackPositions
{
    Bass,
    Mid,
    Treble,
    Slope
};

/* Amp chain setup */
using AmpChain = juce::dsp::ProcessorChain
<
    WaveShaper
>;
enum AmpChainPositions
{
    WaveShaping
};
enum AmpNames
{
    Clean = 1,
    Asinine,
    Reptile,
    Geeky,
    SmolCronch,
    FatMan,
    Circle7,
    ForkInToaster,
    AmpCount    // Used to calculate number of amps
};

/* Effects loop setup */
using EffectsChain = juce::dsp::ProcessorChain
<
    Reverb
>;
enum EffectsChainPositions
{
    OutReverb
};

/* Post effects chain setup */
using OutputChain = juce::dsp::ProcessorChain
<
    Gain,
    Convolution
>;
enum OutputChainPositions
{
    MasterVol,
    Cabinet
};

//==============================================================================
/**
*/
class AmpSimAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    AmpSimAudioProcessor();
    ~AmpSimAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    /* Value Tree */
    juce::AudioProcessorValueTreeState apvts;
    
private:

    /* Stereo channels for each chain */
    InputChain leftInput, rightInput;
    ToneStack leftTone, rightTone;
    AmpChain leftAmp, rightAmp;
    EffectsChain leftEffects, rightEffects;
    OutputChain leftOutput, rightOutput;
    
    /* Noise gate properties*/
    const float gateRatio = 100;
    
    /* Tone stack properties */
    const float bassQ = 0.2f, trebleQ = 0.2f, peakQ = 1.f;
    const float peakFc = 600.f;

    /* Directory paths */
    using File = juce::File;
    File rootDir;
    File assetsDir; // not currently used, needs to be defined in setStateInformation() then used
    int numTries;

    /* UI settings helpers */
    void updateSettings();
    void updateNoiseGate(float thresh, float att, float rel, bool bypass);
    void updatePreGain(float gainDb, float amp);
    void updateToneStack(const ChainSettings& chainSettings);
    void updateBassTone(float freq);
    void updateMidTone(float gainDb);
    void updateTrebleTone(float freq);
    void updateWaveshaper(float shapeSelect);
    void updateReverb(float mix, float room, float damping, float width, bool bypass);
    void updateMasterVol(float gainDb);
    void updateConvolution(float cabinetSelect);

    /* Value Tree initializer */
    juce::AudioProcessorValueTreeState::ParameterLayout createParamLayout();

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AmpSimAudioProcessor)
};
