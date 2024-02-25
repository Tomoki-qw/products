# KSynth_beta

(2024/02/26最終更新)

## 概要

アナログモデリングのポリフォニックシンセサイザー。GUIは現在実装途中のため、DAWデフォルトのものが適用される(cubase 10 pro, ableton live 11 Suiteにて動作確認済み)。

## 詳細

### 機能

- オシレータ2基搭載
- 各オシレータの音色としてサイン波、ノコギリ波、三角波、矩形波、ホワイトノイズから選択
- 各オシレータそれぞれのADSR調整機能
- ピッチベンド機能
- サステイン機能
- 合成方式として、「アナログモデリングモード」と「FMモード」を切り替え可能
    - FMモードの場合、osc1がモジュレータ、osc2がキャリアとなる

### 実行方法

ビルド済みファイルはライセンスの関係上含めることができないため、以下に従ってビルドを行う。後述の開発環境にて動作確認済み。

https://steinbergmedia.github.io/vst3_dev_portal/pages/Tutorials/Using+cmake+for+building+plug-ins.html

### 開発環境

- visual studio 2019 community
- VST3 SDK 3.7.9
