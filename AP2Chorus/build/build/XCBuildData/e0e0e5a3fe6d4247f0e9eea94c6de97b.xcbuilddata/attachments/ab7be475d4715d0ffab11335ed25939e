#!/bin/sh
set -e
if test "$CONFIGURATION" = "Debug"; then :
  cd /Users/cj/Documents/vstplugins/AP2Chorus/build/vst3sdk/public.sdk/samples/vst-hosting/validator
  codesign --force --verbose --sign - /Users/cj/Documents/vstplugins/AP2Chorus/build/bin/Debug/validator
  cd /Users/cj/Documents/vstplugins/AP2Chorus/build/vst3sdk/public.sdk/samples/vst-hosting/validator
  /Users/cj/Documents/vstplugins/AP2Chorus/build/bin/Debug/validator -selftest
fi
if test "$CONFIGURATION" = "Release"; then :
  cd /Users/cj/Documents/vstplugins/AP2Chorus/build/vst3sdk/public.sdk/samples/vst-hosting/validator
  codesign --force --verbose --sign - /Users/cj/Documents/vstplugins/AP2Chorus/build/bin/Release/validator
  cd /Users/cj/Documents/vstplugins/AP2Chorus/build/vst3sdk/public.sdk/samples/vst-hosting/validator
  /Users/cj/Documents/vstplugins/AP2Chorus/build/bin/Release/validator -selftest
fi

