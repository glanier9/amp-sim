/*
  ==============================================================================

    SelectionBox.cpp
    Created: 28 Sep 2022 9:46:08pm
    Author:  Greg Lanier

  ==============================================================================
*/

#include "SelectionBox.h"

void SelectionLookAndFeel::drawComboBox(juce::Graphics& g,
                                    int width, int height,
                                    bool isButtonDown,
                                    int buttonX, int buttonY, int buttonW, int buttonH,
                                    juce::ComboBox& box)
{
    using namespace juce;
    auto cornerSize = box.findParentComponentOfClass<ChoicePropertyComponent>() != nullptr ? 0.0f : 3.0f;
    Rectangle<int> boxBounds ((width - (width * widthOffset))/2, (height - (height * heightOffset)),
                              width * widthOffset, height*heightOffset);

    /* Bounds for area with slider and all assets*/
    g.setColour(Colours::black);
    g.drawRect(0, 0, width, height);   // Local bounds
    
//    g.setColour (box.findColour (ComboBox::backgroundColourId));
    g.setColour(juce::Colours::black);
    g.fillRoundedRectangle (boxBounds.toFloat(), cornerSize);

    g.setColour (box.findColour (ComboBox::outlineColourId));
    g.drawRoundedRectangle (boxBounds.toFloat().reduced (0.5f, 0.5f), cornerSize, 1.0f);

    Rectangle<int> arrowZone (width * widthOffset - 10, 10, 20, height); // Left, top, right, bottom
    Path path;
    path.startNewSubPath ((float) arrowZone.getX() + 3.0f, (float) arrowZone.getCentreY() - 2.0f);
    path.lineTo ((float) arrowZone.getCentreX(), (float) arrowZone.getCentreY() + 3.0f);
    path.lineTo ((float) arrowZone.getRight() - 3.0f, (float) arrowZone.getCentreY() - 2.0f);

    g.setColour (box.findColour (ComboBox::arrowColourId).withAlpha ((box.isEnabled() ? 0.9f : 0.2f)));
    g.strokePath (path, PathStrokeType (2.0f));
    
    /* Label for selection box */
    g.setColour(Colour(255u, 255u, 255u));
    g.setFont(getLabelFontSettings());
    Rectangle<float> textBox;
    /********************************/
//    textBox.setSize(g.getCurrentFont().getStringWidth(SelectionBox::outsideLabel.label), g.getCurrentFont().getHeight());
//    textBox.setCentre(center.getX(), center.getY() + endDist);
//    g.drawFittedText(labels[0].label, textBox.toNearestInt(), juce::Justification::centred, 1);
    /********************************/
}

void SelectionLookAndFeel::positionComboBoxText (juce::ComboBox& box, juce::Label& label)
{
    label.setBounds ((box.getWidth() - (box.getWidth() * widthOffset)) + 2, 11,
                     box.getWidth() - 30,
                     box.getHeight() - 2);
    label.setFont (getComboBoxFont (box));
}
