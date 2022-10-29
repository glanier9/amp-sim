/*
  ==============================================================================

    Switch.cpp
    Created: 28 Oct 2022 9:15:32pm
    Author:  School

  ==============================================================================
*/

#include "Switch.h"

juce::Font SwitchLookAndFeel::getTextButtonFont (juce::TextButton&, int buttonHeight)
{
    return { juce::jmin (16.0f, (float) buttonHeight * 0.6f) };
}

void SwitchLookAndFeel::drawButtonBackground (juce::Graphics& g,
                           juce::Button& button,
                           const juce::Colour& backgroundColour,
                           bool shouldDrawButtonAsHighlighted,
                           bool shouldDrawButtonAsDown)
{
    auto cornerSize = 6.0f;
    auto bounds = button.getLocalBounds().toFloat().reduced (0.5f, 0.5f);

    auto baseColour = backgroundColour.withMultipliedSaturation
                        (button.hasKeyboardFocus (true) ? 1.3f : 0.9f)
                          .withMultipliedAlpha (button.isEnabled() ? 1.0f : 0.5f);

    if (shouldDrawButtonAsDown || shouldDrawButtonAsHighlighted)
        baseColour = baseColour.contrasting (shouldDrawButtonAsDown ? 0.2f : 0.05f);

    g.setColour (baseColour);

    auto flatOnLeft   = button.isConnectedOnLeft();
    auto flatOnRight  = button.isConnectedOnRight();
    auto flatOnTop    = button.isConnectedOnTop();
    auto flatOnBottom = button.isConnectedOnBottom();

    if (flatOnLeft || flatOnRight || flatOnTop || flatOnBottom)
    {
        juce::Path path;
        path.addRoundedRectangle (bounds.getX(), bounds.getY(),
                                  bounds.getWidth(), bounds.getHeight(),
                                  cornerSize, cornerSize,
                                  ! (flatOnLeft  || flatOnTop),
                                  ! (flatOnRight || flatOnTop),
                                  ! (flatOnLeft  || flatOnBottom),
                                  ! (flatOnRight || flatOnBottom));

        g.fillPath (path);

        g.setColour (button.findColour (juce::ComboBox::outlineColourId));
        g.strokePath (path, juce::PathStrokeType (1.0f));
    }
    else
    {
        g.fillRoundedRectangle (bounds, cornerSize);

        g.setColour (button.findColour (juce::ComboBox::outlineColourId));
        g.drawRoundedRectangle (bounds, cornerSize, 1.0f);
    }
}

void SwitchLookAndFeel::drawToggleButton (juce::Graphics& g,
                                          juce::ToggleButton& button,
                                          bool shouldDrawButtonAsHighlighted,
                                          bool shouldDrawButtonAsDown)
{
    auto fontSize = juce::jmin (15.0f, (float) button.getHeight() * 0.75f);
    auto tickWidth = fontSize * 1.1f;

    drawTickBox (g, button, 4.0f, ((float) button.getHeight() - tickWidth) * 0.5f,
                 tickWidth, tickWidth,
                 button.getToggleState(),
                 button.isEnabled(),
                 shouldDrawButtonAsHighlighted,
                 shouldDrawButtonAsDown);

    g.setColour (button.findColour (juce::ToggleButton::textColourId));
    g.setFont (fontSize);

    if (! button.isEnabled())
        g.setOpacity (0.5f);

    // TODO: Change how the text is generated to match the new placing method
    g.drawFittedText (button.getButtonText(),
                      button.getLocalBounds().withTrimmedLeft
                        (juce::roundToInt (tickWidth) + 10)
                         .withTrimmedRight (2),
                      juce::Justification::centredLeft, 10);
}

void SwitchLookAndFeel::drawTickBox (juce::Graphics& g, juce::Component& component,
                                      float x, float y, float w, float h,
                                      const bool ticked,
                                      const bool isEnabled,
                                      const bool shouldDrawButtonAsHighlighted,
                                      const bool shouldDrawButtonAsDown)
{
    juce::ignoreUnused (isEnabled, shouldDrawButtonAsHighlighted,
                        shouldDrawButtonAsDown);

    juce::Rectangle<float> tickBounds (x + component.getLocalBounds().getWidth()/2.f - w/2.f, y, w, h);

    g.setColour (component.findColour (juce::ToggleButton::tickDisabledColourId));
    g.drawRoundedRectangle (tickBounds, 4.0f, 1.0f);

    if (ticked)
    {
        g.setColour (component.findColour (juce::ToggleButton::tickColourId));
        auto tick = getTickShape (0.75f);
        g.fillPath (tick,
                    tick.getTransformToScaleToFit (tickBounds.reduced (4, 5).toFloat(),
                                                   false));
    }
}

void SwitchLookAndFeel::changeToggleButtonWidthToFitText (juce::ToggleButton& button)
{
    auto fontSize = juce::jmin (15.0f, (float) button.getHeight() * 0.75f);
    auto tickWidth = fontSize * 1.1f;

    juce::Font font (fontSize);

    button.setSize (font.getStringWidth (button.getButtonText())
                        + juce::roundToInt (tickWidth) + 14,
                    button.getHeight());
}

//==============================================================================
