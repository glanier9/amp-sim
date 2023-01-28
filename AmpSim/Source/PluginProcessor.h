/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

/* Processor type definitions */
using NoiseGate = juce::dsp::NoiseGate<float>;
using Gain = juce::dsp::Gain<float>;
using WaveShaper = juce::dsp::WaveShaper<float>;
using Filter = juce::dsp::IIR::Filter<float>;
using FilterCoefs = juce::dsp::IIR::Coefficients<float>;
using Reverb = juce::dsp::Reverb;
using ReverbParams = juce::Reverb::Parameters;
using Convolution = juce::dsp::Convolution;
using Chorus = juce::dsp::Chorus<float>;
using Phaser = juce::dsp::Phaser<float>;

/*
 
    Processor Chain Definitions
 
 */
/* Plugin settings for connecting to UI */
struct ChainSettings
{
    bool gateToggle;
    float gateThreshold, gateAttack, gateRelease;
    float preGain;
    float bassFreq, midGain, trebleFreq;
    float waveshaper;
    float reverbToggle;
    float verbMix, verbRoom, verbDamping, verbWidth;
    float masterVol;
    float convolution;
    float chorusRate, chorusDepth, chorusDelay,
            chorusFeedback, chorusMix;
    float phaserRate, phaserDepth, phaserCentFreq,
            phaserFeedback, phaserMix;
};
ChainSettings getChainSettings(juce::AudioProcessorValueTreeState& apvts);

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
    Filter,     // High-pass filter (bass knob)
    Filter,     // Mid peak (mid knob)
    Filter      // Low-pass filter (treble knob)
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
    WaveShaper  // Waveshaping function (selected amp model)
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
const juce::StringArray LowGainAmps
{
    "Squeaky Clean",
    "Asinine",
    "Reptile",
    "Geeky",
    "SmolCronch"
};
const juce::StringArray HighGainAmps
{
    "Fat Man",
    "Circle 7",
    "Fork In Toaster"
};

/* Effects loop setup */
using EffectsChain = juce::dsp::ProcessorChain
<
    Chorus,
    Phaser,
    Reverb
>;
enum EffectsChainPositions
{
    OutChorus,
    OutPhaser,
    OutReverb
};

/* Post effects chain setup */
using OutputChain = juce::dsp::ProcessorChain
<
    Gain,       // Master volume knob
    Convolution // Cabinet selection
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
    void reset() override;

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
    
    /* Oversampling properties */
    juce::dsp::Oversampling<float> oversampler;
    
    /* Noise gate properties*/
    const float gateRatio = 100;
    
    /* Tone stack properties */
    const float bassQ = 0.2f, trebleQ = 0.2f, peakQ = 1.f;
    const float peakFc = 600.f;

    /* UI setting updaters */
    void updateSettings();
    void updateNoiseGate(float thresh, float att, float rel, bool bypass);
    void updatePreGain(float gainDb, float amp);
    void updateToneStack(const ChainSettings& chainSettings);
    void updateBassTone(float freq);
    void updateMidTone(float gainDb);
    void updateTrebleTone(float freq);
    void updateWaveshaper(float shapeSelect);
    void updateChorus(float rate, float depth, float delay, float feedback, float mix);
    void updatePhaser(float rate, float depth, float fc, float feedback, float mix);
    void updateReverb(float mix, float room, float damping, float width, bool bypass);
    void updateMasterVol(float gainDb);
    void updateConvolution(float cabinetSelect);

    /* Value Tree initializer */
    juce::AudioProcessorValueTreeState::ParameterLayout createParamLayout();

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AmpSimAudioProcessor)
};
