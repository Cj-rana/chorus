//------------------------------------------------------------------------
// Copyright(c) 2023 .
//------------------------------------------------------------------------

#include "processor.h"
#include "cids.h"

#include "base/source/fstreamer.h"
#include "pluginterfaces/vst/ivstparameterchanges.h"
#include "public.sdk/source/vst/vstaudioprocessoralgo.h"

using namespace Steinberg;
float gain = 1.0f; // or whatever value you want to use


namespace MyCompanyName {
//------------------------------------------------------------------------
// AP2ChorusProcessor
//------------------------------------------------------------------------
AP2ChorusProcessor::AP2ChorusProcessor ()
{
	//--- set the wanted controller for our processor
	setControllerClass (kAP2ChorusControllerUID);
}

//------------------------------------------------------------------------
AP2ChorusProcessor::~AP2ChorusProcessor ()
{}

//------------------------------------------------------------------------
tresult PLUGIN_API AP2ChorusProcessor::initialize (FUnknown* context)
{
	// Here the Plug-in will be instantiated
	
	//---always initialize the parent-------
	tresult result = AudioEffect::initialize (context);
	// if everything Ok, continue
	if (result != kResultOk)
	{
		return result;
	}

	//--- create Audio IO ------
	addAudioInput (STR16 ("Stereo In"), Steinberg::Vst::SpeakerArr::kStereo);
	addAudioOutput (STR16 ("Stereo Out"), Steinberg::Vst::SpeakerArr::kStereo);

	/* If you don't need an event bus, you can remove the next line */
	addEventInput (STR16 ("Event In"), 1);

	return kResultOk;
}

//------------------------------------------------------------------------
tresult PLUGIN_API AP2ChorusProcessor::terminate ()
{
	// Here the Plug-in will be de-instantiated, last possibility to remove some memory!
	
	//---do not forget to call parent ------
	return AudioEffect::terminate ();
}

//------------------------------------------------------------------------
tresult PLUGIN_API AP2ChorusProcessor::setActive (TBool state)
{
	//--- called when the Plug-in is enable/disable (On/Off) -----
	return AudioEffect::setActive (state);
}

//------------------------------------------------------------------------
tresult PLUGIN_API AP2ChorusProcessor::process (Vst::ProcessData& data)
{
	//--- First : Read inputs parameter changes-----------

    
    if (data.inputParameterChanges)
    {
        int32 numParamsChanged = data.inputParameterChanges->getParameterCount ();
        for (int32 index = 0; index < numParamsChanged; index++)
        {
            if (auto* paramQueue = data.inputParameterChanges->getParameterData (index))
            {
                Vst::ParamValue value;
                int32 sampleOffset;
                int32 numPoints = paramQueue->getPointCount ();
                switch (paramQueue->getParameterId ())
                {
                    case ChorusParams::kParamRateId:
                                        if (paramQueue->getPoint(numPoints - 1, sampleOffset, value) == kResultTrue)
                                            mRate = value;
                                        break;

                                    case ChorusParams::kParamDepthId:
                                        if (paramQueue->getPoint(numPoints - 1, sampleOffset, value) == kResultTrue)
                                            mDepth = value;
                                        break;
				}
			}
		}
	}
	
	//--- Here you have to implement your processing
    if (data.numInputs == 0 || data.numSamples == 0)
        return kResultOk;
    int32 numChannels = data.inputs[0].numChannels;

        //---get audio buffers using helper-functions(vstaudioprocessoralgo.h)-------------
        uint32 sampleFramesSize = getSampleFramesSizeInBytes(processSetup, data.numSamples);
        void** in = getChannelBuffersPointer(processSetup, data.inputs[0]);
        void** out = getChannelBuffersPointer(processSetup, data.outputs[0]);

        // Here could check the silent flags
        // now we will produce the output
        // mark our outputs has not silent
        data.outputs[0].silenceFlags = 0;

        float rate = mRate;
        float depth = mDepth;

        // for each channel (left and right)
        for (int32 i = 0; i < numChannels; i++)
        {
            int32 samples = data.numSamples;
            Vst::Sample32* ptrIn = (Vst::Sample32*)in[i];
            Vst::Sample32* ptrOut = (Vst::Sample32*)out[i];
            Vst::Sample32 tmp;
            // for each sample in this channel
            while (--samples >= 0)
            {
                // apply modulation
                tmp = (*ptrIn++) * gain;
                (*ptrOut++) = tmp;
            }
        }

        return kResultOk;
    
}

//------------------------------------------------------------------------
tresult PLUGIN_API AP2ChorusProcessor::setupProcessing (Vst::ProcessSetup& newSetup)
{
	//--- called before any processing ----
	return AudioEffect::setupProcessing (newSetup);
}

//------------------------------------------------------------------------
tresult PLUGIN_API AP2ChorusProcessor::canProcessSampleSize (int32 symbolicSampleSize)
{
	// by default kSample32 is supported
	if (symbolicSampleSize == Vst::kSample32)
		return kResultTrue;

	// disable the following comment if your processing support kSample64
	/* if (symbolicSampleSize == Vst::kSample64)
		return kResultTrue; */

	return kResultFalse;
}

//------------------------------------------------------------------------
tresult PLUGIN_API AP2ChorusProcessor::setState (IBStream* state)
{
	// called when we load a preset, the model has to be reloaded
	IBStreamer streamer (state, kLittleEndian);
	
	return kResultOk;
}

//------------------------------------------------------------------------
tresult PLUGIN_API AP2ChorusProcessor::getState (IBStream* state)
{
	// here we need to save the model
	IBStreamer streamer (state, kLittleEndian);

	return kResultOk;
}

//------------------------------------------------------------------------
} // namespace MyCompanyName