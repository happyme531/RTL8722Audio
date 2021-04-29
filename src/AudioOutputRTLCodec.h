#pragma once

#include "AudioOutput.h"

class AudioOutputRTLCodec : public AudioOutput
{
  public:
    AudioOutputRTLCodec(long sampleRate = 44100);
    virtual ~AudioOutputRTLCodec() override;
    virtual bool SetRate(int hz) override;
    virtual bool SetBitsPerSample(int bits) override;
    virtual bool SetChannels(int channels) override;
    virtual bool begin() override;
    virtual bool ConsumeSample(int16_t sample[2]) override;
    virtual void flush() override;
    virtual bool stop() override;
  
};
