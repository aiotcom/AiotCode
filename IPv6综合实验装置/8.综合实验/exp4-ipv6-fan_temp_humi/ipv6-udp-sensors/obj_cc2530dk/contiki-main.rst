                                      1 ;--------------------------------------------------------
                                      2 ; File Created by SDCC : free open source ANSI-C Compiler
                                      3 ; Version 3.8.4 #10774 (Linux)
                                      4 ;--------------------------------------------------------
                                      5 	.module contiki_main
                                      6 	.optsdcc -mmcs51 --model-huge
                                      7 	
                                      8 ;--------------------------------------------------------
                                      9 ; Public variables in this module
                                     10 ;--------------------------------------------------------
                                     11 	.globl _main
                                     12 	.globl _OLED_Init
                                     13 	.globl _printf
                                     14 	.globl _random_init
                                     15 	.globl _puthex
                                     16 	.globl _putstring
                                     17 	.globl _netstack_init
                                     18 	.globl _queuebuf_init
                                     19 	.globl _packetbuf_set_datalen
                                     20 	.globl _packetbuf_dataptr
                                     21 	.globl _packetbuf_clear
                                     22 	.globl _cc2530_rf_set_addr
                                     23 	.globl _uart1_set_input
                                     24 	.globl _uart1_init
                                     25 	.globl _leds_off
                                     26 	.globl _leds_on
                                     27 	.globl _serial_line_init
                                     28 	.globl _serial_line_input_byte
                                     29 	.globl _soc_init
                                     30 	.globl _energest_init
                                     31 	.globl _rtimer_init
                                     32 	.globl _ctimer_init
                                     33 	.globl _etimer_next_expiration_time
                                     34 	.globl _etimer_pending
                                     35 	.globl _etimer_request_poll
                                     36 	.globl _clock_time
                                     37 	.globl _clock_init
                                     38 	.globl _autostart_start
                                     39 	.globl _process_run
                                     40 	.globl _process_init
                                     41 	.globl _process_start
                                     42 	.globl ___memcpy
                                     43 	.globl _watchdog_periodic
                                     44 	.globl _watchdog_start
                                     45 	.globl _watchdog_init
                                     46 	.globl _ACTIVE
                                     47 	.globl _TX_BYTE
                                     48 	.globl _RX_BYTE
                                     49 	.globl _ERR
                                     50 	.globl _FE
                                     51 	.globl _SLAVE
                                     52 	.globl _RE
                                     53 	.globl _MODE
                                     54 	.globl _T3OVFIF
                                     55 	.globl _T3CH0IF
                                     56 	.globl _T3CH1IF
                                     57 	.globl _T4OVFIF
                                     58 	.globl _T4CH0IF
                                     59 	.globl _T4CH1IF
                                     60 	.globl _OVFIM
                                     61 	.globl _B_0
                                     62 	.globl _B_1
                                     63 	.globl _B_2
                                     64 	.globl _B_3
                                     65 	.globl _B_4
                                     66 	.globl _B_5
                                     67 	.globl _B_6
                                     68 	.globl _B_7
                                     69 	.globl _P2IF
                                     70 	.globl _UTX0IF
                                     71 	.globl _UTX1IF
                                     72 	.globl _P1IF
                                     73 	.globl _WDTIF
                                     74 	.globl _ACC_0
                                     75 	.globl _ACC_1
                                     76 	.globl _ACC_2
                                     77 	.globl _ACC_3
                                     78 	.globl _ACC_4
                                     79 	.globl _ACC_5
                                     80 	.globl _ACC_6
                                     81 	.globl _ACC_7
                                     82 	.globl _P
                                     83 	.globl _F1
                                     84 	.globl _OV
                                     85 	.globl _RS0
                                     86 	.globl _RS1
                                     87 	.globl _F0
                                     88 	.globl _AC
                                     89 	.globl _CY
                                     90 	.globl _DMAIF
                                     91 	.globl _T1IF
                                     92 	.globl _T2IF
                                     93 	.globl _T3IF
                                     94 	.globl _T4IF
                                     95 	.globl _P0IF
                                     96 	.globl _STIF
                                     97 	.globl _DMAIE
                                     98 	.globl _T1IE
                                     99 	.globl _T2IE
                                    100 	.globl _T3IE
                                    101 	.globl _T4IE
                                    102 	.globl _P0IE
                                    103 	.globl _RFERRIE
                                    104 	.globl _ADCIE
                                    105 	.globl _URX0IE
                                    106 	.globl _URX1IE
                                    107 	.globl _ENCIE
                                    108 	.globl _STIE
                                    109 	.globl _EA
                                    110 	.globl _P2_0
                                    111 	.globl _P2_1
                                    112 	.globl _P2_2
                                    113 	.globl _P2_3
                                    114 	.globl _P2_4
                                    115 	.globl _P2_5
                                    116 	.globl _P2_6
                                    117 	.globl _P2_7
                                    118 	.globl _ENCIF_0
                                    119 	.globl _ENCIF_1
                                    120 	.globl _P1_0
                                    121 	.globl _P1_1
                                    122 	.globl _P1_2
                                    123 	.globl _P1_3
                                    124 	.globl _P1_4
                                    125 	.globl _P1_5
                                    126 	.globl _P1_6
                                    127 	.globl _P1_7
                                    128 	.globl _IT0
                                    129 	.globl _RFERRIF
                                    130 	.globl _IT1
                                    131 	.globl _URX0IF
                                    132 	.globl _ADCIF
                                    133 	.globl _URX1IF
                                    134 	.globl _P0_0
                                    135 	.globl _P0_1
                                    136 	.globl _P0_2
                                    137 	.globl _P0_3
                                    138 	.globl _P0_4
                                    139 	.globl _P0_5
                                    140 	.globl _P0_6
                                    141 	.globl _P0_7
                                    142 	.globl _WDCTL
                                    143 	.globl _U1GCR
                                    144 	.globl _U1UCR
                                    145 	.globl _U1BAUD
                                    146 	.globl _U1DBUF
                                    147 	.globl _U1CSR
                                    148 	.globl _U0GCR
                                    149 	.globl _U0UCR
                                    150 	.globl _U0BAUD
                                    151 	.globl _U0DBUF
                                    152 	.globl _U0CSR
                                    153 	.globl _TIMIF
                                    154 	.globl _T4CC1
                                    155 	.globl _T4CCTL1
                                    156 	.globl _T4CC0
                                    157 	.globl _T4CCTL0
                                    158 	.globl _T4CTL
                                    159 	.globl _T4CNT
                                    160 	.globl _T3CC1
                                    161 	.globl _T3CCTL1
                                    162 	.globl _T3CC0
                                    163 	.globl _T3CCTL0
                                    164 	.globl _T3CTL
                                    165 	.globl _T3CNT
                                    166 	.globl _T2MSEL
                                    167 	.globl _T2IRQM
                                    168 	.globl _T2MOVF2
                                    169 	.globl _T2MOVF1
                                    170 	.globl _T2MOVF0
                                    171 	.globl _T2M1
                                    172 	.globl _T2M0
                                    173 	.globl _T2IRQF
                                    174 	.globl _T2EVTCFG
                                    175 	.globl _T2CTRL
                                    176 	.globl _T1STAT
                                    177 	.globl _T1CCTL2
                                    178 	.globl _T1CCTL1
                                    179 	.globl _T1CCTL0
                                    180 	.globl _T1CTL
                                    181 	.globl _T1CNTH
                                    182 	.globl _T1CNTL
                                    183 	.globl _T1CC2H
                                    184 	.globl _T1CC2L
                                    185 	.globl _T1CC1H
                                    186 	.globl _T1CC1L
                                    187 	.globl _T1CC0H
                                    188 	.globl _T1CC0L
                                    189 	.globl _CLKCONSTA
                                    190 	.globl _CLKCONCMD
                                    191 	.globl _SLEEPSTA
                                    192 	.globl _SLEEPCMD
                                    193 	.globl _STLOAD
                                    194 	.globl _ST2
                                    195 	.globl _ST1
                                    196 	.globl _ST0
                                    197 	.globl _RFERRF
                                    198 	.globl _RFIRQF0
                                    199 	.globl _RFST
                                    200 	.globl _RFD
                                    201 	.globl _RFIRQF1
                                    202 	.globl _PSBANK
                                    203 	.globl _FMAP
                                    204 	.globl _MEMCTR
                                    205 	.globl __XPAGE
                                    206 	.globl _MPAGE
                                    207 	.globl _PMUX
                                    208 	.globl _P2DIR
                                    209 	.globl _P1DIR
                                    210 	.globl _P0DIR
                                    211 	.globl _P2INP
                                    212 	.globl _P1INP
                                    213 	.globl _P2SEL
                                    214 	.globl _P1SEL
                                    215 	.globl _P0SEL
                                    216 	.globl _APCFG
                                    217 	.globl _PERCFG
                                    218 	.globl _P0INP
                                    219 	.globl _P2IEN
                                    220 	.globl _P1IEN
                                    221 	.globl _P0IEN
                                    222 	.globl _PICTL
                                    223 	.globl _P2IFG
                                    224 	.globl _P1IFG
                                    225 	.globl _P0IFG
                                    226 	.globl _DMAREQ
                                    227 	.globl _DMAARM
                                    228 	.globl _DMA0CFGH
                                    229 	.globl _DMA0CFGL
                                    230 	.globl _DMA1CFGH
                                    231 	.globl _DMA1CFGL
                                    232 	.globl _DMAIRQ
                                    233 	.globl _ENCCS
                                    234 	.globl _ENCDO
                                    235 	.globl _ENCDI
                                    236 	.globl _RNDH
                                    237 	.globl _RNDL
                                    238 	.globl _ADCH
                                    239 	.globl _ADCL
                                    240 	.globl _ADCCON3
                                    241 	.globl _ADCCON2
                                    242 	.globl _ADCCON1
                                    243 	.globl _B
                                    244 	.globl _IRCON2
                                    245 	.globl _ACC
                                    246 	.globl _PSW
                                    247 	.globl _IRCON
                                    248 	.globl _IP1
                                    249 	.globl _IEN1
                                    250 	.globl _IP0
                                    251 	.globl _IEN0
                                    252 	.globl _P2
                                    253 	.globl _S1CON
                                    254 	.globl _IEN2
                                    255 	.globl _S0CON
                                    256 	.globl _DPS
                                    257 	.globl _P1
                                    258 	.globl _TCON
                                    259 	.globl _PCON
                                    260 	.globl _DPH1
                                    261 	.globl _DPL1
                                    262 	.globl _DPH0
                                    263 	.globl _DPL0
                                    264 	.globl _SP
                                    265 	.globl _P0
                                    266 	.globl _X_IEEE_ADDR
                                    267 	.globl _X_INFOPAGE
                                    268 	.globl _X_P2DIR
                                    269 	.globl _X_P1DIR
                                    270 	.globl _X_P0DIR
                                    271 	.globl _X_U1GCR
                                    272 	.globl _X_U1UCR
                                    273 	.globl _X_U1BAUD
                                    274 	.globl _X_U1DBUF
                                    275 	.globl _X_U1CSR
                                    276 	.globl _X_P2INP
                                    277 	.globl _X_P1INP
                                    278 	.globl _X_P2SEL
                                    279 	.globl _X_P1SEL
                                    280 	.globl _X_P0SEL
                                    281 	.globl _X_APCFG
                                    282 	.globl _X_PERCFG
                                    283 	.globl _X_T4CC1
                                    284 	.globl _X_T4CCTL1
                                    285 	.globl _X_T4CC0
                                    286 	.globl _X_T4CCTL0
                                    287 	.globl _X_T4CTL
                                    288 	.globl _X_T4CNT
                                    289 	.globl _X_RFIRQF0
                                    290 	.globl _X_T1CCTL2
                                    291 	.globl _X_T1CCTL1
                                    292 	.globl _X_T1CCTL0
                                    293 	.globl _X_T1CTL
                                    294 	.globl _X_T1CNTH
                                    295 	.globl _X_T1CNTL
                                    296 	.globl _X_RFST
                                    297 	.globl _X_T1CC2H
                                    298 	.globl _X_T1CC2L
                                    299 	.globl _X_T1CC1H
                                    300 	.globl _X_T1CC1L
                                    301 	.globl _X_T1CC0H
                                    302 	.globl _X_T1CC0L
                                    303 	.globl _X_RFD
                                    304 	.globl _X_TIMIF
                                    305 	.globl _X_DMAREQ
                                    306 	.globl _X_DMAARM
                                    307 	.globl _X_DMA0CFGH
                                    308 	.globl _X_DMA0CFGL
                                    309 	.globl _X_DMA1CFGH
                                    310 	.globl _X_DMA1CFGL
                                    311 	.globl _X_DMAIRQ
                                    312 	.globl _X_T3CC1
                                    313 	.globl _X_T3CCTL1
                                    314 	.globl _X_T3CC0
                                    315 	.globl _X_T3CCTL0
                                    316 	.globl _X_T3CTL
                                    317 	.globl _X_T3CNT
                                    318 	.globl _X_WDCTL
                                    319 	.globl _X_MEMCTR
                                    320 	.globl _X_CLKCONCMD
                                    321 	.globl _X_U0GCR
                                    322 	.globl _X_U0UCR
                                    323 	.globl _X_T2MSEL
                                    324 	.globl _X_U0BAUD
                                    325 	.globl _X_U0DBUF
                                    326 	.globl _X_RFERRF
                                    327 	.globl _X_SLEEPCMD
                                    328 	.globl _X_RNDH
                                    329 	.globl _X_RNDL
                                    330 	.globl _X_ADCH
                                    331 	.globl _X_ADCL
                                    332 	.globl _X_ADCCON3
                                    333 	.globl _X_ADCCON2
                                    334 	.globl _X_ADCCON1
                                    335 	.globl _X_ENCCS
                                    336 	.globl _X_ENCDO
                                    337 	.globl _X_ENCDI
                                    338 	.globl _X_T1STAT
                                    339 	.globl _X_PMUX
                                    340 	.globl _X_STLOAD
                                    341 	.globl _X_P2IEN
                                    342 	.globl _X_P0IEN
                                    343 	.globl _X_T2IRQM
                                    344 	.globl _X_T2MOVF2
                                    345 	.globl _X_T2MOVF1
                                    346 	.globl _X_T2MOVF0
                                    347 	.globl _X_T2M1
                                    348 	.globl _X_T2M0
                                    349 	.globl _X_T2IRQF
                                    350 	.globl _X_P2
                                    351 	.globl _X_PSBANK
                                    352 	.globl _X_FMAP
                                    353 	.globl _X_CLKCONSTA
                                    354 	.globl _X_SLEEPSTA
                                    355 	.globl _X_T2EVTCFG
                                    356 	.globl _X_ST2
                                    357 	.globl _X_ST1
                                    358 	.globl _X_ST0
                                    359 	.globl _X_T2CTRL
                                    360 	.globl _X__XPAGE
                                    361 	.globl _X_MPAGE
                                    362 	.globl _X_RFIRQF1
                                    363 	.globl _X_P1
                                    364 	.globl _X_P0INP
                                    365 	.globl _X_P1IEN
                                    366 	.globl _X_PICTL
                                    367 	.globl _X_P2IFG
                                    368 	.globl _X_P1IFG
                                    369 	.globl _X_P0IFG
                                    370 	.globl _X_U0CSR
                                    371 	.globl _X_P0
                                    372 	.globl _USBF5
                                    373 	.globl _USBF4
                                    374 	.globl _USBF3
                                    375 	.globl _USBF2
                                    376 	.globl _USBF1
                                    377 	.globl _USBF0
                                    378 	.globl _USBCNTH
                                    379 	.globl _USBCNTL
                                    380 	.globl _USBCNT0
                                    381 	.globl _USBCSOH
                                    382 	.globl _USBCSOL
                                    383 	.globl _USBMAXO
                                    384 	.globl _USBCSIH
                                    385 	.globl _USBCSIL
                                    386 	.globl _USBCS0
                                    387 	.globl _USBMAXI
                                    388 	.globl _USBCTRL
                                    389 	.globl _USBINDEX
                                    390 	.globl _USBFRMH
                                    391 	.globl _USBFRML
                                    392 	.globl _USBCIE
                                    393 	.globl _USBOIE
                                    394 	.globl _USBIIE
                                    395 	.globl _USBCIF
                                    396 	.globl _USBOIF
                                    397 	.globl _USBIIF
                                    398 	.globl _USBPOW
                                    399 	.globl _USBADDR
                                    400 	.globl _CSPT
                                    401 	.globl _CSPZ
                                    402 	.globl _CSPY
                                    403 	.globl _CSPX
                                    404 	.globl _CSPSTAT
                                    405 	.globl _CSPCTRL
                                    406 	.globl _CSPPROG23
                                    407 	.globl _CSPPROG22
                                    408 	.globl _CSPPROG21
                                    409 	.globl _CSPPROG20
                                    410 	.globl _CSPPROG19
                                    411 	.globl _CSPPROG18
                                    412 	.globl _CSPPROG17
                                    413 	.globl _CSPPROG16
                                    414 	.globl _CSPPROG15
                                    415 	.globl _CSPPROG14
                                    416 	.globl _CSPPROG13
                                    417 	.globl _CSPPROG12
                                    418 	.globl _CSPPROG11
                                    419 	.globl _CSPPROG10
                                    420 	.globl _CSPPROG9
                                    421 	.globl _CSPPROG8
                                    422 	.globl _CSPPROG7
                                    423 	.globl _CSPPROG6
                                    424 	.globl _CSPPROG5
                                    425 	.globl _CSPPROG4
                                    426 	.globl _CSPPROG3
                                    427 	.globl _CSPPROG2
                                    428 	.globl _CSPPROG1
                                    429 	.globl _CSPPROG0
                                    430 	.globl _RFC_OBS_CTRL2
                                    431 	.globl _RFC_OBS_CTRL1
                                    432 	.globl _RFC_OBS_CTRL0
                                    433 	.globl _TXFILTCFG
                                    434 	.globl _PTEST1
                                    435 	.globl _PTEST0
                                    436 	.globl _ATEST
                                    437 	.globl _DACTEST2
                                    438 	.globl _DACTEST1
                                    439 	.globl _DACTEST0
                                    440 	.globl _MDMTEST1
                                    441 	.globl _MDMTEST0
                                    442 	.globl _ADCTEST2
                                    443 	.globl _ADCTEST1
                                    444 	.globl _ADCTEST0
                                    445 	.globl _AGCCTRL3
                                    446 	.globl _AGCCTRL2
                                    447 	.globl _AGCCTRL1
                                    448 	.globl _AGCCTRL0
                                    449 	.globl _FSCAL3
                                    450 	.globl _FSCAL2
                                    451 	.globl _FSCAL1
                                    452 	.globl _FSCAL0
                                    453 	.globl _FSCTRL
                                    454 	.globl _RXCTRL
                                    455 	.globl _FREQEST
                                    456 	.globl _MDMCTRL1
                                    457 	.globl _MDMCTRL0
                                    458 	.globl _RFRND
                                    459 	.globl _RFERRM
                                    460 	.globl _RFIRQM1
                                    461 	.globl _RFIRQM0
                                    462 	.globl _TXLAST_PTR
                                    463 	.globl _TXFIRST_PTR
                                    464 	.globl _RXP1_PTR
                                    465 	.globl _RXLAST_PTR
                                    466 	.globl _RXFIRST_PTR
                                    467 	.globl _TXFIFOCNT
                                    468 	.globl _RXFIFOCNT
                                    469 	.globl _RXFIRST
                                    470 	.globl _RSSISTAT
                                    471 	.globl _RSSI
                                    472 	.globl _CCACTRL1
                                    473 	.globl _CCACTRL0
                                    474 	.globl _FSMCTRL
                                    475 	.globl _FIFOPCTRL
                                    476 	.globl _FSMSTAT1
                                    477 	.globl _FSMSTAT0
                                    478 	.globl _TXCTRL
                                    479 	.globl _TXPOWER
                                    480 	.globl _FREQCTRL
                                    481 	.globl _FREQTUNE
                                    482 	.globl _RXMASKCLR
                                    483 	.globl _RXMASKSET
                                    484 	.globl _RXENABLE
                                    485 	.globl _FRMCTRL1
                                    486 	.globl _FRMCTRL0
                                    487 	.globl _SRCEXTEN2
                                    488 	.globl _SRCEXTEN1
                                    489 	.globl _SRCEXTEN0
                                    490 	.globl _SRCSHORTEN2
                                    491 	.globl _SRCSHORTEN1
                                    492 	.globl _SRCSHORTEN0
                                    493 	.globl _SRCMATCH
                                    494 	.globl _FRMFILT1
                                    495 	.globl _FRMFILT0
                                    496 	.globl _SHORT_ADDR1
                                    497 	.globl _SHORT_ADDR0
                                    498 	.globl _PAN_ID1
                                    499 	.globl _PAN_ID0
                                    500 	.globl _EXT_ADDR7
                                    501 	.globl _EXT_ADDR6
                                    502 	.globl _EXT_ADDR5
                                    503 	.globl _EXT_ADDR4
                                    504 	.globl _EXT_ADDR3
                                    505 	.globl _EXT_ADDR2
                                    506 	.globl _EXT_ADDR1
                                    507 	.globl _EXT_ADDR0
                                    508 	.globl _SRCSHORTPENDEN2
                                    509 	.globl _SRCSHORTPENDEN1
                                    510 	.globl _SRCSHORTPENDEN0
                                    511 	.globl _SRCEXTPENDEN2
                                    512 	.globl _SRCEXTPENDEN1
                                    513 	.globl _SRCEXTPENDEN0
                                    514 	.globl _SRCRESINDEX
                                    515 	.globl _SRCRESMASK2
                                    516 	.globl _SRCRESMASK1
                                    517 	.globl _SRCRESMASK0
                                    518 	.globl _SRC_ADDR_TABLE
                                    519 	.globl _TXFIFO
                                    520 	.globl _RXFIFO
                                    521 	.globl _RFCORE_RAM
                                    522 	.globl _CMPCTL
                                    523 	.globl _OPAMPS
                                    524 	.globl _OPAMPC
                                    525 	.globl _STCV2
                                    526 	.globl _STCV1
                                    527 	.globl _STCV0
                                    528 	.globl _STCS
                                    529 	.globl _STCC
                                    530 	.globl _T1CC4H
                                    531 	.globl _T1CC4L
                                    532 	.globl _T1CC3H
                                    533 	.globl _T1CC3L
                                    534 	.globl _XX_T1CC2H
                                    535 	.globl _XX_T1CC2L
                                    536 	.globl _XX_T1CC1H
                                    537 	.globl _XX_T1CC1L
                                    538 	.globl _XX_T1CC0H
                                    539 	.globl _XX_T1CC0L
                                    540 	.globl _T1CCTL4
                                    541 	.globl _T1CCTL3
                                    542 	.globl _XX_T1CCTL2
                                    543 	.globl _XX_T1CCTL1
                                    544 	.globl _XX_T1CCTL0
                                    545 	.globl _CLD
                                    546 	.globl _IRCTL
                                    547 	.globl _CHIPINFO1
                                    548 	.globl _CHIPINFO0
                                    549 	.globl _FWDATA
                                    550 	.globl _FADDRH
                                    551 	.globl _FADDRL
                                    552 	.globl _FCTL
                                    553 	.globl _IVCTRL
                                    554 	.globl _BATTMON
                                    555 	.globl _SRCRC
                                    556 	.globl _DBGDATA
                                    557 	.globl _TESTREG0
                                    558 	.globl _CHIPID
                                    559 	.globl _CHVER
                                    560 	.globl _OBSSEL5
                                    561 	.globl _OBSSEL4
                                    562 	.globl _OBSSEL3
                                    563 	.globl _OBSSEL2
                                    564 	.globl _OBSSEL1
                                    565 	.globl _OBSSEL0
                                    566 	.globl _I2CIO
                                    567 	.globl _I2CWC
                                    568 	.globl _I2CADDR
                                    569 	.globl _I2CDATA
                                    570 	.globl _I2CSTAT
                                    571 	.globl _I2CCFG
                                    572 	.globl _OPAMPMC
                                    573 	.globl _MONMUX
                                    574 ;--------------------------------------------------------
                                    575 ; special function registers
                                    576 ;--------------------------------------------------------
                                    577 	.area RSEG    (ABS,DATA)
      000000                        578 	.org 0x0000
                           000080   579 _P0	=	0x0080
                           000081   580 _SP	=	0x0081
                           000082   581 _DPL0	=	0x0082
                           000083   582 _DPH0	=	0x0083
                           000084   583 _DPL1	=	0x0084
                           000085   584 _DPH1	=	0x0085
                           000087   585 _PCON	=	0x0087
                           000088   586 _TCON	=	0x0088
                           000090   587 _P1	=	0x0090
                           000092   588 _DPS	=	0x0092
                           000098   589 _S0CON	=	0x0098
                           00009A   590 _IEN2	=	0x009a
                           00009B   591 _S1CON	=	0x009b
                           0000A0   592 _P2	=	0x00a0
                           0000A8   593 _IEN0	=	0x00a8
                           0000A9   594 _IP0	=	0x00a9
                           0000B8   595 _IEN1	=	0x00b8
                           0000B9   596 _IP1	=	0x00b9
                           0000C0   597 _IRCON	=	0x00c0
                           0000D0   598 _PSW	=	0x00d0
                           0000E0   599 _ACC	=	0x00e0
                           0000E8   600 _IRCON2	=	0x00e8
                           0000F0   601 _B	=	0x00f0
                           0000B4   602 _ADCCON1	=	0x00b4
                           0000B5   603 _ADCCON2	=	0x00b5
                           0000B6   604 _ADCCON3	=	0x00b6
                           0000BA   605 _ADCL	=	0x00ba
                           0000BB   606 _ADCH	=	0x00bb
                           0000BC   607 _RNDL	=	0x00bc
                           0000BD   608 _RNDH	=	0x00bd
                           0000B1   609 _ENCDI	=	0x00b1
                           0000B2   610 _ENCDO	=	0x00b2
                           0000B3   611 _ENCCS	=	0x00b3
                           0000D1   612 _DMAIRQ	=	0x00d1
                           0000D2   613 _DMA1CFGL	=	0x00d2
                           0000D3   614 _DMA1CFGH	=	0x00d3
                           0000D4   615 _DMA0CFGL	=	0x00d4
                           0000D5   616 _DMA0CFGH	=	0x00d5
                           0000D6   617 _DMAARM	=	0x00d6
                           0000D7   618 _DMAREQ	=	0x00d7
                           000089   619 _P0IFG	=	0x0089
                           00008A   620 _P1IFG	=	0x008a
                           00008B   621 _P2IFG	=	0x008b
                           00008C   622 _PICTL	=	0x008c
                           0000AB   623 _P0IEN	=	0x00ab
                           00008D   624 _P1IEN	=	0x008d
                           0000AC   625 _P2IEN	=	0x00ac
                           00008F   626 _P0INP	=	0x008f
                           0000F1   627 _PERCFG	=	0x00f1
                           0000F2   628 _APCFG	=	0x00f2
                           0000F3   629 _P0SEL	=	0x00f3
                           0000F4   630 _P1SEL	=	0x00f4
                           0000F5   631 _P2SEL	=	0x00f5
                           0000F6   632 _P1INP	=	0x00f6
                           0000F7   633 _P2INP	=	0x00f7
                           0000FD   634 _P0DIR	=	0x00fd
                           0000FE   635 _P1DIR	=	0x00fe
                           0000FF   636 _P2DIR	=	0x00ff
                           0000AE   637 _PMUX	=	0x00ae
                           000093   638 _MPAGE	=	0x0093
                           000093   639 __XPAGE	=	0x0093
                           0000C7   640 _MEMCTR	=	0x00c7
                           00009F   641 _FMAP	=	0x009f
                           00009F   642 _PSBANK	=	0x009f
                           000091   643 _RFIRQF1	=	0x0091
                           0000D9   644 _RFD	=	0x00d9
                           0000E1   645 _RFST	=	0x00e1
                           0000E9   646 _RFIRQF0	=	0x00e9
                           0000BF   647 _RFERRF	=	0x00bf
                           000095   648 _ST0	=	0x0095
                           000096   649 _ST1	=	0x0096
                           000097   650 _ST2	=	0x0097
                           0000AD   651 _STLOAD	=	0x00ad
                           0000BE   652 _SLEEPCMD	=	0x00be
                           00009D   653 _SLEEPSTA	=	0x009d
                           0000C6   654 _CLKCONCMD	=	0x00c6
                           00009E   655 _CLKCONSTA	=	0x009e
                           0000DA   656 _T1CC0L	=	0x00da
                           0000DB   657 _T1CC0H	=	0x00db
                           0000DC   658 _T1CC1L	=	0x00dc
                           0000DD   659 _T1CC1H	=	0x00dd
                           0000DE   660 _T1CC2L	=	0x00de
                           0000DF   661 _T1CC2H	=	0x00df
                           0000E2   662 _T1CNTL	=	0x00e2
                           0000E3   663 _T1CNTH	=	0x00e3
                           0000E4   664 _T1CTL	=	0x00e4
                           0000E5   665 _T1CCTL0	=	0x00e5
                           0000E6   666 _T1CCTL1	=	0x00e6
                           0000E7   667 _T1CCTL2	=	0x00e7
                           0000AF   668 _T1STAT	=	0x00af
                           000094   669 _T2CTRL	=	0x0094
                           00009C   670 _T2EVTCFG	=	0x009c
                           0000A1   671 _T2IRQF	=	0x00a1
                           0000A2   672 _T2M0	=	0x00a2
                           0000A3   673 _T2M1	=	0x00a3
                           0000A4   674 _T2MOVF0	=	0x00a4
                           0000A5   675 _T2MOVF1	=	0x00a5
                           0000A6   676 _T2MOVF2	=	0x00a6
                           0000A7   677 _T2IRQM	=	0x00a7
                           0000C3   678 _T2MSEL	=	0x00c3
                           0000CA   679 _T3CNT	=	0x00ca
                           0000CB   680 _T3CTL	=	0x00cb
                           0000CC   681 _T3CCTL0	=	0x00cc
                           0000CD   682 _T3CC0	=	0x00cd
                           0000CE   683 _T3CCTL1	=	0x00ce
                           0000CF   684 _T3CC1	=	0x00cf
                           0000EA   685 _T4CNT	=	0x00ea
                           0000EB   686 _T4CTL	=	0x00eb
                           0000EC   687 _T4CCTL0	=	0x00ec
                           0000ED   688 _T4CC0	=	0x00ed
                           0000EE   689 _T4CCTL1	=	0x00ee
                           0000EF   690 _T4CC1	=	0x00ef
                           0000D8   691 _TIMIF	=	0x00d8
                           000086   692 _U0CSR	=	0x0086
                           0000C1   693 _U0DBUF	=	0x00c1
                           0000C2   694 _U0BAUD	=	0x00c2
                           0000C4   695 _U0UCR	=	0x00c4
                           0000C5   696 _U0GCR	=	0x00c5
                           0000F8   697 _U1CSR	=	0x00f8
                           0000F9   698 _U1DBUF	=	0x00f9
                           0000FA   699 _U1BAUD	=	0x00fa
                           0000FB   700 _U1UCR	=	0x00fb
                           0000FC   701 _U1GCR	=	0x00fc
                           0000C9   702 _WDCTL	=	0x00c9
                                    703 ;--------------------------------------------------------
                                    704 ; special function bits
                                    705 ;--------------------------------------------------------
                                    706 	.area RSEG    (ABS,DATA)
      000000                        707 	.org 0x0000
                           000087   708 _P0_7	=	0x0087
                           000086   709 _P0_6	=	0x0086
                           000085   710 _P0_5	=	0x0085
                           000084   711 _P0_4	=	0x0084
                           000083   712 _P0_3	=	0x0083
                           000082   713 _P0_2	=	0x0082
                           000081   714 _P0_1	=	0x0081
                           000080   715 _P0_0	=	0x0080
                           00008F   716 _URX1IF	=	0x008f
                           00008D   717 _ADCIF	=	0x008d
                           00008B   718 _URX0IF	=	0x008b
                           00008A   719 _IT1	=	0x008a
                           000089   720 _RFERRIF	=	0x0089
                           000088   721 _IT0	=	0x0088
                           000097   722 _P1_7	=	0x0097
                           000096   723 _P1_6	=	0x0096
                           000095   724 _P1_5	=	0x0095
                           000094   725 _P1_4	=	0x0094
                           000093   726 _P1_3	=	0x0093
                           000092   727 _P1_2	=	0x0092
                           000091   728 _P1_1	=	0x0091
                           000090   729 _P1_0	=	0x0090
                           000099   730 _ENCIF_1	=	0x0099
                           000098   731 _ENCIF_0	=	0x0098
                           0000A7   732 _P2_7	=	0x00a7
                           0000A6   733 _P2_6	=	0x00a6
                           0000A5   734 _P2_5	=	0x00a5
                           0000A4   735 _P2_4	=	0x00a4
                           0000A3   736 _P2_3	=	0x00a3
                           0000A2   737 _P2_2	=	0x00a2
                           0000A1   738 _P2_1	=	0x00a1
                           0000A0   739 _P2_0	=	0x00a0
                           0000AF   740 _EA	=	0x00af
                           0000AD   741 _STIE	=	0x00ad
                           0000AC   742 _ENCIE	=	0x00ac
                           0000AB   743 _URX1IE	=	0x00ab
                           0000AA   744 _URX0IE	=	0x00aa
                           0000A9   745 _ADCIE	=	0x00a9
                           0000A8   746 _RFERRIE	=	0x00a8
                           0000BD   747 _P0IE	=	0x00bd
                           0000BC   748 _T4IE	=	0x00bc
                           0000BB   749 _T3IE	=	0x00bb
                           0000BA   750 _T2IE	=	0x00ba
                           0000B9   751 _T1IE	=	0x00b9
                           0000B8   752 _DMAIE	=	0x00b8
                           0000C7   753 _STIF	=	0x00c7
                           0000C5   754 _P0IF	=	0x00c5
                           0000C4   755 _T4IF	=	0x00c4
                           0000C3   756 _T3IF	=	0x00c3
                           0000C2   757 _T2IF	=	0x00c2
                           0000C1   758 _T1IF	=	0x00c1
                           0000C0   759 _DMAIF	=	0x00c0
                           0000D7   760 _CY	=	0x00d7
                           0000D6   761 _AC	=	0x00d6
                           0000D5   762 _F0	=	0x00d5
                           0000D4   763 _RS1	=	0x00d4
                           0000D3   764 _RS0	=	0x00d3
                           0000D2   765 _OV	=	0x00d2
                           0000D1   766 _F1	=	0x00d1
                           0000D0   767 _P	=	0x00d0
                           0000E7   768 _ACC_7	=	0x00e7
                           0000E6   769 _ACC_6	=	0x00e6
                           0000E5   770 _ACC_5	=	0x00e5
                           0000E4   771 _ACC_4	=	0x00e4
                           0000E3   772 _ACC_3	=	0x00e3
                           0000E2   773 _ACC_2	=	0x00e2
                           0000E1   774 _ACC_1	=	0x00e1
                           0000E0   775 _ACC_0	=	0x00e0
                           0000EC   776 _WDTIF	=	0x00ec
                           0000EB   777 _P1IF	=	0x00eb
                           0000EA   778 _UTX1IF	=	0x00ea
                           0000E9   779 _UTX0IF	=	0x00e9
                           0000E8   780 _P2IF	=	0x00e8
                           0000F7   781 _B_7	=	0x00f7
                           0000F6   782 _B_6	=	0x00f6
                           0000F5   783 _B_5	=	0x00f5
                           0000F4   784 _B_4	=	0x00f4
                           0000F3   785 _B_3	=	0x00f3
                           0000F2   786 _B_2	=	0x00f2
                           0000F1   787 _B_1	=	0x00f1
                           0000F0   788 _B_0	=	0x00f0
                           0000DE   789 _OVFIM	=	0x00de
                           0000DD   790 _T4CH1IF	=	0x00dd
                           0000DC   791 _T4CH0IF	=	0x00dc
                           0000DB   792 _T4OVFIF	=	0x00db
                           0000DA   793 _T3CH1IF	=	0x00da
                           0000D9   794 _T3CH0IF	=	0x00d9
                           0000D8   795 _T3OVFIF	=	0x00d8
                           0000FF   796 _MODE	=	0x00ff
                           0000FE   797 _RE	=	0x00fe
                           0000FD   798 _SLAVE	=	0x00fd
                           0000FC   799 _FE	=	0x00fc
                           0000FB   800 _ERR	=	0x00fb
                           0000FA   801 _RX_BYTE	=	0x00fa
                           0000F9   802 _TX_BYTE	=	0x00f9
                           0000F8   803 _ACTIVE	=	0x00f8
                                    804 ;--------------------------------------------------------
                                    805 ; overlayable register banks
                                    806 ;--------------------------------------------------------
                                    807 	.area REG_BANK_0	(REL,OVR,DATA)
      000000                        808 	.ds 8
                                    809 ;--------------------------------------------------------
                                    810 ; internal ram data
                                    811 ;--------------------------------------------------------
                                    812 	.area DSEG    (DATA)
      000008                        813 _len:
      000008                        814 	.ds 2
                                    815 ;--------------------------------------------------------
                                    816 ; overlayable items in internal ram 
                                    817 ;--------------------------------------------------------
                                    818 ;--------------------------------------------------------
                                    819 ; Stack segment in internal ram 
                                    820 ;--------------------------------------------------------
                                    821 	.area	SSEG
      000021                        822 __start__stack:
      000021                        823 	.ds	1
                                    824 
                                    825 ;--------------------------------------------------------
                                    826 ; indirectly addressable internal ram data
                                    827 ;--------------------------------------------------------
                                    828 	.area ISEG    (DATA)
                                    829 ;--------------------------------------------------------
                                    830 ; absolute internal ram data
                                    831 ;--------------------------------------------------------
                                    832 	.area IABS    (ABS,DATA)
                                    833 	.area IABS    (ABS,DATA)
                                    834 ;--------------------------------------------------------
                                    835 ; bit data
                                    836 ;--------------------------------------------------------
                                    837 	.area BSEG    (BIT)
                                    838 ;--------------------------------------------------------
                                    839 ; paged external ram data
                                    840 ;--------------------------------------------------------
                                    841 	.area PSEG    (PAG,XDATA)
                                    842 ;--------------------------------------------------------
                                    843 ; external ram data
                                    844 ;--------------------------------------------------------
                                    845 	.area XSEG    (XDATA)
                           0061A6   846 _MONMUX	=	0x61a6
                           0061A6   847 _OPAMPMC	=	0x61a6
                           006230   848 _I2CCFG	=	0x6230
                           006231   849 _I2CSTAT	=	0x6231
                           006232   850 _I2CDATA	=	0x6232
                           006233   851 _I2CADDR	=	0x6233
                           006234   852 _I2CWC	=	0x6234
                           006235   853 _I2CIO	=	0x6235
                           006243   854 _OBSSEL0	=	0x6243
                           006244   855 _OBSSEL1	=	0x6244
                           006245   856 _OBSSEL2	=	0x6245
                           006246   857 _OBSSEL3	=	0x6246
                           006247   858 _OBSSEL4	=	0x6247
                           006248   859 _OBSSEL5	=	0x6248
                           006249   860 _CHVER	=	0x6249
                           00624A   861 _CHIPID	=	0x624a
                           00624B   862 _TESTREG0	=	0x624b
                           006260   863 _DBGDATA	=	0x6260
                           006262   864 _SRCRC	=	0x6262
                           006264   865 _BATTMON	=	0x6264
                           006265   866 _IVCTRL	=	0x6265
                           006270   867 _FCTL	=	0x6270
                           006271   868 _FADDRL	=	0x6271
                           006272   869 _FADDRH	=	0x6272
                           006273   870 _FWDATA	=	0x6273
                           006276   871 _CHIPINFO0	=	0x6276
                           006277   872 _CHIPINFO1	=	0x6277
                           006281   873 _IRCTL	=	0x6281
                           006290   874 _CLD	=	0x6290
                           0062A0   875 _XX_T1CCTL0	=	0x62a0
                           0062A1   876 _XX_T1CCTL1	=	0x62a1
                           0062A2   877 _XX_T1CCTL2	=	0x62a2
                           0062A3   878 _T1CCTL3	=	0x62a3
                           0062A4   879 _T1CCTL4	=	0x62a4
                           0062A6   880 _XX_T1CC0L	=	0x62a6
                           0062A7   881 _XX_T1CC0H	=	0x62a7
                           0062A8   882 _XX_T1CC1L	=	0x62a8
                           0062A9   883 _XX_T1CC1H	=	0x62a9
                           0062AA   884 _XX_T1CC2L	=	0x62aa
                           0062AB   885 _XX_T1CC2H	=	0x62ab
                           0062AC   886 _T1CC3L	=	0x62ac
                           0062AD   887 _T1CC3H	=	0x62ad
                           0062AE   888 _T1CC4L	=	0x62ae
                           0062AF   889 _T1CC4H	=	0x62af
                           0062B0   890 _STCC	=	0x62b0
                           0062B1   891 _STCS	=	0x62b1
                           0062B2   892 _STCV0	=	0x62b2
                           0062B3   893 _STCV1	=	0x62b3
                           0062B4   894 _STCV2	=	0x62b4
                           0062C0   895 _OPAMPC	=	0x62c0
                           0062C1   896 _OPAMPS	=	0x62c1
                           0062D0   897 _CMPCTL	=	0x62d0
                           006000   898 _RFCORE_RAM	=	0x6000
                           006000   899 _RXFIFO	=	0x6000
                           006080   900 _TXFIFO	=	0x6080
                           006100   901 _SRC_ADDR_TABLE	=	0x6100
                           006160   902 _SRCRESMASK0	=	0x6160
                           006161   903 _SRCRESMASK1	=	0x6161
                           006162   904 _SRCRESMASK2	=	0x6162
                           006163   905 _SRCRESINDEX	=	0x6163
                           006164   906 _SRCEXTPENDEN0	=	0x6164
                           006165   907 _SRCEXTPENDEN1	=	0x6165
                           006166   908 _SRCEXTPENDEN2	=	0x6166
                           006167   909 _SRCSHORTPENDEN0	=	0x6167
                           006168   910 _SRCSHORTPENDEN1	=	0x6168
                           006169   911 _SRCSHORTPENDEN2	=	0x6169
                           00616A   912 _EXT_ADDR0	=	0x616a
                           00616B   913 _EXT_ADDR1	=	0x616b
                           00616C   914 _EXT_ADDR2	=	0x616c
                           00616D   915 _EXT_ADDR3	=	0x616d
                           00616E   916 _EXT_ADDR4	=	0x616e
                           00616F   917 _EXT_ADDR5	=	0x616f
                           006170   918 _EXT_ADDR6	=	0x6170
                           006171   919 _EXT_ADDR7	=	0x6171
                           006172   920 _PAN_ID0	=	0x6172
                           006173   921 _PAN_ID1	=	0x6173
                           006174   922 _SHORT_ADDR0	=	0x6174
                           006175   923 _SHORT_ADDR1	=	0x6175
                           006180   924 _FRMFILT0	=	0x6180
                           006181   925 _FRMFILT1	=	0x6181
                           006182   926 _SRCMATCH	=	0x6182
                           006183   927 _SRCSHORTEN0	=	0x6183
                           006184   928 _SRCSHORTEN1	=	0x6184
                           006185   929 _SRCSHORTEN2	=	0x6185
                           006186   930 _SRCEXTEN0	=	0x6186
                           006187   931 _SRCEXTEN1	=	0x6187
                           006188   932 _SRCEXTEN2	=	0x6188
                           006189   933 _FRMCTRL0	=	0x6189
                           00618A   934 _FRMCTRL1	=	0x618a
                           00618B   935 _RXENABLE	=	0x618b
                           00618C   936 _RXMASKSET	=	0x618c
                           00618D   937 _RXMASKCLR	=	0x618d
                           00618E   938 _FREQTUNE	=	0x618e
                           00618F   939 _FREQCTRL	=	0x618f
                           006190   940 _TXPOWER	=	0x6190
                           006191   941 _TXCTRL	=	0x6191
                           006192   942 _FSMSTAT0	=	0x6192
                           006193   943 _FSMSTAT1	=	0x6193
                           006194   944 _FIFOPCTRL	=	0x6194
                           006195   945 _FSMCTRL	=	0x6195
                           006196   946 _CCACTRL0	=	0x6196
                           006197   947 _CCACTRL1	=	0x6197
                           006198   948 _RSSI	=	0x6198
                           006199   949 _RSSISTAT	=	0x6199
                           00619A   950 _RXFIRST	=	0x619a
                           00619B   951 _RXFIFOCNT	=	0x619b
                           00619C   952 _TXFIFOCNT	=	0x619c
                           00619D   953 _RXFIRST_PTR	=	0x619d
                           00619E   954 _RXLAST_PTR	=	0x619e
                           00619F   955 _RXP1_PTR	=	0x619f
                           0061A1   956 _TXFIRST_PTR	=	0x61a1
                           0061A2   957 _TXLAST_PTR	=	0x61a2
                           0061A3   958 _RFIRQM0	=	0x61a3
                           0061A4   959 _RFIRQM1	=	0x61a4
                           0061A5   960 _RFERRM	=	0x61a5
                           0061A7   961 _RFRND	=	0x61a7
                           0061A8   962 _MDMCTRL0	=	0x61a8
                           0061A9   963 _MDMCTRL1	=	0x61a9
                           0061AA   964 _FREQEST	=	0x61aa
                           0061AB   965 _RXCTRL	=	0x61ab
                           0061AC   966 _FSCTRL	=	0x61ac
                           0061AD   967 _FSCAL0	=	0x61ad
                           0061AE   968 _FSCAL1	=	0x61ae
                           0061AF   969 _FSCAL2	=	0x61af
                           0061B0   970 _FSCAL3	=	0x61b0
                           0061B1   971 _AGCCTRL0	=	0x61b1
                           0061B2   972 _AGCCTRL1	=	0x61b2
                           0061B3   973 _AGCCTRL2	=	0x61b3
                           0061B4   974 _AGCCTRL3	=	0x61b4
                           0061B5   975 _ADCTEST0	=	0x61b5
                           0061B6   976 _ADCTEST1	=	0x61b6
                           0061B7   977 _ADCTEST2	=	0x61b7
                           0061B8   978 _MDMTEST0	=	0x61b8
                           0061B9   979 _MDMTEST1	=	0x61b9
                           0061BA   980 _DACTEST0	=	0x61ba
                           0061BB   981 _DACTEST1	=	0x61bb
                           0061BC   982 _DACTEST2	=	0x61bc
                           0061BD   983 _ATEST	=	0x61bd
                           0061BE   984 _PTEST0	=	0x61be
                           0061BF   985 _PTEST1	=	0x61bf
                           0061FA   986 _TXFILTCFG	=	0x61fa
                           0061EB   987 _RFC_OBS_CTRL0	=	0x61eb
                           0061EC   988 _RFC_OBS_CTRL1	=	0x61ec
                           0061ED   989 _RFC_OBS_CTRL2	=	0x61ed
                           0061C0   990 _CSPPROG0	=	0x61c0
                           0061C1   991 _CSPPROG1	=	0x61c1
                           0061C2   992 _CSPPROG2	=	0x61c2
                           0061C3   993 _CSPPROG3	=	0x61c3
                           0061C4   994 _CSPPROG4	=	0x61c4
                           0061C5   995 _CSPPROG5	=	0x61c5
                           0061C6   996 _CSPPROG6	=	0x61c6
                           0061C7   997 _CSPPROG7	=	0x61c7
                           0061C8   998 _CSPPROG8	=	0x61c8
                           0061C9   999 _CSPPROG9	=	0x61c9
                           0061CA  1000 _CSPPROG10	=	0x61ca
                           0061CB  1001 _CSPPROG11	=	0x61cb
                           0061CC  1002 _CSPPROG12	=	0x61cc
                           0061CD  1003 _CSPPROG13	=	0x61cd
                           0061CE  1004 _CSPPROG14	=	0x61ce
                           0061CF  1005 _CSPPROG15	=	0x61cf
                           0061D0  1006 _CSPPROG16	=	0x61d0
                           0061D1  1007 _CSPPROG17	=	0x61d1
                           0061D2  1008 _CSPPROG18	=	0x61d2
                           0061D3  1009 _CSPPROG19	=	0x61d3
                           0061D4  1010 _CSPPROG20	=	0x61d4
                           0061D5  1011 _CSPPROG21	=	0x61d5
                           0061D6  1012 _CSPPROG22	=	0x61d6
                           0061D7  1013 _CSPPROG23	=	0x61d7
                           0061E0  1014 _CSPCTRL	=	0x61e0
                           0061E1  1015 _CSPSTAT	=	0x61e1
                           0061E2  1016 _CSPX	=	0x61e2
                           0061E3  1017 _CSPY	=	0x61e3
                           0061E4  1018 _CSPZ	=	0x61e4
                           0061E5  1019 _CSPT	=	0x61e5
                           006200  1020 _USBADDR	=	0x6200
                           006201  1021 _USBPOW	=	0x6201
                           006202  1022 _USBIIF	=	0x6202
                           006204  1023 _USBOIF	=	0x6204
                           006206  1024 _USBCIF	=	0x6206
                           006207  1025 _USBIIE	=	0x6207
                           006209  1026 _USBOIE	=	0x6209
                           00620B  1027 _USBCIE	=	0x620b
                           00620C  1028 _USBFRML	=	0x620c
                           00620D  1029 _USBFRMH	=	0x620d
                           00620E  1030 _USBINDEX	=	0x620e
                           00620F  1031 _USBCTRL	=	0x620f
                           006210  1032 _USBMAXI	=	0x6210
                           006211  1033 _USBCS0	=	0x6211
                           006211  1034 _USBCSIL	=	0x6211
                           006212  1035 _USBCSIH	=	0x6212
                           006213  1036 _USBMAXO	=	0x6213
                           006214  1037 _USBCSOL	=	0x6214
                           006215  1038 _USBCSOH	=	0x6215
                           006216  1039 _USBCNT0	=	0x6216
                           006216  1040 _USBCNTL	=	0x6216
                           006217  1041 _USBCNTH	=	0x6217
                           006220  1042 _USBF0	=	0x6220
                           006222  1043 _USBF1	=	0x6222
                           006224  1044 _USBF2	=	0x6224
                           006226  1045 _USBF3	=	0x6226
                           006228  1046 _USBF4	=	0x6228
                           00622A  1047 _USBF5	=	0x622a
                           007080  1048 _X_P0	=	0x7080
                           007086  1049 _X_U0CSR	=	0x7086
                           007089  1050 _X_P0IFG	=	0x7089
                           00708A  1051 _X_P1IFG	=	0x708a
                           00708B  1052 _X_P2IFG	=	0x708b
                           00708C  1053 _X_PICTL	=	0x708c
                           00708D  1054 _X_P1IEN	=	0x708d
                           00708F  1055 _X_P0INP	=	0x708f
                           007090  1056 _X_P1	=	0x7090
                           007091  1057 _X_RFIRQF1	=	0x7091
                           007093  1058 _X_MPAGE	=	0x7093
                           007093  1059 _X__XPAGE	=	0x7093
                           007094  1060 _X_T2CTRL	=	0x7094
                           007095  1061 _X_ST0	=	0x7095
                           007096  1062 _X_ST1	=	0x7096
                           007097  1063 _X_ST2	=	0x7097
                           00709C  1064 _X_T2EVTCFG	=	0x709c
                           00709D  1065 _X_SLEEPSTA	=	0x709d
                           00709E  1066 _X_CLKCONSTA	=	0x709e
                           00709F  1067 _X_FMAP	=	0x709f
                           00709F  1068 _X_PSBANK	=	0x709f
                           0070A0  1069 _X_P2	=	0x70a0
                           0070A1  1070 _X_T2IRQF	=	0x70a1
                           0070A2  1071 _X_T2M0	=	0x70a2
                           0070A3  1072 _X_T2M1	=	0x70a3
                           0070A4  1073 _X_T2MOVF0	=	0x70a4
                           0070A5  1074 _X_T2MOVF1	=	0x70a5
                           0070A6  1075 _X_T2MOVF2	=	0x70a6
                           0070A7  1076 _X_T2IRQM	=	0x70a7
                           0070AB  1077 _X_P0IEN	=	0x70ab
                           0070AC  1078 _X_P2IEN	=	0x70ac
                           0070AD  1079 _X_STLOAD	=	0x70ad
                           0070AE  1080 _X_PMUX	=	0x70ae
                           0070AF  1081 _X_T1STAT	=	0x70af
                           0070B1  1082 _X_ENCDI	=	0x70b1
                           0070B2  1083 _X_ENCDO	=	0x70b2
                           0070B3  1084 _X_ENCCS	=	0x70b3
                           0070B4  1085 _X_ADCCON1	=	0x70b4
                           0070B5  1086 _X_ADCCON2	=	0x70b5
                           0070B6  1087 _X_ADCCON3	=	0x70b6
                           0070BA  1088 _X_ADCL	=	0x70ba
                           0070BB  1089 _X_ADCH	=	0x70bb
                           0070BC  1090 _X_RNDL	=	0x70bc
                           0070BD  1091 _X_RNDH	=	0x70bd
                           0070BE  1092 _X_SLEEPCMD	=	0x70be
                           0070BF  1093 _X_RFERRF	=	0x70bf
                           0070C1  1094 _X_U0DBUF	=	0x70c1
                           0070C2  1095 _X_U0BAUD	=	0x70c2
                           0070C3  1096 _X_T2MSEL	=	0x70c3
                           0070C4  1097 _X_U0UCR	=	0x70c4
                           0070C5  1098 _X_U0GCR	=	0x70c5
                           0070C6  1099 _X_CLKCONCMD	=	0x70c6
                           0070C7  1100 _X_MEMCTR	=	0x70c7
                           0070C9  1101 _X_WDCTL	=	0x70c9
                           0070CA  1102 _X_T3CNT	=	0x70ca
                           0070CB  1103 _X_T3CTL	=	0x70cb
                           0070CC  1104 _X_T3CCTL0	=	0x70cc
                           0070CD  1105 _X_T3CC0	=	0x70cd
                           0070CE  1106 _X_T3CCTL1	=	0x70ce
                           0070CF  1107 _X_T3CC1	=	0x70cf
                           0070D1  1108 _X_DMAIRQ	=	0x70d1
                           0070D2  1109 _X_DMA1CFGL	=	0x70d2
                           0070D3  1110 _X_DMA1CFGH	=	0x70d3
                           0070D4  1111 _X_DMA0CFGL	=	0x70d4
                           0070D5  1112 _X_DMA0CFGH	=	0x70d5
                           0070D6  1113 _X_DMAARM	=	0x70d6
                           0070D7  1114 _X_DMAREQ	=	0x70d7
                           0070D8  1115 _X_TIMIF	=	0x70d8
                           0070D9  1116 _X_RFD	=	0x70d9
                           0070DA  1117 _X_T1CC0L	=	0x70da
                           0070DB  1118 _X_T1CC0H	=	0x70db
                           0070DC  1119 _X_T1CC1L	=	0x70dc
                           0070DD  1120 _X_T1CC1H	=	0x70dd
                           0070DE  1121 _X_T1CC2L	=	0x70de
                           0070DF  1122 _X_T1CC2H	=	0x70df
                           0070E1  1123 _X_RFST	=	0x70e1
                           0070E2  1124 _X_T1CNTL	=	0x70e2
                           0070E3  1125 _X_T1CNTH	=	0x70e3
                           0070E4  1126 _X_T1CTL	=	0x70e4
                           0070E5  1127 _X_T1CCTL0	=	0x70e5
                           0070E6  1128 _X_T1CCTL1	=	0x70e6
                           0070E7  1129 _X_T1CCTL2	=	0x70e7
                           0070E9  1130 _X_RFIRQF0	=	0x70e9
                           0070EA  1131 _X_T4CNT	=	0x70ea
                           0070EB  1132 _X_T4CTL	=	0x70eb
                           0070EC  1133 _X_T4CCTL0	=	0x70ec
                           0070ED  1134 _X_T4CC0	=	0x70ed
                           0070EE  1135 _X_T4CCTL1	=	0x70ee
                           0070EF  1136 _X_T4CC1	=	0x70ef
                           0070F1  1137 _X_PERCFG	=	0x70f1
                           0070F2  1138 _X_APCFG	=	0x70f2
                           0070F3  1139 _X_P0SEL	=	0x70f3
                           0070F4  1140 _X_P1SEL	=	0x70f4
                           0070F5  1141 _X_P2SEL	=	0x70f5
                           0070F6  1142 _X_P1INP	=	0x70f6
                           0070F7  1143 _X_P2INP	=	0x70f7
                           0070F8  1144 _X_U1CSR	=	0x70f8
                           0070F9  1145 _X_U1DBUF	=	0x70f9
                           0070FA  1146 _X_U1BAUD	=	0x70fa
                           0070FB  1147 _X_U1UCR	=	0x70fb
                           0070FC  1148 _X_U1GCR	=	0x70fc
                           0070FD  1149 _X_P0DIR	=	0x70fd
                           0070FE  1150 _X_P1DIR	=	0x70fe
                           0070FF  1151 _X_P2DIR	=	0x70ff
                           007800  1152 _X_INFOPAGE	=	0x7800
                           00780C  1153 _X_IEEE_ADDR	=	0x780c
                                   1154 ;--------------------------------------------------------
                                   1155 ; absolute external ram data
                                   1156 ;--------------------------------------------------------
                                   1157 	.area XABS    (ABS,XDATA)
                                   1158 ;--------------------------------------------------------
                                   1159 ; external initialized ram data
                                   1160 ;--------------------------------------------------------
                                   1161 	.area XISEG   (XDATA)
                                   1162 	.area HOME    (CODE)
                                   1163 	.area GSINIT0 (CODE)
                                   1164 	.area GSINIT1 (CODE)
                                   1165 	.area GSINIT2 (CODE)
                                   1166 	.area GSINIT3 (CODE)
                                   1167 	.area GSINIT4 (CODE)
                                   1168 	.area GSINIT5 (CODE)
                                   1169 	.area GSINIT  (CODE)
                                   1170 	.area GSFINAL (CODE)
                                   1171 	.area CSEG    (CODE)
                                   1172 ;--------------------------------------------------------
                                   1173 ; interrupt vector 
                                   1174 ;--------------------------------------------------------
                                   1175 	.area HOME    (CODE)
      000000                       1176 __interrupt_vect:
      000000 02 49 CA         [24] 1177 	ljmp	__sdcc_gsinit_startup
      000003 32               [24] 1178 	reti
      000004                       1179 	.ds	7
      00000B 32               [24] 1180 	reti
      00000C                       1181 	.ds	7
      000013 02 05 08         [24] 1182 	ljmp	_uart0_rx_isr
      000016                       1183 	.ds	5
      00001B 32               [24] 1184 	reti
      00001C                       1185 	.ds	7
      000023 32               [24] 1186 	reti
      000024                       1187 	.ds	7
      00002B 02 3E 69         [24] 1188 	ljmp	_clock_isr
      00002E                       1189 	.ds	5
      000033 32               [24] 1190 	reti
      000034                       1191 	.ds	7
      00003B 32               [24] 1192 	reti
      00003C                       1193 	.ds	7
      000043 32               [24] 1194 	reti
      000044                       1195 	.ds	7
      00004B 02 3F 9C         [24] 1196 	ljmp	_rtimer_isr
      00004E                       1197 	.ds	5
      000053 32               [24] 1198 	reti
      000054                       1199 	.ds	7
      00005B 32               [24] 1200 	reti
      00005C                       1201 	.ds	7
      000063 32               [24] 1202 	reti
      000064                       1203 	.ds	7
      00006B 02 48 9B         [24] 1204 	ljmp	_port_0_isr
                                   1205 ;--------------------------------------------------------
                                   1206 ; global & static initialisations
                                   1207 ;--------------------------------------------------------
                                   1208 	.area HOME    (CODE)
                                   1209 	.area GSINIT  (CODE)
                                   1210 	.area GSFINAL (CODE)
                                   1211 	.area GSINIT  (CODE)
                                   1212 	.globl __sdcc_gsinit_startup
                                   1213 	.globl __sdcc_program_startup
                                   1214 	.globl __start__stack
                                   1215 	.globl __mcs51_genXINIT
                                   1216 	.globl __mcs51_genXRAMCLEAR
                                   1217 	.globl __mcs51_genRAMCLEAR
                                   1218 	.area GSFINAL (CODE)
      004A44 02 00 6E         [24] 1219 	ljmp	__sdcc_program_startup
                                   1220 ;--------------------------------------------------------
                                   1221 ; Home
                                   1222 ;--------------------------------------------------------
                                   1223 	.area HOME    (CODE)
                                   1224 	.area HOME    (CODE)
      00006E                       1225 __sdcc_program_startup:
      00006E 02 01 BF         [24] 1226 	ljmp	_main
                                   1227 ;	return from main will return to caller
                                   1228 ;--------------------------------------------------------
                                   1229 ; code
                                   1230 ;--------------------------------------------------------
                                   1231 	.area HOME    (CODE)
                                   1232 ;------------------------------------------------------------
                                   1233 ;Allocation info for local variables in function 'fade'
                                   1234 ;------------------------------------------------------------
                                   1235 ;l                         Allocated to registers r6 r7 
                                   1236 ;i                         Allocated to stack - sp -3
                                   1237 ;a                         Allocated to stack - sp -1
                                   1238 ;k                         Allocated to registers 
                                   1239 ;j                         Allocated to registers r2 r3 
                                   1240 ;sloc0                     Allocated to stack - sp +7
                                   1241 ;------------------------------------------------------------
                                   1242 ;	../../../platform/cc2530dk/./contiki-main.c:74: fade(int l) CC_NON_BANKED
                                   1243 ;	-----------------------------------------
                                   1244 ;	 function fade
                                   1245 ;	-----------------------------------------
      000071                       1246 _fade:
                           000007  1247 	ar7 = 0x07
                           000006  1248 	ar6 = 0x06
                           000005  1249 	ar5 = 0x05
                           000004  1250 	ar4 = 0x04
                           000003  1251 	ar3 = 0x03
                           000002  1252 	ar2 = 0x02
                           000001  1253 	ar1 = 0x01
                           000000  1254 	ar0 = 0x00
      000071 E5 81            [12] 1255 	mov	a,sp
      000073 24 04            [12] 1256 	add	a,#0x04
      000075 F5 81            [12] 1257 	mov	sp,a
      000077 AE 82            [24] 1258 	mov	r6,dpl
      000079 AF 83            [24] 1259 	mov	r7,dph
                                   1260 ;	../../../platform/cc2530dk/./contiki-main.c:78: for(k = 0; k < 400; ++k) {
      00007B 7C 00            [12] 1261 	mov	r4,#0x00
      00007D 7D 00            [12] 1262 	mov	r5,#0x00
      00007F                       1263 00110$:
                                   1264 ;	../../../platform/cc2530dk/./contiki-main.c:79: j = k > 200 ? 400 - k : k;
      00007F C3               [12] 1265 	clr	c
      000080 74 C8            [12] 1266 	mov	a,#0xc8
      000082 9C               [12] 1267 	subb	a,r4
      000083 74 80            [12] 1268 	mov	a,#(0x00 ^ 0x80)
      000085 8D F0            [24] 1269 	mov	b,r5
      000087 63 F0 80         [24] 1270 	xrl	b,#0x80
      00008A 95 F0            [12] 1271 	subb	a,b
      00008C 50 0B            [24] 1272 	jnc	00114$
      00008E 74 90            [12] 1273 	mov	a,#0x90
      000090 C3               [12] 1274 	clr	c
      000091 9C               [12] 1275 	subb	a,r4
      000092 FA               [12] 1276 	mov	r2,a
      000093 74 01            [12] 1277 	mov	a,#0x01
      000095 9D               [12] 1278 	subb	a,r5
      000096 FB               [12] 1279 	mov	r3,a
      000097 80 04            [24] 1280 	sjmp	00115$
      000099                       1281 00114$:
      000099 8C 02            [24] 1282 	mov	ar2,r4
      00009B 8D 03            [24] 1283 	mov	ar3,r5
      00009D                       1284 00115$:
      00009D C0 04            [24] 1285 	push	ar4
      00009F C0 05            [24] 1286 	push	ar5
                                   1287 ;	../../../platform/cc2530dk/./contiki-main.c:81: leds_on(l);
      0000A1 8E 05            [24] 1288 	mov	ar5,r6
      0000A3 8D 82            [24] 1289 	mov	dpl,r5
      0000A5 C0 07            [24] 1290 	push	ar7
      0000A7 C0 06            [24] 1291 	push	ar6
      0000A9 C0 05            [24] 1292 	push	ar5
      0000AB C0 04            [24] 1293 	push	ar4
      0000AD C0 03            [24] 1294 	push	ar3
      0000AF C0 02            [24] 1295 	push	ar2
      0000B1 78 B2            [12] 1296 	mov	r0,#_leds_on
      0000B3 79 86            [12] 1297 	mov	r1,#(_leds_on >> 8)
      0000B5 7A 04            [12] 1298 	mov	r2,#(_leds_on >> 16)
      0000B7 12 05 65         [24] 1299 	lcall	__sdcc_banked_call
      0000BA D0 02            [24] 1300 	pop	ar2
      0000BC D0 03            [24] 1301 	pop	ar3
      0000BE D0 04            [24] 1302 	pop	ar4
      0000C0 D0 05            [24] 1303 	pop	ar5
      0000C2 D0 06            [24] 1304 	pop	ar6
      0000C4 D0 07            [24] 1305 	pop	ar7
                                   1306 ;	../../../platform/cc2530dk/./contiki-main.c:82: for(i = 0; i < j; ++i) {
      0000C6 E5 81            [12] 1307 	mov	a,sp
      0000C8 24 FB            [12] 1308 	add	a,#0xfb
      0000CA F8               [12] 1309 	mov	r0,a
      0000CB E4               [12] 1310 	clr	a
      0000CC F6               [12] 1311 	mov	@r0,a
      0000CD 08               [12] 1312 	inc	r0
      0000CE F6               [12] 1313 	mov	@r0,a
                                   1314 ;	../../../platform/cc2530dk/./contiki-main.c:78: for(k = 0; k < 400; ++k) {
      0000CF D0 05            [24] 1315 	pop	ar5
      0000D1 D0 04            [24] 1316 	pop	ar4
                                   1317 ;	../../../platform/cc2530dk/./contiki-main.c:82: for(i = 0; i < j; ++i) {
      0000D3                       1318 00105$:
      0000D3 E5 81            [12] 1319 	mov	a,sp
      0000D5 24 FD            [12] 1320 	add	a,#0xfd
      0000D7 F8               [12] 1321 	mov	r0,a
      0000D8 C3               [12] 1322 	clr	c
      0000D9 E6               [12] 1323 	mov	a,@r0
      0000DA 9A               [12] 1324 	subb	a,r2
      0000DB 08               [12] 1325 	inc	r0
      0000DC E6               [12] 1326 	mov	a,@r0
      0000DD 64 80            [12] 1327 	xrl	a,#0x80
      0000DF 8B F0            [24] 1328 	mov	b,r3
      0000E1 63 F0 80         [24] 1329 	xrl	b,#0x80
      0000E4 95 F0            [12] 1330 	subb	a,b
      0000E6 50 1D            [24] 1331 	jnc	00101$
                                   1332 ;	../../../platform/cc2530dk/./contiki-main.c:83: a = i;
      0000E8 E5 81            [12] 1333 	mov	a,sp
      0000EA 24 FD            [12] 1334 	add	a,#0xfd
      0000EC F8               [12] 1335 	mov	r0,a
      0000ED A9 81            [24] 1336 	mov	r1,sp
      0000EF 19               [12] 1337 	dec	r1
      0000F0 E6               [12] 1338 	mov	a,@r0
      0000F1 F7               [12] 1339 	mov	@r1,a
      0000F2 08               [12] 1340 	inc	r0
      0000F3 09               [12] 1341 	inc	r1
      0000F4 E6               [12] 1342 	mov	a,@r0
      0000F5 F7               [12] 1343 	mov	@r1,a
                                   1344 ;	../../../platform/cc2530dk/./contiki-main.c:82: for(i = 0; i < j; ++i) {
      0000F6 E5 81            [12] 1345 	mov	a,sp
      0000F8 24 FD            [12] 1346 	add	a,#0xfd
      0000FA F8               [12] 1347 	mov	r0,a
      0000FB 74 01            [12] 1348 	mov	a,#0x01
      0000FD 26               [12] 1349 	add	a,@r0
      0000FE F6               [12] 1350 	mov	@r0,a
      0000FF E4               [12] 1351 	clr	a
      000100 08               [12] 1352 	inc	r0
      000101 36               [12] 1353 	addc	a,@r0
      000102 F6               [12] 1354 	mov	@r0,a
      000103 80 CE            [24] 1355 	sjmp	00105$
      000105                       1356 00101$:
                                   1357 ;	../../../platform/cc2530dk/./contiki-main.c:85: leds_off(l);
      000105 C0 04            [24] 1358 	push	ar4
      000107 C0 05            [24] 1359 	push	ar5
      000109 8E 05            [24] 1360 	mov	ar5,r6
      00010B 8D 82            [24] 1361 	mov	dpl,r5
      00010D C0 07            [24] 1362 	push	ar7
      00010F C0 06            [24] 1363 	push	ar6
      000111 C0 05            [24] 1364 	push	ar5
      000113 C0 04            [24] 1365 	push	ar4
      000115 C0 03            [24] 1366 	push	ar3
      000117 C0 02            [24] 1367 	push	ar2
      000119 78 D2            [12] 1368 	mov	r0,#_leds_off
      00011B 79 86            [12] 1369 	mov	r1,#(_leds_off >> 8)
      00011D 7A 04            [12] 1370 	mov	r2,#(_leds_off >> 16)
      00011F 12 05 65         [24] 1371 	lcall	__sdcc_banked_call
      000122 D0 02            [24] 1372 	pop	ar2
      000124 D0 03            [24] 1373 	pop	ar3
      000126 D0 04            [24] 1374 	pop	ar4
      000128 D0 05            [24] 1375 	pop	ar5
      00012A D0 06            [24] 1376 	pop	ar6
      00012C D0 07            [24] 1377 	pop	ar7
                                   1378 ;	../../../platform/cc2530dk/./contiki-main.c:86: for(i = 0; i < 200 - j; ++i) {
      00012E E5 81            [12] 1379 	mov	a,sp
      000130 24 FB            [12] 1380 	add	a,#0xfb
      000132 F8               [12] 1381 	mov	r0,a
      000133 E4               [12] 1382 	clr	a
      000134 F6               [12] 1383 	mov	@r0,a
      000135 08               [12] 1384 	inc	r0
      000136 F6               [12] 1385 	mov	@r0,a
      000137 74 C8            [12] 1386 	mov	a,#0xc8
      000139 C3               [12] 1387 	clr	c
      00013A 9A               [12] 1388 	subb	a,r2
      00013B FA               [12] 1389 	mov	r2,a
      00013C E4               [12] 1390 	clr	a
      00013D 9B               [12] 1391 	subb	a,r3
      00013E FB               [12] 1392 	mov	r3,a
                                   1393 ;	../../../platform/cc2530dk/./contiki-main.c:78: for(k = 0; k < 400; ++k) {
      00013F D0 05            [24] 1394 	pop	ar5
      000141 D0 04            [24] 1395 	pop	ar4
                                   1396 ;	../../../platform/cc2530dk/./contiki-main.c:86: for(i = 0; i < 200 - j; ++i) {
      000143                       1397 00108$:
      000143 E5 81            [12] 1398 	mov	a,sp
      000145 24 FD            [12] 1399 	add	a,#0xfd
      000147 F8               [12] 1400 	mov	r0,a
      000148 C3               [12] 1401 	clr	c
      000149 E6               [12] 1402 	mov	a,@r0
      00014A 9A               [12] 1403 	subb	a,r2
      00014B 08               [12] 1404 	inc	r0
      00014C E6               [12] 1405 	mov	a,@r0
      00014D 64 80            [12] 1406 	xrl	a,#0x80
      00014F 8B F0            [24] 1407 	mov	b,r3
      000151 63 F0 80         [24] 1408 	xrl	b,#0x80
      000154 95 F0            [12] 1409 	subb	a,b
      000156 50 1D            [24] 1410 	jnc	00111$
                                   1411 ;	../../../platform/cc2530dk/./contiki-main.c:87: a = i;
      000158 E5 81            [12] 1412 	mov	a,sp
      00015A 24 FD            [12] 1413 	add	a,#0xfd
      00015C F8               [12] 1414 	mov	r0,a
      00015D A9 81            [24] 1415 	mov	r1,sp
      00015F 19               [12] 1416 	dec	r1
      000160 E6               [12] 1417 	mov	a,@r0
      000161 F7               [12] 1418 	mov	@r1,a
      000162 08               [12] 1419 	inc	r0
      000163 09               [12] 1420 	inc	r1
      000164 E6               [12] 1421 	mov	a,@r0
      000165 F7               [12] 1422 	mov	@r1,a
                                   1423 ;	../../../platform/cc2530dk/./contiki-main.c:86: for(i = 0; i < 200 - j; ++i) {
      000166 E5 81            [12] 1424 	mov	a,sp
      000168 24 FD            [12] 1425 	add	a,#0xfd
      00016A F8               [12] 1426 	mov	r0,a
      00016B 74 01            [12] 1427 	mov	a,#0x01
      00016D 26               [12] 1428 	add	a,@r0
      00016E F6               [12] 1429 	mov	@r0,a
      00016F E4               [12] 1430 	clr	a
      000170 08               [12] 1431 	inc	r0
      000171 36               [12] 1432 	addc	a,@r0
      000172 F6               [12] 1433 	mov	@r0,a
      000173 80 CE            [24] 1434 	sjmp	00108$
      000175                       1435 00111$:
                                   1436 ;	../../../platform/cc2530dk/./contiki-main.c:78: for(k = 0; k < 400; ++k) {
      000175 0C               [12] 1437 	inc	r4
      000176 BC 00 01         [24] 1438 	cjne	r4,#0x00,00144$
      000179 0D               [12] 1439 	inc	r5
      00017A                       1440 00144$:
      00017A C3               [12] 1441 	clr	c
      00017B EC               [12] 1442 	mov	a,r4
      00017C 94 90            [12] 1443 	subb	a,#0x90
      00017E ED               [12] 1444 	mov	a,r5
      00017F 64 80            [12] 1445 	xrl	a,#0x80
      000181 94 81            [12] 1446 	subb	a,#0x81
      000183 50 03            [24] 1447 	jnc	00145$
      000185 02 00 7F         [24] 1448 	ljmp	00110$
      000188                       1449 00145$:
                                   1450 ;	../../../platform/cc2530dk/./contiki-main.c:90: }
      000188 E5 81            [12] 1451 	mov	a,sp
      00018A 24 FC            [12] 1452 	add	a,#0xfc
      00018C F5 81            [12] 1453 	mov	sp,a
      00018E 22               [24] 1454 	ret
                                   1455 ;------------------------------------------------------------
                                   1456 ;Allocation info for local variables in function 'set_rime_addr'
                                   1457 ;------------------------------------------------------------
                                   1458 ;i                         Allocated to registers 
                                   1459 ;macp                      Allocated to registers 
                                   1460 ;------------------------------------------------------------
                                   1461 ;	../../../platform/cc2530dk/./contiki-main.c:93: set_rime_addr(void) CC_NON_BANKED
                                   1462 ;	-----------------------------------------
                                   1463 ;	 function set_rime_addr
                                   1464 ;	-----------------------------------------
      00018F                       1465 _set_rime_addr:
                                   1466 ;	../../../platform/cc2530dk/./contiki-main.c:98: __xdata unsigned char *macp = &X_IEEE_ADDR;
      00018F 7E 0C            [12] 1467 	mov	r6,#_X_IEEE_ADDR
      000191 7F 78            [12] 1468 	mov	r7,#(_X_IEEE_ADDR >> 8)
                                   1469 ;	../../../platform/cc2530dk/./contiki-main.c:128: for(i = (RIMEADDR_SIZE - 1); i >= 0; --i) {
      000193 7D 07            [12] 1470 	mov	r5,#0x07
      000195                       1471 00102$:
                                   1472 ;	../../../platform/cc2530dk/./contiki-main.c:129: rimeaddr_node_addr.u8[i] = *macp;
      000195 ED               [12] 1473 	mov	a,r5
      000196 24 F6            [12] 1474 	add	a,#_rimeaddr_node_addr
      000198 FB               [12] 1475 	mov	r3,a
      000199 E4               [12] 1476 	clr	a
      00019A 34 15            [12] 1477 	addc	a,#(_rimeaddr_node_addr >> 8)
      00019C FC               [12] 1478 	mov	r4,a
      00019D 8E 82            [24] 1479 	mov	dpl,r6
      00019F 8F 83            [24] 1480 	mov	dph,r7
      0001A1 E0               [24] 1481 	movx	a,@dptr
      0001A2 FA               [12] 1482 	mov	r2,a
      0001A3 A3               [24] 1483 	inc	dptr
      0001A4 AE 82            [24] 1484 	mov	r6,dpl
      0001A6 AF 83            [24] 1485 	mov	r7,dph
      0001A8 8B 82            [24] 1486 	mov	dpl,r3
      0001AA 8C 83            [24] 1487 	mov	dph,r4
      0001AC EA               [12] 1488 	mov	a,r2
      0001AD F0               [24] 1489 	movx	@dptr,a
                                   1490 ;	../../../platform/cc2530dk/./contiki-main.c:130: macp++;
                                   1491 ;	../../../platform/cc2530dk/./contiki-main.c:128: for(i = (RIMEADDR_SIZE - 1); i >= 0; --i) {
      0001AE 1D               [12] 1492 	dec	r5
      0001AF ED               [12] 1493 	mov	a,r5
      0001B0 30 E7 E2         [24] 1494 	jnb	acc.7,00102$
                                   1495 ;	../../../platform/cc2530dk/./contiki-main.c:150: cc2530_rf_set_addr(IEEE802154_PANID);
      0001B3 90 54 49         [24] 1496 	mov	dptr,#0x5449
      0001B6 78 2E            [12] 1497 	mov	r0,#_cc2530_rf_set_addr
      0001B8 79 AB            [12] 1498 	mov	r1,#(_cc2530_rf_set_addr >> 8)
      0001BA 7A 03            [12] 1499 	mov	r2,#(_cc2530_rf_set_addr >> 16)
                                   1500 ;	../../../platform/cc2530dk/./contiki-main.c:151: return;
                                   1501 ;	../../../platform/cc2530dk/./contiki-main.c:152: }
      0001BC 02 05 65         [24] 1502 	ljmp	__sdcc_banked_call
                                   1503 ;------------------------------------------------------------
                                   1504 ;Allocation info for local variables in function 'main'
                                   1505 ;------------------------------------------------------------
                                   1506 ;r                         Allocated to registers r6 
                                   1507 ;------------------------------------------------------------
                                   1508 ;	../../../platform/cc2530dk/./contiki-main.c:155: main(void) CC_NON_BANKED
                                   1509 ;	-----------------------------------------
                                   1510 ;	 function main
                                   1511 ;	-----------------------------------------
      0001BF                       1512 _main:
                                   1513 ;	../../../platform/cc2530dk/./contiki-main.c:158: clock_init();
      0001BF 78 A0            [12] 1514 	mov	r0,#_clock_init
      0001C1 79 3D            [12] 1515 	mov	r1,#(_clock_init >> 8)
      0001C3 7A 00            [12] 1516 	mov	r2,#(_clock_init >> 16)
      0001C5 12 05 65         [24] 1517 	lcall	__sdcc_banked_call
                                   1518 ;	../../../platform/cc2530dk/./contiki-main.c:159: soc_init();
      0001C8 78 9B            [12] 1519 	mov	r0,#_soc_init
      0001CA 79 E3            [12] 1520 	mov	r1,#(_soc_init >> 8)
      0001CC 7A 03            [12] 1521 	mov	r2,#(_soc_init >> 16)
      0001CE 12 05 65         [24] 1522 	lcall	__sdcc_banked_call
                                   1523 ;	../../../platform/cc2530dk/./contiki-main.c:161: rtimer_init();
      0001D1 78 3A            [12] 1524 	mov	r0,#_rtimer_init
      0001D3 79 87            [12] 1525 	mov	r1,#(_rtimer_init >> 8)
      0001D5 7A 04            [12] 1526 	mov	r2,#(_rtimer_init >> 16)
      0001D7 12 05 65         [24] 1527 	lcall	__sdcc_banked_call
                                   1528 ;	../../../platform/cc2530dk/./contiki-main.c:170: process_init();
      0001DA 78 60            [12] 1529 	mov	r0,#_process_init
      0001DC 79 85            [12] 1530 	mov	r1,#(_process_init >> 8)
      0001DE 7A 03            [12] 1531 	mov	r2,#(_process_init >> 16)
      0001E0 12 05 65         [24] 1532 	lcall	__sdcc_banked_call
                                   1533 ;	../../../platform/cc2530dk/./contiki-main.c:177: io_arch_init();
      0001E3 78 D4            [12] 1534 	mov	r0,#_uart1_init
      0001E5 79 B0            [12] 1535 	mov	r1,#(_uart1_init >> 8)
      0001E7 7A 04            [12] 1536 	mov	r2,#(_uart1_init >> 16)
      0001E9 12 05 65         [24] 1537 	lcall	__sdcc_banked_call
                                   1538 ;	../../../platform/cc2530dk/./contiki-main.c:181: io_arch_set_input(serial_line_input_byte);
      0001EC 90 8F 05         [24] 1539 	mov	dptr,#_serial_line_input_byte
      0001EF 75 F0 04         [24] 1540 	mov	b,#(_serial_line_input_byte >> 16)
      0001F2 78 52            [12] 1541 	mov	r0,#_uart1_set_input
      0001F4 79 05            [12] 1542 	mov	r1,#(_uart1_set_input >> 8)
      0001F6 7A 00            [12] 1543 	mov	r2,#(_uart1_set_input >> 16)
      0001F8 12 05 65         [24] 1544 	lcall	__sdcc_banked_call
                                   1545 ;	../../../platform/cc2530dk/./contiki-main.c:182: serial_line_init();
      0001FB 78 2B            [12] 1546 	mov	r0,#_serial_line_init
      0001FD 79 91            [12] 1547 	mov	r1,#(_serial_line_init >> 8)
      0001FF 7A 04            [12] 1548 	mov	r2,#(_serial_line_init >> 16)
      000201 12 05 65         [24] 1549 	lcall	__sdcc_banked_call
                                   1550 ;	../../../platform/cc2530dk/./contiki-main.c:189: OLED_Init();	//初始化OLED
      000204 78 92            [12] 1551 	mov	r0,#_OLED_Init
      000206 79 B3            [12] 1552 	mov	r1,#(_OLED_Init >> 8)
      000208 7A 02            [12] 1553 	mov	r2,#(_OLED_Init >> 16)
      00020A 12 05 65         [24] 1554 	lcall	__sdcc_banked_call
                                   1555 ;	../../../platform/cc2530dk/./contiki-main.c:242: printf("this is print\r\n");
      00020D 74 A2            [12] 1556 	mov	a,#___str_0
      00020F C0 E0            [24] 1557 	push	acc
      000211 74 73            [12] 1558 	mov	a,#(___str_0 >> 8)
      000213 C0 E0            [24] 1559 	push	acc
      000215 74 80            [12] 1560 	mov	a,#0x80
      000217 C0 E0            [24] 1561 	push	acc
      000219 78 21            [12] 1562 	mov	r0,#_printf
      00021B 79 50            [12] 1563 	mov	r1,#(_printf >> 8)
      00021D 7A 00            [12] 1564 	mov	r2,#(_printf >> 16)
      00021F 12 05 65         [24] 1565 	lcall	__sdcc_banked_call
      000222 15 81            [12] 1566 	dec	sp
      000224 15 81            [12] 1567 	dec	sp
      000226 15 81            [12] 1568 	dec	sp
                                   1569 ;	../../../platform/cc2530dk/./contiki-main.c:244: putstring(CONTIKI_VERSION_STRING "\r\n");
      000228 90 73 B2         [24] 1570 	mov	dptr,#___str_1
      00022B 75 F0 80         [24] 1571 	mov	b,#0x80
      00022E 78 6E            [12] 1572 	mov	r0,#_putstring
      000230 79 91            [12] 1573 	mov	r1,#(_putstring >> 8)
      000232 7A 04            [12] 1574 	mov	r2,#(_putstring >> 16)
      000234 12 05 65         [24] 1575 	lcall	__sdcc_banked_call
                                   1576 ;	../../../platform/cc2530dk/./contiki-main.c:245: putstring(MODEL_STRING);
      000237 90 73 C0         [24] 1577 	mov	dptr,#___str_2
      00023A 75 F0 80         [24] 1578 	mov	b,#0x80
      00023D 78 6E            [12] 1579 	mov	r0,#_putstring
      00023F 79 91            [12] 1580 	mov	r1,#(_putstring >> 8)
      000241 7A 04            [12] 1581 	mov	r2,#(_putstring >> 16)
      000243 12 05 65         [24] 1582 	lcall	__sdcc_banked_call
                                   1583 ;	../../../platform/cc2530dk/./contiki-main.c:246: switch(CHIPID) {
      000246 90 62 4A         [24] 1584 	mov	dptr,#_CHIPID
      000249 E0               [24] 1585 	movx	a,@dptr
      00024A FF               [12] 1586 	mov	r7,a
      00024B BF 8D 02         [24] 1587 	cjne	r7,#0x8d,00169$
      00024E 80 42            [24] 1588 	sjmp	00104$
      000250                       1589 00169$:
      000250 BF 95 02         [24] 1590 	cjne	r7,#0x95,00170$
      000253 80 2C            [24] 1591 	sjmp	00103$
      000255                       1592 00170$:
      000255 BF A5 02         [24] 1593 	cjne	r7,#0xa5,00171$
      000258 80 05            [24] 1594 	sjmp	00101$
      00025A                       1595 00171$:
                                   1596 ;	../../../platform/cc2530dk/./contiki-main.c:247: case 0xA5:
      00025A BF B5 44         [24] 1597 	cjne	r7,#0xb5,00105$
      00025D 80 11            [24] 1598 	sjmp	00102$
      00025F                       1599 00101$:
                                   1600 ;	../../../platform/cc2530dk/./contiki-main.c:248: putstring("cc2530");
      00025F 90 73 D1         [24] 1601 	mov	dptr,#___str_3
      000262 75 F0 80         [24] 1602 	mov	b,#0x80
      000265 78 6E            [12] 1603 	mov	r0,#_putstring
      000267 79 91            [12] 1604 	mov	r1,#(_putstring >> 8)
      000269 7A 04            [12] 1605 	mov	r2,#(_putstring >> 16)
      00026B 12 05 65         [24] 1606 	lcall	__sdcc_banked_call
                                   1607 ;	../../../platform/cc2530dk/./contiki-main.c:249: break;
                                   1608 ;	../../../platform/cc2530dk/./contiki-main.c:250: case 0xB5:
      00026E 80 31            [24] 1609 	sjmp	00105$
      000270                       1610 00102$:
                                   1611 ;	../../../platform/cc2530dk/./contiki-main.c:251: putstring("cc2531");
      000270 90 73 D8         [24] 1612 	mov	dptr,#___str_4
      000273 75 F0 80         [24] 1613 	mov	b,#0x80
      000276 78 6E            [12] 1614 	mov	r0,#_putstring
      000278 79 91            [12] 1615 	mov	r1,#(_putstring >> 8)
      00027A 7A 04            [12] 1616 	mov	r2,#(_putstring >> 16)
      00027C 12 05 65         [24] 1617 	lcall	__sdcc_banked_call
                                   1618 ;	../../../platform/cc2530dk/./contiki-main.c:252: break;
                                   1619 ;	../../../platform/cc2530dk/./contiki-main.c:253: case 0x95:
      00027F 80 20            [24] 1620 	sjmp	00105$
      000281                       1621 00103$:
                                   1622 ;	../../../platform/cc2530dk/./contiki-main.c:254: putstring("cc2533");
      000281 90 73 DF         [24] 1623 	mov	dptr,#___str_5
      000284 75 F0 80         [24] 1624 	mov	b,#0x80
      000287 78 6E            [12] 1625 	mov	r0,#_putstring
      000289 79 91            [12] 1626 	mov	r1,#(_putstring >> 8)
      00028B 7A 04            [12] 1627 	mov	r2,#(_putstring >> 16)
      00028D 12 05 65         [24] 1628 	lcall	__sdcc_banked_call
                                   1629 ;	../../../platform/cc2530dk/./contiki-main.c:255: break;
                                   1630 ;	../../../platform/cc2530dk/./contiki-main.c:256: case 0x8D:
      000290 80 0F            [24] 1631 	sjmp	00105$
      000292                       1632 00104$:
                                   1633 ;	../../../platform/cc2530dk/./contiki-main.c:257: putstring("cc2540");
      000292 90 73 E6         [24] 1634 	mov	dptr,#___str_6
      000295 75 F0 80         [24] 1635 	mov	b,#0x80
      000298 78 6E            [12] 1636 	mov	r0,#_putstring
      00029A 79 91            [12] 1637 	mov	r1,#(_putstring >> 8)
      00029C 7A 04            [12] 1638 	mov	r2,#(_putstring >> 16)
      00029E 12 05 65         [24] 1639 	lcall	__sdcc_banked_call
                                   1640 ;	../../../platform/cc2530dk/./contiki-main.c:259: }
      0002A1                       1641 00105$:
                                   1642 ;	../../../platform/cc2530dk/./contiki-main.c:261: putstring("-" CC2530_FLAVOR_STRING ", ");
      0002A1 90 73 ED         [24] 1643 	mov	dptr,#___str_7
      0002A4 75 F0 80         [24] 1644 	mov	b,#0x80
      0002A7 78 6E            [12] 1645 	mov	r0,#_putstring
      0002A9 79 91            [12] 1646 	mov	r1,#(_putstring >> 8)
      0002AB 7A 04            [12] 1647 	mov	r2,#(_putstring >> 16)
      0002AD 12 05 65         [24] 1648 	lcall	__sdcc_banked_call
                                   1649 ;	../../../platform/cc2530dk/./contiki-main.c:262: puthex(CHIPINFO1 + 1);
      0002B0 90 62 77         [24] 1650 	mov	dptr,#_CHIPINFO1
      0002B3 E0               [24] 1651 	movx	a,@dptr
      0002B4 FF               [12] 1652 	mov	r7,a
      0002B5 0F               [12] 1653 	inc	r7
      0002B6 8F 82            [24] 1654 	mov	dpl,r7
      0002B8 78 AA            [12] 1655 	mov	r0,#_puthex
      0002BA 79 91            [12] 1656 	mov	r1,#(_puthex >> 8)
      0002BC 7A 04            [12] 1657 	mov	r2,#(_puthex >> 16)
      0002BE 12 05 65         [24] 1658 	lcall	__sdcc_banked_call
                                   1659 ;	../../../platform/cc2530dk/./contiki-main.c:263: putstring("KB SRAM\r\n");
      0002C1 90 73 F5         [24] 1660 	mov	dptr,#___str_8
      0002C4 75 F0 80         [24] 1661 	mov	b,#0x80
      0002C7 78 6E            [12] 1662 	mov	r0,#_putstring
      0002C9 79 91            [12] 1663 	mov	r1,#(_putstring >> 8)
      0002CB 7A 04            [12] 1664 	mov	r2,#(_putstring >> 16)
      0002CD 12 05 65         [24] 1665 	lcall	__sdcc_banked_call
                                   1666 ;	../../../platform/cc2530dk/./contiki-main.c:300: watchdog_init();
      0002D0 78 10            [12] 1667 	mov	r0,#_watchdog_init
      0002D2 79 87            [12] 1668 	mov	r1,#(_watchdog_init >> 8)
      0002D4 7A 04            [12] 1669 	mov	r2,#(_watchdog_init >> 16)
      0002D6 12 05 65         [24] 1670 	lcall	__sdcc_banked_call
                                   1671 ;	../../../platform/cc2530dk/./contiki-main.c:303: random_init(0);
      0002D9 90 00 00         [24] 1672 	mov	dptr,#0x0000
      0002DC 78 15            [12] 1673 	mov	r0,#_random_init
      0002DE 79 B1            [12] 1674 	mov	r1,#(_random_init >> 8)
      0002E0 7A 04            [12] 1675 	mov	r2,#(_random_init >> 16)
      0002E2 12 05 65         [24] 1676 	lcall	__sdcc_banked_call
                                   1677 ;	../../../platform/cc2530dk/./contiki-main.c:306: process_start(&etimer_process, NULL);
      0002E5 E4               [12] 1678 	clr	a
      0002E6 C0 E0            [24] 1679 	push	acc
      0002E8 C0 E0            [24] 1680 	push	acc
      0002EA C0 E0            [24] 1681 	push	acc
      0002EC 90 18 6D         [24] 1682 	mov	dptr,#_etimer_process
      0002EF 75 F0 00         [24] 1683 	mov	b,#0x00
      0002F2 78 0C            [12] 1684 	mov	r0,#_process_start
      0002F4 79 80            [12] 1685 	mov	r1,#(_process_start >> 8)
      0002F6 7A 03            [12] 1686 	mov	r2,#(_process_start >> 16)
      0002F8 12 05 65         [24] 1687 	lcall	__sdcc_banked_call
      0002FB 15 81            [12] 1688 	dec	sp
      0002FD 15 81            [12] 1689 	dec	sp
      0002FF 15 81            [12] 1690 	dec	sp
                                   1691 ;	../../../platform/cc2530dk/./contiki-main.c:307: ctimer_init();
      000301 78 EC            [12] 1692 	mov	r0,#_ctimer_init
      000303 79 D2            [12] 1693 	mov	r1,#(_ctimer_init >> 8)
      000305 7A 03            [12] 1694 	mov	r2,#(_ctimer_init >> 16)
      000307 12 05 65         [24] 1695 	lcall	__sdcc_banked_call
                                   1696 ;	../../../platform/cc2530dk/./contiki-main.c:310: netstack_init();
      00030A 78 7C            [12] 1697 	mov	r0,#_netstack_init
      00030C 79 92            [12] 1698 	mov	r1,#(_netstack_init >> 8)
      00030E 7A 04            [12] 1699 	mov	r2,#(_netstack_init >> 16)
      000310 12 05 65         [24] 1700 	lcall	__sdcc_banked_call
                                   1701 ;	../../../platform/cc2530dk/./contiki-main.c:311: set_rime_addr();
      000313 12 01 8F         [24] 1702 	lcall	_set_rime_addr
                                   1703 ;	../../../platform/cc2530dk/./contiki-main.c:315: memcpy(&uip_lladdr.addr, &rimeaddr_node_addr, sizeof(uip_lladdr.addr));
      000316 74 08            [12] 1704 	mov	a,#0x08
      000318 C0 E0            [24] 1705 	push	acc
      00031A E4               [12] 1706 	clr	a
      00031B C0 E0            [24] 1707 	push	acc
      00031D 74 F6            [12] 1708 	mov	a,#_rimeaddr_node_addr
      00031F C0 E0            [24] 1709 	push	acc
      000321 74 15            [12] 1710 	mov	a,#(_rimeaddr_node_addr >> 8)
      000323 C0 E0            [24] 1711 	push	acc
      000325 E4               [12] 1712 	clr	a
      000326 C0 E0            [24] 1713 	push	acc
      000328 90 05 F3         [24] 1714 	mov	dptr,#_uip_lladdr
      00032B 75 F0 00         [24] 1715 	mov	b,#0x00
      00032E 78 C7            [12] 1716 	mov	r0,#___memcpy
      000330 79 4E            [12] 1717 	mov	r1,#(___memcpy >> 8)
      000332 7A 00            [12] 1718 	mov	r2,#(___memcpy >> 16)
      000334 12 05 65         [24] 1719 	lcall	__sdcc_banked_call
      000337 E5 81            [12] 1720 	mov	a,sp
      000339 24 FB            [12] 1721 	add	a,#0xfb
      00033B F5 81            [12] 1722 	mov	sp,a
                                   1723 ;	../../../platform/cc2530dk/./contiki-main.c:316: queuebuf_init();
      00033D 78 E0            [12] 1724 	mov	r0,#_queuebuf_init
      00033F 79 9B            [12] 1725 	mov	r1,#(_queuebuf_init >> 8)
      000341 7A 04            [12] 1726 	mov	r2,#(_queuebuf_init >> 16)
      000343 12 05 65         [24] 1727 	lcall	__sdcc_banked_call
                                   1728 ;	../../../platform/cc2530dk/./contiki-main.c:317: process_start(&tcpip_process, NULL);
      000346 E4               [12] 1729 	clr	a
      000347 C0 E0            [24] 1730 	push	acc
      000349 C0 E0            [24] 1731 	push	acc
      00034B C0 E0            [24] 1732 	push	acc
      00034D 90 18 5A         [24] 1733 	mov	dptr,#_tcpip_process
      000350 75 F0 00         [24] 1734 	mov	b,#0x00
      000353 78 0C            [12] 1735 	mov	r0,#_process_start
      000355 79 80            [12] 1736 	mov	r1,#(_process_start >> 8)
      000357 7A 03            [12] 1737 	mov	r2,#(_process_start >> 16)
      000359 12 05 65         [24] 1738 	lcall	__sdcc_banked_call
      00035C 15 81            [12] 1739 	dec	sp
      00035E 15 81            [12] 1740 	dec	sp
      000360 15 81            [12] 1741 	dec	sp
                                   1742 ;	../../../platform/cc2530dk/./contiki-main.c:321: process_start(&viztool_process, NULL);
      000362 E4               [12] 1743 	clr	a
      000363 C0 E0            [24] 1744 	push	acc
      000365 C0 E0            [24] 1745 	push	acc
      000367 C0 E0            [24] 1746 	push	acc
      000369 90 18 CE         [24] 1747 	mov	dptr,#_viztool_process
      00036C 75 F0 00         [24] 1748 	mov	b,#0x00
      00036F 78 0C            [12] 1749 	mov	r0,#_process_start
      000371 79 80            [12] 1750 	mov	r1,#(_process_start >> 8)
      000373 7A 03            [12] 1751 	mov	r2,#(_process_start >> 16)
      000375 12 05 65         [24] 1752 	lcall	__sdcc_banked_call
      000378 15 81            [12] 1753 	dec	sp
      00037A 15 81            [12] 1754 	dec	sp
      00037C 15 81            [12] 1755 	dec	sp
                                   1756 ;	../../../platform/cc2530dk/./contiki-main.c:324: energest_init();
      00037E 78 40            [12] 1757 	mov	r0,#_energest_init
      000380 79 BA            [12] 1758 	mov	r1,#(_energest_init >> 8)
      000382 7A 02            [12] 1759 	mov	r2,#(_energest_init >> 16)
      000384 12 05 65         [24] 1760 	lcall	__sdcc_banked_call
                                   1761 ;	../../../platform/cc2530dk/./contiki-main.c:327: autostart_start(autostart_processes);
      000387 90 74 0B         [24] 1762 	mov	dptr,#_autostart_processes
      00038A 75 F0 80         [24] 1763 	mov	b,#0x80
      00038D 78 4E            [12] 1764 	mov	r0,#_autostart_start
      00038F 79 9A            [12] 1765 	mov	r1,#(_autostart_start >> 8)
      000391 7A 04            [12] 1766 	mov	r2,#(_autostart_start >> 16)
      000393 12 05 65         [24] 1767 	lcall	__sdcc_banked_call
                                   1768 ;	../../../platform/cc2530dk/./contiki-main.c:329: watchdog_start();
      000396 78 16            [12] 1769 	mov	r0,#_watchdog_start
      000398 79 87            [12] 1770 	mov	r1,#(_watchdog_start >> 8)
      00039A 7A 04            [12] 1771 	mov	r2,#(_watchdog_start >> 16)
      00039C 12 05 65         [24] 1772 	lcall	__sdcc_banked_call
                                   1773 ;	../../../platform/cc2530dk/./contiki-main.c:333: do {
      00039F                       1774 00113$:
                                   1775 ;	../../../platform/cc2530dk/./contiki-main.c:335: watchdog_periodic();
      00039F 78 1C            [12] 1776 	mov	r0,#_watchdog_periodic
      0003A1 79 87            [12] 1777 	mov	r1,#(_watchdog_periodic >> 8)
      0003A3 7A 04            [12] 1778 	mov	r2,#(_watchdog_periodic >> 16)
      0003A5 12 05 65         [24] 1779 	lcall	__sdcc_banked_call
                                   1780 ;	../../../platform/cc2530dk/./contiki-main.c:338: if(sleep_flag) {
      0003A8 90 10 ED         [24] 1781 	mov	dptr,#_sleep_flag
      0003AB E0               [24] 1782 	movx	a,@dptr
      0003AC 60 57            [24] 1783 	jz	00112$
                                   1784 ;	../../../platform/cc2530dk/./contiki-main.c:339: if(etimer_pending() &&
      0003AE 78 F2            [12] 1785 	mov	r0,#_etimer_pending
      0003B0 79 91            [12] 1786 	mov	r1,#(_etimer_pending >> 8)
      0003B2 7A 03            [12] 1787 	mov	r2,#(_etimer_pending >> 16)
      0003B4 12 05 65         [24] 1788 	lcall	__sdcc_banked_call
      0003B7 E5 82            [12] 1789 	mov	a,dpl
      0003B9 85 83 F0         [24] 1790 	mov	b,dph
      0003BC 45 F0            [12] 1791 	orl	a,b
      0003BE 60 40            [24] 1792 	jz	00109$
                                   1793 ;	../../../platform/cc2530dk/./contiki-main.c:340: (etimer_next_expiration_time() - clock_time() - 1) > MAX_TICKS) {
      0003C0 78 10            [12] 1794 	mov	r0,#_etimer_next_expiration_time
      0003C2 79 92            [12] 1795 	mov	r1,#(_etimer_next_expiration_time >> 8)
      0003C4 7A 03            [12] 1796 	mov	r2,#(_etimer_next_expiration_time >> 16)
      0003C6 12 05 65         [24] 1797 	lcall	__sdcc_banked_call
      0003C9 AE 82            [24] 1798 	mov	r6,dpl
      0003CB AF 83            [24] 1799 	mov	r7,dph
      0003CD C0 07            [24] 1800 	push	ar7
      0003CF C0 06            [24] 1801 	push	ar6
      0003D1 78 85            [12] 1802 	mov	r0,#_clock_time
      0003D3 79 3D            [12] 1803 	mov	r1,#(_clock_time >> 8)
      0003D5 7A 00            [12] 1804 	mov	r2,#(_clock_time >> 16)
      0003D7 12 05 65         [24] 1805 	lcall	__sdcc_banked_call
      0003DA AC 82            [24] 1806 	mov	r4,dpl
      0003DC AD 83            [24] 1807 	mov	r5,dph
      0003DE D0 06            [24] 1808 	pop	ar6
      0003E0 D0 07            [24] 1809 	pop	ar7
      0003E2 EE               [12] 1810 	mov	a,r6
      0003E3 C3               [12] 1811 	clr	c
      0003E4 9C               [12] 1812 	subb	a,r4
      0003E5 FE               [12] 1813 	mov	r6,a
      0003E6 EF               [12] 1814 	mov	a,r7
      0003E7 9D               [12] 1815 	subb	a,r5
      0003E8 FF               [12] 1816 	mov	r7,a
      0003E9 1E               [12] 1817 	dec	r6
      0003EA BE FF 01         [24] 1818 	cjne	r6,#0xff,00175$
      0003ED 1F               [12] 1819 	dec	r7
      0003EE                       1820 00175$:
      0003EE C3               [12] 1821 	clr	c
      0003EF 74 FF            [12] 1822 	mov	a,#0xff
      0003F1 9E               [12] 1823 	subb	a,r6
      0003F2 74 7F            [12] 1824 	mov	a,#0x7f
      0003F4 9F               [12] 1825 	subb	a,r7
      0003F5 50 09            [24] 1826 	jnc	00109$
                                   1827 ;	../../../platform/cc2530dk/./contiki-main.c:341: etimer_request_poll();
      0003F7 78 58            [12] 1828 	mov	r0,#_etimer_request_poll
      0003F9 79 8F            [12] 1829 	mov	r1,#(_etimer_request_poll >> 8)
      0003FB 7A 03            [12] 1830 	mov	r2,#(_etimer_request_poll >> 16)
      0003FD 12 05 65         [24] 1831 	lcall	__sdcc_banked_call
      000400                       1832 00109$:
                                   1833 ;	../../../platform/cc2530dk/./contiki-main.c:343: sleep_flag = 0;
      000400 90 10 ED         [24] 1834 	mov	dptr,#_sleep_flag
      000403 E4               [12] 1835 	clr	a
      000404 F0               [24] 1836 	movx	@dptr,a
      000405                       1837 00112$:
                                   1838 ;	../../../platform/cc2530dk/./contiki-main.c:346: r = process_run();
      000405 78 84            [12] 1839 	mov	r0,#_process_run
      000407 79 87            [12] 1840 	mov	r1,#(_process_run >> 8)
      000409 7A 03            [12] 1841 	mov	r2,#(_process_run >> 16)
      00040B 12 05 65         [24] 1842 	lcall	__sdcc_banked_call
      00040E AE 82            [24] 1843 	mov	r6,dpl
      000410 AF 83            [24] 1844 	mov	r7,dph
                                   1845 ;	../../../platform/cc2530dk/./contiki-main.c:347: } while(r > 0);
      000412 EE               [12] 1846 	mov	a,r6
      000413 70 8A            [24] 1847 	jnz	00113$
                                   1848 ;	../../../platform/cc2530dk/./contiki-main.c:348: len = NETSTACK_RADIO.pending_packet();
      000415 90 7D 2F         [24] 1849 	mov	dptr,#(_cc2530_rf_driver + 0x0015)
      000418 E4               [12] 1850 	clr	a
      000419 93               [24] 1851 	movc	a,@a+dptr
      00041A FD               [12] 1852 	mov	r5,a
      00041B A3               [24] 1853 	inc	dptr
      00041C E4               [12] 1854 	clr	a
      00041D 93               [24] 1855 	movc	a,@a+dptr
      00041E FE               [12] 1856 	mov	r6,a
      00041F A3               [24] 1857 	inc	dptr
      000420 E4               [12] 1858 	clr	a
      000421 93               [24] 1859 	movc	a,@a+dptr
      000422 FF               [12] 1860 	mov	r7,a
      000423 C0 07            [24] 1861 	push	ar7
      000425 C0 06            [24] 1862 	push	ar6
      000427 C0 05            [24] 1863 	push	ar5
      000429 C0 05            [24] 1864 	push	ar5
      00042B C0 06            [24] 1865 	push	ar6
      00042D C0 07            [24] 1866 	push	ar7
      00042F D0 02            [24] 1867 	pop	ar2
      000431 D0 01            [24] 1868 	pop	ar1
      000433 D0 00            [24] 1869 	pop	ar0
      000435 12 05 65         [24] 1870 	lcall	__sdcc_banked_call
      000438 85 82 08         [24] 1871 	mov	_len,dpl
      00043B 85 83 09         [24] 1872 	mov	(_len + 1),dph
      00043E D0 05            [24] 1873 	pop	ar5
      000440 D0 06            [24] 1874 	pop	ar6
      000442 D0 07            [24] 1875 	pop	ar7
                                   1876 ;	../../../platform/cc2530dk/./contiki-main.c:349: if(len) {
      000444 E5 08            [12] 1877 	mov	a,_len
      000446 45 09            [12] 1878 	orl	a,(_len + 1)
      000448 70 03            [24] 1879 	jnz	00178$
      00044A 02 03 9F         [24] 1880 	ljmp	00113$
      00044D                       1881 00178$:
                                   1882 ;	../../../platform/cc2530dk/./contiki-main.c:350: packetbuf_clear();
      00044D 78 AA            [12] 1883 	mov	r0,#_packetbuf_clear
      00044F 79 A2            [12] 1884 	mov	r1,#(_packetbuf_clear >> 8)
      000451 7A 04            [12] 1885 	mov	r2,#(_packetbuf_clear >> 16)
      000453 12 05 65         [24] 1886 	lcall	__sdcc_banked_call
                                   1887 ;	../../../platform/cc2530dk/./contiki-main.c:351: len = NETSTACK_RADIO.read(packetbuf_dataptr(), PACKETBUF_SIZE);
      000456 90 7D 26         [24] 1888 	mov	dptr,#(_cc2530_rf_driver + 0x000c)
      000459 E4               [12] 1889 	clr	a
      00045A 93               [24] 1890 	movc	a,@a+dptr
      00045B FD               [12] 1891 	mov	r5,a
      00045C A3               [24] 1892 	inc	dptr
      00045D E4               [12] 1893 	clr	a
      00045E 93               [24] 1894 	movc	a,@a+dptr
      00045F FE               [12] 1895 	mov	r6,a
      000460 A3               [24] 1896 	inc	dptr
      000461 E4               [12] 1897 	clr	a
      000462 93               [24] 1898 	movc	a,@a+dptr
      000463 FF               [12] 1899 	mov	r7,a
      000464 C0 07            [24] 1900 	push	ar7
      000466 C0 06            [24] 1901 	push	ar6
      000468 C0 05            [24] 1902 	push	ar5
      00046A 78 EA            [12] 1903 	mov	r0,#_packetbuf_dataptr
      00046C 79 A6            [12] 1904 	mov	r1,#(_packetbuf_dataptr >> 8)
      00046E 7A 04            [12] 1905 	mov	r2,#(_packetbuf_dataptr >> 16)
      000470 12 05 65         [24] 1906 	lcall	__sdcc_banked_call
      000473 AA 82            [24] 1907 	mov	r2,dpl
      000475 AB 83            [24] 1908 	mov	r3,dph
      000477 AC F0            [24] 1909 	mov	r4,b
      000479 D0 05            [24] 1910 	pop	ar5
      00047B D0 06            [24] 1911 	pop	ar6
      00047D D0 07            [24] 1912 	pop	ar7
      00047F C0 07            [24] 1913 	push	ar7
      000481 C0 06            [24] 1914 	push	ar6
      000483 C0 05            [24] 1915 	push	ar5
      000485 74 80            [12] 1916 	mov	a,#0x80
      000487 C0 E0            [24] 1917 	push	acc
      000489 E4               [12] 1918 	clr	a
      00048A C0 E0            [24] 1919 	push	acc
      00048C C0 05            [24] 1920 	push	ar5
      00048E C0 06            [24] 1921 	push	ar6
      000490 C0 07            [24] 1922 	push	ar7
      000492 8A 82            [24] 1923 	mov	dpl,r2
      000494 8B 83            [24] 1924 	mov	dph,r3
      000496 8C F0            [24] 1925 	mov	b,r4
      000498 D0 02            [24] 1926 	pop	ar2
      00049A D0 01            [24] 1927 	pop	ar1
      00049C D0 00            [24] 1928 	pop	ar0
      00049E 12 05 65         [24] 1929 	lcall	__sdcc_banked_call
      0004A1 85 82 08         [24] 1930 	mov	_len,dpl
      0004A4 85 83 09         [24] 1931 	mov	(_len + 1),dph
      0004A7 15 81            [12] 1932 	dec	sp
      0004A9 15 81            [12] 1933 	dec	sp
      0004AB D0 05            [24] 1934 	pop	ar5
      0004AD D0 06            [24] 1935 	pop	ar6
      0004AF D0 07            [24] 1936 	pop	ar7
                                   1937 ;	../../../platform/cc2530dk/./contiki-main.c:352: if(len > 0) {
      0004B1 E5 08            [12] 1938 	mov	a,_len
      0004B3 45 09            [12] 1939 	orl	a,(_len + 1)
      0004B5 70 03            [24] 1940 	jnz	00179$
      0004B7 02 03 9F         [24] 1941 	ljmp	00113$
      0004BA                       1942 00179$:
                                   1943 ;	../../../platform/cc2530dk/./contiki-main.c:353: packetbuf_set_datalen(len);
      0004BA 85 08 82         [24] 1944 	mov	dpl,_len
      0004BD 85 09 83         [24] 1945 	mov	dph,(_len + 1)
      0004C0 78 DC            [12] 1946 	mov	r0,#_packetbuf_set_datalen
      0004C2 79 A6            [12] 1947 	mov	r1,#(_packetbuf_set_datalen >> 8)
      0004C4 7A 04            [12] 1948 	mov	r2,#(_packetbuf_set_datalen >> 16)
      0004C6 12 05 65         [24] 1949 	lcall	__sdcc_banked_call
                                   1950 ;	../../../platform/cc2530dk/./contiki-main.c:354: NETSTACK_RDC.input();
      0004C9 90 7D C2         [24] 1951 	mov	dptr,#(_nullrdc_driver + 0x000c)
      0004CC E4               [12] 1952 	clr	a
      0004CD 93               [24] 1953 	movc	a,@a+dptr
      0004CE FD               [12] 1954 	mov	r5,a
      0004CF A3               [24] 1955 	inc	dptr
      0004D0 E4               [12] 1956 	clr	a
      0004D1 93               [24] 1957 	movc	a,@a+dptr
      0004D2 FE               [12] 1958 	mov	r6,a
      0004D3 A3               [24] 1959 	inc	dptr
      0004D4 E4               [12] 1960 	clr	a
      0004D5 93               [24] 1961 	movc	a,@a+dptr
      0004D6 FF               [12] 1962 	mov	r7,a
      0004D7 C0 07            [24] 1963 	push	ar7
      0004D9 C0 06            [24] 1964 	push	ar6
      0004DB C0 05            [24] 1965 	push	ar5
      0004DD C0 05            [24] 1966 	push	ar5
      0004DF C0 06            [24] 1967 	push	ar6
      0004E1 C0 07            [24] 1968 	push	ar7
      0004E3 D0 02            [24] 1969 	pop	ar2
      0004E5 D0 01            [24] 1970 	pop	ar1
      0004E7 D0 00            [24] 1971 	pop	ar0
      0004E9 12 05 65         [24] 1972 	lcall	__sdcc_banked_call
      0004EC D0 05            [24] 1973 	pop	ar5
      0004EE D0 06            [24] 1974 	pop	ar6
      0004F0 D0 07            [24] 1975 	pop	ar7
                                   1976 ;	../../../platform/cc2530dk/./contiki-main.c:421: }
      0004F2 02 03 9F         [24] 1977 	ljmp	00113$
                                   1978 	.area CSEG    (CODE)
                                   1979 	.area CONST   (CODE)
      0073A2                       1980 ___str_0:
      0073A2 74 68 69 73 20 69 73  1981 	.ascii "this is print"
             20 70 72 69 6E 74
      0073AF 0D                    1982 	.db 0x0d
      0073B0 0A                    1983 	.db 0x0a
      0073B1 00                    1984 	.db 0x00
      0073B2                       1985 ___str_1:
      0073B2 43 6F 6E 74 69 6B 69  1986 	.ascii "Contiki 2.6"
             20 32 2E 36
      0073BD 0D                    1987 	.db 0x0d
      0073BE 0A                    1988 	.db 0x0a
      0073BF 00                    1989 	.db 0x00
      0073C0                       1990 ___str_2:
      0073C0 54 49 20 53 6D 61 72  1991 	.ascii "TI SmartRF05 EB"
             74 52 46 30 35 20 45
             42
      0073CF 0A                    1992 	.db 0x0a
      0073D0 00                    1993 	.db 0x00
      0073D1                       1994 ___str_3:
      0073D1 63 63 32 35 33 30     1995 	.ascii "cc2530"
      0073D7 00                    1996 	.db 0x00
      0073D8                       1997 ___str_4:
      0073D8 63 63 32 35 33 31     1998 	.ascii "cc2531"
      0073DE 00                    1999 	.db 0x00
      0073DF                       2000 ___str_5:
      0073DF 63 63 32 35 33 33     2001 	.ascii "cc2533"
      0073E5 00                    2002 	.db 0x00
      0073E6                       2003 ___str_6:
      0073E6 63 63 32 35 34 30     2004 	.ascii "cc2540"
      0073EC 00                    2005 	.db 0x00
      0073ED                       2006 ___str_7:
      0073ED 2D 46 32 35 36 2C 20  2007 	.ascii "-F256, "
      0073F4 00                    2008 	.db 0x00
      0073F5                       2009 ___str_8:
      0073F5 4B 42 20 53 52 41 4D  2010 	.ascii "KB SRAM"
      0073FC 0D                    2011 	.db 0x0d
      0073FD 0A                    2012 	.db 0x0a
      0073FE 00                    2013 	.db 0x00
                                   2014 	.area XINIT   (CODE)
                                   2015 	.area CABS    (ABS,CODE)
