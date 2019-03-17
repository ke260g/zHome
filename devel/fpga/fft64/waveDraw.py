#!/usr/bin/env python3
# -- coding=utf-8 --
import matplotlib.pyplot as plt
import random
import math

inFileName="dataInput.txt"
outFileName="dataOutput.txt"

def uint8_t2int8_t(val):
    if(val > 127):
        val = val - 256
    return val

x = []
x_labels = []
y = []
y_out = []

try:
    inFile = open(inFileName, 'r')
    outFile = open(outFileName, 'r')
except Exception as e:
    print("Failed to open in/out file:", e)

for line in inFile:
    if len(line) == 0:
        break
    val=int(line[:-1], 16)
    y.append(uint8_t2int8_t(val))
inFile.close()

for line in outFile:
    # complex num, [1] is real-part, [2] is imaginary-part
    com_num = line[:-1].split()
    rea_p = int(com_num[1])
    ima_p = int(com_num[2])
    val = math.sqrt(math.pow(rea_p, 2) + math.pow(ima_p, 2))
    y_out.append(val)
outFile.close()

for i in range(0, 64):
    x.append(i)
    if((i) % 16 == 0):
        x_labels.append(i)
    else:
        x_labels.append('')
x_labels[0] = 0;

inputPlt = plt.subplot(2, 1, 1)
inputPlt.set_title('dataInput')
inputPlt.plot(x, y, color="green",
        label='darkness',
        marker='s', mfc='red', markersize=5)

inputPlt = plt.subplot(2, 1, 2)
inputPlt.set_title('dataOutput')
inputPlt.plot(x, y_out, color="green",
        label='darkness',
        marker='s', mfc='red', markersize=5)
plt.show()
