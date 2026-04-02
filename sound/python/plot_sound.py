#!/usr/bin/env python3
import numpy as np
import matplotlib.pyplot as plt
import sys

if len(sys.argv) != 2:
    print(f'USAGE: {sys.argv[0]} AUDIO')
    sys.exit(1)

# #samples/cycle = sample_rate / freq (~ 100 samples when note=A4)
n_samples_cycle = 44100 / 440
print(f'# samples/cycle = {n_samples_cycle}')

arr = np.loadtxt(sys.argv[1])
plt.bar(range(256), arr[:256])
plt.axhline(xmin=0, xmax=256, color='r')
plt.axvline(x=0, ymin=-1, ymax=1, color='r')
plt.axvline(x=n_samples_cycle, ymin=-1, ymax=1, color='r')
plt.show()
