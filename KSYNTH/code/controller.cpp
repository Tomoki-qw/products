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

		parameters.addParameter(STR16("master volume"), STR16("..."), 10, 1.0, ParameterInfo::kCanAutomate, VOLUME_TAG_MASTER);
		parameters.addParameter(STR16("osc1(carrier) volume"), STR16("..."), 0, 1.0, ParameterInfo::kCanAutomate, VOLUME_TAG_1);
		parameters.addParameter(STR16("osc2(modulator) volume"), STR16("..."), 0, 1.0, ParameterInfo::kCanAutomate, VOLUME_TAG_2);
		parameters.addParameter(STR16("osc3(modulator) volume"), STR16("..."), 0, 1.0, ParameterInfo::kCanAutomate, VOLUME_TAG_3);


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

		StringListParameter* param5 = new StringListParameter(STR16("Oscillator3"), WAVEFORM_TAG3);
		param5->appendString(STR16("sine"));
		param5->appendString(STR16("saw"));
		param5->appendString(STR16("triangle"));
		param5->appendString(STR16("pulse"));
		param5->appendString(STR16("white"));
		parameters.addParameter(param5);

		StringListParameter* param6 = new StringListParameter(STR16("modulator1 crs"), MOD_COARSE1_TAG);
		param6->appendString(STR16("0.5"));
		param6->appendString(STR16("1"));
		param6->appendString(STR16("2"));
		param6->appendString(STR16("3"));
		param6->appendString(STR16("4"));
		param6->appendString(STR16("5"));
		param6->appendString(STR16("6"));
		param6->appendString(STR16("7"));
		param6->appendString(STR16("8"));
		param6->appendString(STR16("9"));
		param6->appendString(STR16("10"));
		parameters.addParameter(param6);

		StringListParameter* param7 = new StringListParameter(STR16("modulator2 crs"), MOD_COARSE2_TAG);
		param7->appendString(STR16("0.5"));
		param7->appendString(STR16("1"));
		param7->appendString(STR16("2"));
		param7->appendString(STR16("3"));
		param7->appendString(STR16("4"));
		param7->appendString(STR16("5"));
		param7->appendString(STR16("6"));
		param7->appendString(STR16("7"));
		param7->appendString(STR16("8"));
		param7->appendString(STR16("9"));
		param7->appendString(STR16("10"));
		parameters.addParameter(param7);

		StringListParameter* param8 = new StringListParameter(STR16("modulator3 crs"), MOD_COARSE3_TAG);
		param8->appendString(STR16("0.5"));
		param8->appendString(STR16("1"));
		param8->appendString(STR16("2"));
		param8->appendString(STR16("3"));
		param8->appendString(STR16("4"));
		param8->appendString(STR16("5"));
		param8->appendString(STR16("6"));
		param8->appendString(STR16("7"));
		param8->appendString(STR16("8"));
		param8->appendString(STR16("9"));
		param8->appendString(STR16("10"));
		parameters.addParameter(param8);
		/*
		StringListParameter* param7 = new StringListParameter(STR16("modulator1 oct"), MOD_OCT1_TAG);
		param7->appendString(STR16("-4"));
		param7->appendString(STR16("-3"));
		param7->appendString(STR16("-2"));
		param7->appendString(STR16("-1"));
		param7->appendString(STR16("0"));
		param7->appendString(STR16("1"));
		param7->appendString(STR16("2"));
		param7->appendString(STR16("3"));
		param7->appendString(STR16("4"));
		parameters.addParameter(param7);
		*/
		parameters.addParameter(STR16("modulator1 oct"), STR16("..."), 0, 0.5, ParameterInfo::kCanAutomate, MOD_OCT1_TAG);
		parameters.addParameter(STR16("modulator2 oct"), STR16("..."), 0, 0.5, ParameterInfo::kCanAutomate, MOD_OCT2_TAG);
		parameters.addParameter(STR16("modulator3 oct"), STR16("..."), 0, 0.5, ParameterInfo::kCanAutomate, MOD_OCT3_TAG);


		parameters.addParameter(STR16("PitchBend"), STR16("..."), 0, 0.5, ParameterInfo::kCanAutomate, PITCHBEND_TAG);

		parameters.addParameter(STR16("osc1 Attack"), STR16("..."), 0, 0.005, ParameterInfo::kCanAutomate, ADSR_OSC1_A);
		parameters.addParameter(STR16("osc1 Decay"), STR16("..."), 0, 0.5, ParameterInfo::kCanAutomate, ADSR_OSC1_D);
		parameters.addParameter(STR16("osc1 Sustain"), STR16("..."), 0, 0, ParameterInfo::kCanAutomate, ADSR_OSC1_S);
		parameters.addParameter(STR16("osc1 Release"), STR16("..."), 0, 0.005, ParameterInfo::kCanAutomate, ADSR_OSC1_R);
		parameters.addParameter(STR16("osc2 Attack"), STR16("..."), 0, 0.005, ParameterInfo::kCanAutomate, ADSR_OSC2_A);
		parameters.addParameter(STR16("osc2 Decay"), STR16("..."), 0, 0.5, ParameterInfo::kCanAutomate, ADSR_OSC2_D);
		parameters.addParameter(STR16("osc2 Sustain"), STR16("..."), 0, 0, ParameterInfo::kCanAutomate, ADSR_OSC2_S);
		parameters.addParameter(STR16("osc2 Release"), STR16("..."), 0, 0.005, ParameterInfo::kCanAutomate, ADSR_OSC2_R);
		parameters.addParameter(STR16("osc3 Attack"), STR16("..."), 0, 0.005, ParameterInfo::kCanAutomate, ADSR_OSC3_A);
		parameters.addParameter(STR16("osc3 Decay"), STR16("..."), 0, 0.5, ParameterInfo::kCanAutomate, ADSR_OSC3_D);
		parameters.addParameter(STR16("osc3 Sustain"), STR16("..."), 0, 0, ParameterInfo::kCanAutomate, ADSR_OSC3_S);
		parameters.addParameter(STR16("osc3 Release"), STR16("..."), 0, 0.005, ParameterInfo::kCanAutomate, ADSR_OSC3_R);

		//filter

		StringListParameter* param9 = new StringListParameter(STR16("O1 filter type"), O1_FILTER_TYPE);
		param9->appendString(STR16("off"));//0
		param9->appendString(STR16("lowpass"));//0.125
		param9->appendString(STR16("highpass"));//0.25
		param9->appendString(STR16("bandpass"));//0.375
		param9->appendString(STR16("notch"));//0.5
		param9->appendString(STR16("lowshelf"));//0.675
		param9->appendString(STR16("highshelf"));//0.75
		param9->appendString(STR16("peaking"));//0.875
		param9->appendString(STR16("allpass"));//1
		parameters.addParameter(param9);

		parameters.addParameter(STR16("O1 FILTER FREQ"), STR16("..."), 0, 1.0, ParameterInfo::kCanAutomate, O1_FILTER_FREQ);
		parameters.addParameter(STR16("O1 FILTER Q"), STR16("..."), 0, 1.0, ParameterInfo::kCanAutomate, O1_FILTER_Q);
		parameters.addParameter(STR16("O1 FILTER GAIN"), STR16("..."), 0, 1.0, ParameterInfo::kCanAutomate, O1_FILTER_GAIN);

		StringListParameter* param10 = new StringListParameter(STR16("O2 filter type"), O2_FILTER_TYPE);
		param10->appendString(STR16("off"));//0
		param10->appendString(STR16("lowpass"));//0.125
		param10->appendString(STR16("highpass"));//0.25
		param10->appendString(STR16("bandpass"));//0.375
		param10->appendString(STR16("notch"));//0.5
		param10->appendString(STR16("lowshelf"));//0.675
		param10->appendString(STR16("highshelf"));//0.75
		param10->appendString(STR16("peaking"));//0.875
		param10->appendString(STR16("allpass"));//1
		parameters.addParameter(param10);

		parameters.addParameter(STR16("O2 FILTER FREQ"), STR16("..."), 0, 1.0, ParameterInfo::kCanAutomate, O2_FILTER_FREQ);
		parameters.addParameter(STR16("O2 FILTER Q"), STR16("..."), 0, 1.0, ParameterInfo::kCanAutomate, O2_FILTER_Q);
		parameters.addParameter(STR16("O2 FILTER GAIN"), STR16("..."), 0, 1.0, ParameterInfo::kCanAutomate, O2_FILTER_GAIN);

		StringListParameter* param11 = new StringListParameter(STR16("O3 filter type"), O3_FILTER_TYPE);
		param11->appendString(STR16("off"));//0
		param11->appendString(STR16("lowpass"));//0.125
		param11->appendString(STR16("highpass"));//0.25
		param11->appendString(STR16("bandpass"));//0.375
		param11->appendString(STR16("notch"));//0.5
		param11->appendString(STR16("lowshelf"));//0.675
		param11->appendString(STR16("highshelf"));//0.75
		param11->appendString(STR16("peaking"));//0.875
		param11->appendString(STR16("allpass"));//1
		parameters.addParameter(param11);

		parameters.addParameter(STR16("O3 FILTER FREQ"), STR16("..."), 0, 1.0, ParameterInfo::kCanAutomate, O3_FILTER_FREQ);
		parameters.addParameter(STR16("O3 FILTER Q"), STR16("..."), 0, 1.0, ParameterInfo::kCanAutomate, O3_FILTER_Q);
		parameters.addParameter(STR16("O3 FILTER GAIN"), STR16("..."), 0, 1.0, ParameterInfo::kCanAutomate, O3_FILTER_GAIN);

		StringListParameter* param12 = new StringListParameter(STR16("Distortion on"), DIST_ONOFF);
		param12->appendString(STR16("off"));
		param12->appendString(STR16("on"));
		parameters.addParameter(param12);
		parameters.addParameter(STR16("Distortion gain"), STR16("..."), 0, 0.1, ParameterInfo::kCanAutomate, DIST_GAIN);
		parameters.addParameter(STR16("Distortion volume"), STR16("..."), 0, 1.0, ParameterInfo::kCanAutomate, DIST_VOLUME);

		StringListParameter* param13 = new StringListParameter(STR16("Chorus on"), CHORUS_ONOFF);
		param13->appendString(STR16("off"));
		param13->appendString(STR16("on"));
		parameters.addParameter(param13);
		parameters.addParameter(STR16("Chorus mix"), STR16("..."), 0, 0.0, ParameterInfo::kCanAutomate, CHORUS_MIX);
		parameters.addParameter(STR16("Chorus rate"), STR16("..."), 0, 0.0, ParameterInfo::kCanAutomate, CHORUS_RATE);
		parameters.addParameter(STR16("Chorus depth"), STR16("..."), 0, 0.0, ParameterInfo::kCanAutomate, CHORUS_DEPTH);
		parameters.addParameter(STR16("Chorus feedback"), STR16("..."), 0, 0.0, ParameterInfo::kCanAutomate, CHORUS_FEEDBACK);

	}

	result = kResultTrue;
	return result;
}

IPlugView* PLUGIN_API MyVSTController::createView(const char* name)
{
	if (strcmp(name, "editor") == 0)
	{
		MyVSTGUIEditor* view = new MyVSTGUIEditor(this);
		return view;
	}
	return 0;
}


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