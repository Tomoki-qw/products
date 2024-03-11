
// ����VST�p�̃C���N���[�h�t�@�C��
#include "guieditor.h"

#include <string>
#include <locale>
#include <codecvt>
// VST3�쐬�ɕK�v�Ȃ̖��O��Ԃ��g�p
namespace Steinberg {
	namespace Vst {

		// ============================================================================================
		// �R���X�g���N�^
		// ============================================================================================
		MyVSTGUIEditor::MyVSTGUIEditor(void* controller)
			: VSTGUIEditor(controller)
		{
			//������
			masterVolKnob = nullptr;
			masterVolDisp = nullptr;
			o1VolKnob = nullptr;
			o1VolDisp = nullptr;
			o2VolKnob = nullptr;
			o2VolDisp = nullptr;
			o3VolKnob = nullptr;
			o3VolDisp = nullptr;
			o1ModCoarceKnob = nullptr;
			o1ModCoarceDisp = nullptr;
			o2ModCoarceKnob = nullptr;
			o2ModCoarceDisp = nullptr;
			o3ModCoarceKnob = nullptr;
			o3ModCoarceDisp = nullptr;
			o1ModOctSlider = nullptr;
			o1ModOctDisp = nullptr;
			o2ModOctSlider = nullptr;
			o2ModOctDisp = nullptr;
			o3ModOctSlider = nullptr;
			o3ModOctDisp = nullptr;

			o1FilterFreq = nullptr;
			o1FilterQ = nullptr;
			o1FilterGain = nullptr;
			o2FilterFreq = nullptr;
			o2FilterQ = nullptr;
			o2FilterFreq = nullptr;
			o3FilterQ = nullptr;
			o3FilterGain = nullptr;
			o3FilterGain = nullptr;
			// �R���X�g���N�^�ŃE�B���h�E�T�C�Y��ݒ肷��
			// �ݒ肵�Ȃ���΁A�E�B���h�E���J���Ȃ�
			ViewRect viewRect(0, 0, 960, 540);
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
			CRect size(0, 0, 960, 540);

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

			createOnOffButton(SYNTH_MODE, 78, 470, "fm_mode.png");
			createOnOffButton(SUSTAIN_TAG, 602, 50, "normal_switch.png");
			createHSlider(PITCHBEND_TAG, 725, 60);

			int mF1x = 120;
			int mF1y = 190;
		
			o1ModCoarceKnob = createKnob(MOD_COARSE1_TAG, mF1x, mF1y);
			o1ModCoarceDisp = createTextValue(MOD_COARSE1_TAG, mF1x - 10, mF1y + 10);
			createTextLabel(mF1x - 10, mF1y + 40, "crs");

			int mF2x = 120;
			int mF2y = 297;
			
			o2ModCoarceKnob = createKnob(MOD_COARSE2_TAG, mF2x, mF2y);
			o2ModCoarceDisp = createTextValue(MOD_COARSE2_TAG, mF2x - 10, mF2y + 10);
			createTextLabel(mF2x - 10, mF2y + 40, "crs");

			int mF3x = 120;
			int mF3y = 404;

			o3ModCoarceKnob = createKnob(MOD_COARSE3_TAG, mF3x, mF3y);
			o3ModCoarceDisp = createTextValue(MOD_COARSE3_TAG, mF3x - 10, mF3y + 10);
			createTextLabel(mF3x - 10, mF3y + 40, "crs");

			int mVx = 848;
			int mVy = 38;
			masterVolKnob = createKnob(VOLUME_TAG_MASTER, mVx, mVy);
			//masterVolDisp = createTextValue(VOLUME_TAG_MASTER, mVx-10, mVy+40);
			createTextLabel(mVx-10, mVy+40, "vol");

			int o1Vx = 610;
			int o1Vy = 175;
			o1VolKnob = createKnob(VOLUME_TAG_1, o1Vx, o1Vy);
			createTextLabel(o1Vx - 10, o1Vy + 40, "vol");

			int o2Vx = 610;
			int o2Vy = 282;
			o2VolKnob = createKnob(VOLUME_TAG_2, o2Vx, o2Vy);
			createTextLabel(o2Vx - 10, o2Vy + 40, "vol");

			int o3Vx = 610;
			int o3Vy = 389;
			o3VolKnob = createKnob(VOLUME_TAG_3, o3Vx, o3Vy);
			createTextLabel(o3Vx - 10, o3Vy + 40, "vol");

			createComboboxWaveform(WAVEFORM_TAG1, 57, 153);
			createComboboxWaveform(WAVEFORM_TAG2, 57, 260);
			createComboboxWaveform(WAVEFORM_TAG3, 57, 367);

			createSlider(ADSR_OSC1_A, 514, 160);
			createTextLabel(489, 220, "A");
			createSlider(ADSR_OSC1_D, 540, 160);
			createTextLabel(515, 220, "D");
			createSlider(ADSR_OSC1_S, 566, 160);
			createTextLabel(541, 220, "S");
			createSlider(ADSR_OSC1_R, 592, 160);
			createTextLabel(567, 220, "R");

			createSlider(ADSR_OSC2_A, 514, 267);
			createTextLabel(489, 327, "A");
			createSlider(ADSR_OSC2_D, 540, 267);
			createTextLabel(515, 327, "D");
			createSlider(ADSR_OSC2_S, 566, 267);
			createTextLabel(541, 327, "S");
			createSlider(ADSR_OSC2_R, 592, 267);
			createTextLabel(567, 327, "R");

			createSlider(ADSR_OSC3_A, 514, 374);
			createTextLabel(489, 434, "A");
			createSlider(ADSR_OSC3_D, 540, 374);
			createTextLabel(515, 434, "D");
			createSlider(ADSR_OSC3_S, 566, 374);
			createTextLabel(541, 434, "S");
			createSlider(ADSR_OSC3_R, 592, 374);
			createTextLabel(567, 434, "R");

			o1ModOctSlider = createHSlider(MOD_OCT1_TAG, 115, 157);
			createTextLabel(110, 165, "oct");

			o2ModOctSlider = createHSlider(MOD_OCT2_TAG, 115, 264);
			createTextLabel(110, 272, "oct");

			o3ModOctSlider = createHSlider(MOD_OCT3_TAG, 115, 374);
			createTextLabel(110, 379, "oct");



			createComboboxFilter(O1_FILTER_TYPE, 250, 153);
			createComboboxFilter(O2_FILTER_TYPE, 250, 260);
			createComboboxFilter(O3_FILTER_TYPE, 250, 367);
			int x1 = 290;
			int x2 = 340;
			int x3 = 390;
			int y1 = 175;
			int y2 = 282;
			int y3 = 389;

			o1FilterFreq = createKnob(O1_FILTER_FREQ, x1, y1);
			o1FilterQ = createKnob(O1_FILTER_Q, x2, y1);
			o1FilterGain = createKnob(O1_FILTER_GAIN, x3, y1);
			o2FilterFreq = createKnob(O2_FILTER_FREQ, x1, y2);
			o2FilterQ = createKnob(O2_FILTER_Q, x2, y2);
			o2FilterGain = createKnob(O2_FILTER_GAIN, x3, y2);
			o3FilterFreq = createKnob(O3_FILTER_FREQ, x1, y3);
			o3FilterQ = createKnob(O3_FILTER_Q, x2, y3);
			o3FilterGain = createKnob(O3_FILTER_GAIN, x3, y3);

			createTextLabel(x1 - 10, y1 + 40, "freq");
			createTextLabel(x2 - 10, y1 + 40, "q");
			createTextLabel(x3 - 10, y1 + 40, "gain");
			createTextLabel(x1 - 10, y2 + 40, "freq");
			createTextLabel(x2 - 10, y2 + 40, "q");
			createTextLabel(x3 - 10, y2 + 40, "gain");
			createTextLabel(x1 - 10, y3 + 40, "freq");
			createTextLabel(x2 - 10, y3 + 40, "q");
			createTextLabel(x3 - 10, y3 + 40, "gain");

			//distortion
			int dist_x1 = 780;
			int dist_y1 = 170;
			int dist_x2 = 830;
			int dist_y2 = 170;
			createOnOffButton(DIST_ONOFF, 720, 185, "normal_switch.png");
			createKnob(DIST_GAIN, dist_x1, dist_y1);
			createTextLabel(dist_x1 - 10, dist_y1 + 40, "gain");
			createKnob(DIST_VOLUME, dist_x2, dist_y2);
			createTextLabel(dist_x2 - 10, dist_y2 + 40, "volume");
			//chorus
			int chorus_x1 = 780;
			int chorus_y1 = 277;
			int chorus_x2 = 830;
			int chorus_y2 = 277;
			int chorus_x3 = 780;
			int chorus_y3 = 357;
			int chorus_x4 = 830;
			int chorus_y4 = 357;
			createOnOffButton(CHORUS_ONOFF, 720, 292, "normal_switch.png");
			createKnob(CHORUS_MIX, chorus_x1, chorus_y1);
			createTextLabel(chorus_x1 - 10, chorus_y1 + 40, "mix");
			createKnob(CHORUS_RATE, chorus_x2, chorus_y2);
			createTextLabel(chorus_x2 - 10, chorus_y2 + 40, "rate");
			createKnob(CHORUS_DEPTH, chorus_x3, chorus_y3);
			createTextLabel(chorus_x3 - 10, chorus_y3 + 40, "depth");
			createKnob(CHORUS_FEEDBACK, chorus_x4, chorus_y4);
			createTextLabel(chorus_x4 - 10, chorus_y4 + 40, "feedback");


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

			// �l��\���������R���g���[�������삳�ꂽ���ǂ������m�F
			CControl* control = getTextPair(pControl);
			if (control != nullptr) {
				// �p�����[�^�[���當������擾
				String128 tmp;
				controller->getParamStringByValue(index, value, tmp);

				// tmp �� std::u16string �ɕϊ�
				std::u16string tmpString(tmp, tmp + std::char_traits<char16_t>::length(tmp));

				// UTF-16�������UTF-8�ɕϊ�
				std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> convert;
				std::string utf8Text = convert.to_bytes(tmpString);

				// �擾������������e�L�X�g���x���ɐݒ�
				((CTextLabel*)control)->setText(utf8Text.c_str());

				// �e�L�X�g���x���R���g���[�����ĕ`�悷��
				control->setDirty();
			}
		}
		CControl* MyVSTGUIEditor::getTextPair(CControl* control) {
			//if (control == masterVolKnob)return masterVolDisp;
			//else if (control == o1VolKnob)return o1VolDisp;
			//else if (control == o2VolKnob)return o2VolDisp;
			//else return nullptr;
			if (control == o1ModCoarceKnob)return o1ModCoarceDisp;
			else if (control == o2ModCoarceKnob)return o2ModCoarceDisp;
			else if (control == o3ModCoarceKnob)return o3ModCoarceDisp;
			else return nullptr;
		}
		;
		// ============================================================================================
		// �e�R���g���[�����쐬���鎩��֐�
		// ============================================================================================
		CControl* MyVSTGUIEditor::createKnob(ParamID tag, int x, int y)
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

			return control;
		}
		CControl* MyVSTGUIEditor::createKnobTransparent(ParamID tag, int x, int y)
		{
			// �m�u�R���g���[�����쐬����

			// �܂��͉摜�t�@�C����ǂݍ���
				CBitmap* backbmp = new CBitmap("knob_transparent.png");
				CBitmap* handlebmp = new CBitmap("knob_handle_transparent.png");




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

			return control;
		}


		// �X���C�_�[���쐬���郁���o�[�֐�
		CControl* MyVSTGUIEditor::createSlider(ParamID tag, int x, int y)
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
			return control;
		}

		CControl* MyVSTGUIEditor::createHSlider(ParamID tag, int x, int y)
		{
			// ���^�X���C�_�[�R���g���[���̍쐬

			// �܂��͉摜�t�@�C����ǂݍ���
			CBitmap* backbmp = new CBitmap("slider_h.png");
			CBitmap* handlebmp = new CBitmap("slider_handle_h.png");

			// �摜�t�@�C������T�C�Y���擾����
			CRect  size;
			size(0, 0, backbmp->getWidth(), backbmp->getHeight());
			size.offset(x, y);   // �ʒu��ݒ�(frame�̍��オ0,0�ƂȂ�)

			// �R���g���[���̍쐬
			// �X���C�_�[�n���h���̓X���C�_�[�w�i�摜�̏ォ�牺�܂œ����Ȃ��悤�A
			// �኱�̃}�[�W������������B���̃}�[�W���͉摜�ɂ���ĕς��
			int bmpmargin = 1;
			CHorizontalSlider* control = new CHorizontalSlider(size, this, tag,
				x + bmpmargin,
				x + backbmp->getWidth() - (handlebmp->getWidth() + bmpmargin),
				handlebmp, backbmp);
			// �R���g���[���̃X�^�C����ύX���A�n���h���̓�����������E��
			control->setStyle(CSliderBase::kLeft | CSliderBase::kHorizontal);
			// �p�����[�^�̌��݂̒l���擾���A�R���g���[���ɔ��f
			ParamValue value = controller->getParamNormalized(tag);
			control->setValueNormalized(value);

			// �X���C�_�[���t���[���ɓo�^
			frame->addView(control);

			// �ǂݍ��񂾉摜�͖Y�ꂸ���
			backbmp->forget();
			handlebmp->forget();

			// �쐬�����R���g���[���̃|�C���^��Ԃ�
			return control;
		}



		// �R���{�{�b�N�X���쐬���郁���o�[�֐�
		void MyVSTGUIEditor::createComboboxWaveform(ParamID tag, int x, int y)
		{
			// �R���{�{�b�N�X�̃T�C�Y��ݒ�(�T�C�Y�͓K��)
			CRect  size;
			size(0, 0, 60, 20);
			size.offset(x, y);

			// �R���{�{�b�N�X�쐬
			COptionMenu* control = new COptionMenu(size, this, tag);

			// �R���{�{�b�N�X�ɑI������ǉ�����
			control->addEntry("sine");
			control->addEntry("saw");
			control->addEntry("triangle");
			control->addEntry("pulse");
			control->addEntry("white noise");


			// �p�����[�^�̌��݂̒l���擾���A�R���{�{�b�N�X���f
			ParamValue value = controller->getParamNormalized(tag);
			control->setValueNormalized(value);

			// ���^�t�H���g���w��
			control->setFont(kNormalFontBig);

			// �����F�E�w�i�F��ݒ�
			control->setFontColor(kWhiteCColor);
			control->setBackColor(kTransparentCColor);
			control->setFrameColor(kTransparentCColor);

			// �R���{�{�b�N�X���t���[���ɓo�^
			frame->addView(control);

		}

		void MyVSTGUIEditor::createComboboxOct(ParamID tag, int x, int y)
		{
			// �R���{�{�b�N�X�̃T�C�Y��ݒ�(�T�C�Y�͓K��)
			CRect  size;
			size(0, 0, 60, 16);
			size.offset(x, y);

			// �R���{�{�b�N�X�쐬
			COptionMenu* control = new COptionMenu(size, this, tag);

			// �R���{�{�b�N�X�ɑI������ǉ�����
			control->addEntry("-4");
			control->addEntry("-3");
			control->addEntry("-2");
			control->addEntry("-1");
			control->addEntry("0");


			// �p�����[�^�̌��݂̒l���擾���A�R���{�{�b�N�X���f
			ParamValue value = controller->getParamNormalized(tag);
			control->setValueNormalized(value);

			// ���^�t�H���g���w��
			control->setFont(kNormalFontBig);

			// �����F�E�w�i�F��ݒ�
			control->setFontColor(kWhiteCColor);
			control->setBackColor(kTransparentCColor);
			control->setFrameColor(kTransparentCColor);

			// �R���{�{�b�N�X���t���[���ɓo�^
			frame->addView(control);

		}

		void MyVSTGUIEditor::createComboboxFilter(ParamID tag, int x, int y)
		{
			// �R���{�{�b�N�X�̃T�C�Y��ݒ�(�T�C�Y�͓K��)
			CRect  size;
			size(0, 0, 60, 20);
			size.offset(x, y);

			// �R���{�{�b�N�X�쐬
			COptionMenu* control = new COptionMenu(size, this, tag);

			// �R���{�{�b�N�X�ɑI������ǉ�����
			control->addEntry("off");
			control->addEntry("lowpass");
			control->addEntry("highpass");
			control->addEntry("bandpass");
			control->addEntry("notch");
			control->addEntry("lowshelf");
			control->addEntry("highshelf");
			control->addEntry("peaking");
			control->addEntry("allpass");

			// �p�����[�^�̌��݂̒l���擾���A�R���{�{�b�N�X���f
			ParamValue value = controller->getParamNormalized(tag);
			control->setValueNormalized(value);

			// ���^�t�H���g���w��
			control->setFont(kNormalFontBig);

			// �����F�E�w�i�F��ݒ�
			control->setFontColor(kWhiteCColor);
			control->setBackColor(kTransparentCColor);
			control->setFrameColor(kTransparentCColor);

			// �R���{�{�b�N�X���t���[���ɓo�^
			frame->addView(control);

		}

		CControl* MyVSTGUIEditor::createTextLabel(int x, int y, UTF8StringPtr text)
		{
			// �e�L�X�g���x���R���g���[�����쐬����
			
			// �R���g���[���̃T�C�Y��ݒ�(�T�C�Y�͓K��)
			CRect  size;
			size(0, 0, 60, 20);
			size.offset(x, y);   // �ʒu��ݒ�(frame�̍��オ0,0�ƂȂ�)

			// �R���g���[���쐬
			CTextLabel* control = new CTextLabel(size, text);

			// ���^�t�H���g���w��
			control->setFont(kNormalFontBig);

			// �����F�E�w�i�F��ݒ�
			control->setFontColor(kWhiteCColor);
			control->setBackColor(kTransparentCColor);
			control->setFrameColor(kTransparentCColor);

			// �R���g���[�����t���[���ɓo�^
			frame->addView(control);

			// �쐬�����R���g���[���̃|�C���^��Ԃ�
			return control;
		}

		CControl* MyVSTGUIEditor::createTextValue(ParamID tag, int x, int y)
		{
			// �e�L�X�g���x���R���g���[�����쐬����

			// �R���g���[���̃T�C�Y��ݒ�(�T�C�Y�͓K��)
			CRect  size;
			size(0, 0, 60, 15);
			size.offset(x, y);   // �ʒu��ݒ�(frame�̍��オ0,0�ƂȂ�)

			// �R���g���[���쐬
			CTextLabel* control = new CTextLabel(size);

			// �t�H���g���w��
			control->setFont(kNormalFontBig);

			// �����F�E�w�i�F��ݒ�
			control->setFontColor(kGreyCColor);
			control->setBackColor(kTransparentCColor);
			control->setFrameColor(kTransparentCColor);

			// �R���g���[�����t���[���ɓo�^
			frame->addView(control);

			// �쐬�����R���g���[���̃|�C���^��Ԃ�
			return control;
		}

		CControl* MyVSTGUIEditor::createOnOffButton(ParamID tag, int x, int y, UTF8StringPtr filename)
		{
			// �I���E�I�t�{�^���R���g���[�����쐬����

			// �܂��͉摜�t�@�C����ǂݍ���
			CBitmap* bmp = new CBitmap(filename);

			// �R���g���[���̃T�C�Y���摜�t�@�C������擾����
			// �I����ԂƃI�t��Ԃ�1�̉摜(�㉺��)�ɂȂ��Ă���̂ŁA������1/2�ɂ���
			CRect size(0, 0, bmp->getWidth(), bmp->getHeight() / 2);
			size.offset(x, y);   // �ʒu��ݒ�(frame�̍��オ0,0�ƂȂ�)

			// �R���g���[���̍쐬
			COnOffButton* control = new COnOffButton(size, this, tag, bmp);

			// �p�����[�^�̌��݂̒l���擾���A�R���g���[���ɔ��f
			ParamValue value = controller->getParamNormalized(tag);
			control->setValueNormalized(value);

			// �R���g���[�����t���[���ɓo�^
			frame->addView(control);

			// �ǂݍ��񂾉摜�͖Y�ꂸ���
			bmp->forget();

			// �쐬�����R���g���[���̃|�C���^��Ԃ�
			return control;
		}

	}
} // namespace Steinberg��Vst�̏I���

