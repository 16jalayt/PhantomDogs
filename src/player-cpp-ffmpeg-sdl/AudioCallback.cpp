#include "AudioCallback.h"
#include "FFPlayer.h"
#include "FFAudio.h"

extern "C"
{
#include <libavcodec/avcodec.h>
#include <libavfilter/avfilter.h>
#include <libavformat/avformat.h>
#include <libavformat/avio.h>
#include <libavutil/avutil.h>
#include <libswresample/swresample.h>
#include <libswscale/swscale.h>
#include <libavutil/frame.h>
#include <libavutil/imgutils.h>
}

FFAudio* AudioCallback::audio_instance = 0;
void AudioCallback::set_audio_instance(FFAudio* audio_instance)
{
	AudioCallback::audio_instance = audio_instance;
}

//NOTE: stops calling callback when repeating
void AudioCallback::audio_callback(void* userdata, Uint8* stream, int len)
{
	if (stopaudio)
	{
		SDL_PauseAudio(0);
		//stopaudio = false;
		return;
	}

	AVCodecContext* aCodecCtx = (AVCodecContext*)userdata;
	int len1, audio_size;

	static uint8_t audio_buff[192000 * 3 / 2];
	static unsigned int audio_buf_size = 0;
	static unsigned int audio_buf_index = 0;

	SDL_memset(stream, 0, len);

	while (len > 0)
	{
		if (audio_buf_index >= audio_buf_size)
		{
			audio_size = AudioCallback::audio_instance->audio_decode_frame(aCodecCtx, audio_buff, sizeof(audio_buff));
			if (audio_size < 0)
			{
				audio_buf_size = 1024;
				memset(audio_buff, 0, audio_buf_size);
			}
			else
				audio_buf_size = audio_size;

			audio_buf_index = 0;
		}
		len1 = audio_buf_size - audio_buf_index;
		if (len1 > len)
			len1 = len;

		SDL_MixAudio(stream, audio_buff + audio_buf_index, len, SDL_MIX_MAXVOLUME);

		len -= len1;
		stream += len1;
		audio_buf_index += len1;
	}
}