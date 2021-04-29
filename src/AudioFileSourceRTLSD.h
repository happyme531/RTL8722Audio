#pragma once
#include "AudioFileSource.h"
#include "FatFs_SD.h"


class AudioFileSourceRTLSD : public AudioFileSource
{
  public:
    AudioFileSourceRTLSD();
    AudioFileSourceRTLSD(const char *filename);
    virtual ~AudioFileSourceRTLSD() override;
    
    virtual bool open(const char *filename) override;
    virtual uint32_t read(void *data, uint32_t len) override;
    virtual bool seek(int32_t pos, int dir) override;
    virtual bool close() override;
    virtual bool isOpen() override;
    virtual uint32_t getSize() override;
    virtual uint32_t getPos() override;

  private:
    FatFsSD fs;
    SdFatFile f;
};
