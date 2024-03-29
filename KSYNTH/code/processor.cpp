#include "myvst3fuid.h"
#include "processor.h"
#include "myvst3def.h"
#include "distortion.h"
#include "chorus.h"

namespace Steinberg{
namespace Vst {

MyVSTProcessor::MyVSTProcessor()
{
	setControllerClass(ControllerUID);
}

tresult PLUGIN_API MyVSTProcessor::initialize(FUnknown* context)
{
	tresult result = AudioEffect::initialize(context);
	if (result == kResultTrue)
	{
		addAudioOutput(STR16("AudioOutput"), SpeakerArr::kStereo);
		addEventInput(STR16("Event Input"), 1);
	}
	return result;
}

tresult PLUGIN_API MyVSTProcessor::setBusArrangements(SpeakerArrangement* inputs, int32 numIns, SpeakerArrangement* outputs, int32 numOuts)
{
	// inputとoutputのバスが1つずつで、かつinputとoutputの構成がステレオの場合
	if (numOuts == 1 && outputs[0] == SpeakerArr::kStereo)
	{
		return AudioEffect::setBusArrangements(inputs, numIns, outputs, numOuts);
	}
	return kResultFalse;
}

tresult PLUGIN_API MyVSTProcessor::process(ProcessData& data)
{
	if (data.inputParameterChanges != NULL)
	{
		int32 paramChangeCount = data.inputParameterChanges->getParameterCount();
		for (int32 i = 0; i < paramChangeCount; i++)
		{
			IParamValueQueue* queue = data.inputParameterChanges->getParameterData(i);
			if (queue != NULL)
			{
				int32 tag = queue->getParameterId();
				int32 valueChangeCount = queue->getPointCount();
				ParamValue value;
				int32 sampleOffset;
				if (queue->getPoint(valueChangeCount - 1, sampleOffset, value) == kResultTrue)
				{
					switch (tag)
					{
						
					case SUSTAIN_TAG: // SustainPedalの処理
						//もし今サステインがオンで、
						if (voicemanager.getSusPedal() == true ) {
							//かつ、sustainのノブをオフに操作したなら
							if (value == 0.0f) { voicemanager.susPedal(false); };		
						}
						//もし今サステインがオフで、
						else{
							//かつ、sustainのノブをオンに操作したなら
							if (value == 1.0f) { voicemanager.susPedal(true); };
						}
						break;
						
					case VOLUME_TAG_MASTER:
						voicemanager.setMasterVolume(value);
						break;

					case VOLUME_TAG_1:
						voicemanager.setVolume(VOLUME_TAG_1, value);
						break;
					case VOLUME_TAG_2:
						voicemanager.setVolume(VOLUME_TAG_2, value);
						break;
					case VOLUME_TAG_3:
						voicemanager.setVolume(VOLUME_TAG_3, value);
						break;
					case PITCHBEND_TAG: 
						value = value * 4.0f - 2.0f;
						voicemanager.setPitchBend(value);
						break;
					case WAVEFORM_TAG1:
						voicemanager.setWaveformType(WAVEFORM_TAG1, value);
						break;
					case WAVEFORM_TAG2:
						voicemanager.setWaveformType(WAVEFORM_TAG2, value);
						break;
					case WAVEFORM_TAG3:
						voicemanager.setWaveformType(WAVEFORM_TAG3, value);
						break;
					case ADSR_OSC1_A:
						voicemanager.setADSR(ADSR_OSC1_A, value);
						break;
					case ADSR_OSC1_D:
						voicemanager.setADSR(ADSR_OSC1_D, value);
						break;
					case ADSR_OSC1_S:
						voicemanager.setADSR(ADSR_OSC1_S, value);
						break;
					case ADSR_OSC1_R:
						voicemanager.setADSR(ADSR_OSC1_R, value);
						break;
					case ADSR_OSC2_A:
						voicemanager.setADSR(ADSR_OSC2_A, value);
						break;
					case ADSR_OSC2_D:
						voicemanager.setADSR(ADSR_OSC2_D, value);
						break;
					case ADSR_OSC2_S:
						voicemanager.setADSR(ADSR_OSC2_S, value);
						break;
					case ADSR_OSC2_R:
						voicemanager.setADSR(ADSR_OSC2_R, value);
						break;
					case ADSR_OSC3_A:
						voicemanager.setADSR(ADSR_OSC3_A, value);
						break;
					case ADSR_OSC3_D:
						voicemanager.setADSR(ADSR_OSC3_D, value);
						break;
					case ADSR_OSC3_S:
						voicemanager.setADSR(ADSR_OSC3_S, value);
						break;
					case ADSR_OSC3_R:
						voicemanager.setADSR(ADSR_OSC3_R, value);
						break;

					case MOD_COARSE1_TAG:
						voicemanager.setModCoarse(MOD_COARSE1_TAG, value);
						break;
					case MOD_COARSE2_TAG:
						voicemanager.setModCoarse(MOD_COARSE2_TAG, value);
						break;
					case MOD_COARSE3_TAG:
						voicemanager.setModCoarse(MOD_COARSE3_TAG, value);
						break;
					case MOD_OCT1_TAG:
						voicemanager.setModOct(MOD_OCT1_TAG, value);
						break;
					case MOD_OCT2_TAG:
						voicemanager.setModOct(MOD_OCT2_TAG, value);
						break;
					case MOD_OCT3_TAG:
						voicemanager.setModOct(MOD_OCT3_TAG, value);
						break;
					case SYNTH_MODE:
						voicemanager.switchSynthMode();
						break;
						/*
					case FILTER_TYPE_TAG:
						voicemanager.setFilterFreq();
					case LOWPASS_TEST:
						voicemanager.setFilterFreq(value);
					case Q_TEST:
						voicemanager.setFilterQ(value);
						*/

					case O1_FILTER_TYPE:
						voicemanager.setFilterType(tag, value);
						break;
					case O2_FILTER_TYPE:
						voicemanager.setFilterType(tag, value);
						break;
					case O3_FILTER_TYPE:
						voicemanager.setFilterType(tag, value);
						break;

					case O1_FILTER_FREQ:
						voicemanager.setFilterFreq(tag, value);
						break;
					case O2_FILTER_FREQ:
						voicemanager.setFilterFreq(tag, value);
						break;
					case O3_FILTER_FREQ:
						voicemanager.setFilterFreq(tag, value);
						break;
					case O1_FILTER_Q:
						voicemanager.setFilterQ(tag, value);
						break;
					case O2_FILTER_Q:
						voicemanager.setFilterQ(tag, value);
						break;
					case O3_FILTER_Q:
						voicemanager.setFilterQ(tag, value);
						break;
					case O1_FILTER_GAIN:
						voicemanager.setFilterGain(tag, value);
						break;
					case O2_FILTER_GAIN:
						voicemanager.setFilterGain(tag, value);
						break;
					case O3_FILTER_GAIN:
						voicemanager.setFilterGain(tag, value);
						break;
					case DIST_ONOFF:
						isDistOn = (int)value;
						break;
					case DIST_GAIN:
						dist_gain = 10.0f * value;
						break;
					case DIST_VOLUME:
						dist_volume = value;
						break;
					case CHORUS_ONOFF:
						isChorusOn = (int)value;
						break;
					case CHORUS_MIX:
						chorus_mix = value;
						break;
					case CHORUS_RATE:
						chorus_rate = 16.0f * value;
						break;
					case CHORUS_DEPTH:
						chorus_depth = 195.0f * value + 5.0f;
						break;
					case CHORUS_FEEDBACK:
						chorus_feedback = value;
						break;
					}
				}
			}
		}
	}


	IEventList* eventList = data.inputEvents;
	if (eventList != NULL)
	{
		int32 numEvent = eventList->getEventCount();
		for (int32 i = 0; i < numEvent; i++)
		{
			Event event;
			if (eventList->getEvent(i, event) == kResultOk)
			{
				int16 channel;
				int16 noteNo;
				float velocity;
				switch (event.type)
				{
				case Event::kNoteOnEvent: // ノートオンイベントの場合
					channel = event.noteOn.channel;
					noteNo = event.noteOn.pitch;
					velocity = event.noteOn.velocity;

					onNoteOn(channel, noteNo, velocity);

					break;

				case Event::kNoteOffEvent: // ノートオフイベントの場合
					channel = event.noteOff.channel;
					noteNo = event.noteOff.pitch;
					velocity = event.noteOff.velocity;

					onNoteOff(channel, noteNo, velocity);
					break;
				}
			}
		}
	}

	Sample32* outL = data.outputs[0].channelBuffers32[0];
	Sample32* outR = data.outputs[0].channelBuffers32[1];

	for (int32 i = 0; i < data.numSamples; i++)
	{
		float out = voicemanager.process();
		voicemanager.update();

		outL[i] = out;
		outR[i] = out;
	}
	if (isDistOn) {
		distortion(outL, outR, outL, outR, data.numSamples, dist_gain, dist_volume);
	}
	if (isChorusOn) {
		chorus(outL, outR, outL, outR, data.numSamples, chorus_mix, chorus_rate, chorus_depth, chorus_feedback);
	}
	return kResultTrue;
}


void MyVSTProcessor::onNoteOn(int channel, int note, float velocity)
{
	voicemanager.noteOn(channel, note, velocity);

}

void MyVSTProcessor::onNoteOff(int channel, int note, float velocity)
{
	voicemanager.noteOff(note);
}


} } 