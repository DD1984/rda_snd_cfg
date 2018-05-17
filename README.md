rda_snd_cfg - config sound on Orange Pi 2G-IOT ARM (RDA8810) for Ubuntu firmware

first of all:
 stop systemd service that configure sound through mixers
 this service write wrong data to sound card, and after that, when try to start play - sound card hangs!

on ubuntu 16.04 i comment some lines in files:
 - /lib/udev/rules.d/90-alsa-restore.rules
    #TEST!="/etc/alsa/state-daemon.conf", TEST=="/usr/sbin/alsactl", RUN+="/usr/sbin/alsactl -E HOME=/run/alsa restore $attr{device/number}"
    #TEST=="/etc/alsa/state-daemon.conf", TEST=="/usr/sbin/alsactl", RUN+="/usr/sbin/alsactl -E HOME=/run/alsa nrestore $attr{device/number}"

 - /etc/rc.local
    #amixer cset numid=17,iface=MIXER,name='Audio phone in' 1
    #amixer cset numid=20,iface=MIXER,name='Audio speaker out' 1
    #amixer cset numid=22,iface=MIXER,name='Audio analog headsetmic' 1

then:
 copy rda_snd_cfg to rootfs and execute it after board boot up

test sound: aplay /home/orangepi/AudioTest/TestAudio.wav


