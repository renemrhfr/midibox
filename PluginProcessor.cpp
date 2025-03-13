#include "PluginProcessor.h"
#include "PluginEditor.h"

MidiCCToolAudioProcessor::MidiCCToolAudioProcessor()
        : parameters(*this, nullptr, "Parameters", {
        std::make_unique<juce::AudioParameterInt>("channel", "MIDI Channel", 1.0f, 16.0f, 1.0f),
        std::make_unique<juce::AudioParameterInt>("controller", "Controller Number", 0.0f, 127.0f, 58.0f),
        std::make_unique<juce::AudioParameterInt>("value", "Value", 0.0f, 127.0f, 1.0f)
})
{
    // No need to manually add parameters
}

MidiCCToolAudioProcessor::~MidiCCToolAudioProcessor() = default;

void MidiCCToolAudioProcessor::processBlock(juce::AudioBuffer<float>& buffer,
                                            juce::MidiBuffer& midiMessages)
{
    // First, check if processing is suspended
    if (isSuspended()) {
        return;
    }

    // Collect incoming Midi Info
    juce::MidiBuffer tempMidi;
    for (const auto metadata : midiMessages)
    {
        tempMidi.addEvent(metadata.getMessage(), metadata.samplePosition);
    }

    // Add our own Message
    auto const* channelParam = parameters.getRawParameterValue("channel");
    auto const* controllerParam = parameters.getRawParameterValue("controller");
    auto const* valueParam = parameters.getRawParameterValue("value");

    auto channel = static_cast<int>(*channelParam);
    auto controller = static_cast<int>(*controllerParam);
    auto value = static_cast<int>(*valueParam);

    tempMidi.addEvent(juce::MidiMessage::controllerEvent(channel, controller, value), 0);
    midiMessages.swapWith(tempMidi);
}

juce::AudioProcessorEditor* MidiCCToolAudioProcessor::createEditor()
{
    return new MidiCCToolAudioProcessorEditor(*this);
}

void MidiCCToolAudioProcessor::getStateInformation(juce::MemoryBlock& destData)
{
    auto state = parameters.copyState();
    std::unique_ptr<juce::XmlElement> xml(state.createXml());
    copyXmlToBinary(*xml, destData);
}

void MidiCCToolAudioProcessor::setStateInformation(const void* data, int sizeInBytes)
{
    std::unique_ptr<juce::XmlElement> xml(getXmlFromBinary(data, sizeInBytes));
    if (xml != nullptr) {
        parameters.replaceState(juce::ValueTree::fromXml(*xml));
    }
}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new MidiCCToolAudioProcessor();
}