cmake_minimum_required(VERSION 3.22)

project(MidiBox VERSION 0.0.1)

# Use a consistent path to JUCE
add_subdirectory("../../JUCENEW/JUCE" "JUCE-bin")

juce_add_plugin(MidiBox
        COMPANY_NAME "renemrhfr"
        IS_SYNTH FALSE
        NEEDS_MIDI_INPUT TRUE
        NEEDS_MIDI_OUTPUT TRUE
        IS_MIDI_EFFECT TRUE
        VST3_CATEGORIES "Midi" "Tools"
        EDITOR_WANTS_KEYBOARD_FOCUS FALSE
        COPY_PLUGIN_AFTER_BUILD TRUE
        PLUGIN_MANUFACTURER_CODE Locu
        PLUGIN_CODE Lrbr
        FORMATS VST3 Standalone
        PRODUCT_NAME "MidiBox")

juce_generate_juce_header(MidiBox)

# Set macOS deployment target if on Apple platform
if(APPLE)
    set(CMAKE_OSX_DEPLOYMENT_TARGET "10.13" CACHE STRING "Minimum OS X deployment version" FORCE)

    # Define bundle locations for post-build commands
    set(VST3_BUNDLE_DIR "${CMAKE_BINARY_DIR}/MidiBox_artefacts/${CMAKE_BUILD_TYPE}/VST3/MidiBox.vst3")
    set(STANDALONE_BUNDLE_DIR "${CMAKE_BINARY_DIR}/MidiBox_artefacts/${CMAKE_BUILD_TYPE}/Standalone/MidiBox.app")

    # Custom commands for signing bundles with direct path references
    add_custom_command(TARGET MidiBox_VST3 POST_BUILD
            COMMAND codesign --force --deep -s - "${VST3_BUNDLE_DIR}"
            COMMENT "Ad-hoc signing VST3 bundle for development"
    )

    add_custom_command(TARGET MidiBox_Standalone POST_BUILD
            COMMAND codesign --force --deep -s - "${STANDALONE_BUNDLE_DIR}"
            COMMENT "Ad-hoc signing Standalone bundle for development"
    )

    # Set bundle properties
    set_target_properties(MidiBox_VST3 PROPERTIES
            BUNDLE TRUE
            BUNDLE_EXTENSION "vst3"
            XCODE_ATTRIBUTE_WRAPPER_EXTENSION "vst3"
            XCODE_ATTRIBUTE_GENERATE_PKGINFO_FILE "YES"
            XCODE_ATTRIBUTE_PRODUCT_NAME "MidiBox"
            XCODE_ATTRIBUTE_BUNDLE_IDENTIFIER "com.renemrhfr.MidiBox"
            MACOSX_BUNDLE_GUI_IDENTIFIER "com.renemrhfr.MidiBox"
            MACOSX_BUNDLE_BUNDLE_VERSION "${PROJECT_VERSION}"
            MACOSX_BUNDLE_SHORT_VERSION_STRING "${PROJECT_VERSION}")
endif()

target_sources(MidiBox
        PRIVATE
        PluginEditor.cpp
        PluginProcessor.cpp)

target_compile_definitions(MidiBox
        PUBLIC
        JUCE_WEB_BROWSER=0
        JUCE_USE_CURL=0
        JUCE_VST3_CAN_REPLACE_VST2=0)

target_link_libraries(MidiBox
        PRIVATE
        juce::juce_audio_utils
        PUBLIC
        juce::juce_dsp
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags)