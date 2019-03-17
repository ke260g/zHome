# HDL: Hardware Description Language
+ ABEL: Advanced Boolean Equation Language, (DATAI/O Company)
+ Superlog: upgrade and extended Verilog, (Co-Design Automation)
+ SystemC: designed basic on SoC, (Synopsys and CoWare)
+ VHDL: Very-high-speed integerated circuit HDL, (DoD)
+ Verilog HDL: Verilog HDL, (GDA, -\>Cadence)

> DoD: United States Department of Defense </br>
> GDA: Gateway Design Automation, purchased by Cadence
> Superlog: using upper Verilog-RTL-level subset

+ Programmable ASIC Devices: CPLD Versus FPGA
FPGA: Field-Programmable Gate Array
CPLD: Complex Programmable Logic Device

### 3 kinds of core
+ firm core, FPGA
+ hard core, ASIC
+ soft core,

##### Compare to CPU, the most important feature of FPGA
    + highly-real-time
    + Programmable Devices

##### implementation of Complex Digital System Circuit
+ special MCU
+ high-density FPGA
+ special ASIC
+ existing MCU-IP-Core with special ASIC

### Verilog HDL History
01. 1983, in GDA(Gate Way Design Automation) Company, Phil Moorby create firstly
02. 1983, Moorby join hand with Cadence
03. 1984 - 1985, Moorby create Verilog-XL, a simulator
04. 1986, Moorby fast-gate-level simulate algorithm, Verilog-XL-algorithm
05. 1989, Cadence purchase GDA, Verilog belongs to Cadence
06. 1990, Cadence make Verilog public
07. 1990, Cadence build OVI(Open Verilog International), maintain Verilog
08. 1995, IEEE publish `Verilog HDL 1364-1995`
09. 2001, IEEE publish `Verilog HDL 1364-2001`
10. 2005, IEEE publish `System Verilog 1800-2005`
+ Note: Verilog comes from digital ciruit simulator

##### Verilog 5 level
switch >> gate >> RTL >> algorithm >> system

### Verilog HDL Syntax
##### KeyWords
+ input, output, inout
+ module(), endmodule, begin, end, fork, join
+ assign, =, <=
+ initial
+ task, endtask
+ function, endfunction
+ always@(), posedge, negedge, or, and
+ if-else
+ case, default, endcase
+ forever, repeat, while, for
+ reg, wire, integer, parameter
+ defparam
##### Constant Expression
+ {bit-width} ' {b/h/d} {value}
    {b/h/d}, binary/heximal/decimal
    {value}, represent as {b/h/d}
    {bit-width}, a `virtual register` to store the value
+ {value}, after first digit `_` will be delete when compile,
    so that `_` can be used to make the {value} more readable.
+ parameter-type, something like macro in C, but number only(string is permitted)
##### operator
+ numeric, + - x / %
+ evaluate, = <=
+ compare,  > < >= <=
+ logic, && || !
+ condition, ?:
+ bit, ~ | ^ & ^~
+ shitf, << >>
+ splicing, {}
+ delay, #num, means delay num time-units
##### preprocess
+ timescale {time-unit} / {time-precision}
+ include
+ define
+ ifdef, ifndef, else, elsif, endif
+ reset
+ protecte

# Verilog Simulation in Linux
+ install **iverlog**, compiler and synthesis tools
+ install **gtkwave**, view the signal-wave in gui
+ `iverilog -tnull src.v test_bench.v`, check the syntax
+ `iverilog -o binary -tvvp src.v test_bench.v`, synthesis
+ in test\_bench, 2 most important sentence
    + `$dumpfile("output_vcd_file.vcd");`, output vcd file name
    + `$dumpvars(0, top_module_instance_name);`, signal show in gtkwave
+ `vvp -n binary`, simulate
+ `gtkwave outpu_vcd_file.vcd`, view the signal-wave
