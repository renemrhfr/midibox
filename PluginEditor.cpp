#include "PluginEditor.h"

MidiCCToolAudioProcessorEditor::MidiCCToolAudioProcessorEditor(MidiCCToolAudioProcessor& p)
        : AudioProcessorEditor(&p), processor(p)
{
    titleLabel.setFont(juce::Font(28.0f, juce::Font::bold));
    titleLabel.setText("MIDI BOX", juce::dontSendNotification);
    titleLabel.setJustificationType(juce::Justification::left);
    addAndMakeVisible(titleLabel);

    subtitleLabel.setFont(juce::Font(16.0f));
    subtitleLabel.setText("MIDI CC Controller", juce::dontSendNotification);
    subtitleLabel.setJustificationType(juce::Justification::left);
    subtitleLabel.setColour(juce::Label::textColourId, juce::Colours::white.withAlpha(0.7f));
    addAndMakeVisible(subtitleLabel);

    copyrightLabel.setFont(juce::Font(12.0f));
    copyrightLabel.setText("0.0.2 by renemrhfr", juce::dontSendNotification);
    copyrightLabel.setColour(juce::Label::textColourId, juce::Colour(245, 158, 11));
    copyrightLabel.setJustificationType(juce::Justification::right);
    addAndMakeVisible(copyrightLabel);

    channelLabel.setFont(juce::Font(20.0f, juce::Font::bold));
    channelLabel.setText("CHANNEL", juce::dontSendNotification);
    channelLabel.setJustificationType(juce::Justification::left);
    channelLabel.setColour(juce::Label::textColourId, juce::Colour(245, 158, 11));
    addAndMakeVisible(channelLabel);

    channelSlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    channelSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 20);
    channelSlider.setRange(1.0, 16.0, 1.0);
    channelSlider.setValue(1);
    channelSlider.setLookAndFeel(&channelLookAndFeel);
    channelSlider.setNumDecimalPlacesToDisplay(0);
    addAndMakeVisible(channelSlider);

    controllerLabel.setFont(juce::Font(20.0f, juce::Font::bold));
    controllerLabel.setText("CONTROL", juce::dontSendNotification);
    controllerLabel.setJustificationType(juce::Justification::left);
    controllerLabel.setColour(juce::Label::textColourId, juce::Colour(239, 68, 68));
    addAndMakeVisible(controllerLabel);

    controllerSlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    controllerSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 20);
    controllerSlider.setRange(0.0, 127.0, 1.0);
    controllerSlider.setValue(127);
    controllerSlider.setLookAndFeel(&controllerLookAndFeel);
    controllerSlider.setNumDecimalPlacesToDisplay(0);
    addAndMakeVisible(controllerSlider);

    valueLabel.setFont(juce::Font(20.0f, juce::Font::bold));
    valueLabel.setText("VALUE", juce::dontSendNotification);
    valueLabel.setJustificationType(juce::Justification::left);
    valueLabel.setColour(juce::Label::textColourId, juce::Colour(59, 130, 246));
    addAndMakeVisible(valueLabel);

    valueSlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    valueSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 20);
    valueSlider.setRange(0.0, 127.0, 1.0);
    valueSlider.setValue(127);
    valueSlider.setLookAndFeel(&valueLookAndFeel);
    valueSlider.setNumDecimalPlacesToDisplay(0);
    addAndMakeVisible(valueSlider);

    // Setup parameter attachments
    auto const& params = processor.getParameters();
    channelAttachment = std::make_unique<juce::SliderParameterAttachment>(
            *params.getParameter("channel"),
            channelSlider
    );

    controllerAttachment = std::make_unique<juce::SliderParameterAttachment>(
            *params.getParameter("controller"),
            controllerSlider
    );

    valueAttachment = std::make_unique<juce::SliderParameterAttachment>(
            *params.getParameter("value"),
            valueSlider
    );

    // Window setup - maximally reduced height
    setSize(500, 185);
}

MidiCCToolAudioProcessorEditor::~MidiCCToolAudioProcessorEditor()
{
    channelSlider.setLookAndFeel(nullptr);
    controllerSlider.setLookAndFeel(nullptr);
    valueSlider.setLookAndFeel(nullptr);
}

void MidiCCToolAudioProcessorEditor::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colour(28, 25, 23));
    auto drawPanel = [&](juce::Rectangle<int> const& area, juce::Colour accentColor) {
        g.setColour(juce::Colour(39, 35, 33));
        g.fillRoundedRectangle(area.toFloat(), 8.0f);
        g.setColour(accentColor.withAlpha(0.3f));
        g.drawRoundedRectangle(area.toFloat(), 8.0f, 1.0f);
    };
    drawPanel(channelArea, juce::Colour(245, 158, 11));
    drawPanel(controllerArea, juce::Colour(239, 68, 68));
    drawPanel(valueArea, juce::Colour(59, 130, 246));
}

void MidiCCToolAudioProcessorEditor::resized()
{
    auto bounds = getLocalBounds();
    auto headerSection = bounds.removeFromTop(50);
    headerSection = headerSection.reduced(20, 5);

    auto titleArea = headerSection.removeFromLeft(250);
    titleLabel.setBounds(titleArea.removeFromTop(25));
    subtitleLabel.setBounds(titleArea);

    copyrightLabel.setBounds(getWidth() - 120, getHeight() - 15, 110, 12);

    bounds = bounds.reduced(20, 0);
    int panelWidth = (bounds.getWidth() - 20) / 3;  // 20 = 2 gaps of 10px
    int panelHeight = 110; // Panel height

    bounds.removeFromTop(0);
    auto layoutPanel = [](juce::Rectangle<int> area, juce::Label& label, juce::Slider& slider) {
        const int labelHeight = 25;
        const int sliderHeight = 30;
        const int spacing = 5;
        label.setBounds(area.removeFromTop(labelHeight));
        area.removeFromTop(spacing);
        slider.setBounds(area.removeFromTop(sliderHeight + 25));
    };

    channelArea = bounds.removeFromLeft(panelWidth).withHeight(panelHeight);
    layoutPanel(channelArea.reduced(10), channelLabel, channelSlider);
    bounds.removeFromLeft(10);  // Reduced gap

    controllerArea = bounds.removeFromLeft(panelWidth).withHeight(panelHeight);
    layoutPanel(controllerArea.reduced(10), controllerLabel, controllerSlider);
    bounds.removeFromLeft(10);

    valueArea = bounds.withHeight(panelHeight);
    layoutPanel(valueArea.reduced(10), valueLabel, valueSlider);
}