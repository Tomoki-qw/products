/*
#ifndef __GUIEDITOR_H__
#define __GUIEDITOR_H__

// VST3 SDK�̃C���N���[�h�t�@�C��
#include "public.sdk/source/vst/vstguieditor.h"
#include "pluginterfaces/vst/ivstplugview.h"

// ����VST�p�̃C���N���[�h�t�@�C��
#include "myvst3def.h"

// VST3�쐬�ɕK�v�Ȃ̖��O��Ԃ��g�p
namespace Steinberg {
	namespace Vst {

		using namespace VSTGUI;

		// ============================================================================================
		// VST��GUI�N���X
		// ============================================================================================
		class MyVSTGUIEditor : public VSTGUIEditor, public IControlListener
		{
		public:
			// �R���X�g���N�^(�K�{)
			MyVSTGUIEditor(void* controller);

			// GUI�E�B���h�E���J�����Ƃ��ɌĂяo�����֐�(�K�{)
			virtual bool PLUGIN_API open(void* parent, const PlatformType& platformType = PlatformType::kDefaultNative);

			// GUI�E�B���h�E������Ƃ��ɌĂяo�����֐�(�K�{)
			virtual void PLUGIN_API close();

			// GUI�E�B���h�E�̃R���g���[���𑀍삵���Ƃ��ɌĂяo�����֐�(�K�{)
			void valueChanged(CControl* pControl);

			// ����֐�
			// �m�u�R���g���[�����쐬����֐�
			void createKnob(ParamID tag, int x, int y);
			void createSlider(ParamID tag, int x, int y);
			void createCombobox(ParamID tag, int x, int y);

			// VSTGUIEditor�N���X�̊e��ݒ������GUI�N���X�u��������}�N��(�K�{)
			DELEGATE_REFCOUNT(VSTGUIEditor)
		};



	}
} // namespace Steinberg��Vst�̏I���

#endif
*/