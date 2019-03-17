##### onsemi noi serial production naming rules:
+ noip2sn1300A-qdi <=> noi xNyy RRRR A - yyy
+ x: product serial alphabet
+ N: 4_LVDS(1)/ parallel(2)/ 2_LVDS(3)
+ yy:  
    + mono(SN)
    + color(SE)
    + mono with NIR enhanced (FN)
+ RRRR: resolution
+ -yyy: -qdi(without protective foil), -qti(with protective foil)

##### Device Type Specification
+ Serial Peripheral Interface (SPI), ctrl-interface
+ Programmable Region-of-Interest (ROI) Readout

+ pipelined diff triggered in master-mode global-shutter
+ pipelined GS slave mode <= equal to => triggered GS slave mode

+ multi-window, window-overlap-readout
+ subsampling


##### block overview (P1)
+ PLL: input-clk typically is 72 MHz
+ LVDS: input-clk is 360 MHz in 10bits and 288 MHz in 8bits, need a 100ou resistor
+ PLL, LVDS Receiver, Clock input >> CMOS-Clock >> Clock-Distribution
+ AEC
+ SPI > ctrl-regs, clock-period::100ns(clock 10Mhz)
+ Image Core { Image-Core-Bias, Row-Decoder, Pixel-Array }
+ Column Structure, Column Multiplexer, programmable-Resolution
+ AFE, Analog Front End, PGA and ADC, black calibration
+ Data Formatting, CRC, frame-sync-data
+ Serializers & LVDS Interface >> 8 LVDS Output Channels
    288 MHz output driver
    10-bits, 720 MHz output-per-channel
    8-bits, 576 MHz output-per-channel
    extra-2-LVDS-output, output-clock & frame-format-sync

##### Dark Technology
+ Protective Foil
+ AEC: Automatic Exposure Control
+ CDS (correlated double sampling),
    reducing noise and increasing dynamic range
+ ZROT (Zero Row Overhead Time Mode), enable higher frame rate
    line-img-data pipelined-readout
+ NIR (extended Near-Infrared)
+ mircolens, a thing placed over pixels, improving abs-responsivity of the photodiodes
    solve the problem about not-vertical-ray
+ Black Calibration, Black Level Algorithm
+ black calibration loop,
    ensure that the black level is mapped to match the correct ADC input level.
+ Multiple Slope Integration, 3 slopes, to increase the dynamic range of the sensor

### work sequence
##### working FSM diagram, Status List
+ Power off > Low-Power Standby > Standby(1) > Intemediate Standby > Standby(2) > Idle > Running
##### Status Change Action
+ Power Up Sequence, vdd_18 > vdd_33 > vdd_pix > clock_input > reset_n > spi_active
    10 us between two steps, power-supply should ramp-up
+ Power Down Sequence, reset_n > clock_input > vdd_pix > vdd_33 > vdd_18
    10 us between two steps, power-supply should ramp-down
