
struct spi_reg_val {
    int addr;
    short data;
};

/* noip3sn, 10-bit mode with PLL, NZROT */

/* [1] Power Up Sequence in hardware level */

/* [2] enable clock management part1 */
struct spi_reg_val enb_clk_man_p1[8] = {
    { .addr =   2, .data = 0x0000 }, /* monochrome */
    { .addr =  32, .data = 0x7014 }, /* for noip3, not noip1 */
    { .addr =  20, .data = 0x0000 }, /* configure clock management */
    { .addr =  17, .data = 0x2113 }, /* configure PLL */
    { .addr =  26, .data = 0x2280 }, /* configure PLL lock detetor */
    { .addr =  27, .data = 0x3D2D }, /* configure PLL lock detetor */
    { .addr =   8, .data = 0x0000 }, /* release PLL soft reset */
    { .addr =  16, .data = 0x0003 }, /* enable PLL */
    /* after it, reach status-Standby(1) */
};

/* [3] enable clock management part2 */
/* enable all internal clock distribution */
struct spi_reg_val enb_clk_man_p2_a[3] = {
    { .addr =   9, .data = 0x0000 }, /* release clock soft reset */
    { .addr =  32, .data = 0x7016 }, /* enable logic clock for P3 only */
    { .addr =  34, .data = 0x0001 }, /* enable logic block */
    /* after it, reach status-Intermediate_Standby */
};
/* required register upload */
struct spi_reg_val enb_clk_man_p2_b[102] = {
    { .addr =  41, .data = 0x0854 }, { .addr =  42, .data = 0x0200 },
    { .addr =  43, .data = 0x000C }, { .addr =  65, .data = 0x48CB },
    { .addr =  66, .data = 0x53C4 }, { .addr =  67, .data = 0x4544 },
    { .addr =  68, .data = 0x0085 }, { .addr =  69, .data = 0x0848 },
    { .addr =  70, .data = 0x4411 }, { .addr =  71, .data = 0x9788 }, // # 10
    { .addr =  72, .data = 0x3330 }, { .addr = 128, .data = 0x4714 },
    { .addr = 129, .data = 0x8001 }, { .addr = 171, .data = 0x1002 },
    { .addr = 175, .data = 0x0080 }, { .addr = 176, .data = 0x00E6 },
    { .addr = 177, .data = 0x0400 }, { .addr = 192, .data = 0x000C },
    { .addr = 193, .data = 0x2C00 }, { .addr = 194, .data = 0x02E4 }, // # 20
    { .addr = 197, .data = 0x0104 }, { .addr = 199, .data = 0x0174 },
    { .addr = 200, .data = 0x0804 }, { .addr = 201, .data = 0x0060 },
    { .addr = 204, .data = 0x01E1 }, { .addr = 207, .data = 0x0000 },
    { .addr = 208, .data = 0xA100 }, { .addr = 211, .data = 0x0E39 },
    { .addr = 215, .data = 0x111F }, { .addr = 216, .data = 0x7F00 }, // # 30
    { .addr = 219, .data = 0x0020 }, { .addr = 220, .data = 0x2432 },
    { .addr = 224, .data = 0x3E17 }, { .addr = 227, .data = 0x0000 },
    { .addr = 250, .data = 0x2081 }, { .addr = 256, .data = 0xA100 },
    { .addr = 257, .data = 0x0000 }, { .addr = 258, .data = 0x07FF },
    { .addr = 384, .data = 0xC800 }, { .addr = 385, .data = 0xFB1F }, // # 40
    { .addr = 386, .data = 0xFB1F }, { .addr = 387, .data = 0xFB12 },
    { .addr = 388, .data = 0xF912 }, { .addr = 389, .data = 0xF902 },
    { .addr = 390, .data = 0xF804 }, { .addr = 391, .data = 0xF008 },
    { .addr = 392, .data = 0xF102 }, { .addr = 393, .data = 0xF30F },
    { .addr = 394, .data = 0xF30F }, { .addr = 395, .data = 0xF30F }, // # 50
    { .addr = 396, .data = 0xF30F }, { .addr = 397, .data = 0xF30F },
    { .addr = 398, .data = 0xF30F }, { .addr = 399, .data = 0xF102 },
    { .addr = 400, .data = 0xF008 }, { .addr = 401, .data = 0xF24A },
    { .addr = 402, .data = 0xF264 }, { .addr = 403, .data = 0xF226 },
    { .addr = 404, .data = 0xF021 }, { .addr = 405, .data = 0xF002 }, // # 60
    { .addr = 406, .data = 0xF40A }, { .addr = 407, .data = 0xF005 },
    { .addr = 408, .data = 0xF20F }, { .addr = 409, .data = 0xF20F },
    { .addr = 410, .data = 0xF20F }, { .addr = 411, .data = 0xF20F },
    { .addr = 412, .data = 0xF005 }, { .addr = 413, .data = 0xEC05 },
    { .addr = 414, .data = 0xC801 }, { .addr = 415, .data = 0xC800 }, // # 70
    { .addr = 416, .data = 0xC800 }, { .addr = 417, .data = 0xCC0A },
    { .addr = 418, .data = 0xC806 }, { .addr = 419, .data = 0xC800 },
    { .addr = 420, .data = 0x0030 }, { .addr = 421, .data = 0x2175 },
    { .addr = 422, .data = 0x2071 }, { .addr = 423, .data = 0x0071 },
    { .addr = 424, .data = 0x107C }, { .addr = 425, .data = 0x0071 }, // # 80
    { .addr = 426, .data = 0x0031 }, { .addr = 427, .data = 0x01B2 },
    { .addr = 428, .data = 0x21B5 }, { .addr = 429, .data = 0x20B1 },
    { .addr = 430, .data = 0x00B1 }, { .addr = 431, .data = 0x10BC },
    { .addr = 432, .data = 0x00B1 }, { .addr = 433, .data = 0x0030 },
    { .addr = 434, .data = 0x0030 }, { .addr = 435, .data = 0x2075 }, // # 90
    { .addr = 436, .data = 0x2071 }, { .addr = 437, .data = 0x0071 },
    { .addr = 438, .data = 0x107C }, { .addr = 439, .data = 0x0071 },
    { .addr = 440, .data = 0x0031 }, { .addr = 441, .data = 0x01B2 },
    { .addr = 442, .data = 0x21B5 }, { .addr = 443, .data = 0x20B1 },
    { .addr = 444, .data = 0x00B1 }, { .addr = 445, .data = 0x10BC }, // #100
    { .addr = 446, .data = 0x00B1 }, { .addr = 447, .data = 0x0030 }, // #102
    /* after it, reach status-Standby(1) */
};

/* [4] soft power up */
struct spi_reg_val soft_power_up[8] = {
    { .addr =  10, .data = 0x0000 }, /* release soft reset state */
    { .addr =  32, .data = 0x7017 }, /* enable analogue clock P3 only */
    { .addr =  64, .data = 0x0001 }, /* enable biasing clock */
    { .addr =  40, .data = 0x0003 }, /* enable column multiplexer */
    { .addr =  48, .data = 0x0001 }, /* enable AFE */
    { .addr =  68, .data = 0x0085 }, /* enable LVDS bias */
    { .addr =  72, .data = 0x3337 }, /* enable charge pump */
    { .addr = 112, .data = 0x0007 }, /* enable LVDS transmitters */
};

/* enable sequencer */
struct spi_reg_val enb_seq = { .addr = 192, .data = 0x080D };

/* disable sequecer */
struct spi_reg_val dis_seq = { .addr = 192, .data = 0x080C };

/* soft power down */
struct spi_reg_val soft_power_down[7] = {
    { .addr = 112, .data = 0x0000 }, /* disable LVDS transmitters */
    { .addr =  72, .data = 0x3330 }, /* disable charge pump */
    { .addr =  48, .data = 0x0000 }, /* disable AFE */
    { .addr =  40, .data = 0x0000 }, /* disable cloumn multiplexer */
    { .addr =  64, .data = 0x0000 }, /* disable biasing clock */
    { .addr =  32, .data = 0x7016 }, /* disable analogue clock P3 only */
    { .addr =  10, .data = 0x0999 }, /* soft reset */
}

/* disable clock management part2 */
struct spi_reg_val dis_clk_man_p2[3] = {
    { .addr =  32, .data = 0x7014 }, /* disable logic clock P3 only */
    { .addr =  34, .data = 0x0000 }, /* disable logic blocks */
    { .addr =   9, .data = 0x0009 }, /* soft reset clock generator */
}

/* disable clock management part1 */
struct spi_reg_val dis_clk_man_p1[2] = {
    { .addr =   8, .data = 0x0099 }, /* soft reset PLL */
    { .addr =  16, .data = 0x0000 }, /* disable PLL */
}
