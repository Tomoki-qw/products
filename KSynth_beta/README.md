# KSynth_beta

(2024/03/06最終更新)

## 概要

加算合成方式とFM合成方式両方を搭載したポリフォニックシンセサイザー。**GUIは現在実装途中。** cubase 10 pro, ableton live 11 Suiteにて動作確認済み。

## 詳細

### 機能

- オシレータ3基搭載
- 各オシレータの音色としてサイン波、ノコギリ波、三角波、矩形波、ホワイトノイズから選択
- 各オシレータそれぞれのADSR調整機能
- ピッチベンド機能
- サステイン機能
- 合成方式として、「加算モード」と「FMモード」を切り替え可能
    - FMモードの場合、osc1がキャリア、osc2、3がモジュレータとなる

### 実行方法

ビルド済みファイルはライセンスの関係上含めることができないため、以下に従ってビルドを行う。後述の開発環境にてビルド成功確認済み。

https://steinbergmedia.github.io/vst3_dev_portal/pages/Tutorials/Using+cmake+for+building+plug-ins.html

※**ビルドの際、SDKのうち以下ファイルを本プログラムのソースコードと同ディレクトリに配置する必要あり。**

- VST_SDK\vst3sdk\public.sdk\source\main\dllmain.cpp

### 開発環境
- windows 10 home
- visual studio 2019 community
- VST3 SDK 3.7.9
