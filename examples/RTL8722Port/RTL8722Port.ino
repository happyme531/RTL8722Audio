#include <Arduino.h>
#include <AudioFileSourceRTLSD.h>
#include <AudioOutputRTLCodec.h>
#include <AudioGeneratorFLAC.h>
#include <AudioCodec.h>

AudioFileSourceRTLSD *source = NULL;
AudioOutputRTLCodec *output = NULL;
AudioGeneratorFLAC *decoder = NULL;

void setup() {
  Serial.begin(115200);
  Serial.println();
  delay(1000);

  audioLogger = &Serial;  
  source = new AudioFileSourceRTLSD();
  output = new AudioOutputRTLCodec();
  decoder = new AudioGeneratorFLAC();
  source->open("test.flac");
  decoder->begin(source,output);
  Codec.setOutputVolume(55, 55);
}

void loop(){
   if (decoder->isRunning()) {
    if (!decoder->loop()) decoder->stop();
  } else {
    Serial.println("Decode done");
    delay(1000);
  }
}