# LD3320语音识别模块和TTS20语音合成模块的综合程序

该程序在Arduino实现了一个简单的语音交互功能，使用语音控制Led灯，并使用语音播报来回复，用来模拟智能音箱的应用场景。

## 安装库

需要安装Arduino LD3320语音识别库和TTS20语音合成库，请参考文档：

- LD3320语音识别库：<https://docs.emakefun.com/#/zh-cn/ph2.0_sensors/smart_module/speech_recognizer/speech_recognizer>

- TTS20语音合成库：<https://docs.emakefun.com/#/zh-cn/ph2.0_sensors/smart_module/tts20_module/tts20_module>

## 使用

- 对着语音识别模块说"小易小易"进行唤醒，唤醒成功后语音播报模块会回答: "在呢"。

- 唤醒后对着语音识别说: "请开灯"，led灯会亮，语音合成模块会播报："已开灯"，并重新等待唤醒。

- 唤醒后对着语音识别说: "请关灯"，led灯会灭，语音合成模块会播报："已关灯"，并重新等待唤醒。

- 唤醒后如果10秒内未识别到新的指令，则播报"有需要再叫我"，并重新等待唤醒。
