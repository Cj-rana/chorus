//------------------------------------------------------------------------
// Copyright(c) 2023 My Plug-in Company.
//------------------------------------------------------------------------

#pragma once

#include "pluginterfaces/base/funknown.h"
#include "pluginterfaces/vst/vsttypes.h"

namespace MyCompanyName {
//------------------------------------------------------------------------
static const Steinberg::FUID kAP2ChorusProcessorUID (0x67823860, 0xB68B59EF, 0x867DD695, 0x8141E70A);
static const Steinberg::FUID kAP2ChorusControllerUID (0xF74D0DDA, 0x7C9E542F, 0xB96F51E9, 0x482A082B);

#define AP2ChorusVST3Category "Fx"

//------------------------------------------------------------------------
} // namespace MyCompanyName

enum ChorusParams : Steinberg::Vst::ParamID
{
    kParamRateId = 102, // should be a unique id...
    kParamDepthId = 103,
    kParamMixId = 104,
    kParamFeedbackId = 105,

};