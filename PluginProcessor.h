#pragma once
#include <JuceHeader.h>

class MidiCCToolAudioProcessor : public juce::AudioProcessor
{
public:
    MidiCCToolAudioProcessor();
    ~MidiCCToolAudioProcessor() override;

    void prepareToPlay(double, int) override {}
    void releaseResources() override {}
    void processBlock(juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    bool isMidiEffect() const override { return true; }
    double getTailLengthSeconds() const override { return 0.0; }

    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override { return true; }

    const juce::String getName() const override { return JucePlugin_Name; }
    bool acceptsMidi() const override { return true; }
    bool producesMidi() const override { return true; }

    int getNumPrograms() override { return 1; }
    int getCurrentProgram() override { return 0; }
    void setCurrentProgram(int) override {}
    const juce::String getProgramName(int) override { return {}; }
    void changeProgramName(int, const juce::String&) override {}

    void getStateInformation(juce::MemoryBlock& destData) override;
    void setStateInformation(const void* data, int sizeInBytes) override;

    void sendMidiCC();

    juce::AudioProcessorValueTreeState& getParameters() { return parameters; }

private:
    juce::AudioProcessorValueTreeState parameters;

    bool isPlaying = false;
    bool lastActiveState = true;  // Track the last active state

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MidiCCToolAudioProcessor)

    void suspendProcessing(bool shouldSuspend);
};