//------------------------------------------------------------------------
// Copyright(c) 2023 .
//------------------------------------------------------------------------

#pragma once

#include "pluginterfaces/base/funknown.h"
#include "pluginterfaces/vst/vsttypes.h"

namespace MyCompanyName {
//------------------------------------------------------------------------
static const Steinberg::FUID kChorusEffectProcessorUID (0x912AED3E, 0x9095530B, 0x8A4AFE7F, 0x1DA13A52);
static const Steinberg::FUID kChorusEffectControllerUID (0xDEBA44A8, 0x9DF45FFC, 0xA4F484A9, 0x4CDC85F0);

#define ChorusEffectVST3Category "Fx"

//------------------------------------------------------------------------
} // namespace MyCompanyName
