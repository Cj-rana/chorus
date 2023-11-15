#pragma once

#include "public.sdk/source/vst/vstaudioeffect.h"
#include <vector>

class ChorusEffectProcessor : public Steinberg::Vst::AudioEffect
{
public:
    ChorusEffectProcessor();
    ~ChorusEffectProcessor();

    // AudioEffect overrides
    tresult PLUGIN_API initialize(Steinberg::FUnknown* context) SMTG_OVERRIDE;
    tresult PLUGIN_API terminate() SMTG_OVERRIDE;
    tresult PLUGIN_API setActive(Steinberg::TBool state) SMTG_OVERRIDE;
    tresult PLUGIN_API process(Steinberg::Vst::ProcessData& data) SMTG_OVERRIDE;
    tresult PLUGIN_API setState(Steinberg::IBStream* state) SMTG_OVERRIDE;
    tresult PLUGIN_API getState(Steinberg::IBStream* state) SMTG_OVERRIDE;
    tresult PLUGIN_API setParamNormalized(Steinberg::Vst::ParamID tag, Steinberg::Vst::ParamValue value) SMTG_OVERRIDE;
    tresult PLUGIN_API getParamStringByValue(Steinberg::Vst::ParamID tag, Steinberg::Vst::ParamValue valueNormalized, Steinberg::Vst::String128 string) SMTG_OVERRIDE;
    tresult PLUGIN_API getParamValueByString(Steinberg::Vst::ParamID tag, Steinberg::Vst::TChar* string, Steinberg::Vst::ParamValue& valueNormalized) SMTG_OVERRIDE;

    static Steinberg::FUnknown* createInstance(void* context);

    // Custom methods for generating sine wave and applying delay
    double generateSineWave();
    void processDelay(Steinberg::Vst::Sample32* buffer, int32 numSamples);

private:
    double sampleRate;
    double frequency;
    double amplitude;
    double phase;
    double delayTime;
    std::vector<Steinberg::Vst::Sample32> delayBuffer;
    size_t writeIndex;
};
