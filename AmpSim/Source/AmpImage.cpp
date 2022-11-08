/*
  ==============================================================================

    AmpImage.cpp
    Created: 8 Nov 2022 12:28:15pm
    Author:  School

  ==============================================================================
*/

#include <JuceHeader.h>
#include "AmpImage.h"

//==============================================================================
AmpImage::AmpImage()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

AmpImage::~AmpImage()
{
}

void AmpImage::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

//    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background
//
//    g.setColour (juce::Colours::grey);
//    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component
//
//    g.setColour (juce::Colours::white);
//    g.setFont (14.0f);
//    g.drawText ("AmpImage", getLocalBounds(),
//                juce::Justification::centred, true);   // draw some placeholder text
    juce::Image image = juce::ImageCache::getFromMemory(BinaryData::capybara_jpeg, BinaryData::capybara_jpegSize);
    g.drawImageAt(image, 0, 0);
}

void AmpImage::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}
