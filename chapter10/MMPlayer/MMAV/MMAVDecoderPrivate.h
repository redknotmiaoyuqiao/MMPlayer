#pragma once

extern "C"
{
#include <libavformat/avformat.h>
}

class MMAVDecoderPrivate
{
public:
	AVCodecContext * codecContext = nullptr;
};