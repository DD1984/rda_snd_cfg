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
	int channels = 2, ret, g_codec_start;
	unsigned int sample_rate = 44100;

	// 3. open mixer
	if (open_mixer()) {
		printf("open mixer err, exit. \n");
		goto mixer_err;
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



	printf("hello world\n");
	//close_mixer();

mixer_err:
	printf("err\n");
}

#if 0
[   27.961914] rda_gouda_enable_store in
[   28.198181] rda calibdata: GET_MIC_GAINS - ana - 18, adc - 0, alg - 6.
[   28.198852] rda calibdata: GET_MIC_GAINS - ana - 12, adc - 0, alg - 3.
[   28.199645] rda calibdata: GET_MIC_GAINS - ana - 9, adc - 0, alg - 3.
[   28.215637] -->sound/core/control.c:snd_ctl_elem_write[915] codec: rda-codec, ctrl: ITF, val: 2
[   28.216613] -->sound/core/control.c:snd_ctl_elem_write[915] codec: rda-codec, ctrl: SpkSel, val: 2
[   28.217712] audio SPK = 2
[   28.217712] 
[   28.218200] audio gpio extpa is invalid !
[   28.218200] 
[   28.218872] audio gpio extpa 1 is invalid !
[   28.218872] 
[   28.219970] <rda_msys>: pid = 39, rda-codec: ext_len = 0
[   28.220458] <rda_msys>: end of pending msg
[   28.225646] -->sound/core/control.c:snd_ctl_elem_write[915] codec: rda-codec, ctrl: Capture Volume, val: 2
[   28.226684] -->sound/core/control.c:snd_ctl_elem_write[915] codec: rda-codec, ctrl: ForceMainMic, val: 0
[   28.228332] <rda_msys>: pid = 39, rda-codec: ext_len = 0
[   28.228820] <rda_msys>: end of pending msg
[   28.236755] -->sound/core/control.c:snd_ctl_elem_write[915] codec: rda-codec, ctrl: Commit Setup, val: 0
[   28.238220] <rda_msys>: pid = 39, rda-codec: ext_len = 0
[   28.238708] <rda_msys>: end of pending msg
[   28.250793] -->sound/core/control.c:snd_ctl_elem_write[915] codec: rda-codec, ctrl: OutSampleRate, val: 44100
[   28.251892] -->sound/core/control.c:snd_ctl_elem_write[915] codec: rda-codec, ctrl: OutChannelNumber, val: 2
[   28.253112] -->sound/core/control.c:snd_ctl_elem_write[915] codec: rda-codec, ctrl: InSampleRate, val: 8000
[   28.254333] -->sound/core/control.c:snd_ctl_elem_write[915] codec: rda-codec, ctrl: InChannelNumber, val: 1
[   28.367736] -->sound/core/control.c:snd_ctl_elem_write[915] codec: rda-codec, ctrl: Playback Volume, val: 7
[   28.368774] -->sound/core/control.c:snd_ctl_elem_write[915] codec: rda-codec, ctrl: Commit Setup, val: 0
[   28.370422] <rda_msys>: pid = 39, rda-codec: ext_len = 0
[   28.370910] <rda_msys>: end of pending msg
[   29.486877] -->sound/core/control.c:snd_ctl_elem_write[915] codec: rda-codec, ctrl: ITF, val: 1
[   29.487854] -->sound/core/control.c:snd_ctl_elem_write[915] codec: rda-codec, ctrl: SpkSel, val: 1
[   29.488952] audio SPK = 1
[   29.488952] 
[   29.490539] <rda_msys>: pid = 39, rda-codec: ext_len = 0
[   29.491088] <rda_msys>: end of pending msg
[   29.491638] -->sound/core/control.c:snd_ctl_elem_write[915] codec: rda-codec, ctrl: Capture Volume, val: 2
[   29.492797] -->sound/core/control.c:snd_ctl_elem_write[915] codec: rda-codec, ctrl: ForceMainMic, val: 1
[   29.494567] <rda_msys>: pid = 39, rda-codec: ext_len = 0
[   29.495117] <rda_msys>: end of pending msg
[   29.495727] -->sound/core/control.c:snd_ctl_elem_write[915] codec: rda-codec, ctrl: Commit Setup, val: 0
[   29.498107] <rda_msys>: pid = 39, rda-codec: ext_len = 0
[   29.498596] <rda_msys>: end of pending msg
[   29.506530] -->sound/core/control.c:snd_ctl_elem_write[915] codec: rda-codec, ctrl: OutSampleRate, val: 44100
[   29.507690] -->sound/core/control.c:snd_ctl_elem_write[915] codec: rda-codec, ctrl: OutChannelNumber, val: 2
[   29.509216] -->sound/core/control.c:snd_ctl_elem_write[915] codec: rda-codec, ctrl: CodecAppMode, val: 0
[   29.510559] sound/soc/rda/rda_codec.c:rda_codec_codec_app_mode[339] condec: rda-codec
[   29.511718] <rda_msys>: pid = 39, rda-codec: ext_len = 0
[   29.512268] <rda_msys>: end of pending msg
[   29.513122] -->sound/core/control.c:snd_ctl_elem_write[915] codec: rda-codec, ctrl: StartPlay, val: 0
[   29.515930] --->sound/soc/rda/rda_codec.c:aud_StreamStart[99] itf: 1, codec: rda-codec, stream: ce30bbb0, cfg: ce30bbcc
[   29.517517] --->arch/arm/plat-rda/md_sys.c:rda_msys_send_cmd[326]
[   29.519287] --->arch/arm/plat-rda/md_sys.c:rda_msys_send_cmd[344]
[   29.576232] <rda_msys>: pid = 39, rda-codec: ext_len = 0
[   29.576721] <rda_msys>: end of pending msg
[   29.577270] --->sound/soc/rda/rda_codec.c:aud_StreamStart[106]
[   29.578063] -->sound/core/control.c:snd_ctl_elem_write[915] codec: rda-codec, ctrl: ITF, val: 1
[   29.579040] -->sound/core/control.c:snd_ctl_elem_write[915] codec: rda-codec, ctrl: SpkSel, val: 1
[   29.580139] audio SPK = 1
[   29.580139] 
[   29.581054] <rda_msys>: pid = 39, rda-codec: ext_len = 0
[   29.581542] <rda_msys>: end of pending msg
[   29.582336] -->sound/core/control.c:snd_ctl_elem_write[915] codec: rda-codec, ctrl: Capture Volume, val: 2
[   29.583496] -->sound/core/control.c:snd_ctl_elem_write[915] codec: rda-codec, ctrl: ForceMainMic, val: 1
[   29.586791] <rda_msys>: pid = 39, rda-codec: ext_len = 0
[   29.587341] <rda_msys>: end of pending msg
[   29.588195] -->sound/core/control.c:snd_ctl_elem_write[915] codec: rda-codec, ctrl: Commit Setup, val: 0
[   29.589721] <rda_msys>: pid = 39, rda-codec: ext_len = 0
[   29.590270] <rda_msys>: end of pending msg
[   29.593688] audio [start aud ifc] : substream->stream is [0], PLAYBACK, cmd is [1] 
[   29.593688] 
[   31.015380] rda_gouda_stretch_pre_wait_and_enable_clk : gouda is active.
[   31.965332] rda_gouda_stretch_pre_wait_and_enable_clk : gouda is active.
[   32.465332] rda_gouda_stretch_pre_wait_and_enable_clk : gouda is active.
[   33.315368] rda_gouda_stretch_pre_wait_and_enable_clk : gouda is active.
[   33.825317] rda_gouda_stretch_pre_wait_and_enable_clk : gouda is active.
[   34.078369] audio [stop aud ifc] : substream->stream is [0], PLAYBACK, cmd is [0] 
[   34.078369] 
[   34.079650] -->sound/core/control.c:snd_ctl_elem_write[915] codec: rda-codec, ctrl: Stop, val: 0
[   34.092407] <rda_msys>: pid = 39, rda-codec: ext_len = 0
[   34.092407] <rda_msys>: end of pending msg
[   34.269836] -->sound/core/control.c:snd_ctl_elem_write[915] codec: rda-codec, ctrl: ITF, val: 2
[   34.269897] -->sound/core/control.c:snd_ctl_elem_write[915] codec: rda-codec, ctrl: SpkSel, val: 2
[   34.269897] audio SPK = 2
[   34.269897] 
[   34.269897] audio gpio extpa is invalid !
[   34.269897] 
[   34.269958] audio gpio extpa 1 is invalid !
[   34.269958] 
[   34.270385] <rda_msys>: pid = 39, rda-codec: ext_len = 0
[   34.270385] <rda_msys>: end of pending msg
[   34.270568] -->sound/core/control.c:snd_ctl_elem_write[915] codec: rda-codec, ctrl: Capture Volume, val: 2
[   34.270629] -->sound/core/control.c:snd_ctl_elem_write[915] codec: rda-codec, ctrl: ForceMainMic, val: 0
[   34.271057] <rda_msys>: pid = 39, rda-codec: ext_len = 0
[   34.271057] <rda_msys>: end of pending msg
[   34.271423] -->sound/core/control.c:snd_ctl_elem_write[915] codec: rda-codec, ctrl: Commit Setup, val: 0
[   34.271850] <rda_msys>: pid = 39, rda-codec: ext_len = 0
[   34.271850] <rda_msys>: end of pending msg
[   34.655334] rda_gouda_stretch_pre_wait_and_enable_clk : gouda is active.
#endif
