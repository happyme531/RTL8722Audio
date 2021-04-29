#include "AudioFileSourceRTLSD.h"

AudioFileSourceRTLSD::AudioFileSourceRTLSD(){
  fs.begin();
}

AudioFileSourceRTLSD::AudioFileSourceRTLSD(const char *filename)
{
  fs.begin();
  open(filename);
}

bool AudioFileSourceRTLSD::open(const char *filename)
{
  char absolute_filename[128];
  sprintf(absolute_filename, "%s%s", fs.getRootPath(), filename);
  f = fs.open(absolute_filename);
  return f;
}

AudioFileSourceRTLSD::~AudioFileSourceRTLSD()
{
  if (f) f.close();
}

uint32_t AudioFileSourceRTLSD::read(void *data, uint32_t len)
{
  return f.read(reinterpret_cast<uint8_t*>(data), len);
}

bool AudioFileSourceRTLSD::seek(int32_t pos, int dir)
{
  if (!f) return false;
  if (dir==SEEK_SET) return f.seek(pos);
  else if (dir==SEEK_CUR) return f.seek(f.position() + pos);
  else if (dir==SEEK_END) return f.seek(f.size() + pos);
  return false;
}

bool AudioFileSourceRTLSD::close()
{
  f.close();
  return true;
}

bool AudioFileSourceRTLSD::isOpen()
{
  return f?true:false;
}

uint32_t AudioFileSourceRTLSD::getSize()
{
  if (!f) return 0;
  return f.size();
}

uint32_t AudioFileSourceRTLSD::getPos()
{
  if (!f) return 0;
  return f.position();
}
