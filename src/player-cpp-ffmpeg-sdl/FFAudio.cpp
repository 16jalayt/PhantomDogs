#include "FFAudio.h"
#include <assert.h>
#include "defs.h"
#include "AudioCallback.h"
#include "../Audio.h"

FFAudio::FFAudio(AVCodecContext* pCodecAudioCtx)
{
	AudioCallback::set_audio_instance(this);

	swrCtx = swr_alloc();
	if (swrCtx == NULL)
	{
		printf("FFAudio: Failed to load audio\n");
		return;
	}

#if LIBAVUTIL_VERSION_MAJOR >= 59
	av_opt_set_chlayout(swrCtx, "in_chlayout", &pCodecAudioCtx->ch_layout, 0);
	av_opt_set_chlayout(swrCtx, "out_chlayout", &pCodecAudioCtx->ch_layout, 0);
#else
	av_opt_set_channel_layout(swrCtx, "in_channel_layout", pCodecAudioCtx->channel_layout, 0);
	av_opt_set_channel_layout(swrCtx, "out_channel_layout", pCodecAudioCtx->channel_layout, 0);
#endif
	av_opt_set_int(swrCtx, "in_sample_rate", pCodecAudioCtx->sample_rate, 0);
	av_opt_set_int(swrCtx, "out_sample_rate", pCodecAudioCtx->sample_rate, 0);
	av_opt_set_sample_fmt(swrCtx, "in_sample_fmt", pCodecAudioCtx->sample_fmt, 0);
	av_opt_set_sample_fmt(swrCtx, "out_sample_fmt", AV_SAMPLE_FMT_FLT, 0);

	int res = swr_init(swrCtx);

	if (res != 0)
	{
		printf("FFAudio: Failed to initialize audio\n");
		return;
	}

	//TODO: redo so resample hapens to audio driver not other way around
	memset(&wantedSpec, 0, sizeof(wantedSpec));

#if LIBAVUTIL_VERSION_MAJOR < 59
	wantedSpec.channels = pCodecAudioCtx->channels;
#else
	wantedSpec.channels = pCodecAudioCtx->ch_layout.nb_channels;
#endif
	wantedSpec.freq = pCodecAudioCtx->sample_rate;
	wantedSpec.format = AUDIO_S16SYS;
	wantedSpec.silence = 0;
	wantedSpec.samples = SDL_AUDIO_BUFFER_SIZE;
	wantedSpec.userdata = pCodecAudioCtx;
	wantedSpec.callback = AudioCallback::audio_callback;
}
FFAudio::~FFAudio()
{
	stopaudio = true;
	//SDL_PauseAudio(true);
	//SDL_CloseAudio();
	Audio::binkAudioLock = false;
}

void FFAudio::open()
{
	//SDL_AudioInit("winmm");
	//SDL_AudioInit("directsound");
	if (SDL_OpenAudio(&wantedSpec, &audioSpec) < 0)
	{
		printf("FFAudio: Failed to open audio\n");
		return;
	}
	//Currently due to callback, only one bink can play audio;
	Audio::binkAudioLock = true;

	wanted_frame.format = AV_SAMPLE_FMT_S16;
	wanted_frame.sample_rate = audioSpec.freq;

#if LIBAVUTIL_VERSION_MAJOR < 59
	wanted_frame.channel_layout = av_get_default_channel_layout(audioSpec.channels);
	wanted_frame.channels = audioSpec.channels;
#else
	av_channel_layout_default(&wanted_frame.ch_layout, audioSpec.channels);
#endif

	audioq.nb_packets = 0;
	audioq.size = 0;
	audioq.last = NULL;
	audioq.first = NULL;
	audioq.mutex = SDL_CreateMutex();
	audioq.cond = SDL_CreateCond();

	SDL_PauseAudio(0);
}

int FFAudio::audio_decode_frame(AVCodecContext* aCodecCtx, uint8_t* audio_buf, int buf_size) {
	static AVPacket pkt;
	static uint8_t* audio_pkt_data = NULL;
	static int audio_pkt_size = 0;
	static AVFrame frame;

	int len1;
	int data_size = 0;

	SwrContext* swr_ctx = NULL;

	while (1 && !stopaudio)
	{
		while (audio_pkt_size > 0)
		{
			avcodec_send_packet(aCodecCtx, &pkt);
			avcodec_receive_frame(aCodecCtx, &frame);

			len1 = frame.pkt_size;
			if (len1 < 0)
			{
				audio_pkt_size = 0;
				break;
			}

			audio_pkt_data += len1;
			audio_pkt_size -= len1;

			data_size = 0;

			//needed?
			if (swr_ctx)
			{
				swr_free(&swr_ctx);
				swr_ctx = NULL;
			}

#if LIBAVUTIL_VERSION_MAJOR < 59
			swr_ctx = swr_alloc_set_opts(NULL, wanted_frame.channel_layout, (AVSampleFormat)wanted_frame.format, wanted_frame.sample_rate,
				frame.channel_layout, (AVSampleFormat)frame.format, frame.sample_rate, 0, NULL);
#else
			swr_alloc_set_opts2(&swr_ctx, &wanted_frame.ch_layout, (AVSampleFormat)wanted_frame.format, wanted_frame.sample_rate,
				&frame.ch_layout, (AVSampleFormat)frame.format, frame.sample_rate, 0, NULL);
#endif

			if (!swr_ctx || swr_init(swr_ctx) < 0)
			{
				printf("FFAudio: swr_init failed\n");
				return 0;
			}

			int dst_nb_samples = (int)av_rescale_rnd(swr_get_delay(swr_ctx, frame.sample_rate) + frame.nb_samples,
				wanted_frame.sample_rate, wanted_frame.format, AV_ROUND_INF);

			int len2 = swr_convert(swr_ctx, &audio_buf, dst_nb_samples,
				(const uint8_t**)frame.data, frame.nb_samples);
			if (len2 < 0)
			{
				printf("FFAudio: swr_convert failed\n");
				return 0;
			}

			av_packet_unref(&pkt);

			if (swr_ctx)
			{
				swr_free(&swr_ctx);
				swr_ctx = NULL;
			}

#if LIBAVUTIL_VERSION_MAJOR < 59
			return wanted_frame.channels * len2 * av_get_bytes_per_sample(AV_SAMPLE_FMT_S16);
#else
			return wanted_frame.ch_layout.nb_channels * len2 * av_get_bytes_per_sample(AV_SAMPLE_FMT_S16);
#endif
		}

		if (getAudioPacket(&audioq, &pkt, 1) < 0)
			return -1;

		audio_pkt_data = pkt.data;
		audio_pkt_size = pkt.size;
	}
	return -1;
}

int FFAudio::put_audio_packet(AVPacket* packet)
{
	AVPacketList* pktl;
	AVPacket* newPkt;

	newPkt = (AVPacket*)av_calloc(1, sizeof(AVPacket));

	if (av_packet_ref(newPkt, packet) < 0)
		return -1;

	pktl = (AVPacketList*)av_malloc(sizeof(AVPacketList));
	if (!pktl)
		return -1;

	pktl->pkt = *newPkt;
	pktl->next = NULL;

	SDL_LockMutex(audioq.mutex);

	if (!audioq.last)
		audioq.first = pktl;
	else
		audioq.last->next = pktl;

	audioq.last = pktl;

	audioq.nb_packets++;
	audioq.size += newPkt->size;

	SDL_CondSignal(audioq.cond);
	SDL_UnlockMutex(audioq.mutex);

	return 0;
}

int FFAudio::getAudioPacket(AudioPacket* q, AVPacket* pkt, int block) {
	AVPacketList* pktl;
	int ret = 0;

	SDL_LockMutex(q->mutex);

	while (1 && !stopaudio)
	{
		pktl = q->first;
		if (pktl)
		{
			q->first = pktl->next;
			if (!q->first)
				q->last = NULL;

			q->nb_packets--;
			q->size -= pktl->pkt.size;

			*pkt = pktl->pkt;
			av_free(pktl);
			ret = 1;
			break;
		}
		else if (!block)
		{
			ret = 0;
			break;
		}
		else
		{
			SDL_CondWait(q->cond, q->mutex);
		}
	}

	SDL_UnlockMutex(q->mutex);

	return ret;
}