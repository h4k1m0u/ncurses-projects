1. Audio files (duration=1s below) are generated in Nyquist (from within Audacity), as suggested in [Audacity docs][nyquist]. In Audacity's menu, go to Tools > Nyquist Prompt and apply the following:
```lisp
(osc a4 1)
```

Similarly, the major scale could be generated as follows:

```lisp
; major-scale-mono.mp3
(seq
  (osc c4 1)
  (osc d4 1)
  (osc e4 1)
  (osc f4 1)
  (osc g4 1)
  (osc a4 1)
  (osc b4 1)
  (osc c5 1))
```

When exporting audio, choose:
- Format: `Wav/Mp3`.
- Channels `Mono/stereo`: single sample per frame or interleaved L1 R1 L2 R2... (for stereo, 1 frame = 2 samples)
- The sample rate of `44100Hz`: Number of frames per second.
- Encoding of `32-bit float` (i.e. samples in [-1, 1]).

[nyquist]: https://www.audacity-forum.de/download/edgar/nyquist/nyquist-doc/manual/part2.html#17

2. Convert it from wav/mp3 to a raw float32 binary file:

```terminal
$ ffmpeg -i audio/a4-1s.wav -f f32le audio/a4-1s.raw
```

3. For debugging, convert the raw file to txt (one value per line):

```terminal
$ od -t f4 -An -w4 audio/a4-1s.raw | awk '{ print $1 }' > audio/a4-1s.txt
$ ./python/plot_sound.py audio/a4-1s.txt  # plot audio samples
```

4) Suppose that the sample rate used to save the mp3 file in Audacity was 48000Hz (or 44100Hz) and knowing that each float occupies 4 floats, the file size can be easily predicted for a mono/stereo track knowing its duration:

```terminal
$ sample_rate=48000 # or 44100
$ duration=1
$ size_float=4
$ n_channels=1 # n_channels=2 for stereo
$ size_predicted=$(( sample_rate * duration * size_float * n_channels ))
$ size_actual=$(du -b a4.raw | awk '{ print $1 }')
$ [ $size_predicted -eq $size_actual ] && echo "EQUAL"
```

5) Float32 audio samples can be read with mini-audio. See [miniaudio example][miniaudio-example].

[miniaudio-example]: https://gist.github.com/h4k1m0u/cf78cd3df706acfe0c2041e0f3aa91e3
