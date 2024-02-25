/*
// ����VST�p�̃C���N���[�h�t�@�C��
#include "guieditor.h"


// VST3�쐬�ɕK�v�Ȃ̖��O��Ԃ��g�p
namespace Steinberg {
	namespace Vst {

		// ============================================================================================
		// �R���X�g���N�^
		// ============================================================================================
		MyVSTGUIEditor::MyVSTGUIEditor(void* controller)
			: VSTGUIEditor(controller)
		{
			// �R���X�g���N�^�ŃE�B���h�E�T�C�Y��ݒ肷��
			// �ݒ肵�Ȃ���΁A�E�B���h�E���J���Ȃ�
			ViewRect viewRect(0, 0, 200, 200);
			setRect(viewRect);
		}

		// ============================================================================================
		// GUI�E�B���h�E���J�����Ƃ��A�����Ƃ��ɌĂяo�����֐�
		// ============================================================================================
		bool PLUGIN_API MyVSTGUIEditor::open(void* parent, const PlatformType& platformType)
		{
			// GUI�E�B���h�E���J���ꂽ�Ƃ��ɁAUI���쐬����

			// �܂��̓t���[��(�z�u�̈�)�����łɍ쐬�E�ݒ肳��Ă��邩�m�F�B
			// ���łɍ쐬�E�ݒ肳��Ă���ꍇ(frame��NULL�łȂ��ꍇ)�͏I��
			// frame�͌p�����N���X�Œ�`����Ă���B
			if (frame) { return false; }

			// �쐬����t���[���̃T�C�Y��ݒ�
			CRect size(0, 0, 200, 200);

			// �t���[�����쐬�B�쐬�Ɏ��s������(NULL�Ȃ�)�I���B
			// �����ɂ́A�t���[���T�C�Y�A����GUI�N���X�̃|�C���^���w�肷��
			frame = new CFrame(size, this);
			if (frame == NULL) { return false; }

			// �쐬�����t���[���ɔw�i�摜��ݒ�
			CBitmap* cbmp = new CBitmap("background.png"); // ���\�[�X����w�i�摜��ǂݍ���
			frame->setBackground(cbmp); // �t���[���ɔw�i�摜��ݒ�
			cbmp->forget();	// �t���[���ɐݒ��͔w�i�摜��forget�ŉ�����Ă���

			// �쐬�����t���[�����J��
			frame->open(parent);


			//�@---------------------------------------------
			// ��������e�R���g���[���̍쐬
			createCombobox(PARAM_TYPE_TAG, 10, 10);
			createKnob(PARAM_SPEED_TAG, 20, 35);
			createSlider(PARAM_DEPTH_TAG, 20, 90);

			// GUI�E�B���h�E�̃I�[�v���ɐ��������ꍇ��true��Ԃ�
			return true;
		}


		// GUI�E�B���h�E������Ƃ��ɌĂяo�����֐�
		void PLUGIN_API MyVSTGUIEditor::close()
		{
			// GUI�E�B���h�E�������Ƃ��ɁAUI���폜����

			// �t���[�������
			// �w�i�摜��ǉ������܂�(�m�u�j��X���C�_�[�Ȃǂ����킹�ĉ�������
			// (�ʂŉ������K�v�͂Ȃ�)
			if (frame)
			{
				frame->forget();
				frame = 0;
			}
		}

		// ============================================================================================
		// GUI�E�B���h�E�̃R���g���[���𑀍삵���Ƃ��ɌĂяo�����֐�
		// ============================================================================================
		void MyVSTGUIEditor::valueChanged(CControl* pControl)
		{
			// �ǂ̃p�����[�^�[�����삳�ꂽ�����擾����B
			int32 index = pControl->getTag();

			// �p�����[�^�[�̒l���擾����B
			float value = pControl->getValueNormalized();

			// �擾�����l���p�����[�^�[�ɔ��f������
			controller->setParamNormalized(index, value);

			// ���������N���X�ɔ��f�����l��ʒm����
			controller->performEdit(index, value);
		}

		// ============================================================================================
		// �e�R���g���[�����쐬���鎩��֐�
		// ============================================================================================
		void MyVSTGUIEditor::createKnob(ParamID tag, int x, int y)
		{
			// �m�u�R���g���[�����쐬����

			// �܂��͉摜�t�@�C����ǂݍ���
			CBitmap* backbmp = new CBitmap("knob.png");
			CBitmap* handlebmp = new CBitmap("knob_handle.png");

			// �m�u�R���g���[���̃T�C�Y���摜�t�@�C������擾����
			CRect size(0, 0, backbmp->getWidth(), backbmp->getHeight());

			// �m�u�R���g���[���̈ʒu���w��
			// �ʒu��ݒ�(frame�̍��オ0,0�ƂȂ�)
			size.offset(x, y);

			// �m�u�R���g���[���̍쐬
			CKnob* control = new CKnob(size, this, tag, backbmp, handlebmp);

			// �p�����[�^�̌��݂̒l���擾���A�R���g���[���ɔ��f
			// controller�͌p�����N���X�Œ�`����Ă���A
			// GUIEditor�N���X���Ăяo�����R���g���[������N���X�������B
			ParamValue value = controller->getParamNormalized(tag);
			control->setValueNormalized(value);

			// �m�u�R���g���[�����t���[���ɓo�^
			frame->addView(control);

			// �ǂݍ��񂾉摜�͖Y�ꂸ���
			backbmp->forget();
			handlebmp->forget();

		}

		// �X���C�_�[���쐬���郁���o�[�֐�
		void MyVSTGUIEditor::createSlider(ParamID tag, int x, int y)
		{
			// �X���C�_�[�̍쐬
			// �܂��͉摜�t�@�C����ǂݍ���
			CBitmap* backbmp = new CBitmap("slider.png");
			CBitmap* handlebmp = new CBitmap("slider_handle.png");

			// �摜�t�@�C������T�C�Y���擾����
			CRect  size;
			size(0, 0, backbmp->getWidth(), backbmp->getHeight());
			size.offset(x, y);   // �ʒu��ݒ�(tergetframe�̍��オ0,0�ƂȂ�)

			// �X���C�_�[�̍쐬
			// �X���C�_�[�n���h���̓X���C�_�[�w�i�摜�̏ォ�牺�܂œ����Ȃ��悤�A
			// �኱�̃}�[�W������������B���̃}�[�W���͉摜�ɂ���ĕς��
			int bmpmargin = 1;
			CVerticalSlider* control = new CVerticalSlider(size, this, tag,
				y + bmpmargin,
				y + backbmp->getHeight() - (handlebmp->getHeight() + bmpmargin),
				handlebmp, backbmp);

			// �p�����[�^�̌��݂̒l���擾���A�R���g���[���ɔ��f
			ParamValue value = controller->getParamNormalized(tag);
			control->setValueNormalized(value);

			// �X���C�_�[���t���[���ɓo�^
			frame->addView(control);

			// �ǂݍ��񂾉摜�͖Y�ꂸ���
			backbmp->forget();
			handlebmp->forget();

		}

		// �R���{�{�b�N�X���쐬���郁���o�[�֐�
		void MyVSTGUIEditor::createCombobox(ParamID tag, int x, int y)
		{
			// �R���{�{�b�N�X�̃T�C�Y��ݒ�(�T�C�Y�͓K��)
			CRect  size;
			size(0, 0, 60, 16);
			size.offset(x, y);

			// �R���{�{�b�N�X�쐬
			COptionMenu* control = new COptionMenu(size, this, tag);

			// �R���{�{�b�N�X�ɑI������ǉ�����
			control->addEntry("Volume");
			control->addEntry("Tremolo");
			control->addEntry("Panning");


			// �p�����[�^�̌��݂̒l���擾���A�R���{�{�b�N�X���f
			ParamValue value = controller->getParamNormalized(tag);
			control->setValueNormalized(value);

			// ���^�t�H���g���w��
			control->setFont(kNormalFontSmaller);

			// �����F�E�w�i�F��ݒ�
			control->setFontColor(kWhiteCColor);
			control->setBackColor(kBlackCColor);
			control->setFrameColor(kRedCColor);

			// �R���{�{�b�N�X���t���[���ɓo�^
			frame->addView(control);

		}

	}
} // namespace Steinberg��Vst�̏I���

*/