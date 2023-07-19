/*
Audio player and meta recurators library. Choice of public domain or MIT-0. See license statements at the end of this file.
miniplayer - v0.0.1 - 2020-05-25

Tadjaur Aurelien - wk.taur@gmail.com

GitHub:  https://github.com/tadjaur/miniplayer
*/
/*
Introduction
============
miniplayer is a single file library for audio playback and retrieve audio metadata. To use it, do the following in one .c file:

    ```c
    #include "miniplayer.c"
    ```

You can #include miniplayer.c in other parts of the program just like any other header.

miniplayer uses miniaudio (https://github.com/dr-soft/miniaudio) for audio playback and taglib to retrieve audio meta data.
*/

#ifndef __A_PLAYER__C__
#define __A_PLAYER__C__

#include <stdio.h>
// #include <taglib/tag_c.h>
#define DR_FLAC_IMPLEMENTATION
#include "extras/dr_flac.h" /* Enables FLAC decoding. */
// #include "src/external/dr_flac.h" /* Enables FLAC decoding. */
#define DR_MP3_IMPLEMENTATION
#include "extras/dr_mp3.h" /* Enables MP3 decoding. */
// #include "src/external/dr_mp3.h" /* Enables MP3 decoding. */
#define DR_WAV_IMPLEMENTATION
#include "extras/dr_wav.h" /* Enables WAV decoding. */
// #include "src/external/dr_wav.h" /* Enables WAV decoding. */
#define STB_VORBIS_IMPLEMENTATION
#include "extras/stb_vorbis.c"
// #include "src/external/stb_vorbis.h"
#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio.h"
// #include "src/external/miniaudio.h"

typedef enum MP_BOOL MP_BOOL;

enum MP_BOOL
{
    MP_FALSE = (ma_uint32)0,
    MP_TRUE = (ma_uint32)1
};

#define MP_SAMPLE_FORMAT ma_format_f32
#define MP_CHANNEL_COUNT 2
#define MP_SAMPLE_RATE 48000 //44100//48000

typedef struct mp_media mp_media;
typedef struct mp_media_prop mp_media_prop;
typedef struct mp_playlist_config mp_playlist_config;

struct mp_media
{
    ma_uint32 id;
    // ma_uint32 frames_read;
    ma_uint32 complete;
    ma_decoder decoder;
    mp_media *next;
    mp_media *prev;
};

struct mp_media_prop
{
    ma_uint32 bitrate;
    ma_uint32 sample_rate;
    ma_uint32 channels;
    ma_uint32 length;
};

struct mp_playlist_config
{
    ma_uint32 medias_count;
    ma_int32 current_media_id;
    mp_media *current_media;
    mp_media *first_media;
    mp_media *last_media;
    ma_device device;
    ma_event default_stop_event;
    ma_decoder_config default_decoder_config; // default decoder config of playlist because all decoder need to have the same output format.
    ma_uint32 first_to_last;
    // int is_playing;
    // int reverse_playlist;
    ma_uint32 to_left;
    char **medias_path;
    // enum MP_EVENT next_event;
    ma_uint32 repeat_count; //TODO: add repeat option 0 => not repeat, -1 infinite, +1 > number of reapeat
};

mp_playlist_config *playlist_config = 0;
//// TODO: uncomment when taglib android compilation bug fixed
// int mp__len(char *string, int start)
// {
//     if (string[start] == '\0')
//         return start;
//     start++;
//     return mp__len(string, start);
// }
// int mp_len(char *string)
// {
//     return mp__len(string, 0);
// }

// char *mp_to_str(int value)
// {
//     char *dt = (char *)calloc(20, sizeof(char));
//     snprintf(dt, 20, "%i", value);
//     return dt;
// }

// char *mp_concat(char *a, char *b)
// {
//     int rlen = 0, len_a = mp_len(a), len_b = mp_len(b);
//     int tlen = len_a + len_b;
//     char *r = (char *)calloc(tlen + 1, sizeof(char));
//     char *head = r;
//     while (1)
//     {
//         if (rlen < len_a)
//         {
//             *r = *a++;
//         }
//         else if (rlen < tlen)
//         {
//             *r = *b++;
//         }
//         else
//         {
//             *r = '\0';
//             break;
//         }
//         (void)*r++;
//         rlen++;
//     }
//     return head;
// }

// char *mp_concat_n(char *string_vec[], int count)
// {
//     int i;
//     char *data = "";
//     if (count == 0)
//         return "";
//     if (count == 1)
//         return string_vec[0];
//     for (i = 0; i < count; i++)
//     {
//         char *old = data;
//         data = mp_concat(old, string_vec[i]);
//         if (i > 0)
//             free(old);
//     }
//     return data;
// }

/* set the volume of the master */
MP_BOOL mp_setVolume(float volume)
{
    if (!playlist_config)
    {
        return MP_FALSE;
    }
    if (ma_device_set_master_volume(&playlist_config->device, volume) == MA_SUCCESS)
    {
        return MP_TRUE;
    }
    return MP_FALSE;
}

//// TODO: uncomment when taglib android compilation bug fixed
// /*
//     return JSON string representation of the media tags and propreties
//     example: {"tags":{"title":"","artist":"","album":"","year":0,"comment":"","track":0,"genre":""},"properties":{"bitrate":1411,"sample_rate":44100,"channels":2,"length":178}}
// */
// char *mp_meta(char *file_path)
// {
//     char *encoded_tags = "", *encoded_properties = "";
//     TagLib_File *file;
//     TagLib_Tag *tag;
//     const TagLib_AudioProperties *properties;
//     TagLib_File_Type ftype[] = {TagLib_File_MPEG, TagLib_File_OggVorbis, TagLib_File_FLAC, TagLib_File_OggFlac, TagLib_File_WavPack};
//     int max_iteration = 5;
//     while (max_iteration > 0)
//     {
//         max_iteration--;
//         file = taglib_file_new_type(file_path, ftype[max_iteration]);
//         if (file == NULL)
//             continue;
//         tag = taglib_file_tag(file);
//         properties = taglib_file_audioproperties(file);
//         if (tag == NULL || properties == NULL)
//             continue;
//         int bitrate = taglib_audioproperties_bitrate(properties),
//             samplerate = taglib_audioproperties_samplerate(properties),
//             channels = taglib_audioproperties_channels(properties),
//             length = taglib_audioproperties_length(properties);
//         if (!bitrate && !samplerate && !channels)
//             continue;
//         encoded_properties = mp_concat_n((char *[]){"\"bitrate\":", mp_to_str(bitrate),
//                                                     ",\"sample_rate\":", mp_to_str(samplerate),
//                                                     ",\"channels\":", mp_to_str(channels),
//                                                     ",\"length\":", mp_to_str(length)},
//                                          8);
//         encoded_tags = mp_concat_n((char *[]){"\"title\":\"", taglib_tag_title(tag),
//                                               "\",\"artist\":\"", taglib_tag_artist(tag),
//                                               "\",\"album\":\"", taglib_tag_album(tag),
//                                               "\",\"year\":", mp_to_str(taglib_tag_year(tag)),
//                                               ",\"comment\":\"", taglib_tag_comment(tag),
//                                               "\",\"track\":", mp_to_str(taglib_tag_track(tag)),
//                                               ",\"genre\":\"", taglib_tag_genre(tag), "\""},
//                                    15);
//         break;
//     }

//     char *r = mp_concat_n((char *[]){"{\"tags\":{", encoded_tags, "},\"properties\":{", encoded_properties, "}}"}, 5);
//     taglib_tag_free_strings();
//     taglib_file_free(file);
//     if (encoded_tags[0] != '\0')
//         free(encoded_tags);
//     if (encoded_properties[0] != '\0')
//         free(encoded_properties);
//     return r;
// }

ma_uint32 read_and_mix_pcm_frames_f32(float *pOutputF32, ma_uint32 max_frames_count)
{
    /*
    The way mixing works is that we just read into a temporary buffer, then take the contents of that buffer and mix it with the
    contents of the output buffer by simply adding the samples together. You could also clip the samples to -1..+1, but I'm not
    doing that in this example.
    */
    float temp_out_frames[4096];
    ma_uint32 temp_out_frames_capacity = ma_countof(temp_out_frames) / MP_CHANNEL_COUNT;
    ma_uint32 total_frames_read = 0;
    while (total_frames_read < max_frames_count)
    {
        ma_uint32 iSample;
        ma_uint32 iteration_frames_read;
        ma_uint32 totalFramesRemaining = max_frames_count - total_frames_read;
        ma_uint32 iteration_max_out_frame = temp_out_frames_capacity;
        if (iteration_max_out_frame > totalFramesRemaining)
        {
            iteration_max_out_frame = totalFramesRemaining;
        }
        iteration_frames_read = (ma_uint32)ma_decoder_read_pcm_frames(&playlist_config->current_media->decoder, temp_out_frames, iteration_max_out_frame);
        printf("\rframeread:%i", iteration_frames_read);
        if (iteration_frames_read == 0)
        {
            break;
        }
        /* Mix the frames together. */
        for (iSample = 0; iSample < iteration_frames_read * MP_CHANNEL_COUNT; ++iSample)
        {
            pOutputF32[total_frames_read * MP_CHANNEL_COUNT + iSample] += temp_out_frames[iSample];
        }
        total_frames_read += iteration_frames_read;
        if (iteration_frames_read < iteration_max_out_frame)
        {
            break; /* Reached EOF. */
        }
    }
    return total_frames_read;
}

void __try_release_medias()
{
    if (playlist_config->current_media)
    {
        mp_media *n = playlist_config->current_media->next, *p = playlist_config->current_media->prev;
        while (1)
        {
            int change = 0;
            if (n)
            {
                mp_media *temp = n->next;
                ma_decoder_uninit(&(n->decoder));
                free(n);
                n = temp;
                change = 1;
            }
            if (p)
            {
                mp_media *temp = p->prev;
                ma_decoder_uninit(&(p->decoder));
                free(p);
                p = temp;
                change = 1;
            }
            if (!change)
                break;
        }
        ma_decoder_uninit(&(playlist_config->current_media->decoder));
        free(playlist_config->current_media);
    }
}

void __try_release()
{
    if (playlist_config)
    {
        __try_release_medias();
        ma_device_uninit(&playlist_config->device);
        free(playlist_config);
        playlist_config = 0;
    }
}

void mp_stop()
{
    ma_device_stop(&playlist_config->device);
    __try_release();
}

mp_media_prop *mp_media_properties(char *file_path)
{
    unsigned int sampleCount, sampleRate, channels;
    float final_length = 0.0f;
    /// ref: raudio.c 1118
    drwav *ctxWav = (drwav *)malloc(sizeof(drwav));
    mp_media_prop *result = (mp_media_prop *)malloc(sizeof(mp_media_prop));
    if (drwav_init_file(ctxWav, file_path, NULL))
    {
        sampleCount = (unsigned int)ctxWav->totalPCMFrameCount * ctxWav->channels;
        sampleRate = ctxWav->sampleRate;
        channels = ctxWav->channels;
        if (sampleCount && sampleRate && channels)
        {
            result->length = (float)sampleCount / (sampleRate * channels);
            result->channels = channels;
            result->sample_rate = sampleRate;
            result->bitrate = sampleCount;
            free(ctxWav);
            return result;
        }
    }
    free(ctxWav);
    
    drmp3 *ctxMp3 = (drmp3 *)malloc(sizeof(drmp3));
    int response = drmp3_init_file(ctxMp3, file_path, NULL);

    if (response > 0)
    {
        sampleCount = (unsigned int)drmp3_get_pcm_frame_count(ctxMp3) * ctxMp3->channels;
        sampleRate = ctxMp3->sampleRate;
        channels = ctxMp3->channels;
        if (sampleCount && sampleRate && channels)
        {
            result->length = (float)sampleCount / (sampleRate * channels);
            result->channels = channels;
            result->sample_rate = sampleRate;
            result->bitrate = sampleCount;
            free(ctxMp3);
            return result;
        }
    }
    free(ctxMp3);
    stb_vorbis *ctxData = stb_vorbis_open_filename(file_path, NULL, NULL);
    if (ctxData != NULL)
    {
        stb_vorbis_info info = stb_vorbis_get_info(ctxData); // Get Ogg file info
        sampleCount = (unsigned int)stb_vorbis_stream_length_in_samples(ctxData) * info.channels;
        sampleRate = info.sample_rate;
        channels = info.channels;
        if (sampleCount && sampleRate && channels)
        {
            result->length = (float)sampleCount / (sampleRate * channels);
            result->channels = channels;
            result->sample_rate = sampleRate;
            result->bitrate = sampleCount;
            free(ctxData);
            return result;
        }
    }
    free(ctxData);
    drflac *ctxFlac = drflac_open_file(file_path, NULL);
    if (ctxFlac != NULL)
    {
        sampleCount = (unsigned int)ctxFlac->totalPCMFrameCount;
        sampleRate = ctxFlac->sampleRate;
        channels = ctxFlac->channels;
        if (sampleCount && sampleRate && channels)
        {
            result->length = (float)sampleCount / (sampleRate * channels);
            result->channels = channels;
            result->sample_rate = sampleRate;
            result->bitrate = sampleCount;
            free(ctxFlac);
            return result;
        }
    }

    free(ctxFlac);
    free(result);
    return NULL;
}

MP_BOOL __init_media()
{
    if (playlist_config->current_media_id >= playlist_config->medias_count ||
        playlist_config->current_media_id < 0)
    {
        return MP_FALSE;
    }
    if (playlist_config->current_media_id == 0 && playlist_config->to_left == 0 && playlist_config->current_media)
    {
        playlist_config->current_media = playlist_config->first_media;
        return MP_TRUE;
    }
    if (playlist_config->current_media_id + 1 == playlist_config->medias_count && playlist_config->to_left == 1 && playlist_config->current_media)
    {
        playlist_config->current_media = playlist_config->last_media;
        return MP_TRUE;
    }
    if (playlist_config->current_media)
    {
        if (playlist_config->to_left &&
            playlist_config->current_media->prev &&
            playlist_config->current_media->prev->id == playlist_config->current_media_id)
        {
            playlist_config->current_media = playlist_config->current_media->prev;
            return MP_TRUE;
        }
        if (!playlist_config->to_left &&
            playlist_config->current_media->next &&
            playlist_config->current_media->next->id == playlist_config->current_media_id)
        {
            playlist_config->current_media = playlist_config->current_media->next;
            return MP_TRUE;
        }
    }
    mp_media *temp = (mp_media *)malloc(sizeof(mp_media));
    printf("load file: %s\n", playlist_config->medias_path[playlist_config->current_media_id]);
    ma_result result = ma_decoder_init_file_wav(playlist_config->medias_path[playlist_config->current_media_id], &playlist_config->default_decoder_config, &temp->decoder);
    if (result != MA_SUCCESS)
        result = ma_decoder_init_file_mp3(playlist_config->medias_path[playlist_config->current_media_id], &playlist_config->default_decoder_config, &temp->decoder);
    if (result != MA_SUCCESS)
        result = ma_decoder_init_file_flac(playlist_config->medias_path[playlist_config->current_media_id], &playlist_config->default_decoder_config, &temp->decoder);
    if (result != MA_SUCCESS)
        result = ma_decoder_init_file_vorbis(playlist_config->medias_path[playlist_config->current_media_id], &playlist_config->default_decoder_config, &temp->decoder);
    if (result != MA_SUCCESS)
    {

        printf("load file error result: %i\n", result);
        free(temp);
        return MP_FALSE;
    }
    // temp->frames_read = 0;
    temp->next = temp->prev = 0;
    temp->id = playlist_config->current_media_id;
    if (playlist_config->current_media)
    {
        if (playlist_config->to_left)
        {
            temp->next = playlist_config->current_media;
            if (playlist_config->current_media->prev)
            {
                temp->prev = playlist_config->current_media->prev;
            }
            playlist_config->current_media->prev = temp;
        }
        else
        {
            temp->prev = playlist_config->current_media;
            if (playlist_config->current_media->next)
            {
                temp->next = playlist_config->current_media->next;
            }
            playlist_config->current_media->next = temp;
        }
    }
    else
    {
        playlist_config->first_media = temp;
    }
    playlist_config->current_media = temp;
    return MP_TRUE;
}

void mp_set_next_media_id()
{
    if (playlist_config->current_media_id == -2)
    {
        playlist_config->current_media_id = 0;
        return;
    }
    if (playlist_config->to_left == 1)
    {
        if (/*playlist_config->first_to_last && */ playlist_config->current_media_id == 0)
        {
            playlist_config->current_media_id = playlist_config->medias_count - 1;
            return;
        }
        playlist_config->current_media_id--;
        return;
    }
    if ((playlist_config->repeat_count != 0) &&
        playlist_config->current_media_id + 1 == playlist_config->medias_count)
    {
        if (!playlist_config->last_media)
            playlist_config->last_media = playlist_config->current_media;
        playlist_config->current_media_id = 0;
        playlist_config->repeat_count--;
        return;
    }
    else {
    playlist_config->current_media_id = 0;
    }
    playlist_config->current_media_id++;
}

MP_BOOL mp_init_next_media()
{
    while (1)
    {
        mp_set_next_media_id();
        if (playlist_config->current_media_id >= playlist_config->medias_count ||
            playlist_config->current_media_id < 0)
            return MP_FALSE;
        if (__init_media())
        {
            ma_decoder_seek_to_pcm_frame(&playlist_config->current_media->decoder, (ma_uint64)0);
            return MP_TRUE;
        }
    }
}

void data_callback(ma_device *pDevice, void *pOutput, const void *pInput, ma_uint32 max_frames_count)
{
    float *pOutputF32 = (float *)pOutput;
    MA_ASSERT(pDevice->playback.format == MP_SAMPLE_FORMAT); /* <-- Important for this example. */
    ma_uint32 framesRead = read_and_mix_pcm_frames_f32(pOutputF32, max_frames_count);
    // playlist_config->current_media->frames_read += framesRead;
    if (framesRead < max_frames_count)
    { // media complete play
        printf("frame in pcm %i\n", (int)ma_decoder_get_length_in_pcm_frames(&playlist_config->current_media->decoder));
        // printf("frame read %i\n", playlist_config->current_media->frames_read);
        if (!mp_init_next_media())
        {
            ma_event_signal(&playlist_config->default_stop_event);
            mp_stop();
        }
    }
    (void)pInput;
}

MP_BOOL mp_play()
{
    if (!playlist_config->current_media && !mp_init_next_media())
    {
        return MP_FALSE;
    }
    if (ma_device_start(&playlist_config->device) != MA_SUCCESS)
    {
        return MP_FALSE;
    }
    return MP_TRUE;
}

MP_BOOL mp_pause()
{
    if (ma_device_stop(&playlist_config->device) != MA_SUCCESS)
    {
        return MP_FALSE;
    }
    return MP_TRUE;
}

MP_BOOL mp_prev()
{
    ma_uint32 old_direction = playlist_config->to_left;
    playlist_config->to_left = !old_direction;
    mp_pause();
    MP_BOOL done = mp_init_next_media();
    playlist_config->to_left = old_direction;
    if (!done)
    {
        return MP_FALSE;
    }
    if (mp_play())
        return MP_TRUE;
    return MP_FALSE;
}

MP_BOOL mp_next()
{
    ma_uint32 old_direction = playlist_config->to_left;
    playlist_config->to_left = !old_direction;
    mp_pause();
    MP_BOOL done = mp_init_next_media();
    playlist_config->to_left = old_direction;
    if (!done)
    {
        return MP_FALSE;
    }
    mp_play();
    return MP_TRUE;
}

MP_BOOL mp_replay()
{
    mp_pause();
    ma_decoder_seek_to_pcm_frame(&playlist_config->current_media->decoder, (ma_uint64)0);
    return mp_play();
}

MP_BOOL mp_init(char **medias_path, ma_uint32 count)
{
    ma_result result;
    ma_device_config deviceConfig;
    if (count == 0)
    {
        return MP_FALSE;
    }
    playlist_config = (mp_playlist_config *)malloc(sizeof(mp_playlist_config));
    playlist_config->medias_count = count;
    playlist_config->medias_path = medias_path;
    playlist_config->current_media_id = -2;
    playlist_config->first_media = playlist_config->last_media = playlist_config->current_media = 0;
    playlist_config->first_to_last = playlist_config->to_left = playlist_config->repeat_count = 0;
    playlist_config->default_decoder_config = ma_decoder_config_init(MP_SAMPLE_FORMAT, MP_CHANNEL_COUNT, MP_SAMPLE_RATE);
    /* Create only a single device. The decoders will be mixed together in the callback. In this example the data format needs to be the same as the decoders. */
    deviceConfig = ma_device_config_init(ma_device_type_playback);
    deviceConfig.playback.format = MP_SAMPLE_FORMAT;
    deviceConfig.playback.channels = MP_CHANNEL_COUNT;
    deviceConfig.sampleRate = MP_SAMPLE_RATE;
    deviceConfig.dataCallback = data_callback;
    deviceConfig.pUserData = NULL;
    if (ma_device_init(NULL, &deviceConfig, &playlist_config->device) != MA_SUCCESS)
    {
        printf("Failed to open playback device.\n");
        free(playlist_config);
        playlist_config = 0;
        return MP_FALSE;
    }
    /*
    We can't stop in the audio thread so we instead need to use an event. We wait on this thread in the main thread, and signal it in the audio thread. This
    needs to be done before starting the device. We need a context to initialize the event, which we can get from the device. Alternatively you can initialize
    a context separately, but we don't need to do that for this example.
    */
    ma_event_init(playlist_config->device.pContext, &playlist_config->default_stop_event);
    return MP_TRUE;
}

#endif //!__A_PLAYER__C__

void __attribute__((constructor)) initLibrary(void)
{
    printf("Audio Library is initialized\n");
}
void __attribute__((destructor)) cleanUpLibrary(void)
{
    __try_release();
    printf("Audio Library is exited\n");
}

/*
This software is available as a choice of the following licenses. Choose
whichever you prefer.

===============================================================================
ALTERNATIVE 1 - Public Domain (www.unlicense.org)
===============================================================================
This is free and unencumbered software released into the public domain.

Anyone is free to copy, modify, publish, use, compile, sell, or distribute this
software, either in source code form or as a compiled binary, for any purpose,
commercial or non-commercial, and by any means.

In jurisdictions that recognize copyright laws, the author or authors of this
software dedicate any and all copyright interest in the software to the public
domain. We make this dedication for the benefit of the public at large and to
the detriment of our heirs and successors. We intend this dedication to be an
overt act of relinquishment in perpetuity of all present and future rights to
this software under copyright law.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

For more information, please refer to <http://unlicense.org/>

===============================================================================
ALTERNATIVE 2 - MIT No Attribution
===============================================================================
Copyright 2020 Tadjaur Aurelien

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
of the Software, and to permit persons to whom the Software is furnished to do
so.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

int main(int argc, char **argv)
{
    mp_init(&argv[2], 1);
    mp_play();
    ma_event_wait(&playlist_config->default_stop_event);
    return 0;
}
