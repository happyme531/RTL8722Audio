#include "AudioOutputRTLCodec.h"
#include <AudioCodec.h>
#include <cinttypes>

static int16_t buf[384];
static int buf_s = 0;

AudioOutputRTLCodec::AudioOutputRTLCodec(long sampleRate) {
  Codec.setSampleRate(sampleRate);
}
AudioOutputRTLCodec::~AudioOutputRTLCodec(){
}
bool AudioOutputRTLCodec::SetRate(int hz){
  Codec.setSampleRate(hz);
  return true;
}
bool AudioOutputRTLCodec::SetBitsPerSample(int bits){
  Codec.setBitDepth(bits);
  return true;
}
bool AudioOutputRTLCodec::SetChannels(int channels){
  Codec.setChannelCount(channels);
  return true;
}
bool AudioOutputRTLCodec::begin(){
  Codec.setChannelCount(2);
  Codec.begin(false, true);
  return true;
}
bool AudioOutputRTLCodec::ConsumeSample(int16_t sample[2]){
  buf[buf_s] = sample[0];
  buf[buf_s+1] = sample[1];
  buf_s += 2;
  if(buf_s >= 384){
    buf_s = 0;
    while(!Codec.writeAvaliable());
    Codec.writeDataPage(buf, 384);
  }
  return true;
}
void AudioOutputRTLCodec::flush(){
  while(!Codec.writeAvaliable());
  Codec.writeDataPage(buf, buf_s);
  buf_s = 0;
}

bool AudioOutputRTLCodec::stop(){
  Codec.end();
  return true;
}