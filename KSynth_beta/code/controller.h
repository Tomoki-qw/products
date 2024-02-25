#include "public.sdk/source/vst/vsteditcontroller.h"
#include "pluginterfaces/vst/ivstmidicontrollers.h" // MIDI��PitchBend��ControlChange���������߂ɕK�v

// GUI
//#include "guieditor.h"

namespace Steinberg{
namespace Vst {

class MyVSTController : public EditController
						, public IMidiMapping // MIDI��PitchBend��ControlChange���������߂ɕK�v

{
public:
	// �N���X������������֐�(�K�{)
	tresult PLUGIN_API initialize(FUnknown* context);

	// ����VST GUIEditor���쐬����֐�
	//IPlugView* PLUGIN_API createView(const char* name);

	// ����VST Controller�N���X�̃C���X�^���X���쐬���邽�߂̊֐�
	static FUnknown* createInstance(void*) { return (IEditController*)new MyVSTController(); }

	// MIDI��PitchBend��ControlChange�ƃp�����[�^���֘A�t����֐�
	virtual tresult PLUGIN_API getMidiControllerAssignment(int32 busIndex, int16 channel, CtrlNumber midiControllerNumber, ParamID& id);

	// VST��{�C���^�[�t�F�C�X(IMidiMapping ��)���I�[�o�[���C�h�����ꍇ�ɕK�v�Ȑ錾(�ڍוs��)
	// DEF_INTERFACE�ɃC���^�[�t�F�C�X���I�[�o�[���C�h���������������Ă����B
	OBJ_METHODS(MyVSTController, EditController)
		DEFINE_INTERFACES
		DEF_INTERFACE(IMidiMapping)
		END_DEFINE_INTERFACES(EditController)
		REFCOUNT_METHODS(EditController)
};


} } 