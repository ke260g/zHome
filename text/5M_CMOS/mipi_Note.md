mipi alliance: a alliance work for mipi
working group in mipi-alliance:
+ [Analog Control Interface Working Group](http://mipi.org/working-groups/analog-control-interface)
+ [Battery Interface Working Group](http://mipi.org/working-groups/battery-interface)
+ [Debug Working Group](http://mipi.org/working-groups/debug)
+ [DigRFsm Working Group](http://mipi.org/working-groups/digrfsm-working-group)
+ [Low Latency Interface Working Group]()
+ [Low Speed Multipoint Link Working Group](http://mipi.org/working-groups/low-speed-multipoint-link)
+ [Marketing Working Group](http://mipi.org/working-groups/marketing)
+ [RF Front-End Working Group](http://mipi.org/working-groups/rf-front-end)
+ [Sensor Birds of a Feather Group]()
+ [Technical Steering Group](http://www.mipi.org/working-groups/technical-steering-group)
+ [Test Working Group](http://mipi.org/working-groups/test-working-group)
+ [UniPro Working Group](http://mipi.org/working-groups/unipro-working-group)

+ [Camera Working Group](http://mipi.org/working-groups/camera) : CSI-2, CSI-3
+ [Display Working Group](http://mipi.org/displayinterop) : DPI-2, DCS, DSI
+ [PHY Working Group](http://mipi.org/working-groups/phy) : D-PHY, M-PHY

MIPI:
+ Mobile Industry Processor Interface
+ a open standard for various interface

C/M/D-PHY:
+ Physical Layer Specification for CSI and DSI
+ PHY means physical, C/M/D means 3 diff specification
+ C-PHY: C means
+ D-PHY: D means 500 in Roman-Number, 500M ~ 1000M bit/s
+ M-PHY: M means

### D-PHY
+ description of src-sync, high-speed, low-power physical
+ D-PHY transmit mode
    1. **Low-Power**, 10Mhz(max), control, single-ended-signal
    2. **High-Speed**, 80 ~ 1000 Mbps/Lane, data transmission, differential signal
    3. low level protocol specify minimum unit of data is one byte
    4. lower-bit is sent before the higher-bit data
+ possible lane in PHY
    1. Low-Power Transport  (LP-TX)
    2. Low-Power Recieve    (LP-RX)
    3. High-Speed Transport (HS-TX)
    4. High-Speed Recieve   (HS-RX)
+ 3 main kind of lane
    1. unidirectional clock lane (Master: HS-TX, LP-TX) (Slave: HS-RX, LP-RX)
    2. unidirectional data lane (Master: HS-TX, LP-TX) (Slave: HS-RX, LP-RX)
    3. bidirectional data lane (Master, Slave£ºHS-TX, LP-TX, HS-RX, LP-RX, LP-CD)
    4. (no bidirectional clock lane)


> APPI: Abstracted PHY-Protocol Interface(complete PHY, all Lanes)
> PPI: PHY-Protocol Interface(**per Lane**, some signals can be shared with **multi-lanes**)
> LP-CD: ?

MIPI-DSI: Display-Serial-Interface
MIPI-CSI: Camera-Serial-Interface

MIPI-CIS: Camera Interface Specification
