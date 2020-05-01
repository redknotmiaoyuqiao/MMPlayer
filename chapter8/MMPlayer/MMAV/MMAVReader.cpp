#include "MMAV.h"

#include "MMAVReaderPrivate.h"
#include "MMAVPacketPrivate.h"
#include "MMAVDecoderPrivate.h"
#include "MMAVStreamPrivate.h"

MMAVReader::MMAVReader()
{
	imp = new MMAVReaderPrivate();
	imp->formatCtx = avformat_alloc_context();
}

MMAVReader::~MMAVReader()
{
	if (imp->formatCtx != nullptr) {
		avformat_free_context(imp->formatCtx);
		imp->formatCtx = nullptr;
	}

	if (imp != nullptr) {
		delete imp;
		imp = nullptr;
	}
}

int MMAVReader::Open(const char* path)
{
	if (imp->formatCtx == nullptr) {
		return -1;
	}
	int ret = avformat_open_input(&imp->formatCtx, path, nullptr, nullptr);

	if (!ret) {
		avformat_find_stream_info(imp->formatCtx, nullptr);
	}

	return ret;
}

int MMAVReader::GetStreamCount()
{
	return imp->formatCtx->nb_streams;
}

int MMAVReader::GetStream(MMAVStream* avStream, int streamId)
{
	AVStream* ffmpegStream = imp->formatCtx->streams[streamId];

	avStream->streamIndex = ffmpegStream->index;

	avcodec_parameters_copy(avStream->imp->codecpar, ffmpegStream->codecpar);
	
	return 0;
}

int MMAVReader::GetVideoStreamIndex()
{
	return av_find_best_stream(imp->formatCtx, AVMediaType::AVMEDIA_TYPE_VIDEO, -1, -1, NULL, NULL);
}

int MMAVReader::GetAudioStreamIndex()
{
	return av_find_best_stream(imp->formatCtx, AVMediaType::AVMEDIA_TYPE_AUDIO, -1, -1, NULL, NULL);
}

int MMAVReader::Close()
{
	if (imp->formatCtx == nullptr) {
		return -1;
	}
	avformat_close_input(&imp->formatCtx);
	return 0;
}

int MMAVReader::Read(MMAVPacket* packet)
{
	if (imp->formatCtx == nullptr) {
		return -1;
	}
	int ret = av_read_frame(imp->formatCtx, packet->imp->pkt);
	return ret;
}