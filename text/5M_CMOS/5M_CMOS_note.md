Mess Info:
    sub-LVDS-Serial can be converted to mipi-CSI with IC
    CIS: cmos image sensors7
    APS-C: Advanced Photo System type-C
    ITU-R: International Technological University Radiocommunication-Sector

nanopc-T2 s5p6618 video-interfaces:
+ LVDS: output
+ MIPI-DSI: output
+ MIPI-CSI: input, new version VDS-serial-transfer, support CSI2
+ DVP: input, traditional camif

Cmos Sensor Core Features:
    chroma:  Monochrom, RGB, RGBW
    interface: CMOS-Parallel, sub-LVDS-Serial
    technology(Sony): pregius(global shutter), starvis(super ISO)

Application Stages:
    Moblie, Camera, Industry, Surveillance, HomeSecurity
    Motion_Monitoring, Barcode_Scanning, Machine_Vision

Target cmos sensors:
+ On Sony auth-website, target cmos:
    + IMX264LLR/LQR, 5M, 2/3 inch, global-shutter
    + IMX250LLR/LQR, 5M, 2/3 inch, global-shutter
+ On semicondutor products:
    + PYTHON5000, so-called NOIP1SN5000A, 5M, 1 inch, global-shutter

Produtor:
+ on semiconductor [onsemiProductWebsite](http://www.onsemi.com/PowerSolutions/parametrics.do?id=101682&lctn=header)
+ sony [sonyProductWebsite](http://www.sony-semicon.co.jp/products_en/IS/sensor0/products/cmos.html)
+ samsung
+ Omni Vision
> aptina, a branch company of Micron Technology, was purchased by onsemi

LVDS to MIPI: (LCMXO3)
+ SN65LVDS324, but input-LVDS-Parallel
+ ADV7782
+ LCMXO3, with the provided ip-core in its website
+ success-sony-cmos-sensors:
    + IMX136, IMX236, 2M, 1/3 inch
    + IMX144,
    + IMX172, 12.4M, 1/2.5 inch
    + IMX178, 5M, 1/2 inch

Resolution Description:
+ VGA: 640 * 480, 0.3M, Video-Graphics-Array
    + QVGA: Quarter-VGA, 320 * 240, 0.07M
    + WVGA: Wide-VGA 800 * 480,
    + HVGA: Half-size-VGA, 480 * 320,
    + SVGA: Super-VGA, 800 * 600
+ XGA: eXtended-Graphics-Array, 1024 * 768
    + SXGA: Super-XGA, 1280 * 1024
    + SXGA+: Super-XGA-+, 1400 * 1050
+ 1080P:    1920 * 1080, 2M
+ 720P:     1280 * 720, 0.92M
+           1920 * 1200, 2.3M

