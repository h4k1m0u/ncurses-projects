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

N_BARS = 256
arr = np.loadtxt(sys.argv[1])
plt.bar(range(N_BARS), arr[:N_BARS])
plt.axhline(xmin=0, xmax=N_BARS, color='r')
plt.axvline(x=0, ymin=-1, ymax=1, color='r')
plt.axvline(x=n_samples_cycle, ymin=-1, ymax=1, color='r')
plt.show()
