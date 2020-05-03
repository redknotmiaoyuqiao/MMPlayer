#include "MMAV.h"

#include "MMAVPacketPrivate.h"

MMAVPacket::MMAVPacket()
{
	imp = new MMAVPacketPrivate();
	imp->pkt = av_packet_alloc();
}

MMAVPacket::~MMAVPacket()
{
	if (imp->pkt != nullptr) {
		av_packet_free(&imp->pkt);
		imp->pkt = nullptr;
	}

	if (imp != nullptr) {
		delete imp;
		imp = nullptr;
	}
}

int MMAVPacket::GetIndex()
{
	return imp->pkt->stream_index;
}