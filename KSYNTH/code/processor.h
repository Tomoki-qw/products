#include "public.sdk/source/vst/vstaudioeffect.h"
#include "pluginterfaces/vst/ivstparameterchanges.h"
#include "pluginterfaces/vst/ivstevents.h" // �C�x���g�o�X���p���ɕK�v

#include <cmath>
#include "CVoiceManager.h"


namespace Steinberg{
namespace Vst {

class MyVSTProcessor : public AudioEffect
{
protected:
	CVoiceManager voicemanager;
	
public:
	// �R���X�g���N�^
	MyVSTProcessor();

	// �N���X������������֐�(�K�{)puro
	tresult PLUGIN_API initialize(FUnknown* context);

	// �o�X�\����ݒ肷��֐��B
	tresult PLUGIN_API setBusArrangements(SpeakerArrangement* inputs, int32 numIns, SpeakerArrangement* outputs, int32 numOuts);

	// �����M������������֐�(�K�{)
	tresult PLUGIN_API process(ProcessData& data);

	// ����֐�
	// MIDI�m�[�g�I���C�x���g�AMIDI�m�[�g�I�t�C�x���g���󂯎�����ꍇ�ɏ�������֐�
	virtual void onNoteOn (int channel, int note, float velocity);
	virtual void onNoteOff(int channel, int note, float velocity);

	// ����VST Processor�N���X�̃C���X�^���X���쐬���邽�߂̊֐�(�K�{)
	static FUnknown* createInstance(void*) { return (IAudioProcessor*)new MyVSTProcessor(); }
};


}
} 