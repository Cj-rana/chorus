#!/bin/sh
set -e
if test "$CONFIGURATION" = "Debug"; then :
  cd /Users/cj/Documents/vstplugins/AP2Chorus/build
  codesign --force --verbose --sign - /Users/cj/Documents/vstplugins/AP2Chorus/build/VST3/Debug/AP2Chorus.vst3
  cd /Users/cj/Documents/vstplugins/AP2Chorus/build/bin
  /Users/cj/Documents/vstplugins/AP2Chorus/build/bin/Debug/moduleinfotool -create -version 1.0.0.0 -path /Users/cj/Documents/vstplugins/AP2Chorus/build/VST3/Debug/AP2Chorus.vst3 -output /Users/cj/Documents/vstplugins/AP2Chorus/build/VST3/Debug/AP2Chorus.vst3/Contents/Resources/moduleinfo.json
  cd /Users/cj/Documents/vstplugins/AP2Chorus/build/bin
  codesign -f -s - -v /Users/cj/Documents/vstplugins/AP2Chorus/build/VST3/Debug/AP2Chorus.vst3/Contents/Resources/moduleinfo.json
  cd /Users/cj/Documents/vstplugins/AP2Chorus/build/bin
  /Users/cj/Documents/vstplugins/AP2Chorus/build/bin/Debug/validator /Users/cj/Documents/vstplugins/AP2Chorus/build/VST3/Debug/AP2Chorus.vst3 
  cd /Users/cj/Documents/vstplugins/AP2Chorus/build
  /Applications/CMake.app/Contents/bin/cmake -E make_directory /Users/cj/Library/Audio/Plug-Ins/VST3
  ln -svfF /Users/cj/Documents/vstplugins/AP2Chorus/build/VST3/Debug/AP2Chorus.vst3 /Users/cj/Library/Audio/Plug-Ins/VST3
fi
if test "$CONFIGURATION" = "Release"; then :
  cd /Users/cj/Documents/vstplugins/AP2Chorus/build
  codesign --force --verbose --sign - /Users/cj/Documents/vstplugins/AP2Chorus/build/VST3/Release/AP2Chorus.vst3
  cd /Users/cj/Documents/vstplugins/AP2Chorus/build/bin
  /Users/cj/Documents/vstplugins/AP2Chorus/build/bin/Release/moduleinfotool -create -version 1.0.0.0 -path /Users/cj/Documents/vstplugins/AP2Chorus/build/VST3/Release/AP2Chorus.vst3 -output /Users/cj/Documents/vstplugins/AP2Chorus/build/VST3/Release/AP2Chorus.vst3/Contents/Resources/moduleinfo.json
  cd /Users/cj/Documents/vstplugins/AP2Chorus/build/bin
  codesign -f -s - -v /Users/cj/Documents/vstplugins/AP2Chorus/build/VST3/Release/AP2Chorus.vst3/Contents/Resources/moduleinfo.json
  cd /Users/cj/Documents/vstplugins/AP2Chorus/build/bin
  /Users/cj/Documents/vstplugins/AP2Chorus/build/bin/Release/validator  /Users/cj/Documents/vstplugins/AP2Chorus/build/VST3/Release/AP2Chorus.vst3
  cd /Users/cj/Documents/vstplugins/AP2Chorus/build
  /Applications/CMake.app/Contents/bin/cmake -E make_directory /Users/cj/Library/Audio/Plug-Ins/VST3
  ln -svfF /Users/cj/Documents/vstplugins/AP2Chorus/build/VST3/Release/AP2Chorus.vst3 /Users/cj/Library/Audio/Plug-Ins/VST3
fi

