
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
		protected:
			//�}�X�^�[
			//�{�����[��
			CControl* masterVolKnob;
			CControl* masterVolDisp;

			//�I�V���[�^1
			//�{�����[��
			CControl* o1VolKnob;
			CControl* o1VolDisp;
			
			//�I�V���[�^2
			//�{�����[��
			CControl* o2VolKnob;
			CControl* o2VolDisp;

			CControl* o3VolKnob;
			CControl* o3VolDisp;
			
			//fine
			CControl* o1ModCoarceKnob;
			CControl* o1ModCoarceDisp;

			CControl* o2ModCoarceKnob;
			CControl* o2ModCoarceDisp;

			CControl* o3ModCoarceKnob;
			CControl* o3ModCoarceDisp;

			CControl* o1ModOctSlider;
			CControl* o1ModOctDisp;

			CControl* o2ModOctSlider;
			CControl* o2ModOctDisp;

			CControl* o3ModOctSlider;
			CControl* o3ModOctDisp;
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
			CControl* createKnob(ParamID tag, int x, int y);
			CControl* createKnobTransparent(ParamID tag, int x, int y);
			CControl* createSlider(ParamID tag, int x, int y);
			CControl* createHSlider(ParamID tag, int x, int y);
			void createComboboxWaveform(ParamID tag, int x, int y);
			void createComboboxOct(ParamID tag, int x, int y);
			CControl*  createTextLabel(int x, int y, UTF8StringPtr text);
			CControl* createTextValue(ParamID tag, int x, int y);
			CControl* createOnOffButton(ParamID tag, int x, int y, UTF8StringPtr filename);
			//���삵���m�u�ɑΉ����Ă���e�L�X�g��������
			CControl* getTextPair(CControl* control);
			// VSTGUIEditor�N���X�̊e��ݒ������GUI�N���X�u��������}�N��(�K�{)
			DELEGATE_REFCOUNT(VSTGUIEditor)
		};



	}
} // namespace Steinberg��Vst�̏I���

#endif
