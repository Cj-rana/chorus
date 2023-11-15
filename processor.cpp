#pragma once

#include "public.sdk/source/vst/vstaudioeffect.h"
#include "ChorusEffectProcessor.h"

MyPluginProcessor::MyPluginProcessor()
    : sampleRate(44100.0), frequency(440.0), amplitude(0.5), phase(0.0), delayTime(500.0), writeIndex(0)
{
    // Initialize the delay buffer with zeros (replace with your own initialization logic)
    delayBuffer.resize(static_cast<size_t>(sampleRate * delayTime / 1000.0), 0.0);
}

MyPluginProcessor::~ChorusEffectProcessor()
{
}

tresult PLUGIN_API ChorusEffectProcessor::initialize(Steinberg::FUnknown* context)
{
    // Initialize the AudioEffect base class
    tresult result = AudioEffect::initialize(context);
    if (result != kResultOk)
        return result;

    // Initialize any additional parameters or settings here

    return kResultOk;
}

tresult PLUGIN_API ChorusEffectProcessor::terminate()
{
    // Clean up resources
    delayBuffer.clear();

    // Terminate the AudioEffect base class
    return AudioEffect::terminate();
}

tresult PLUGIN_API ChorusEffectProcessor::setActive(Steinberg::TBool state)
{
    // Handle activation and deactivation
    return AudioEffect::setActive(state);
}

tresult PLUGIN_API ChorusEffectProcessor::process(Steinberg::Vst::ProcessData& data)
{
    // Process audio data here
    if (data.numInputs == 0 || data.numSamples == 0)
        return kResultOk;

    // Process each channel separately
    for (int32 channel = 0; channel < data.numChannels; ++channel)
    {
        Steinberg::Vst::Sample32* inBuffer = (Steinberg::Vst::Sample32*)data.inputs[channel].channelBuffers32;
        Steinberg::Vst::Sample32* outBuffer = (Steinberg::Vst::Sample32*)data.outputs[channel].channelBuffers32;

        for (int32 i = 0; i < data.numSamples; ++i)
        {
            // Generate sine wave
            double inputSample = generateSineWave();

            // Apply delay
            processDelay(outBuffer, i);

            // Mix the original and delayed signals
            outBuffer[i] += static_cast<Steinberg::Vst::Sample32>(inputSample);

            // Update write index for the circular buffer
            writeIndex = (writeIndex + 1) % delayBuffer.size();
        }
    }

    return kResultOk;
}

double ChorusEffectProcessor::generateSineWave()
{
    double sample = amplitude * std::sin(2.0 * M_PI * frequency * phase / sampleRate);
    phase += 1.0;
    if (phase >= sampleRate)
        phase -= sampleRate;
    return sample;
}

void ChorusEffectProcessor::processDelay(Steinberg::Vst::Sample32* buffer, int32 index)
{
    // Read delayed sample from circular buffer
    size_t readIndex = (writeIndex + delayBuffer.size() - static_cast<size_t>(delayTime * sampleRate / 1000.0)) % delayBuffer.size();
    Steinberg::Vst::Sample32 delayedSample = delayBuffer[readIndex];

    // Write current sample to circular buffer
    delayBuffer[writeIndex] = buffer[index];
}

tresult PLUGIN_API ChorusEffectProcessor::setState(Steinberg::IBStream* state)
{
    // Save the plugin state (if needed)
    return kResultOk;
}

tresult PLUGIN_API ChorusEffectProcessor::getState(Steinberg::IBStream* state)
{
    // Load the plugin state (if needed)
    return kResultOk;
}

tresult PLUGIN_API ChorusEffectProcessor::setParamNormalized(Steinberg::Vst::ParamID tag, Steinberg::Vst::ParamValue value)
{
    // Handle parameter changes
    switch (tag)
    {
        case kParamFrequencyId:
            frequency = 20.0 + value * 1980.0; // Adjust to desired frequency range
            break;

        case kParamAmplitudeId:
            amplitude = value;
            break;

        case kParamDelayTimeId:
            delayTime = 10.0 + value * 990.0; // Adjust to desired delay time range
            break;

        default:
            break;
    }

    return kResultOk;
}

tresult PLUGIN_API ChorusEffectProcessor::getParamStringByValue(Steinberg::Vst::ParamID tag, Steinberg::Vst::ParamValue valueNormalized, Steinberg::Vst::String128 string)
{
    // Convert parameter value to string (if needed)
    return kResultOk;
}

tresult PLUGIN_API ChorusEffectProcessor::getParamValueByString(Steinberg::Vst::ParamID tag, Steinberg::Vst::TChar* string, Steinberg::Vst::ParamValue& valueNormalized)
{
    // Convert string to parameter value (if needed)
    return kResultOk;
}

static const Steinberg::FUID ChorusEffectProcessorUID(0x12345678, 0x9ABCDEF0, 0xABCDEF01, 0x23456789);

// Factory function for creating an instance of the processor
Steinberg::FUnknown* ChorusEffectProcessor::createInstance(void* context)
{
    return static_cast<Steinberg::IAudioProcessor*>(new MyPluginProcessor);
}
