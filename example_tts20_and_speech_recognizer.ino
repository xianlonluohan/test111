#include <Arduino.h>

#include "speech_recognizer.h"
#include "tts20.h"

namespace {
constexpr uint8_t g_led_pin = 3;

constexpr uint32_t kSpeechRecognizerTimeoutMs = 10000;

emakefun::SpeechRecognizer g_speech_recognizer(emakefun::SpeechRecognizer::kDefaultI2cAddress);

em::Tts20 g_tts20(em::Tts20::kDefaultI2cAddress, Wire);

}  // namespace

void setup() {
  Serial.begin(115200);
  Serial.println(F("setup"));

  Wire.begin();

  g_tts20.Init();

  Serial.println(F("TTS20 module initialization was successful"));

  const auto result = g_speech_recognizer.Initialize(&Wire);
  if (0 == result) {
    Serial.println(F("speech recognizer initialization was successful"));
  } else {
    Serial.println(String(F("speech recognizer initialization failed: ")) + result);
    while (true);
  }

  g_speech_recognizer.SetRecognitionMode(emakefun::SpeechRecognizer::kKeywordTrigger);
  g_speech_recognizer.SetTimeout(kSpeechRecognizerTimeoutMs);
  g_speech_recognizer.AddKeyword(0, F("xiao yi xiao yi"));
  g_speech_recognizer.AddKeyword(1, F("qing kai deng"));
  g_speech_recognizer.AddKeyword(2, F("qing guan deng"));

  pinMode(g_led_pin, OUTPUT);
  digitalWrite(g_led_pin, LOW);

  Serial.println(F("setup done"));
}

void loop() {
  const auto result = g_speech_recognizer.Recognize();
  switch (result) {
    case 1: {
      Serial.println(F("已开灯"));
      g_tts20.Play(F("已开灯"));
      digitalWrite(g_led_pin, HIGH);
      break;
    }
    case 2: {
      Serial.println(F("已关灯"));
      g_tts20.Play(F("已关灯"));
      digitalWrite(g_led_pin, LOW);
      break;
    }
    default: {
      break;
    }
  }

  switch (g_speech_recognizer.GetEvent()) {
    case emakefun::SpeechRecognizer::kEventKeywordTriggered: {
      Serial.println(F("在呢"));
      g_tts20.Play(F("在呢"));
      break;
    }

    case emakefun::SpeechRecognizer::kEventSpeechRecognitionTimedOut: {
      Serial.println(F("有需要再叫我"));
      g_tts20.Play(F("有需要再叫我"));
      break;
    }
    default: {
      break;
    }
  }
}
