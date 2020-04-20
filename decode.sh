#!/bin/bash

#	NOAA IMAGE Decoder
#	by 0fabris
#	04/2020

#NOAA 19 Frequency
FREQ=137100

fname="tmpaudio.wav"

#if $1 is set, use that for audio input
if [ -z $1 ]; then
	audio_name="audio_noaa_$(date +%Y%m%d_%H%M%S).wav"	
	rtl_fm -f "$FREQ"K -g 7.1 -s 48k -E deemp -F 9 - | sox -t raw -e signed -c 1 -b 16 -r 48000 - "$audio_name" rate 11025;
else
	audio_name=$1
fi

#if $2 is set use that for image output
if [ -z $2 ]; then
	image_name="noaa_$(date +%Y%m%d_%H%M%S).png"
else
	image_name=$2
fi

#Info Output
echo "Audio name: $audio_name"
echo "Destination image: $image_name"
echo ""

#Sample at 11025
ffmpeg -loglevel error -i "$audio_name" -ar 11025 -y "$fname";

#Analyse with wxtoimg
wxtoimg -l -t NOAA -e MSA-precip -R 1 "$fname" "$image_name";

#Not needed - Picture rotation of 180' if passage is northbound 
#convert -rotate 180 "$image_name" "$image_name";

#Clean up
rm "$fname";
echo "Success!"
