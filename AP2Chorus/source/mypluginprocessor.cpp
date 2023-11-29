//------------------------------------------------------------------------
// Copyright(c) 2023 My Plug-in Company.
//------------------------------------------------------------------------

#include "mypluginprocessor.h"
#include "myplugincids.h"

#include "base/source/fstreamer.h"
#include "pluginterfaces/vst/ivstparameterchanges.h"
#include "public.sdk/source/vst/vstaudioprocessoralgo.h"

#include "Buffer.h"
#include "Osc.h"

#include <iostream>




using namespace Steinberg;


namespace MyCompanyName {
//------------------------------------------------------------------------
// AP2ChorusProcessor
//------------------------------------------------------------------------
AP2ChorusProcessor::AP2ChorusProcessor ():mBuffer(), Osc()
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

	if (result != kResultOk)
	{
		return result;
	}
	
	
	addAudioInput(STR16("Audio In"), Steinberg::Vst::SpeakerArr::kStereo);
	addAudioOutput(STR16("Audio Out"), Steinberg::Vst::SpeakerArr::kStereo);

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
				case ChorusParams::kParamMixId:
					if (paramQueue->getPoint(numPoints - 1, sampleOffset, value) == kResultTrue)
						mMix = value;
					break;
				}


			}
		}
	}
	
	//-- Flush case: we only need to update parameter, noprocessing possible
	if (data.numInputs == 0 || data.numSamples == 0)
		return kResultOk;

	//--- Here, you have to implement your processing
	int32 numChannels = data.inputs[0].numChannels;


	//---get audio buffers using helper-functions(vstaudioprocessoralgo.h)-------------
	uint32 sampleFramesSize = getSampleFramesSizeInBytes(processSetup, data.numSamples);
	void** in = getChannelBuffersPointer(processSetup, data.inputs[0]);
	void** out = getChannelBuffersPointer(processSetup, data.outputs[0]);

	// Here could check the silent flags
	// 


	data.outputs[0].silenceFlags = 0;

	float rate = mRate;
	float depth = mDepth;
	
	const float centre= 27.5/1000.0f;
		
		// for each channel (left and right)
		for (int32 i = 0; i < numChannels; i++)
		{
			int32 samples = data.numSamples;
			Vst::Sample32* ptrIn = (Vst::Sample32*)in[i];
			Vst::Sample32* ptrOut = (Vst::Sample32*)out[i];
			Vst::Sample32 tmp;
			Vst::Sample32 out;
			// for each sample in this channel
			float wet = mMix;
			float feedback = mFeedback;


			while (--samples >= 0)
			{
				// apply modulation
				tmp = (*ptrIn++);


				//mBuffer[i].write(tmp);
				float delaySeconds = (Osc[i].process(mRate, mDepth) / 1000.0f) + centre;

				float delaySamples = delaySeconds * processSetup.sampleRate;
				Vst::Sample32 delayed = mBuffer[i].readInterp(delaySamples);

				out = ((1 - wet) * tmp) + (wet * delayed);

				(*ptrOut++) = out;

				mBuffer[i].write((1 - mFeedback) * tmp + mFeedback * out);
			}
		}
	

	// 
	// // normally we have to check each channel (simplification)
	if (data.inputs[0].silenceFlags != 0)
	{
		// mark output silence too
		data.outputs[0].silenceFlags = data.inputs[0].silenceFlags;

		// the plug-in has to be sure that if it sets the flags silence that the output buffer are clear
		for (int32 i = 0; i < numChannels; i++)
		{
			// do not need to be cleared if the buffers are the same (in this case input buffer are
			 // already cleared by the host)
			if (in[i] != out[i])
			{
				memset(out[i], 0, sampleFramesSize);
			}
		}
		// nothing to do at this point
		
	}

	return kResultOk;
}

//------------------------------------------------------------------------
tresult PLUGIN_API AP2ChorusProcessor::setupProcessing (Vst::ProcessSetup& newSetup)
{
	//--- called before any processing ----

	mBuffer[0] = ap2::RingBuffer(newSetup.sampleRate * (50.0 / 1000.0));
	mBuffer[1] = ap2::RingBuffer(newSetup.sampleRate * (50.0 / 1000.0));

	Osc[0]=ap2::SawOsc(newSetup.sampleRate,0);
	Osc[1] = ap2::SawOsc(newSetup.sampleRate,90);

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
	if (!state)
		return kResultFalse;

	// called when we load a preset or project, the model has to be reloaded
	//IBStreamer streamer(state, kLittleEndian);
	//float savedParam1 = 0.f;
	//float savedParam2 = 0.f;

	//if (streamer.readFloat(savedParam1) == false)
		//return kResultFalse;
//	mRate = savedParam1;

	//if (streamer.readFloat(savedParam2) == false)
		//return kResultFalse;
	//mDepth = savedParam2;
	
	//return kResultOk;
}

//------------------------------------------------------------------------
tresult PLUGIN_API AP2ChorusProcessor::getState (IBStream* state)
{
	// here we need to save the model
	//float toSaveParam1 = mRate;
	//float toSaveParam2 = mDepth;
	//IBStreamer streamer (state, kLittleEndian);
	//streamer.writeFloat(toSaveParam1);
	//streamer.writeFloat(toSaveParam2);

	return kResultOk;
}

//------------------------------------------------------------------------
} // namespace MyCompanyName
