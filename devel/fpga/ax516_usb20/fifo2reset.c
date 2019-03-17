SYNCDELAY;
FIFORESET = 0x80; // activate NAK-ALL to avoid race conditions
SYNCDELAY;
EP2FIFOCFG &= 0xef; //switching to manual mode
SYNCDELAY;

// access start
// access handler
// ...

// access end

EP2FIFOCFG |= 0x10; // switching to auto mode
SYNCDELAY;
FIFORESET = 0x00; //Release NAKALL
SYNCDELAY;

#if 0 /* async discard all the data in FIFO2 */
FIFORESET = 0x02; // Reset FIFO 2
SYNCDELAY;
OUTPKTEND = 0X82; //OUTPKTEND done twice if EP2 is double buffered
SYNCDELAY;
OUTPKTEND = 0X82;
SYNCDELAY;
#endif

#if 0 /* async send 512 data to FIFO2 */
EP2BCH = 0x02;
SYNCDELAY;
EP2BCL = 0x00; // commit newly pkt. to interface fifo
SYNCDELAY;
OUTPKTEND = 0x02; // committed pkt.
#endif

		case 0xB0:
			SYNCDELAY;
			FIFORESET = 0x80; // activate NAK-ALL to avoid race conditions
			SYNCDELAY;
			EP2FIFOCFG &= 0xef; //switching to manual mode
			SYNCDELAY;
			FIFORESET = 0x82; // Reset FIFO 2
			SYNCDELAY;
			OUTPKTEND = 0X82; //OUTPKTEND done twice if EP2 is double buffered
			SYNCDELAY;
			OUTPKTEND = 0X82;
			SYNCDELAY;
			EP2FIFOCFG |= 0x10; // switching to auto mode
			SYNCDELAY;
			FIFORESET = 0x00; //Release NAKALL
			SYNCDELAY;
			break;