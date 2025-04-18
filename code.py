# SPDX-FileCopyrightText: 2021 Kattni Rembor for Adafruit Industries
#
# SPDX-License-Identifier: MIT

"""
CircuitPython I2S MP3 playback example.
Plays a single MP3 once.
"""
import board
import digitalio
import audiomp3
import audiobusio
import audiomixer

toggle = digitalio.DigitalInOut(board.GP22)
toggle.switch_to_input(pull=digitalio.Pull.DOWN)

v1 = digitalio.DigitalInOut(board.GP2)
v1.switch_to_input(pull=digitalio.Pull.DOWN)
v2 = digitalio.DigitalInOut(board.GP3)
v2.switch_to_input(pull=digitalio.Pull.DOWN)
v3 = digitalio.DigitalInOut(board.GP4)
v3.switch_to_input(pull=digitalio.Pull.DOWN)

audio = audiobusio.I2SOut(board.GP18, board.GP19, board.GP20)

mp3 = audiomp3.MP3Decoder(open("talking2.mp3", "rb"))

mixer = audiomixer.Mixer(voice_count=1, sample_rate=24000, channel_count=1,
    bits_per_sample=16, samples_signed=True)

audio.play(mixer)
mixer.voice[0].play(mp3, loop=True)

mixer.voice[0].level = 0.1

while audio.playing:
    volume = 0.0
    if (toggle.value):
        inp = 0
        inp = (inp << 1) | v3.value
        inp = (inp << 1) | v2.value
        inp = (inp << 1) | v1.value

        volume = 0.05*(inp)
    mixer.voice[0].level = volume
