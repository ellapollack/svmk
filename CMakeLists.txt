cmake_minimum_required(VERSION 3.7.2)

project(SVMK VERSION 0.0.1)

add_subdirectory(JUCE)

juce_add_console_app(svmk
    PRODUCT_NAME "svmk"
    MICROPHONE_PERMISSION_ENABLED TRUE
    )

juce_generate_juce_header(svmk)

target_sources(svmk PRIVATE
    svmk.cpp
    UIThread.cpp)

target_compile_definitions(svmk PRIVATE
    JUCE_WEB_BROWSER=0
    JUCE_USE_CURL=0)

target_link_libraries(svmk PRIVATE
    juce::juce_core
    juce::juce_audio_utils)

set_target_properties(svmk PROPERTIES CXX_STANDARD 17)