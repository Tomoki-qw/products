
// 自作VST用のインクルードファイル
#include "guieditor.h"

#include <string>
#include <locale>
#include <codecvt>
// VST3作成に必要なの名前空間を使用
namespace Steinberg {
	namespace Vst {

		// ============================================================================================
		// コンストラクタ
		// ============================================================================================
		MyVSTGUIEditor::MyVSTGUIEditor(void* controller)
			: VSTGUIEditor(controller)
		{
			//初期化
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
			// コンストラクタでウィンドウサイズを設定する
			// 設定しなければ、ウィンドウが開かない
			ViewRect viewRect(0, 0, 960, 540);
			setRect(viewRect);
		}
		// ============================================================================================
		// GUIウィンドウを開いたとき、閉じたときに呼び出される関数
		// ============================================================================================
		bool PLUGIN_API MyVSTGUIEditor::open(void* parent, const PlatformType& platformType)
		{
			// GUIウィンドウが開かれたときに、UIを作成する

			// まずはフレーム(配置領域)がすでに作成・設定されているか確認。
			// すでに作成・設定されている場合(frameがNULLでない場合)は終了
			// frameは継承元クラスで定義されている。
			if (frame) { return false; }

			// 作成するフレームのサイズを設定
			CRect size(0, 0, 960, 540);

			// フレームを作成。作成に失敗したら(NULLなら)終了。
			// 引数には、フレームサイズ、自作GUIクラスのポインタを指定する
			frame = new CFrame(size, this);
			if (frame == NULL) { return false; }

			// 作成したフレームに背景画像を設定
			CBitmap* cbmp = new CBitmap("background.png"); // リソースから背景画像を読み込む
			frame->setBackground(cbmp); // フレームに背景画像を設定
			cbmp->forget();	// フレームに設定後は背景画像はforgetで解放しておく

			// 作成したフレームを開く
			frame->open(parent);


			//　---------------------------------------------
			// ここから各コントローラの作成

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


			// GUIウィンドウのオープンに成功した場合はtrueを返す
			return true;
		}


		// GUIウィンドウを閉じたときに呼び出される関数
		void PLUGIN_API MyVSTGUIEditor::close()
		{
			// GUIウィンドウが閉じたときに、UIを削除する

			// フレームを解放
			// 背景画像や追加したつまみ(ノブ）やスライダーなどもあわせて解放される
			// (個別で解放する必要はない)
			if (frame)
			{
				frame->forget();
				frame = 0;
			}
		}

		// ============================================================================================
		// GUIウィンドウのコントローラを操作したときに呼び出される関数
		// ============================================================================================
		void MyVSTGUIEditor::valueChanged(CControl* pControl)
		{
			// どのパラメーターが操作されたかを取得する。
			int32 index = pControl->getTag();

			// パラメーターの値を取得する。
			float value = pControl->getValueNormalized();

			// 取得した値をパラメーターに反映させる
			controller->setParamNormalized(index, value);

			// 音声処理クラスに反映した値を通知する
			controller->performEdit(index, value);

			// 値を表示したいコントロールが操作されたかどうかを確認
			CControl* control = getTextPair(pControl);
			if (control != nullptr) {
				// パラメーターから文字列を取得
				String128 tmp;
				controller->getParamStringByValue(index, value, tmp);

				// tmp を std::u16string に変換
				std::u16string tmpString(tmp, tmp + std::char_traits<char16_t>::length(tmp));

				// UTF-16文字列をUTF-8に変換
				std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> convert;
				std::string utf8Text = convert.to_bytes(tmpString);

				// 取得した文字列をテキストラベルに設定
				((CTextLabel*)control)->setText(utf8Text.c_str());

				// テキストラベルコントロールを再描画する
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
		// 各コントローラを作成する自作関数
		// ============================================================================================
		CControl* MyVSTGUIEditor::createKnob(ParamID tag, int x, int y)
		{
			// ノブコントロールを作成する

			// まずは画像ファイルを読み込む
				CBitmap* backbmp = new CBitmap("knob.png");
				CBitmap* handlebmp = new CBitmap("knob_handle.png");
				
			

			// ノブコントロールのサイズを画像ファイルから取得する
			CRect size(0, 0, backbmp->getWidth(), backbmp->getHeight());

			// ノブコントロールの位置を指定
			// 位置を設定(frameの左上が0,0となる)
			size.offset(x, y);

			// ノブコントロールの作成
			CKnob* control = new CKnob(size, this, tag, backbmp, handlebmp);

			// パラメータの現在の値を取得し、コントローラに反映
			// controllerは継承元クラスで定義されており、
			// GUIEditorクラスを呼び出したコントローラ操作クラスを示す。
			ParamValue value = controller->getParamNormalized(tag);
			control->setValueNormalized(value);

			// ノブコントロールをフレームに登録
			frame->addView(control);

			// 読み込んだ画像は忘れず解放
			backbmp->forget();
			handlebmp->forget();

			return control;
		}
		CControl* MyVSTGUIEditor::createKnobTransparent(ParamID tag, int x, int y)
		{
			// ノブコントロールを作成する

			// まずは画像ファイルを読み込む
				CBitmap* backbmp = new CBitmap("knob_transparent.png");
				CBitmap* handlebmp = new CBitmap("knob_handle_transparent.png");




			// ノブコントロールのサイズを画像ファイルから取得する
			CRect size(0, 0, backbmp->getWidth(), backbmp->getHeight());

			// ノブコントロールの位置を指定
			// 位置を設定(frameの左上が0,0となる)
			size.offset(x, y);

			// ノブコントロールの作成
			CKnob* control = new CKnob(size, this, tag, backbmp, handlebmp);

			// パラメータの現在の値を取得し、コントローラに反映
			// controllerは継承元クラスで定義されており、
			// GUIEditorクラスを呼び出したコントローラ操作クラスを示す。
			ParamValue value = controller->getParamNormalized(tag);
			control->setValueNormalized(value);

			// ノブコントロールをフレームに登録
			frame->addView(control);

			// 読み込んだ画像は忘れず解放
			backbmp->forget();
			handlebmp->forget();

			return control;
		}


		// スライダーを作成するメンバー関数
		CControl* MyVSTGUIEditor::createSlider(ParamID tag, int x, int y)
		{
			// スライダーの作成
			// まずは画像ファイルを読み込む
			CBitmap* backbmp = new CBitmap("slider.png");
			CBitmap* handlebmp = new CBitmap("slider_handle.png");

			// 画像ファイルからサイズを取得する
			CRect  size;
			size(0, 0, backbmp->getWidth(), backbmp->getHeight());
			size.offset(x, y);   // 位置を設定(tergetframeの左上が0,0となる)

			// スライダーの作成
			// スライダーハンドルはスライダー背景画像の上から下まで動かないよう、
			// 若干のマージンを持たせる。このマージンは画像によって変わる
			int bmpmargin = 1;
			CVerticalSlider* control = new CVerticalSlider(size, this, tag,
				y + bmpmargin,
				y + backbmp->getHeight() - (handlebmp->getHeight() + bmpmargin),
				handlebmp, backbmp);

			// パラメータの現在の値を取得し、コントローラに反映
			ParamValue value = controller->getParamNormalized(tag);
			control->setValueNormalized(value);

			// スライダーをフレームに登録
			frame->addView(control);

			// 読み込んだ画像は忘れず解放
			backbmp->forget();
			handlebmp->forget();
			return control;
		}

		CControl* MyVSTGUIEditor::createHSlider(ParamID tag, int x, int y)
		{
			// 横型スライダーコントロールの作成

			// まずは画像ファイルを読み込む
			CBitmap* backbmp = new CBitmap("slider_h.png");
			CBitmap* handlebmp = new CBitmap("slider_handle_h.png");

			// 画像ファイルからサイズを取得する
			CRect  size;
			size(0, 0, backbmp->getWidth(), backbmp->getHeight());
			size.offset(x, y);   // 位置を設定(frameの左上が0,0となる)

			// コントロールの作成
			// スライダーハンドルはスライダー背景画像の上から下まで動かないよう、
			// 若干のマージンを持たせる。このマージンは画像によって変わる
			int bmpmargin = 1;
			CHorizontalSlider* control = new CHorizontalSlider(size, this, tag,
				x + bmpmargin,
				x + backbmp->getWidth() - (handlebmp->getWidth() + bmpmargin),
				handlebmp, backbmp);
			// コントロールのスタイルを変更し、ハンドルの動きを左から右に
			control->setStyle(CSliderBase::kLeft | CSliderBase::kHorizontal);
			// パラメータの現在の値を取得し、コントロールに反映
			ParamValue value = controller->getParamNormalized(tag);
			control->setValueNormalized(value);

			// スライダーをフレームに登録
			frame->addView(control);

			// 読み込んだ画像は忘れず解放
			backbmp->forget();
			handlebmp->forget();

			// 作成したコントロールのポインタを返す
			return control;
		}



		// コンボボックスを作成するメンバー関数
		void MyVSTGUIEditor::createComboboxWaveform(ParamID tag, int x, int y)
		{
			// コンボボックスのサイズを設定(サイズは適当)
			CRect  size;
			size(0, 0, 60, 20);
			size.offset(x, y);

			// コンボボックス作成
			COptionMenu* control = new COptionMenu(size, this, tag);

			// コンボボックスに選択肢を追加する
			control->addEntry("sine");
			control->addEntry("saw");
			control->addEntry("triangle");
			control->addEntry("pulse");
			control->addEntry("white noise");


			// パラメータの現在の値を取得し、コンボボックス反映
			ParamValue value = controller->getParamNormalized(tag);
			control->setValueNormalized(value);

			// 小型フォントを指定
			control->setFont(kNormalFontBig);

			// 文字色・背景色を設定
			control->setFontColor(kWhiteCColor);
			control->setBackColor(kTransparentCColor);
			control->setFrameColor(kTransparentCColor);

			// コンボボックスをフレームに登録
			frame->addView(control);

		}

		void MyVSTGUIEditor::createComboboxOct(ParamID tag, int x, int y)
		{
			// コンボボックスのサイズを設定(サイズは適当)
			CRect  size;
			size(0, 0, 60, 16);
			size.offset(x, y);

			// コンボボックス作成
			COptionMenu* control = new COptionMenu(size, this, tag);

			// コンボボックスに選択肢を追加する
			control->addEntry("-4");
			control->addEntry("-3");
			control->addEntry("-2");
			control->addEntry("-1");
			control->addEntry("0");


			// パラメータの現在の値を取得し、コンボボックス反映
			ParamValue value = controller->getParamNormalized(tag);
			control->setValueNormalized(value);

			// 小型フォントを指定
			control->setFont(kNormalFontBig);

			// 文字色・背景色を設定
			control->setFontColor(kWhiteCColor);
			control->setBackColor(kTransparentCColor);
			control->setFrameColor(kTransparentCColor);

			// コンボボックスをフレームに登録
			frame->addView(control);

		}

		void MyVSTGUIEditor::createComboboxFilter(ParamID tag, int x, int y)
		{
			// コンボボックスのサイズを設定(サイズは適当)
			CRect  size;
			size(0, 0, 60, 20);
			size.offset(x, y);

			// コンボボックス作成
			COptionMenu* control = new COptionMenu(size, this, tag);

			// コンボボックスに選択肢を追加する
			control->addEntry("off");
			control->addEntry("lowpass");
			control->addEntry("highpass");
			control->addEntry("bandpass");
			control->addEntry("notch");
			control->addEntry("lowshelf");
			control->addEntry("highshelf");
			control->addEntry("peaking");
			control->addEntry("allpass");

			// パラメータの現在の値を取得し、コンボボックス反映
			ParamValue value = controller->getParamNormalized(tag);
			control->setValueNormalized(value);

			// 小型フォントを指定
			control->setFont(kNormalFontBig);

			// 文字色・背景色を設定
			control->setFontColor(kWhiteCColor);
			control->setBackColor(kTransparentCColor);
			control->setFrameColor(kTransparentCColor);

			// コンボボックスをフレームに登録
			frame->addView(control);

		}

		CControl* MyVSTGUIEditor::createTextLabel(int x, int y, UTF8StringPtr text)
		{
			// テキストラベルコントロールを作成する
			
			// コントロールのサイズを設定(サイズは適当)
			CRect  size;
			size(0, 0, 60, 20);
			size.offset(x, y);   // 位置を設定(frameの左上が0,0となる)

			// コントロール作成
			CTextLabel* control = new CTextLabel(size, text);

			// 小型フォントを指定
			control->setFont(kNormalFontBig);

			// 文字色・背景色を設定
			control->setFontColor(kWhiteCColor);
			control->setBackColor(kTransparentCColor);
			control->setFrameColor(kTransparentCColor);

			// コントロールをフレームに登録
			frame->addView(control);

			// 作成したコントロールのポインタを返す
			return control;
		}

		CControl* MyVSTGUIEditor::createTextValue(ParamID tag, int x, int y)
		{
			// テキストラベルコントロールを作成する

			// コントロールのサイズを設定(サイズは適当)
			CRect  size;
			size(0, 0, 60, 15);
			size.offset(x, y);   // 位置を設定(frameの左上が0,0となる)

			// コントロール作成
			CTextLabel* control = new CTextLabel(size);

			// フォントを指定
			control->setFont(kNormalFontBig);

			// 文字色・背景色を設定
			control->setFontColor(kGreyCColor);
			control->setBackColor(kTransparentCColor);
			control->setFrameColor(kTransparentCColor);

			// コントロールをフレームに登録
			frame->addView(control);

			// 作成したコントロールのポインタを返す
			return control;
		}

		CControl* MyVSTGUIEditor::createOnOffButton(ParamID tag, int x, int y, UTF8StringPtr filename)
		{
			// オン・オフボタンコントロールを作成する

			// まずは画像ファイルを読み込む
			CBitmap* bmp = new CBitmap(filename);

			// コントロールのサイズを画像ファイルから取得する
			// オン状態とオフ状態が1つの画像(上下で)になっているので、高さは1/2にする
			CRect size(0, 0, bmp->getWidth(), bmp->getHeight() / 2);
			size.offset(x, y);   // 位置を設定(frameの左上が0,0となる)

			// コントロールの作成
			COnOffButton* control = new COnOffButton(size, this, tag, bmp);

			// パラメータの現在の値を取得し、コントロールに反映
			ParamValue value = controller->getParamNormalized(tag);
			control->setValueNormalized(value);

			// コントロールをフレームに登録
			frame->addView(control);

			// 読み込んだ画像は忘れず解放
			bmp->forget();

			// 作成したコントロールのポインタを返す
			return control;
		}

	}
} // namespace SteinbergとVstの終わり

