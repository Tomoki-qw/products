#include "myvst3fuid.h"
#include "controller.h"
#include "myvst3def.h"


namespace Steinberg{
namespace Vst {


tresult PLUGIN_API MyVSTController::initialize(FUnknown* context)
{
	tresult result = EditController::initialize(context);
	if (result == kResultTrue)
	{
		StringListParameter* param1 = new StringListParameter(STR16("Sustain"), SUSTAIN_TAG);
		param1->appendString(STR16("off"));  
		param1->appendString(STR16("on"));
		parameters.addParameter(param1);

		StringListParameter* param2 = new StringListParameter(STR16("mode"), SYNTH_MODE);
		param2->appendString(STR16("analog"));
		param2->appendString(STR16("FM"));
		parameters.addParameter(param2);

		parameters.addParameter(STR16("master volume"), STR16("..."), 0, 1.0, ParameterInfo::kCanAutomate, VOLUME_TAG_MASTER);
		parameters.addParameter(STR16("osc1(modulator) volume"), STR16("..."), 0, 1.0, ParameterInfo::kCanAutomate, VOLUME_TAG_1);
		parameters.addParameter(STR16("osc2(carrier) volume"), STR16("..."), 0, 1.0, ParameterInfo::kCanAutomate, VOLUME_TAG_2);


		StringListParameter* param3 = new StringListParameter(STR16("Oscillator1"), WAVEFORM_TAG1);
		param3->appendString(STR16("sine"));
		param3->appendString(STR16("saw"));
		param3->appendString(STR16("triangle"));
		param3->appendString(STR16("pulse"));
		param3->appendString(STR16("white"));
		parameters.addParameter(param3);

		StringListParameter* param4 = new StringListParameter(STR16("Oscillator2"), WAVEFORM_TAG2);
		param4->appendString(STR16("sine"));
		param4->appendString(STR16("saw"));
		param4->appendString(STR16("triangle"));
		param4->appendString(STR16("pulse"));
		param4->appendString(STR16("white"));
		parameters.addParameter(param4);

		parameters.addParameter(STR16("PitchBend"), STR16("..."), 0, 0.5, ParameterInfo::kCanAutomate, PITCHBEND_TAG);

		parameters.addParameter(STR16("osc1 Attack"), STR16("..."), 0, 0.005, ParameterInfo::kCanAutomate, ADSR_OSC1_A);
		parameters.addParameter(STR16("osc1 Decay"), STR16("..."), 0, 0.5, ParameterInfo::kCanAutomate, ADSR_OSC1_D);
		parameters.addParameter(STR16("osc1 Sustain"), STR16("..."), 0, 0, ParameterInfo::kCanAutomate, ADSR_OSC1_S);
		parameters.addParameter(STR16("osc1 Release"), STR16("..."), 0, 0.005, ParameterInfo::kCanAutomate, ADSR_OSC1_R);
		parameters.addParameter(STR16("osc2 Attack"), STR16("..."), 0, 0.005, ParameterInfo::kCanAutomate, ADSR_OSC2_A);
		parameters.addParameter(STR16("osc2 Decay"), STR16("..."), 0, 0.5, ParameterInfo::kCanAutomate, ADSR_OSC2_D);
		parameters.addParameter(STR16("osc2 Sustain"), STR16("..."), 0, 0, ParameterInfo::kCanAutomate, ADSR_OSC2_S);
		parameters.addParameter(STR16("osc2 Release"), STR16("..."), 0, 0.005, ParameterInfo::kCanAutomate, ADSR_OSC2_R);
	}

	result = kResultTrue;
	return result;
}
/*
IPlugView* PLUGIN_API MyVSTController::createView(const char* name)
{
	if (strcmp(name, "editor") == 0)
	{
		MyVSTGUIEditor* view = new MyVSTGUIEditor(this);
		return view;
	}
	return 0;
}
*/

tresult PLUGIN_API MyVSTController::getMidiControllerAssignment(int32 busIndex, int16 channel, CtrlNumber midiControllerNumber, ParamID& id)
{

	switch (midiControllerNumber)
	{
	case kCtrlSustainOnOff:
		id = SUSTAIN_TAG;
		return kResultTrue;
	case kPitchBend:
		id = PITCHBEND_TAG;
		return kResultTrue;
	}
	
	return kResultFalse;
}


} } 