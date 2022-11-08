/*
  ==============================================================================

    FxKnob1.cpp
    Created: 28 Oct 2022 8:50:57pm
    Author:  School

  ==============================================================================
*/

#include <JuceHeader.h>
#include "FxKnob1.h"

void FxKnob1LookAndFeel::drawRotarySlider(juce::Graphics &g,
                                   int x, int y, int width, int height,
                                   float sliderPosProportional, float rotaryStartAngle,
                                   float rotaryEndAngle, juce::Slider &slider)
{
    using namespace juce;
    auto bounds = Rectangle<float>(x, y, width, height);
    auto center = bounds.getCentre();
    Path path; Rectangle<float> rect;
    auto sliderAngle = jmap(sliderPosProportional, 0.f, 1.f,
                            rotaryStartAngle, rotaryEndAngle);   // in radians
    
    /* Knob fill */
    g.setColour(Colour(0u, 0u, 0u));
    g.fillEllipse(bounds);
    
    /* Knob border */
    g.setColour(Colour(0u, 150u, 255u));
    g.drawEllipse(bounds, (bounds.getX() - center.getX())/15);
    
    /* Bounds for rotating indicator */
    g.setColour(Colour(0u, 150u, 255u));
    rect.setLeft(center.getX() - bounds.getWidth()/20);
    rect.setRight(center.getX() + bounds.getWidth()/20);
    rect.setTop(bounds.getY() - 1);
    rect.setBottom(center.getY() - ((center.getY() - bounds.getY())*0.6) );
    path.addEllipse(rect);
    jassert(rotaryStartAngle < rotaryEndAngle);
    path.applyTransform(AffineTransform().rotated(sliderAngle,
                                                 center.getX(), center.getY()));
    
    g.fillPath(path);
}

//==============================================================================

void FxKnob1::paint (juce::Graphics& g)
{
    using namespace juce;
    
    /* Setup */
    auto startAngle = degreesToRadians(180.f + 30.f); // 7 o'clock
    auto endAngle = degreesToRadians(180.f - 30.f)
                    + MathConstants<float>::twoPi; // 5 o'clock
    auto range = getRange();
    auto sliderBounds = getSliderBounds();
    auto center = sliderBounds.getCentre();
    Rectangle<float> centerCirc;
    Path path;
    auto knobCenterRadius = (center.getX() - sliderBounds.getX())/8;
    auto startDist = center.getY() - (center.getY() - sliderBounds.getHeight()/2 - 8);
    auto endDist = startDist + getSliderBounds().getWidth()/5;
    Rectangle<float> textBox;
    
    /* Generate knob */
    getLookAndFeel().drawRotarySlider(g,
                                      sliderBounds.getX(), sliderBounds.getY(),
                                      sliderBounds.getWidth(), sliderBounds.getHeight(),
                                      jmap(getValue(), range.getStart(), range.getEnd(),
                                           0.0, 1.0),
                                      startAngle, endAngle,
                                      *this);
    
    /* Center knob circle */
    g.setColour(Colour(255u, 255u, 255u));
    centerCirc.setLeft(center.getX() - knobCenterRadius);
    centerCirc.setRight(center.getX() + knobCenterRadius);
    centerCirc.setTop(center.getY() - knobCenterRadius);
    centerCirc.setBottom(center.getY() + knobCenterRadius);
    g.drawEllipse(centerCirc, 1.f);
    path.addEllipse(centerCirc);
    g.fillPath(path);
    
    /* Label below knob */
    g.setColour(Colour(255u, 255u, 255u));
    g.setFont(getFontSettings());
    textBox.setSize(g.getCurrentFont().getStringWidth(labels[0].label), g.getCurrentFont().getHeight());
    textBox.setCentre(center.getX(), center.getY() + endDist);
    g.drawFittedText(labels[0].label, textBox.toNearestInt(), juce::Justification::centred, 1);
}

juce::Rectangle<int> FxKnob1::getSliderBounds() const
{
    auto bounds = getLocalBounds();
    juce::Rectangle<int> sliderBounds;
    auto size = juce::jmin(bounds.getWidth(), bounds.getHeight());
    auto sizeOffset = size/2.f;
    size -= sizeOffset; // Shrink box from border
    
    sliderBounds.setSize(size, size);
    sliderBounds.setCentre(bounds.getCentreX(), 0);
    sliderBounds.setY(sizeOffset/2);
    
    return sliderBounds;
}
