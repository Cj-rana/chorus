#pragma once

#include "public.sdk/source/vst/vsteditcontroller.h"

class ChorusEffectController : public Steinberg::Vst::EditController
{
public:
    // EditController overrides
    tresult PLUGIN_API initialize(Steinberg::FUnknown* context) SMTG_OVERRIDE;
    tresult PLUGIN_API terminate() SMTG_OVERRIDE;
    tresult PLUGIN_API setComponentState(Steinberg::IBStream* state) SMTG_OVERRIDE;
    Steinberg::IPlugView* PLUGIN_API createView(Steinberg::FIDString name) SMTG_OVERRIDE;
    tresult PLUGIN_API setState(Steinberg::IBStream* state) SMTG_OVERRIDE;
    tresult PLUGIN_API getState(Steinberg::IBStream* state) SMTG_OVERRIDE;

    static Steinberg::FUnknown* createInstance(void* context);
};
