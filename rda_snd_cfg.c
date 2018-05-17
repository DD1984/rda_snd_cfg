#include <stdio.h>
#include <string.h>

#include <tinyalsa/asoundlib.h>


/* Mixer control names */
#define MIXER_PLAYBACK_VOLUME                    "Playback Volume"
#define MIXER_CAPTURE_VOLUME                     "Capture Volume"
#define MIXER_ITF                                "ITF"
#define MIXER_SPK_SEL                            "SpkSel"
#define MIXER_FORCE_MAINMIC                      "ForceMainMic"
#define MIXER_CODEC_APP_MODE                     "CodecAppMode"
#define MIXER_START_PLAY                         "StartPlay"
#define MIXER_START_RECORD                       "StartRecord"
#define MIXER_STOP                               "Stop"
#define MIXER_OUT_SAMPLE_RATE                    "OutSampleRate"
#define MIXER_IN_SAMPLE_RATE                     "InSampleRate"
#define MIXER_OUT_CHANNEL_NB                     "OutChannelNumber"
#define MIXER_IN_CHANNEL_NB                      "InChannelNumber"
#define MIXER_COMMIT_SETUP                       "Commit Setup"


#define MIXER_LOOP_MODE                          "Loop Mode"

typedef struct {
	struct mixer_ctl *playback_volume;
	struct mixer_ctl *capture_volume;

	struct mixer_ctl *itf;
	struct mixer_ctl *codec_app_mode;
	struct mixer_ctl *start_play;
	struct mixer_ctl *start_record;
	struct mixer_ctl *stop;
	struct mixer_ctl *out_sample_rate;
	struct mixer_ctl *out_channel_nb;
	struct mixer_ctl *in_sample_rate;
	struct mixer_ctl *in_channel_nb;
	struct mixer_ctl *spkSel;
	struct mixer_ctl *force_mainmic;
	struct mixer_ctl *commit_setup;
	
	struct mixer_ctl *loop_mode;
	
} mixer_ctls;

struct mixer *g_mixer = NULL;
mixer_ctls g_mixer_ctls;


int open_mixer(void)
{
	g_mixer = mixer_open(0);
	if (!g_mixer) {
		printf( "audio-hal : Unable to open the mixer, aborting.\n");
		return -1;
	}

	memset(&g_mixer_ctls, 0, sizeof(g_mixer_ctls));

	g_mixer_ctls.playback_volume = mixer_get_ctl_by_name(g_mixer, MIXER_PLAYBACK_VOLUME);
	g_mixer_ctls.capture_volume = mixer_get_ctl_by_name(g_mixer, MIXER_CAPTURE_VOLUME);
	g_mixer_ctls.itf = mixer_get_ctl_by_name(g_mixer, MIXER_ITF);
	g_mixer_ctls.spkSel = mixer_get_ctl_by_name(g_mixer, MIXER_SPK_SEL);
	g_mixer_ctls.force_mainmic = mixer_get_ctl_by_name(g_mixer, MIXER_FORCE_MAINMIC);
	g_mixer_ctls.codec_app_mode = mixer_get_ctl_by_name(g_mixer, MIXER_CODEC_APP_MODE);
	g_mixer_ctls.start_play = mixer_get_ctl_by_name(g_mixer, MIXER_START_PLAY);
	g_mixer_ctls.start_record = mixer_get_ctl_by_name(g_mixer, MIXER_START_RECORD);
	g_mixer_ctls.stop = mixer_get_ctl_by_name(g_mixer, MIXER_STOP);
	g_mixer_ctls.out_sample_rate = mixer_get_ctl_by_name(g_mixer, MIXER_OUT_SAMPLE_RATE);
	g_mixer_ctls.out_channel_nb = mixer_get_ctl_by_name(g_mixer, MIXER_OUT_CHANNEL_NB);
	g_mixer_ctls.in_sample_rate = mixer_get_ctl_by_name(g_mixer, MIXER_IN_SAMPLE_RATE);
	g_mixer_ctls.in_channel_nb = mixer_get_ctl_by_name(g_mixer, MIXER_IN_CHANNEL_NB);
	g_mixer_ctls.commit_setup = mixer_get_ctl_by_name(g_mixer, MIXER_COMMIT_SETUP);
	
	g_mixer_ctls.loop_mode = mixer_get_ctl_by_name(g_mixer, MIXER_LOOP_MODE);

	if(     !g_mixer_ctls.playback_volume ||
			!g_mixer_ctls.capture_volume ||
			!g_mixer_ctls.itf ||
			!g_mixer_ctls.spkSel ||
			!g_mixer_ctls.force_mainmic ||
			!g_mixer_ctls.codec_app_mode||
			!g_mixer_ctls.start_play||
			!g_mixer_ctls.start_record||
			!g_mixer_ctls.stop||
			!g_mixer_ctls.out_sample_rate ||
			!g_mixer_ctls.out_channel_nb||
			!g_mixer_ctls.in_sample_rate ||
			!g_mixer_ctls.in_channel_nb||
			!g_mixer_ctls.commit_setup) {
		printf("audio-hal : Get mixers error, aborting.\n");
		printf("audio-hal : mixer_ctls.playback_volume [%x] \n", (unsigned int)g_mixer_ctls.playback_volume);
		printf("audio-hal : mixer_ctls.capture_volume  [%x] \n", (unsigned int)g_mixer_ctls.capture_volume);
		printf("audio-hal : mixer_ctls.itf             [%x] \n", (unsigned int)g_mixer_ctls.itf);
		printf("audio-hal : mixer_ctls.spkSel          [%x] \n", (unsigned int)g_mixer_ctls.spkSel);
		printf("audio-hal : mixer_ctls.force_mainmic   [%x] \n", (unsigned int)g_mixer_ctls.force_mainmic);
		printf("audio-hal : mixer_ctls.codec_app_mode  [%x] \n", (unsigned int)g_mixer_ctls.codec_app_mode);
		printf("audio-hal : mixer_ctls.start_play      [%x] \n", (unsigned int)g_mixer_ctls.start_play);
		printf("audio-hal : mixer_ctls.start_record    [%x] \n", (unsigned int)g_mixer_ctls.start_record);
		printf("audio-hal : mixer_ctls.stop            [%x] \n", (unsigned int)g_mixer_ctls.stop);
		printf("audio-hal : mixer_ctls.out_sample_rate [%x] \n", (unsigned int)g_mixer_ctls.out_sample_rate);
		printf("audio-hal : mixer_ctls.in_sample_rate  [%x] \n", (unsigned int)g_mixer_ctls.in_sample_rate);
		printf("audio-hal : mixer_ctls.out_channel_nb  [%x] \n", (unsigned int)g_mixer_ctls.out_channel_nb);
		printf("audio-hal : mixer_ctls.in_channel_nb   [%x] \n", (unsigned int)g_mixer_ctls.in_channel_nb);
		printf("audio-hal : mixer_ctls.commit_setup    [%x] \n", (unsigned int)g_mixer_ctls.commit_setup);
		return -1;
	}

	return 0;
}

void close_mixer(void)
{
	if(g_mixer)
		mixer_close(g_mixer);
	g_mixer = NULL;
}

void main(int argc, char *argv[])
{
	// see all defines in kernel - rda_codec_adp.h

	int ret;

	if (open_mixer()) {
		printf("open mixer err, exit. \n");
		return;
	}

	//*************

	ret = mixer_ctl_set_value(g_mixer_ctls.itf, 0, 1); //headset
	printf("%s:%s[%d] ret = %d\n", __FILE__, __func__, __LINE__, ret);

	ret = mixer_ctl_set_value(g_mixer_ctls.spkSel, 0, 1); //headset
	printf("%s:%s[%d] ret = %d\n", __FILE__, __func__, __LINE__, ret);

	ret = mixer_ctl_set_value(g_mixer_ctls.capture_volume, 0, 2);
	printf("%s:%s[%d] ret = %d\n", __FILE__, __func__, __LINE__, ret);

	ret = mixer_ctl_set_value(g_mixer_ctls.force_mainmic, 0, 0);
	printf("%s:%s[%d] ret = %d\n", __FILE__, __func__, __LINE__, ret);
	


	ret = mixer_ctl_set_value(g_mixer_ctls.playback_volume, 0, 7);
	printf("%s:%s[%d] ret = %d\n", __FILE__, __func__, __LINE__, ret);
	

	ret = mixer_ctl_set_value(g_mixer_ctls.commit_setup , 0, 0);
	printf("%s:%s[%d] ret = %d\n", __FILE__, __func__, __LINE__, ret);

	//************

	//************
	ret = mixer_ctl_set_value(g_mixer_ctls.out_sample_rate , 0, 44100);
	printf("%s:%s[%d] ret = %d\n", __FILE__, __func__, __LINE__, ret);

	ret = mixer_ctl_set_value(g_mixer_ctls.out_channel_nb, 0, 2);
	printf("%s:%s[%d] ret = %d\n", __FILE__, __func__, __LINE__, ret);

	ret = mixer_ctl_set_value(g_mixer_ctls.in_channel_nb, 0, 1);
	printf("%s:%s[%d] ret = %d\n", __FILE__, __func__, __LINE__, ret);



	ret = mixer_ctl_set_value(g_mixer_ctls.in_sample_rate, 0, 8000);
	printf("%s:%s[%d] ret = %d\n", __FILE__, __func__, __LINE__, ret);



	ret = mixer_ctl_set_value(g_mixer_ctls.codec_app_mode, 0, 0);
	printf("%s:%s[%d] ret = %d\n", __FILE__, __func__, __LINE__, ret);

	ret = mixer_ctl_set_value(g_mixer_ctls.commit_setup , 0, 0);
	printf("%s:%s[%d] ret = %d\n", __FILE__, __func__, __LINE__, ret);

	//********

	if (argc == 2 && strcmp(argv[1], "s") == 0)
		ret = mixer_ctl_set_value(g_mixer_ctls.stop, 0, 0);
	else
		ret = mixer_ctl_set_value(g_mixer_ctls.start_play, 0, 0);

	printf("%s:%s[%d] ret = %d\n", __FILE__, __func__, __LINE__, ret);

	close_mixer();
}

