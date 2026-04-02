1. Audio files (duration=1s below) are generated in Nyquist (from within Audacity):
```lisp
(osc a4 1)
```

2. Convert it from wav/mp3 to a raw float32 binary file:

```terminal
$ ffmpeg -i audio/a4-1s.wav -f f32le audio/a4-1s.raw
```

3. For debugging, convert the raw file to txt (one value per line):

```terminal
$ od -t f4 -An -w4 audio/a4-1s.raw | awk '{ print $1 }' > audio/a4-1s.txt
$ ./python/plot_sound.py audio/a4-1s.txt  # plot audio samples
```
