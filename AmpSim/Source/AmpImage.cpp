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
    /* Load image from app resources */
    juce::Image image = juce::ImageCache::getFromMemory(BinaryData::capybara_jpeg, BinaryData::capybara_jpegSize);
    g.drawImageAt(image, 0, 0);
}

void AmpImage::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}
