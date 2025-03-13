//
// Created by Rene Maierhofer on 13.03.25.
//
#pragma once
#include <JuceHeader.h>

class ChannelSliderLookAndFeel : public juce::LookAndFeel_V4
{
public:
    ChannelSliderLookAndFeel()
    {
        setColour(juce::Slider::backgroundColourId, juce::Colour(20, 20, 20));
        setColour(juce::Slider::thumbColourId, juce::Colours::white);
        setColour(juce::Slider::trackColourId, juce::Colour(245, 158, 11));
        setColour(juce::Slider::textBoxBackgroundColourId, juce::Colours::black);
        setColour(juce::Slider::textBoxOutlineColourId, juce::Colours::transparentBlack);
        setColour(juce::Slider::textBoxTextColourId, juce::Colour(245, 158, 11));
    }

};

class ControllerSliderLookAndFeel : public ChannelSliderLookAndFeel
{
public:
    ControllerSliderLookAndFeel()
    {
        setColour(juce::Slider::trackColourId, juce::Colour(239, 68, 68));
        setColour(juce::Slider::textBoxTextColourId, juce::Colour(239, 68, 68));
    }
};

class ValueSliderLookAndFeel : public ChannelSliderLookAndFeel
{
public:
    ValueSliderLookAndFeel()
    {
        setColour(juce::Slider::trackColourId, juce::Colour(59, 130, 246));
        setColour(juce::Slider::textBoxTextColourId, juce::Colour(59, 130, 246));
    }
};
