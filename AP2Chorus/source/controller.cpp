//------------------------------------------------------------------------
// Copyright(c) 2023 My Plug-in Company.
//------------------------------------------------------------------------

#include "myplugincontroller.h"
#include "myplugincids.h"
#include "base/source/fstreamer.h"



using namespace Steinberg;

namespace MyCompanyName {

//------------------------------------------------------------------------
// AP2ChorusController Implementation
//------------------------------------------------------------------------
tresult PLUGIN_API AP2ChorusController::initialize (FUnknown* context)
{
	// Here the Plug-in will be instantiated

	//---do not forget to call parent ------
	tresult result = EditControllerEx1::initialize (context);
	if (result != kResultOk)
	{
		return result;
	}

	// Here you could register some parameters


	Vst::Parameter* rateParam = new Vst::RangeParameter(
		STR16("Rate"), ChorusParams::kParamRateId, STR16("Hz"), 0.357, 3.57, 0.357 //Freq of LFO
	);
	parameters.addParameter(rateParam);

	Vst::Parameter* depthParam = new Vst::RangeParameter(
		STR16("Depth"), ChorusParams::kParamDepthId, STR16("Amplitude"), 5.5, 22.5, 5.5 //min,max,default
	);//Amplitude of LFO
	parameters.addParameter(depthParam);

	//VST3 Parameters are always floating values between 0.0 and 1.0

	return kResultTrue;
}

//------------------------------------------------------------------------
tresult PLUGIN_API AP2ChorusController::terminate ()
{
	// Here the Plug-in will be de-instantiated, last possibility to remove some memory!

	//---do not forget to call parent ------
	return EditControllerEx1::terminate ();
}

//------------------------------------------------------------------------
tresult PLUGIN_API AP2ChorusController::setComponentState (IBStream* state)
{
	// Here you get the state of the component (Processor part)
	if (!state)
		return kResultFalse;

	return kResultOk;
}

//------------------------------------------------------------------------
tresult PLUGIN_API AP2ChorusController::setState (IBStream* state)
{
	// Here, you get the state of the component (Processor part)

	if (!state)
		return kResultFalse;

	IBStreamer streamer(state, kLittleEndian);
	float savedParam1 = 0.f;
	if (streamer.readFloat(savedParam1) == false)
		return kResultFalse;

	float savedParam2 = 0.f;
	if (streamer.readFloat(savedParam2) == false)
		return kResultFalse;

	// sync with our parameter
	if (auto param = parameters.getParameter(ChorusParams::kParamRateId))
		param->setNormalized(savedParam1);

	if (auto param = parameters.getParameter(ChorusParams::kParamDepthId))
		param->setNormalized(savedParam2);

	return kResultOk;

	

}

//------------------------------------------------------------------------
tresult PLUGIN_API AP2ChorusController::getState (IBStream* state)
{
	// Here you are asked to deliver the state of the controller (if needed)
	// Note: the real state of your plug-in is saved in the processor

	return kResultTrue;
}

//------------------------------------------------------------------------
IPlugView* PLUGIN_API AP2ChorusController::createView (FIDString name)
{
	// Here the Host wants to open your editor (if you have one)
	if (FIDStringsEqual (name, Vst::ViewType::kEditor))
	{
		// create your editor here and return a IPlugView ptr of it
        return nullptr;
	}
	return nullptr;
}

//------------------------------------------------------------------------
tresult PLUGIN_API AP2ChorusController::setParamNormalized (Vst::ParamID tag, Vst::ParamValue value)
{
	// called by host to update your parameters
	tresult result = EditControllerEx1::setParamNormalized (tag, value);
	return result;
}

//------------------------------------------------------------------------
tresult PLUGIN_API AP2ChorusController::getParamStringByValue (Vst::ParamID tag, Vst::ParamValue valueNormalized, Vst::String128 string)
{
	// called by host to get a string for given normalized value of a specific parameter
	// (without having to set the value!)
	return EditControllerEx1::getParamStringByValue (tag, valueNormalized, string);
}

//------------------------------------------------------------------------
tresult PLUGIN_API AP2ChorusController::getParamValueByString (Vst::ParamID tag, Vst::TChar* string, Vst::ParamValue& valueNormalized)
{
	// called by host to get a normalized value from a string representation of a specific parameter
	// (without having to set the value!)
	return EditControllerEx1::getParamValueByString (tag, string, valueNormalized);
}

//------------------------------------------------------------------------
} // namespace MyCompanyName
