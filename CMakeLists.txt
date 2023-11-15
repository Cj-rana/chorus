cmake_minimum_required(VERSION 3.14.0)
set(CMAKE_OSX_DEPLOYMENT_TARGET 10.13 CACHE STRING "")

set(vst3sdk_SOURCE_DIR "/Users/cj/Documents/VST_SDK/vst3sdk")
if(NOT vst3sdk_SOURCE_DIR)
    message(FATAL_ERROR "Path to VST3 SDK is empty!")
endif()

project(ChorusEffect
    # This is your plug-in version number. Change it here only.
    # Version number symbols usable in C++ can be found in
    # source/version.h and ${PROJECT_BINARY_DIR}/projectversion.h.
    VERSION 1.0.0.0 
    DESCRIPTION "ChorusEffect VST 3 Plug-in"
)

set(SMTG_VSTGUI_ROOT "${vst3sdk_SOURCE_DIR}")

add_subdirectory(${vst3sdk_SOURCE_DIR} ${PROJECT_BINARY_DIR}/vst3sdk)
smtg_enable_vst3_sdk()

smtg_add_vst3plugin(ChorusEffect
    source/version.h
    source/cids.h
    source/processor.h
    source/processor.cpp
    source/controller.h
    source/controller.cpp
    source/entry.cpp
)

#- VSTGUI Wanted ----
if(SMTG_ENABLE_VSTGUI_SUPPORT)
    target_sources(ChorusEffect
        PRIVATE
            resource/editor.uidesc
    )
    target_link_libraries(ChorusEffect
        PRIVATE
            vstgui_support
    )
    smtg_target_add_plugin_resources(ChorusEffect
        RESOURCES
            "resource/editor.uidesc"
    )
endif(SMTG_ENABLE_VSTGUI_SUPPORT)
# -------------------

smtg_target_add_plugin_snapshots (ChorusEffect
    RESOURCES
        resource/912AED3E9095530B8A4AFE7F1DA13A52_snapshot.png
        resource/912AED3E9095530B8A4AFE7F1DA13A52_snapshot_2.0x.png
)

target_link_libraries(ChorusEffect
    PRIVATE
        sdk
)

smtg_target_configure_version_file(ChorusEffect)

if(SMTG_MAC)
    smtg_target_set_bundle(ChorusEffect
        BUNDLE_IDENTIFIER chorus
        COMPANY_NAME ""
    )
    smtg_target_set_debug_executable(ChorusEffect
        "/Applications/VST3PluginTestHost.app"
        "--pluginfolder;$(BUILT_PRODUCTS_DIR)"
    )
elseif(SMTG_WIN)
    target_sources(ChorusEffect PRIVATE 
        resource/win32resource.rc
    )
    if(MSVC)
        set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ChorusEffect)

        smtg_target_set_debug_executable(ChorusEffect
            "$(ProgramW6432)/Steinberg/VST3PluginTestHost/VST3PluginTestHost.exe"
            "--pluginfolder \"$(OutDir)/\""
        )
    endif()
endif(SMTG_MAC)
