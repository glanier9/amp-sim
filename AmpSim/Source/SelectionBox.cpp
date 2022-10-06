/*
  ==============================================================================

    SelectionBox.cpp
    Created: 28 Sep 2022 9:46:08pm
    Author:  Greg Lanier

  ==============================================================================
*/

#include "SelectionBox.h"

/*
    Draw the combo box with label and all graphics
 */
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
    Path path;

    /* Bounds for area with slider and all assets */
    g.setColour(Colours::black);
    g.drawRect(0, 0, width, height);
    
    /* Box of clickable combo box */
    g.setColour(juce::Colours::black);
    g.fillRoundedRectangle (boxBounds.toFloat(), cornerSize);

    /* Outline for combo box */
    g.setColour (box.findColour (ComboBox::outlineColourId));
    g.drawRoundedRectangle (boxBounds.toFloat().reduced (0.5f, 0.5f), cornerSize, 1.0f);
    
    /* Arrow signifying dropdown */
    g.setColour (box.findColour (ComboBox::arrowColourId).withAlpha ((box.isEnabled() ? 0.9f : 0.2f)));
    Rectangle<int> arrowZone (width * widthOffset - 10, 10, 20, height); // Left, top, right, bottom
    path.startNewSubPath ((float) arrowZone.getX() + 3.0f, (float) arrowZone.getCentreY() - 2.0f);
    path.lineTo ((float) arrowZone.getCentreX(), (float) arrowZone.getCentreY() + 3.0f);
    path.lineTo ((float) arrowZone.getRight() - 3.0f, (float) arrowZone.getCentreY() - 2.0f);
    g.strokePath (path, PathStrokeType (2.0f));
    
    /* Label for around the box */
    g.setColour(Colour(255u, 255u, 255u));
    g.setFont(getLabelFontSettings());
    Rectangle<float> textBox;
    auto center = boxBounds.getCentre();
    g.setColour(Colour(255u, 255u, 255u));
    textBox.setSize(g.getCurrentFont().getStringWidth(outsideLabels[0].label), g.getCurrentFont().getHeight());
    textBox.setCentre(center.getX(), center.getY() - boxBounds.getY() - 5);
    g.drawFittedText(outsideLabels[0].label, textBox.toNearestInt(), juce::Justification::centred, 1);
}

/*
    Position the displayed text for combo box selection
 */
void SelectionLookAndFeel::positionComboBoxText (juce::ComboBox& box, juce::Label& label)
{
    label.setBounds ((box.getWidth() - (box.getWidth() * widthOffset)) + 2, 11,
                     box.getWidth() - 30,
                     box.getHeight() - 2);
    label.setFont (getComboBoxFont (box));
}
