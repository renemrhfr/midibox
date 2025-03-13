#pragma once
#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "LookAndFeel.h"

class MidiCCToolAudioProcessorEditor : public juce::AudioProcessorEditor
{
public:
    explicit MidiCCToolAudioProcessorEditor(MidiCCToolAudioProcessor&);
    ~MidiCCToolAudioProcessorEditor() override;
    void paint(juce::Graphics&) override;
    void resized() override;

private:
    MidiCCToolAudioProcessor& processor;

    ChannelSliderLookAndFeel channelLookAndFeel;
    ControllerSliderLookAndFeel controllerLookAndFeel;
    ValueSliderLookAndFeel valueLookAndFeel;

    juce::Label titleLabel;
    juce::Label subtitleLabel;
    juce::Label copyrightLabel;

    juce::Label channelLabel;
    juce::Slider channelSlider;

    juce::Label controllerLabel;
    juce::Slider controllerSlider;

    juce::Label valueLabel;
    juce::Slider valueSlider;

    juce::Rectangle<int> channelArea;
    juce::Rectangle<int> controllerArea;
    juce::Rectangle<int> valueArea;

    std::unique_ptr<juce::SliderParameterAttachment> channelAttachment;
    std::unique_ptr<juce::SliderParameterAttachment> controllerAttachment;
    std::unique_ptr<juce::SliderParameterAttachment> valueAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MidiCCToolAudioProcessorEditor)
};