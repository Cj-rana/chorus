//------------------------------------------------------------------------
// Copyright(c) 2023 .
//------------------------------------------------------------------------

#pragma once

#include "pluginterfaces/base/funknown.h"
#include "pluginterfaces/vst/vsttypes.h"

namespace MyCompanyName {
//------------------------------------------------------------------------
static const Steinberg::FUID kAP2ChorusProcessorUID (0xCAEF7E4A, 0x3B4B59E5, 0x9A24F993, 0xF76D1923);
static const Steinberg::FUID kAP2ChorusControllerUID (0xCA5C47DA, 0xE7F45288, 0x8065C5B6, 0x506BE3A2);

#define AP2ChorusVST3Category "Fx"

//------------------------------------------------------------------------
} // namespace MyCompanyName
enum ChorusParams : Steinberg::Vst::ParamID
{
    kParamRateId = 102, // should be a unique id...
    kParamDepthId = 103,
};
