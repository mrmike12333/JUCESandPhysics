cmake_minimum_required(VERSION 3.22)

project(
    SandPhysics
    VERSION 0.0.1
    DESCRIPTION "A sand physics program written in JUCE"
    )

add_subdirectory(JUCE)

juce_add_gui_app(SandPhysics
    PRODUCT_NAME "Sand Physics App"
    )

target_sources(SandPhysics
    PRIVATE
        src/Main.cpp
        src/MainComponent.cpp
        src/SandComponent.cpp
    )

target_compile_definitions(SandPhysics
    PRIVATE
        JUCE_WEB_BROWSER=0
        JUCE_USE_CURL=0
        JUCE_APPLICATION_NAME_STRING="$<TARGET_PROPERTY:SandPhysics,JUCE_PRODUCT_NAME>"
        JUCE_APPLICATION_VERSION_STRING="$<TARGET_PROPERTY:SandPhysics,JUCE_VERSION>")

target_link_libraries(SandPhysics
    PRIVATE
        juce::juce_gui_extra
    PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags
    )