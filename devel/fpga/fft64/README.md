### 64FFT, 2DIT, 2DIF, 4DIF
+ 3 method fft, 64 input, support real-number input only
+ the imaginary part of the complex-number should be `0`

##### simple description of files
+ dataInput.txt: input data, format:
    + 64 rows, one column
    + each column is 8-bit heximal unsigned data
+ dataOutput.txt, output data, format:
    + 64 rows, 3 columns
    + each-row: index real-part imaginary-part
+ fft\_xxxx.v: fft alogrithm core module
+ tb.v: test\_bench, top-level module
+ waveDraw.py:
    + using py3, matplotlib
    + read 'dataInput.txt' and show in line chart
    + read 'dataOutput.txt', show complex-number's module
    + complex-number's module is `sqrt(r**2 + i**2)`
+ fft64\_xxxx\_factors.c: calculate the ratate-factors
    + part of the std-output can be directly copied into \*.v
