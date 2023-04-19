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
    effect1.labels.add({0.f, "Chorus"});
    effect1.labels.add({1.f, "Mix"});
    effect1.labels.add({2.f, "Rate"});
    effect1.labels.add({3.f, "Depth"});
    effect1.labels.add({4.f, "Delay"});
    effect2.labels.add({0.f, "Phaser"});
    effect2.labels.add({1.f, "Mix"});
    effect2.labels.add({2.f, "Rate"});
    effect2.labels.add({3.f, "Depth"});
    
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
    convolutionCombo.addItem("No Cabinet", 1);
    convolutionCombo.addSectionHeading("Amp Cabinets");
    convolutionCombo.addItem("Cabinet", 2);
    convolutionCombo.addSectionHeading("Special");
    convolutionCombo.addItem("Cassette", 3);
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
    chorusMixAtt = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>
        (audioProcessor.apvts, "CHORUSMIX", effect1.knob1);
    chorusRateAtt = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>
        (audioProcessor.apvts, "CHORUSRATE", effect1.knob2);
    chorusDepthAtt = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>
        (audioProcessor.apvts, "CHORUSDEPTH", effect1.knob3);
    chorusDelayAtt = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>
        (audioProcessor.apvts, "CHORUSDELAY", effect1.knob4);
    
    
    /* Effect 2 */
    phaserMixAtt = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>
    (audioProcessor.apvts, "PHASERMIX", effect2.knob1);
    phaserRateAtt = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>
        (audioProcessor.apvts, "PHASERRATE", effect2.knob2);
    phaserDepthAtt = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>
        (audioProcessor.apvts, "PHASERDEPTH", effect2.knob3);
//    phaserFcAtt = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>
//        (audioProcessor.apvts, "PHASERFC", *(effect2.menuKnob1.get()));

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
    auto functionCenterX = (float)ampImage.getX() + ampImage.getHeight()/2.f;
    auto functionCenterY = ampImage.getHeight()/2.f;
    auto functionQuadrantWidth = ampImage.getHeight()/2.f; auto functionHeight = ampImage.getHeight();
    auto functionWidth = (float)ampImage.getHeight();
    auto waveshapeThicc = 2.f;
    
    waveShapePath.clear();
    
//    waveShapePath.startNewSubPath(ampImage.getX(), ampImage.getHeight()/2.f);
//    waveShapePath.startNewSubPath(0, getHeight()/2.f);

    
    /* Background color based on amp selection*/
    switch(imageCheck)
    {
            /* Low gain amps */
        case Clean:
            
            g.setGradientFill(juce::ColourGradient(juce::Colours::yellow, 0, 0,
                                                   juce::Colours::black, getInitialWindowSize().getX(),
                                                   getInitialWindowSize().getY(),
                                                   true));
            
            // Waveshaping: y = x
            waveShapePath.startNewSubPath(functionCenterX, functionCenterY); // Pixel where the path starts
            for (auto x = 1.f; x <= functionQuadrantWidth; ++x)
            {
                waveShapePath.lineTo(functionCenterX + x,
                                     functionCenterY -
                                     x); // Positive Input
                waveShapePath.lineTo(functionCenterX - x,
                                     functionCenterY +
                                     x); // Negative Input

            }
            
            break;
            
        case Asinine:
            g.setGradientFill(juce::ColourGradient(juce::Colours::green, 0, 0,
                                                   juce::Colours::black, getInitialWindowSize().getX(),
                                                   getInitialWindowSize().getY(),
                                                   true));
            
            // Waveshaping: x/(abs(x) + 1.0f)
            waveShapePath.startNewSubPath(functionCenterX, functionCenterY); // Pixel where the path starts
//            for (auto x = 1.f; x < functionQuadrantWidth; ++x)
//            {
//                auto input = x/functionQuadrantWidth;
//                waveShapePath.lineTo(functionCenterX + x, // Positive Input
//                                     functionCenterY -
//                                     functionQuadrantWidth*(input/(abs(input) + 1.0f)));
//
//            }
            
            for (auto x = 1.f; x <= functionWidth; ++x)
            {
                auto input = x/functionQuadrantWidth;
                waveShapePath.lineTo(functionCenterX + x, // Positive Input
                                     functionCenterY -
                                     functionQuadrantWidth*(input/(abs(input) + 1.0f)));

            }
            
            
            
            
            
            
            
//            waveShapePath.startNewSubPath(functionCenterX, functionCenterY); // Pixel where the path starts
//            waveShapePath.startNewSubPath(functionCenterX, functionCenterY); // Pixel where the path starts
//            for (auto x = -1.f; x < -1*functionQuadrantWidth; ++x)
//            {
//                auto input = x/functionQuadrantWidth;
//                waveShapePath.lineTo(functionCenterX + x, // Negative Input
//                                     functionCenterY +
//                                     functionQuadrantWidth*(input/(abs(input) + 1.0f)));
//
//            }
            
//            waveShapePath.startNewSubPath(ampImage.getX(), ampImage.getHeight()); // Pixel where the path starts
//            for (auto x = 1.0f; x < (float)ampImage.getWidth(); ++x)
//            {
//                waveShapePath.lineTo(x + ampImage.getX(), // Line X pixel position
//                                     ampImage.getHeight() // Line Y pixel position
//                                     - x*((float)ampImage.getHeight()/(float)ampImage.getHeight()));
//            }
//
            break;
            
        case Reptile:
            g.setGradientFill(juce::ColourGradient(juce::Colours::blue, 0, 0,
                                                   juce::Colours::black, getInitialWindowSize().getX(),
                                                   getInitialWindowSize().getY(),
                                                   true));
            
            waveShapePath.startNewSubPath(ampImage.getX(), ampImage.getHeight()/2.f);
//            for (auto x = 1.0f; x < (float) getWidth(); ++x)
//            {
//                waveShapePath.lineTo(x, (float) getHeight() / 2.0f
//                                     + ((float)getHeight() - waveshapeThicc)/2.0f
//                                     * std::sin (x * 160 * 0.0001f));
//            }
            for (auto x = 1.0f; x < (float)ampImage.getWidth(); ++x)
            {
                waveShapePath.lineTo(x + ampImage.getX(),
                                     (float) ampImage.getHeight() / 2.0f
                                     + ((float)ampImage.getHeight() - waveshapeThicc)/2.0f
                                     * std::sin (x * 80 * 0.0001f));
            }
            
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
    
    /* Draw Waveshaping function */
    g.setColour (juce::Colours::black);
    g.strokePath (waveShapePath, juce::PathStrokeType (waveshapeThicc));
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
//            ampImage.setImage(juce::ImageCache::getFromMemory(BinaryData::capybara_jpeg, BinaryData::capybara_jpegSize));
//            waveShapePath.startNewSubPath(0, ampImage.getHeight()/2);
//            for (auto x = 1.0f; x < (float) getWidth(); ++x)
//            {
//                waveShapePath.lineTo(x, ampImage.getHeight()/2 + (float) ampImage.getHeight() * 2.0f
//                                 * std::sin (x * 1000 * 0.0001f));
//            }
//            waveShapePath.scaleToFit(ampImage.getX(), ampImage.getY(),
//                                     ampImage.getWidth(), ampImage.getHeight(), true);
            break;
            
        case Asinine:
//            ampImage.setImage(juce::ImageCache::getFromMemory(BinaryData::capybara2_jpeg, BinaryData::capybara2_jpegSize));
            break;
            
        case Reptile:
//            ampImage.setImage(juce::ImageCache::getFromMemory(BinaryData::capybara3_jpeg, BinaryData::capybara3_jpegSize));
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
