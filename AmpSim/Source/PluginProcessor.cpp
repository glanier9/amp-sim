/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "BinaryData.h"

//==============================================================================
AmpSimAudioProcessor::AmpSimAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ),
    /* Initialize members */
    apvts(*this, nullptr, "Parameters", createParamLayout())
#endif
{
    /*
            Constructor Stuff
     */
    
    /* Set up file system  for cabinets */
    // These are currently the same, but I left in just to show how changes can be made
    // between platforms.
//    #if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
//        rootDir = juce::File::getSpecialLocation(juce::File::globalApplicationsDirectory);
//        numTries = 0;
//        while (!rootDir.getChildFile("AmpSim").exists() && numTries++ < 40)
//        {
//            rootDir = rootDir.getParentDirectory();
//        }
//    #elif __APPLE__
//        rootDir = juce::File::getSpecialLocation(juce::File::globalApplicationsDirectory);
//        numTries = 0;
//        while (!rootDir.getChildFile("AmpSim").exists() && numTries++ < 40)
//        {
//            rootDir = rootDir.getParentDirectory();
//        }
//    #endif
    
}

AmpSimAudioProcessor::~AmpSimAudioProcessor()
{
}

//==============================================================================
const juce::String AmpSimAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool AmpSimAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool AmpSimAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool AmpSimAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double AmpSimAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int AmpSimAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int AmpSimAudioProcessor::getCurrentProgram()
{
    return 0;
}

void AmpSimAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String AmpSimAudioProcessor::getProgramName (int index)
{
    return {};
}

void AmpSimAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void AmpSimAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    /* Prepare dsp chain */
    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = samplesPerBlock;
//    spec.numChannels = getTotalNumOutputChannels();
    spec.numChannels = 1;
    spec.sampleRate = sampleRate;

    /* Get DSP values from UI */
    updateSettings();

    /* Prepare DSP chains */
    leftInput.prepare(spec); rightInput.prepare(spec);
    leftTone.prepare(spec); rightTone.prepare(spec);
    leftAmp.prepare(spec); rightAmp.prepare(spec);
    leftEffects.prepare(spec); rightEffects.prepare(spec);
    leftOutput.prepare(spec); rightOutput.prepare(spec);
    
    /* Empty DSP chains */
    leftInput.reset(); rightInput.reset();
    leftTone.reset(); rightTone.reset();
    leftAmp.reset(); rightAmp.reset();
    leftEffects.reset(); rightEffects.reset();
    leftOutput.reset(); rightOutput.reset();
}

void AmpSimAudioProcessor::releaseResources()
{
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool AmpSimAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void AmpSimAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    /* Get basic processing info */
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    /* Clear old buffer */
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    
    /* Get slider/button/combo box settings to update dsp values */
    updateSettings();
    
    /* Process input chain */
    juce::dsp::AudioBlock<float> InputBlock(buffer);
    auto leftBlock = InputBlock.getSingleChannelBlock(0);
    auto rightBlock = InputBlock.getSingleChannelBlock(1);
    juce::dsp::ProcessContextReplacing<float> leftInputContext(leftBlock);
    juce::dsp::ProcessContextReplacing<float> rightInputContext(rightBlock);
    leftInput.process(leftInputContext); rightInput.process(rightInputContext);
    
    /* Process tone stack */
    juce::dsp::AudioBlock<float> toneBlock(buffer);
    leftBlock = toneBlock.getSingleChannelBlock(0);
    rightBlock = toneBlock.getSingleChannelBlock(1);
    juce::dsp::ProcessContextReplacing<float> leftToneContext(leftBlock);
    juce::dsp::ProcessContextReplacing<float> rightToneContext(rightBlock);
    leftTone.process(leftToneContext); rightTone.process(rightToneContext);

    /* Process amp chain */
    juce::dsp::AudioBlock<float> ampBlock(buffer);
    leftBlock = ampBlock.getSingleChannelBlock(0);
    rightBlock = ampBlock.getSingleChannelBlock(1);
    juce::dsp::ProcessContextReplacing<float> leftAmpContext(leftBlock);
    juce::dsp::ProcessContextReplacing<float> rightAmpContext(rightBlock);
    leftAmp.process(leftAmpContext); rightAmp.process(rightAmpContext);
    
    /* Process effects chain */
    juce::dsp::AudioBlock<float> effectsBlock(buffer);
    leftBlock = effectsBlock.getSingleChannelBlock(0);
    rightBlock = effectsBlock.getSingleChannelBlock(1);
    juce::dsp::ProcessContextReplacing<float> leftEffectsContext(leftBlock);
    juce::dsp::ProcessContextReplacing<float> rightEffectsContext(rightBlock);
    leftEffects.process(leftEffectsContext); rightEffects.process(rightEffectsContext);
    
    /* Process output chain */
    juce::dsp::AudioBlock<float> outputBlock(buffer);
    leftBlock = outputBlock.getSingleChannelBlock(0);
    rightBlock = outputBlock.getSingleChannelBlock(1);
    juce::dsp::ProcessContextReplacing<float> leftOutputContext(leftBlock);
    juce::dsp::ProcessContextReplacing<float> rightOutputContext(rightBlock);
    leftOutput.process(leftOutputContext); rightOutput.process(rightOutputContext);
}

//==============================================================================
bool AmpSimAudioProcessor::hasEditor() const
{
    return true;
}

juce::AudioProcessorEditor* AmpSimAudioProcessor::createEditor()
{
    return new AmpSimAudioProcessorEditor (*this);
}

//==============================================================================
void AmpSimAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    /* Loads plugin parameter state */
    juce::MemoryOutputStream mos(destData, true);
    apvts.state.writeToStream(mos);
}

void AmpSimAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    /* Restores plugin state from memory */
    auto tree = juce::ValueTree::readFromData(data, sizeInBytes);
    if (tree.isValid())
    {
        apvts.replaceState(tree);
        updateSettings();
    }
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new AmpSimAudioProcessor();
}

juce::AudioProcessorValueTreeState::ParameterLayout AmpSimAudioProcessor::createParamLayout()
{
    /* Generate param layout*/
    juce::AudioProcessorValueTreeState::ParameterLayout layout;

    /*
        Layout parameters
     */

    /* Noise Gate*/
    layout.add(std::make_unique<juce::AudioParameterBool>
        ("GATE", "Gate Bypass", 
            true));
    layout.add(std::make_unique<juce::AudioParameterFloat>
        ("GATETHRESH", "Gate Threshold", -60.f, -40.f, 
            -50.f));
    layout.add(std::make_unique<juce::AudioParameterFloat>
        ("GATEATT", "Gate Attack", 0.f, 50.f, 
            25.f));
    layout.add(std::make_unique<juce::AudioParameterFloat>
        ("GATEREL", "Gate Release", 0.f, 50.f, 
            25.f));

    /* Pregain */
//    layout.add(std::make_unique<juce::AudioParameterFloat>
//        ("GAIN", "Gain", 50.f, 80.f, 65.f));
    layout.add(std::make_unique<juce::AudioParameterFloat>
        ("GAIN", "Gain", 0.f, 100.f, 50.f));

    /* EQ filters */
    layout.add(std::make_unique<juce::AudioParameterFloat>
        ("BASS", "Bass",
            juce::NormalisableRange<float>(-318.f, -60.f, 1.f, 1.f), // Range
            -189.f)); // Default value
    layout.add(std::make_unique<juce::AudioParameterFloat>
        ("MID", "Mid",
            juce::NormalisableRange<float>(-24.f, 0.f, 0.1f, 1.f),
            -12.5f));
    layout.add(std::make_unique<juce::AudioParameterFloat>
        ("TREBLE", "Treble",
            juce::NormalisableRange<float>(800.f, 2500.f, 1.f, 1.f),
            1700.f));

    /* Waveshaper */
    layout.add(std::make_unique<juce::AudioParameterFloat>
        ("WAVESHAPER", "Waveshaper", 1.0f, (float)AmpCount - 1.f,
            1.0f));
    
    /* Chorus */
    layout.add(std::make_unique<juce::AudioParameterFloat>
       ("CHORUSRATE", "Chorus Rate", 1.f, 10.f, 5.f));
    layout.add(std::make_unique<juce::AudioParameterFloat>
       ("CHORUSDEPTH", "Chorus Depth", 0.f, 1.f, 0.5f));
    layout.add(std::make_unique<juce::AudioParameterFloat>
       ("CHORUSDELAY", "Chorus Delay", 1.f, 100.f, 50.f));
    layout.add(std::make_unique<juce::AudioParameterFloat>
       ("CHORUSFEEDBACK", "Chorus Feedback", -1.f, 1.f, 0.f));
    layout.add(std::make_unique<juce::AudioParameterFloat>
       ("CHORUSMIX", "Chorus Mix", 0.f, 1.f, 0.5f));
    
    /* Reverb */
    layout.add(std::make_unique<juce::AudioParameterBool>
        ("REVERB", "Reverb Bypass", 
            true));
    layout.add(std::make_unique<juce::AudioParameterFloat>
        ("VERBMIX", "Reverb Mix", 0.f, 1.f, 
            0.5f));
    layout.add(std::make_unique<juce::AudioParameterFloat>
        ("VERBROOM", "Reverb Room", 0.f, 1.f, 
            0.5f));
    layout.add(std::make_unique<juce::AudioParameterFloat>
        ("VERBDAMPING", "Reverb Damping", 0.f, 1.f, 
            0.5f));
    layout.add(std::make_unique<juce::AudioParameterFloat>
        ("VERBWIDTH", "Reverb Width", 0.f, 1.f, 
            0.5f));

    /* Master volume */
    layout.add(std::make_unique<juce::AudioParameterFloat>
        ("MASTERVOL", "Output", -40.f, 0.f,
            -20.f));

    /* Cabinet */
    layout.add(std::make_unique<juce::AudioParameterFloat>
        ("CONVOLUTION", "Cabinet", 1.f, 2.f,
            1.f));

    return(layout);
}

ChainSettings getChainSettings(juce::AudioProcessorValueTreeState& apvts)
{
    ChainSettings settings;

    /* Noise gate */
    settings.gateToggle = apvts.getRawParameterValue("GATE")->load() > 0.5f;
    settings.gateThreshold = apvts.getRawParameterValue("GATETHRESH")->load();
    settings.gateAttack = apvts.getRawParameterValue("GATEATT")->load();
    settings.gateRelease = apvts.getRawParameterValue("GATEREL")->load();

    /* Pregain */
    settings.preGain = apvts.getRawParameterValue("GAIN")->load();

    /* EQ filters */
    settings.bassFreq = apvts.getRawParameterValue("BASS")->load();
    settings.midGain = apvts.getRawParameterValue("MID")->load();
    settings.trebleFreq = apvts.getRawParameterValue("TREBLE")->load();

    /* Waveshaper */
    settings.waveshaper = apvts.getRawParameterValue("WAVESHAPER")->load();
    
    /* Chorus */
    settings.chorusRate = apvts.getRawParameterValue("CHORUSRATE")->load();
    settings.chorusDepth = apvts.getRawParameterValue("CHORUSDEPTH")->load();
    settings.chorusDelay = apvts.getRawParameterValue("CHORUSDELAY")->load();
    settings.chorusFeedback = apvts.getRawParameterValue("CHORUSFEEDBACK")->load();
    settings.chorusMix = apvts.getRawParameterValue("CHORUSMIX")->load();
    
    /* Reverb */
    settings.reverbToggle = apvts.getRawParameterValue("REVERB")->load();
    settings.verbMix = apvts.getRawParameterValue("VERBMIX")->load();
    settings.verbRoom = apvts.getRawParameterValue("VERBROOM")->load();
    settings.verbDamping = apvts.getRawParameterValue("VERBDAMPING")->load();
    settings.verbWidth = apvts.getRawParameterValue("VERBWIDTH")->load();

    /* Master volume */
    settings.masterVol = apvts.getRawParameterValue("MASTERVOL")->load();

    /* Convolution */
    settings.convolution = apvts.getRawParameterValue("CONVOLUTION")->load();

    return settings;
}

void AmpSimAudioProcessor::updateSettings()
{
    /* Retrieve slider settings*/
    ChainSettings settings = getChainSettings(apvts);

    /* Update dsp settings */
    updateNoiseGate(settings.gateThreshold, settings.gateAttack, settings.gateRelease, 
        settings.gateToggle);
    updatePreGain(settings.preGain, settings.waveshaper);
    updateToneStack(settings);
    updateWaveshaper(settings.waveshaper);
    updateChorus(settings.chorusRate, settings.chorusDepth, settings.chorusDelay,
                 settings.chorusFeedback, settings.chorusMix);
    updateReverb(settings.verbMix, settings.verbRoom, settings.verbDamping,
        settings.verbWidth, settings.reverbToggle);
    updateMasterVol(settings.masterVol);
    updateConvolution(settings.convolution);
}

void AmpSimAudioProcessor::updateNoiseGate(float thresh, float att, float rel, bool bypass)
{
    /* Retrieve stage template */
    auto& leftGate = leftInput.template get<InputChainPositions::Gate>();
    auto& rightGate = rightInput.template get<InputChainPositions::Gate>();

    /* Toggle on/off */
    leftInput.setBypassed<InputChainPositions::Gate>(bypass);
    rightInput.setBypassed<InputChainPositions::Gate>(bypass);

    /* Threshold */
    leftGate.setThreshold(thresh);
    rightGate.setThreshold(thresh);

    /* Ratio */
    leftGate.setRatio(gateRatio);
    rightGate.setRatio(gateRatio);

    /* Attack */
    leftGate.setAttack(att);
    rightGate.setAttack(att);

    /* Release */
    leftGate.setRelease(rel);
    rightGate.setRelease(rel);
}

void AmpSimAudioProcessor::updatePreGain(float gainDb, float amp)
{
    /* Retrieve stage template */
    auto& leftPreGain = leftInput.template get<InputChainPositions::PreGain>();
    auto& rightPreGain = rightInput.template get<InputChainPositions::PreGain>();

    /* Set new gain level */
//    switch((int)amp)
//    {
//        case Circle7:
//            leftPreGain.setGainDecibels(gainDb - 20.f);
//            rightPreGain.setGainDecibels(gainDb - 20.f);
//            break;
//        default:
//            leftPreGain.setGainDecibels(gainDb);
//            rightPreGain.setGainDecibels(gainDb);
//            break;
//    }
    
    leftPreGain.setGainDecibels(gainDb);
    rightPreGain.setGainDecibels(gainDb);
}

void AmpSimAudioProcessor::updateToneStack(const ChainSettings &chainSettings)
{
    updateBassTone(chainSettings.bassFreq);
    updateMidTone(chainSettings.midGain);
    updateTrebleTone(chainSettings.trebleFreq);
}

void AmpSimAudioProcessor::updateBassTone(float freq)
{
    auto& leftBass = leftTone.template get<ToneStackPositions::Bass>();
    auto& rightBass = rightTone.template get<ToneStackPositions::Bass>();

    leftBass.coefficients = juce::dsp::IIR::Coefficients<float>::
        makeHighPass(getSampleRate(), -1 * freq, bassQ);
    rightBass.coefficients = juce::dsp::IIR::Coefficients<float>::
        makeHighPass(getSampleRate(), -1 * freq, bassQ);
}

void AmpSimAudioProcessor::updateMidTone(float gainDb)
{
    auto& leftMid = leftTone.template get<ToneStackPositions::Mid>();
    auto& rightMid = rightTone.template get<ToneStackPositions::Mid>();

    leftMid.coefficients = juce::dsp::IIR::Coefficients<float>::
        makePeakFilter(getSampleRate(), peakFc, peakQ, 
            juce::Decibels::decibelsToGain(gainDb));
    rightMid.coefficients = juce::dsp::IIR::Coefficients<float>::
        makePeakFilter(getSampleRate(), peakFc, peakQ, 
            juce::Decibels::decibelsToGain(gainDb));
}

void AmpSimAudioProcessor::updateTrebleTone(float freq)
{
    auto& leftTreble = leftTone.template get<ToneStackPositions::Treble>();
    auto& rightTreble = rightTone.template get<ToneStackPositions::Treble>();

    leftTreble.coefficients = juce::dsp::IIR::Coefficients<float>::
        makeLowPass(getSampleRate(), freq, trebleQ);
    rightTreble.coefficients = juce::dsp::IIR::Coefficients<float>::
        makeLowPass(getSampleRate(), freq, trebleQ);
}

void AmpSimAudioProcessor::updateWaveshaper(float shapeSelect)
{
    /* Retrieve stage template */
    auto& leftWaveShape = leftAmp.template get<AmpChainPositions::WaveShaping>();
    auto& rightWaveShape = rightAmp.template get<AmpChainPositions::WaveShaping>();
    
    /* Assign waveshaper function from combo box selection */
    switch ((int)shapeSelect)
    {
    
            /* Clean amp, no waveshaping */
        case Clean:
            /* No waveshaping function */
            leftWaveShape.functionToUse = [](float x) {
                return x;
            };
            rightWaveShape.functionToUse = [](float x) {
                return x;
            };
            break;
            
            /* Soft clippers, low gain */
        case Asinine:       // Asymptotic
            leftWaveShape.functionToUse = [](float x) {
                return x/(abs(x) + 1);
            };
            rightWaveShape.functionToUse = [](float x) {
                return x/(abs(x) + 1);
            };
            break;
        case Reptile:       // Scaled arctan
            leftWaveShape.functionToUse = [](float x) {
                return (2.f/juce::MathConstants<float>::pi) * std::atan(x * juce::MathConstants<float>::halfPi);
            };
            rightWaveShape.functionToUse = [](float x) {
                return (2.f/juce::MathConstants<float>::pi) * std::atan(x * juce::MathConstants<float>::halfPi);
            };
            break;
        case Geeky:         // Algebraic
            leftWaveShape.functionToUse = [](float x) {
                return x/(sqrt(1 + pow(x, 2.f)));
            };
            rightWaveShape.functionToUse = [](float x) {
                return x/(sqrt(1 + pow(x, 2.f)));
            };
            break;
        case SmolCronch:    // Hyperbolic tangent
            leftWaveShape.functionToUse = [](float x) {
                return std::tanh(x);
            };
            rightWaveShape.functionToUse = [](float x) {
                return std::tanh(x);
            };
            break;
            
            /* Hard clippers, high gain*/
        case FatMan:        // Polynomail
            leftWaveShape.functionToUse = [](float x)
            {
                if (x > -1.f)
                {
                    if (x < 1)
                        return ( (3.f/2.f)*x - (1.f/2.f)*pow(x, 3.f) );
                    else
                        return 1.f;
                }
                else
                    return -1.f;
            };
            rightWaveShape.functionToUse = [](float x)
            {
                if (x > -1.f)
                {
                    if (x < 1)
                        return ( (3.f/2.f)*x - (1.f/2.f)*pow(x, 3.f) );
                    else
                        return 1.f;
                }
                else
                    return -1.f;
            };
            break;
        case Circle7:
            leftWaveShape.functionToUse = [](float x) {
                if (x > -0.08905f)
                {
                    if (x < 0.320018f)
                        return -6.153f*pow(x, 2.f) + 3.9375f*x;
                    else
                        return 0.630035f;
                }
                else
                    return (-3.f/4.f)*( 1.f - pow(1.f - (abs(x) - 0.032847f), 12.f) + (1.f/3.f)*(abs(x) - 0.032847f)) + 0.01f;
            };
            rightWaveShape.functionToUse = [](float x) {
                if (x > -0.08905f)
                {
                    if (x < 0.320018f)
                        return -6.153f*pow(x, 2.f) + 3.9375f*x;
                    else
                        return 0.630035f;
                }
                else
                    return (-3.f/4.f)*( 1.f - pow(1.f - (abs(x) - 0.032847f), 12.f) + (1.f/3.f)*(abs(x) - 0.032847f)) + 0.01f;
            };
            break;
        case ForkInToaster: // Basic hard clipper
            leftWaveShape.functionToUse = [](float x)
            {
                return juce::jlimit(float(-1), float(1), x);
            };
            rightWaveShape.functionToUse = [](float x)
            {
                return juce::jlimit(float(-1), float(1), x);
            };
            break;
        }
}

void AmpSimAudioProcessor::updateChorus(float rate, float depth, float delay, float feedback, float mix)
{
    auto& leftChorus = leftEffects.template get<EffectsChainPositions::OutChorus>();
    auto& rightChorus = rightEffects.template get<EffectsChainPositions::OutChorus>();
    
    /* Rate */
    leftChorus.setRate(rate);
    rightChorus.setRate(rate);
    
    /* Depth */
    leftChorus.setDepth(depth);
    rightChorus.setDepth(depth);
    
    /* Delay */
    leftChorus.setCentreDelay(delay);
    rightChorus.setCentreDelay(delay);

    /* Feedback */
    leftChorus.setFeedback(feedback);
    rightChorus.setFeedback(feedback);
    
    /* Mix */
    leftChorus.setMix(mix);
    rightChorus.setMix(mix);
}

void AmpSimAudioProcessor::updateReverb(float mix, float room, float damping, float width, bool enable)
{
    auto& leftVerb = leftEffects.template get<EffectsChainPositions::OutReverb>();
    auto& rightVerb = rightEffects.template get<EffectsChainPositions::OutReverb>();
    
    /* Toggle on/off */
    leftVerb.setEnabled(!enable);
    rightVerb.setEnabled(!enable);
    
    ReverbParams params;
    params.roomSize = room;
    params.damping = damping;
    params.wetLevel = mix;
    params.dryLevel = 1 - mix;
    params.width = width;
    
    leftVerb.setParameters(params);
    rightVerb.setParameters(params);
}

void AmpSimAudioProcessor::updateMasterVol(float gainDb)
{
    /* Retrieve stage template */
    auto& leftMasterVol = leftOutput.template get<OutputChainPositions::MasterVol>();
    auto& rightMasterVol = rightOutput.template get<OutputChainPositions::MasterVol>();

    /* Set new gain */
    leftMasterVol.setGainDecibels(gainDb);
    rightMasterVol.setGainDecibels(gainDb);
}

void AmpSimAudioProcessor::updateConvolution(float cabinetSelect)
{
    /* Retrieve stage template */
    auto& leftCabinet = leftOutput.template get<OutputChainPositions::Cabinet>();
    auto& rightCabinet = rightOutput.template get<OutputChainPositions::Cabinet>();

    /* Assign convolution from combo box selection */
    switch ((int)cabinetSelect)
    {
    case 1:
        /* Guitar amp cabinet */
        leftCabinet.loadImpulseResponse(BinaryData::guitar_amp_wav,
                                        BinaryData::guitar_amp_wavSize,
                                        juce::dsp::Convolution::Stereo::yes,
                                        juce::dsp::Convolution::Trim::no,
                                        1024);
        rightCabinet.loadImpulseResponse(BinaryData::guitar_amp_wav,
                                        BinaryData::guitar_amp_wavSize,
                                        juce::dsp::Convolution::Stereo::yes,
                                        juce::dsp::Convolution::Trim::no,
                                        1024);
        break;
    case 2:
        leftCabinet.loadImpulseResponse(BinaryData::cassette_recorder_wav,
                                        BinaryData::cassette_recorder_wavSize,
                                        juce::dsp::Convolution::Stereo::yes,
                                        juce::dsp::Convolution::Trim::no,
                                        1024);
        rightCabinet.loadImpulseResponse(BinaryData::cassette_recorder_wav,
                                        BinaryData::cassette_recorder_wavSize,
                                        juce::dsp::Convolution::Stereo::yes,
                                        juce::dsp::Convolution::Trim::no,
                                        1024);
        break;
    }
}
