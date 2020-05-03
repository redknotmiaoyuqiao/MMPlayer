#include "MMAV.h"

#include "MMAVStreamPrivate.h"

MMAVStream::MMAVStream()
{
	imp = new MMAVStreamPrivate();
	imp->codecpar = avcodec_parameters_alloc();
}

MMAVStream::~MMAVStream()
{
	if (imp->codecpar != nullptr) {
		avcodec_parameters_free(&imp->codecpar);
		imp->codecpar = nullptr;
	}
	if (imp != nullptr) {
		delete imp;
		imp = nullptr;
	}
}