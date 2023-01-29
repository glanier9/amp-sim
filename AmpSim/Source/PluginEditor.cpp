/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "BinaryData.h"

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
    reverbLevelAtt = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>
        (audioProcessor.apvts, "VERBMIX", reverb.knob);
    reverbToggleAtt = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>
        (audioProcessor.apvts, "REVERB", reverb.button);
    
    /* Chorus */
    chorusRateAtt = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>
        (audioProcessor.apvts, "CHORUSRATE", effect1.knob1);
    chorusMixAtt = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>
        (audioProcessor.apvts, "CHORUSMIX", effect1.knob2);
    chorusDepthAtt = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>
        (audioProcessor.apvts, "CHORUSDEPTH", effect1.knob3);
    
    /* Effect 2 */
    phaserRateAtt = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>
        (audioProcessor.apvts, "PHASERRATE", effect2.knob1);
    phaserMixAtt = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>
        (audioProcessor.apvts, "PHASERMIX", effect2.knob2);
    phaserDepthAtt = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>
        (audioProcessor.apvts, "PHASERDEPTH", effect2.knob3);

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
        &effect1,
        
        /* Fx 2 */
        &effect2,
        
        /* Image */
        &ampImage
    };
}

//==============================================================================
/*
    UI Visuals
 */
//==============================================================================
void AmpSimAudioProcessorEditor::paint (juce::Graphics& g)
{
    /* Background color based on amp selection*/
    switch(imageCheck)
    {
            /* Low gain amps */
        case Clean:
            g.setGradientFill(juce::ColourGradient(juce::Colours::yellow, 0, 0,
                                                   juce::Colours::black, getInitialWindowSize().getX(),
                                                   getInitialWindowSize().getY(),
                                                   true));
            break;
            
        case Asinine:
            g.setGradientFill(juce::ColourGradient(juce::Colours::green, 0, 0,
                                                   juce::Colours::black, getInitialWindowSize().getX(),
                                                   getInitialWindowSize().getY(),
                                                   true));
            break;
            
        case Reptile:
            g.setGradientFill(juce::ColourGradient(juce::Colours::blue, 0, 0,
                                                   juce::Colours::black, getInitialWindowSize().getX(),
                                                   getInitialWindowSize().getY(),
                                                   true));
            break;
            
        case Geeky:
            g.setGradientFill(juce::ColourGradient(juce::Colours::red, 0, 0,
                                                   juce::Colours::black, getInitialWindowSize().getX(),
                                                   getInitialWindowSize().getY(),
                                                   true));
            break;
            
        case SmolCronch:
            g.setGradientFill(juce::ColourGradient(juce::Colours::brown, 0, 0,
                                                   juce::Colours::black, getInitialWindowSize().getX(),
                                                   getInitialWindowSize().getY(),
                                                   true));
            break;
            
            /* High gain amps */
        case FatMan:
            g.setGradientFill(juce::ColourGradient(juce::Colours::purple, 0, 0,
                                                   juce::Colours::black, getInitialWindowSize().getX(),
                                                   getInitialWindowSize().getY(),
                                                   true));
            break;
            
        case Circle7:
            g.setGradientFill(juce::ColourGradient(juce::Colours::orange, 0, 0,
                                                   juce::Colours::black, getInitialWindowSize().getX(),
                                                   getInitialWindowSize().getY(),
                                                   true));
            break;
            
        case ForkInToaster:
            g.setGradientFill(juce::ColourGradient(juce::Colours::aqua, 0, 0,
                                                   juce::Colours::black, getInitialWindowSize().getX(),
                                                   getInitialWindowSize().getY(),
                                                   true));
            break;
    }
    
    /* Fill in whole background */
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
    auto imageArea = windowBounds;
    
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
    noiseGate.setBounds(singleKnobFxArea.removeFromLeft(singleKnobFxArea.getWidth()/2.f));
    
    /* Reverb section */
    reverb.setBounds(singleKnobFxArea);
    
    /* Effect 1 section */
    effect1.setBounds(fxArea1);
    
    /* Effect 2 section */
    effect2.setBounds(fxArea2);
    
    /* Image */
    ampImage.setBounds(imageArea);
}

//==============================================================================
/*
    UI Listeners
 */
//==============================================================================
void AmpSimAudioProcessorEditor::waveshaperChanged()
{
    imageCheck = waveShaperCombo.indexOfItemId(waveShaperCombo.getSelectedId()) + 1;
                                               
    /* Update amp photo */
    switch (imageCheck)
    {
            /* Low gain amps */
        case Clean:
            ampImage.setImage(juce::ImageCache::getFromMemory(BinaryData::capybara_jpeg, BinaryData::capybara_jpegSize));
            break;
            
        case Asinine:
            ampImage.setImage(juce::ImageCache::getFromMemory(BinaryData::capybara2_jpeg, BinaryData::capybara2_jpegSize));
            break;
            
        case Reptile:
            ampImage.setImage(juce::ImageCache::getFromMemory(BinaryData::capybara3_jpeg, BinaryData::capybara3_jpegSize));
            break;
            
        case Geeky:
            ampImage.setImage(juce::ImageCache::getFromMemory(BinaryData::capybara4_jpeg, BinaryData::capybara4_jpegSize));
            break;
            
        case SmolCronch:
            ampImage.setImage(juce::ImageCache::getFromMemory(BinaryData::capybara5_jpeg, BinaryData::capybara5_jpegSize));
            break;
            
            /* High gain amps*/
        case FatMan:
            ampImage.setImage(juce::ImageCache::getFromMemory(BinaryData::capybara6_jpeg, BinaryData::capybara6_jpegSize));
            break;
            
        case Circle7:
            ampImage.setImage(juce::ImageCache::getFromMemory(BinaryData::capybara7_jpeg, BinaryData::capybara7_jpegSize));
            break;
            
        case ForkInToaster:
            ampImage.setImage(juce::ImageCache::getFromMemory(BinaryData::capybara8_jpeg, BinaryData::capybara8_jpegSize));
            break;
    }
    
    /* Update background */
    repaint();
}
void AmpSimAudioProcessorEditor::convolutionChanged()
{
    switch (convolutionCombo.getSelectedId())
    {
    case stylePlain:
        break;
    case styleBold:
        break;
    case styleItalic:
        break;
    default:
        break;
    }
}
