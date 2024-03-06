
#ifndef __GUIEDITOR_H__
#define __GUIEDITOR_H__

// VST3 SDKのインクルードファイル
#include "public.sdk/source/vst/vstguieditor.h"
#include "pluginterfaces/vst/ivstplugview.h"

// 自作VST用のインクルードファイル
#include "myvst3def.h"

// VST3作成に必要なの名前空間を使用
namespace Steinberg {
	namespace Vst {

		using namespace VSTGUI;

		// ============================================================================================
		// VSTのGUIクラス
		// ============================================================================================
		class MyVSTGUIEditor : public VSTGUIEditor, public IControlListener
		{
		protected:
			//マスター
			//ボリューム
			CControl* masterVolKnob;
			CControl* masterVolDisp;

			//オシレータ1
			//ボリューム
			CControl* o1VolKnob;
			CControl* o1VolDisp;
			
			//オシレータ2
			//ボリューム
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
			// コンストラクタ(必須)
			MyVSTGUIEditor(void* controller);

			// GUIウィンドウを開いたときに呼び出される関数(必須)
			virtual bool PLUGIN_API open(void* parent, const PlatformType& platformType = PlatformType::kDefaultNative);

			// GUIウィンドウを閉じたときに呼び出される関数(必須)
			virtual void PLUGIN_API close();

			// GUIウィンドウのコントローラを操作したときに呼び出される関数(必須)
			void valueChanged(CControl* pControl);

			// 自作関数
			// ノブコントロールを作成する関数
			CControl* createKnob(ParamID tag, int x, int y);
			CControl* createKnobTransparent(ParamID tag, int x, int y);
			CControl* createSlider(ParamID tag, int x, int y);
			CControl* createHSlider(ParamID tag, int x, int y);
			void createComboboxWaveform(ParamID tag, int x, int y);
			void createComboboxOct(ParamID tag, int x, int y);
			CControl*  createTextLabel(int x, int y, UTF8StringPtr text);
			CControl* createTextValue(ParamID tag, int x, int y);
			CControl* createOnOffButton(ParamID tag, int x, int y, UTF8StringPtr filename);
			//操作したノブに対応しているテキストを見つける
			CControl* getTextPair(CControl* control);
			// VSTGUIEditorクラスの各種設定を自作GUIクラス置き換えるマクロ(必須)
			DELEGATE_REFCOUNT(VSTGUIEditor)
		};



	}
} // namespace SteinbergとVstの終わり

#endif
