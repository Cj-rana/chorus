cmake_minimum_required(VERSION 3.14.0)
set(CMAKE_OSX_DEPLOYMENT_TARGET 10.13 CACHE STRING "")

set(vst3sdk_SOURCE_DIR "C:/Users/Etienne Quartey-Papa/Downloads/vst-sdk_3.7.9_build-61_2023-10-09/VST_SDK/vst3sdk")
if(NOT vst3sdk_SOURCE_DIR)
    message(FATAL_ERROR "Path to VST3 SDK is empty!")
endif()

project(AP2Chorus
    # This is your plug-in version number. Change it here only.
    # Version number symbols usable in C++ can be found in
    # source/version.h and ${PROJECT_BINARY_DIR}/projectversion.h.
    VERSION 1.0.0.0 
    DESCRIPTION "AP2Chorus VST 3 Plug-in"
)

set(SMTG_VSTGUI_ROOT "${vst3sdk_SOURCE_DIR}")

add_subdirectory(${vst3sdk_SOURCE_DIR} ${PROJECT_BINARY_DIR}/vst3sdk)
smtg_enable_vst3_sdk()

smtg_add_vst3plugin(AP2Chorus
    source/version.h
    source/myplugincids.h
    source/mypluginprocessor.h
    source/mypluginprocessor.cpp
    source/myplugincontroller.h
    source/myplugincontroller.cpp
    source/mypluginentry.cpp
)

#- VSTGUI Wanted ----
if(SMTG_ENABLE_VSTGUI_SUPPORT)
    target_sources(AP2Chorus
        PRIVATE
            resource/myplugineditor.uidesc
    )
    target_link_libraries(AP2Chorus
        PRIVATE
            vstgui_support
    )
    smtg_target_add_plugin_resources(AP2Chorus
        RESOURCES
            "resource/myplugineditor.uidesc"
    )
endif(SMTG_ENABLE_VSTGUI_SUPPORT)
# -------------------

smtg_target_add_plugin_snapshots (AP2Chorus
    RESOURCES
        resource/67823860B68B59EF867DD6958141E70A_snapshot.png
        resource/67823860B68B59EF867DD6958141E70A_snapshot_2.0x.png
)

target_link_libraries(AP2Chorus
    PRIVATE
        sdk
)

smtg_target_configure_version_file(AP2Chorus)

if(SMTG_MAC)
    smtg_target_set_bundle(AP2Chorus
        BUNDLE_IDENTIFIER com.ap2.chorus
        COMPANY_NAME "My Plug-in Company"
    )
    smtg_target_set_debug_executable(AP2Chorus
        "/Applications/VST3PluginTestHost.app"
        "--pluginfolder;$(BUILT_PRODUCTS_DIR)"
    )
elseif(SMTG_WIN)
    target_sources(AP2Chorus PRIVATE 
        resource/win32resource.rc
    )
    if(MSVC)
        set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT AP2Chorus)

        smtg_target_set_debug_executable(AP2Chorus
            "$(ProgramW6432)/Steinberg/VST3PluginTestHost/VST3PluginTestHost.exe"
            "--pluginfolder \"$(OutDir)/\""
        )
    endif()
endif(SMTG_MAC)
