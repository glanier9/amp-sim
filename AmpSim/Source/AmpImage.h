/*
  ==============================================================================

    AmpImage.h
    Created: 8 Nov 2022 12:28:15pm
    Author:  School

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class AmpImage  : public juce::Component
{
public:
    AmpImage();
    ~AmpImage() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AmpImage)
};
