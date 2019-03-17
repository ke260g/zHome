# USB Note
| version | libusb | libusb-compat |
| :-: | :-: | :-: |
| include | libusb-1.0/libusb.h | usb.h |
| so | libusb-1.0.so | usb.so |
| pkgconfig | libusb-1.0.pc | libusb.pc |

### software operation knowledge
+ descriptors { configurations, interfaces, endpoints }
+ transfer mode
    + control/bulk/interrupt/isochronous/stream
+ transfer process
    + { bulk, control, isochronous } : { token >> data > handshake }
    + interrupt : { token >> data }
### some concepts
+ device, config, interface, port(provide by usb_interface_chip)
+ dev-drv >>> usb-core >> master-control-driver > master-controller -bus
+ gadget-driver >>> gadget api >> udc-driver > slave-controller -bus

### kinds of device
+ some for device class, some for interface class from libusb
---
| class code | class name |
| --: | :-- |
| 1 | audio |
| 2 | communication device, phone, moden |
| 3 | HID, Human Interactive Device |
| 6 | image device, scaner, camera |
| 7 | printer |
| 8 | mass storage |
| 9 | hub class |
| 11 | chip card/smart card |
| 13 | Content Security |
| 14 | Video Interface |
| 15 | Personal Healthcare |
| 220 | Diagnostic Device |
| 224 | Wireless Controller(Interface) |
| 239 | Miscellaneous |
| 254 | Application Specific(Interface) |
| 255 | vendor specific |

### UHCI/OHCI/EHCI/XHCI
+ USB_1.1, USB_2.0, USB_3.0
+ master-controller
+ master-controller-driver

### OTG
+ miro/mini, 5 pins
    + VCC, D+, D-, GND, ID
+ A-Device: ID--GND
+ B-Device: ID--VCC
+ OTG-Device: using MicroAB, can change between Master/Slave
+ B-Device: can only be Slave

##### OTG SRP (Session Request Protocol)
+ using by B-Device, request A-Device to open VCC
+ need A-Device support and response SRP from B-Device.

##### OTG ADP (Attach Detection Protocol)

##### OTG HNP (Host Negotiation Protocol)

-----
### EHCI controller protocol
+ PCI Configuration Register
+ Host Controller Capability Registers
+ Host Controller Operational Registers

##### EHCI Capability Registers
`struct echi_caps { }`
| Offset | Size | Mnemonic | Register Name |
| :-: | :-: | :-: | :-: |
| 00h | 1 | CAPLENGTH | Capability Register Length |
| 01h | 1 | Reserved | N/A |
| 02h | 2 | HCIVERSION | Interface Version Number |
| 04h | 4 | HCSPARAMS | Structural Parameters |
| 08h | 4 | HCCPARAMS | Capability Parameters |
| 0Ch | 8 | HCSP-PORTROUTE | Companion Port Route Description |

##### EHCI Operational Registers
`struct echi_regs { }`
| Offset | Size | Mnemonic | Register Name |
| :-: | :-: | :-: | :-: |
| 00h | 4 | USB_CMD | USB Command |
| 04h | 4 | USB_STS | USB Status |
| 08h | 4 | USB_NTR | USB Interrupt Enable |
| 0ch | 4 | FR_INDEX | USB Frame Index |
| 10h | 4 | CTRLDS_SEGMENT | 4G Segment Seletor |
| 14h | 4 | PERIODIC_LIST_BASE | Frame List Base Address |
| 18h | 4 | ASYNC_LIST_ADDR | Next Asynchronous List Addresss |
| 1c-3f | | Reserved | N/A |
| 40h | 4 | CONFIG_FLAG | Configured Flag Register |
| 44h | 4 | PORTSC(1-N_PORTS) | Port Status/Control |

----
### ECHI data modules, all so-called data structure
1. Periodic Frame List
2. Asynchronous List Queue Head Pointer
3. Isochronous (High-Speed) Transfer Descriptor (iTD)
4. Split Transaction Isochronous Transfer Descriptor (siTD)
5. Queue Element Transfer Descriptor (qTD)
6. Queue Head
7. Periodic Frame Span Traversal Node (FSTN)
    
### ECHI time schedule V.S. asynchronous schedule

### usb-core, controlling host
`struct urb { }` usb requeset block
+ bus, port, interface, channel
+ transmit: { control, interrupt, batch, isochronic }
+ one physical host chip has one bus, each bus has one or more port
+ port is physical usb port, some are hotplugable, some are inside
+ each usb-host(root-hub) does not have the related port

### USB device class (in protocol), B-Device
+ { **Device** >>> **Configuration** >> **Interface** > **Endpoint** } Descriptor
+ Each physical device has only one **Device Descriptor**
+ each **Device** has one or more **Configuration**, descripting functionality
+ each **Configuration** has one or more **Interface**
+ each **Interface** has one or more **Endpoint**

### USB device class (in libusb), B-Device
+ **dev-desc** >>>> **config-desc** >>> **iface** >> **iface-desc** > **ep-desc**
+ each physical device has only one **dev-desc**
+ each physical device has one or more **config-desc**
+ each **config-desc** has one or more **iface**
+ each **iface** has one or more **iface-desc**
+ each **iface** has zero or one or more **ep-desc**
+ variant **iface-desc** have <u>the same set of ep-desc</u> or <u>none</u>

### USB device string description in libusb
+ **device**.iManufacturer
+ **device**.iProduct
+ **dev-desc**.iConfiguration
+ libusb_get_string_descriptor_ascii()

### Token and PIDs
| PID Type | PID Name |
| --: | :-- |
| Token | IN, OUT, SOF, SETUP |
| Data | DATA0, DATA1, DATA2, MDATA |
| Handshake | ACK, NAK, STALL, NYET |
| Special | PRE, ERR, SPLIT, PING |
| PID Type | PID Name |
| --: | :-- |
| Token | IN, OUT, SOF, SETUP |
| Data | DATA0, DATA1, DATA2, MDATA |
| Handshake | ACK, NAK, STALL, NYET |
| Special | PRE, ERR, SPLIT, PING |

# Questions
+ libusb_get_port_numbers(), what does it means
+ usb mouse always transfer 32bits bytes data
    + [00:07] scroll up or down
    + [08:15] move up or down
    + [16:23] move left or right
    + [24:31] mouse button

