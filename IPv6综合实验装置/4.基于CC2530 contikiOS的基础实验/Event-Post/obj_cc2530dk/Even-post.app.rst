                                      1 ;--------------------------------------------------------
                                      2 ; File Created by SDCC : free open source ANSI-C Compiler
                                      3 ; Version 3.8.4 #10774 (Linux)
                                      4 ;--------------------------------------------------------
                                      5 	.module Even_post
                                      6 	.optsdcc -mmcs51 --model-huge
                                      7 	
                                      8 ;--------------------------------------------------------
                                      9 ; Public variables in this module
                                     10 ;--------------------------------------------------------
                                     11 	.globl _autostart_processes
                                     12 	.globl _SHT2x_ReadTemp
                                     13 	.globl _SHT2x_ReadHumi
                                     14 	.globl _SHT2x_GetHumi
                                     15 	.globl _SHT2x_GetTemp
                                     16 	.globl _OLED_P8x16Str
                                     17 	.globl _etimer_restart
                                     18 	.globl _etimer_set
                                     19 	.globl _process_alloc_event
                                     20 	.globl _process_post
                                     21 	.globl _printf
                                     22 	.globl _ACTIVE
                                     23 	.globl _TX_BYTE
                                     24 	.globl _RX_BYTE
                                     25 	.globl _ERR
                                     26 	.globl _FE
                                     27 	.globl _SLAVE
                                     28 	.globl _RE
                                     29 	.globl _MODE
                                     30 	.globl _T3OVFIF
                                     31 	.globl _T3CH0IF
                                     32 	.globl _T3CH1IF
                                     33 	.globl _T4OVFIF
                                     34 	.globl _T4CH0IF
                                     35 	.globl _T4CH1IF
                                     36 	.globl _OVFIM
                                     37 	.globl _B_0
                                     38 	.globl _B_1
                                     39 	.globl _B_2
                                     40 	.globl _B_3
                                     41 	.globl _B_4
                                     42 	.globl _B_5
                                     43 	.globl _B_6
                                     44 	.globl _B_7
                                     45 	.globl _P2IF
                                     46 	.globl _UTX0IF
                                     47 	.globl _UTX1IF
                                     48 	.globl _P1IF
                                     49 	.globl _WDTIF
                                     50 	.globl _ACC_0
                                     51 	.globl _ACC_1
                                     52 	.globl _ACC_2
                                     53 	.globl _ACC_3
                                     54 	.globl _ACC_4
                                     55 	.globl _ACC_5
                                     56 	.globl _ACC_6
                                     57 	.globl _ACC_7
                                     58 	.globl _P
                                     59 	.globl _F1
                                     60 	.globl _OV
                                     61 	.globl _RS0
                                     62 	.globl _RS1
                                     63 	.globl _F0
                                     64 	.globl _AC
                                     65 	.globl _CY
                                     66 	.globl _DMAIF
                                     67 	.globl _T1IF
                                     68 	.globl _T2IF
                                     69 	.globl _T3IF
                                     70 	.globl _T4IF
                                     71 	.globl _P0IF
                                     72 	.globl _STIF
                                     73 	.globl _DMAIE
                                     74 	.globl _T1IE
                                     75 	.globl _T2IE
                                     76 	.globl _T3IE
                                     77 	.globl _T4IE
                                     78 	.globl _P0IE
                                     79 	.globl _RFERRIE
                                     80 	.globl _ADCIE
                                     81 	.globl _URX0IE
                                     82 	.globl _URX1IE
                                     83 	.globl _ENCIE
                                     84 	.globl _STIE
                                     85 	.globl _EA
                                     86 	.globl _P2_0
                                     87 	.globl _P2_1
                                     88 	.globl _P2_2
                                     89 	.globl _P2_3
                                     90 	.globl _P2_4
                                     91 	.globl _P2_5
                                     92 	.globl _P2_6
                                     93 	.globl _P2_7
                                     94 	.globl _ENCIF_0
                                     95 	.globl _ENCIF_1
                                     96 	.globl _P1_0
                                     97 	.globl _P1_1
                                     98 	.globl _P1_2
                                     99 	.globl _P1_3
                                    100 	.globl _P1_4
                                    101 	.globl _P1_5
                                    102 	.globl _P1_6
                                    103 	.globl _P1_7
                                    104 	.globl _IT0
                                    105 	.globl _RFERRIF
                                    106 	.globl _IT1
                                    107 	.globl _URX0IF
                                    108 	.globl _ADCIF
                                    109 	.globl _URX1IF
                                    110 	.globl _P0_0
                                    111 	.globl _P0_1
                                    112 	.globl _P0_2
                                    113 	.globl _P0_3
                                    114 	.globl _P0_4
                                    115 	.globl _P0_5
                                    116 	.globl _P0_6
                                    117 	.globl _P0_7
                                    118 	.globl _WDCTL
                                    119 	.globl _U1GCR
                                    120 	.globl _U1UCR
                                    121 	.globl _U1BAUD
                                    122 	.globl _U1DBUF
                                    123 	.globl _U1CSR
                                    124 	.globl _U0GCR
                                    125 	.globl _U0UCR
                                    126 	.globl _U0BAUD
                                    127 	.globl _U0DBUF
                                    128 	.globl _U0CSR
                                    129 	.globl _TIMIF
                                    130 	.globl _T4CC1
                                    131 	.globl _T4CCTL1
                                    132 	.globl _T4CC0
                                    133 	.globl _T4CCTL0
                                    134 	.globl _T4CTL
                                    135 	.globl _T4CNT
                                    136 	.globl _T3CC1
                                    137 	.globl _T3CCTL1
                                    138 	.globl _T3CC0
                                    139 	.globl _T3CCTL0
                                    140 	.globl _T3CTL
                                    141 	.globl _T3CNT
                                    142 	.globl _T2MSEL
                                    143 	.globl _T2IRQM
                                    144 	.globl _T2MOVF2
                                    145 	.globl _T2MOVF1
                                    146 	.globl _T2MOVF0
                                    147 	.globl _T2M1
                                    148 	.globl _T2M0
                                    149 	.globl _T2IRQF
                                    150 	.globl _T2EVTCFG
                                    151 	.globl _T2CTRL
                                    152 	.globl _T1STAT
                                    153 	.globl _T1CCTL2
                                    154 	.globl _T1CCTL1
                                    155 	.globl _T1CCTL0
                                    156 	.globl _T1CTL
                                    157 	.globl _T1CNTH
                                    158 	.globl _T1CNTL
                                    159 	.globl _T1CC2H
                                    160 	.globl _T1CC2L
                                    161 	.globl _T1CC1H
                                    162 	.globl _T1CC1L
                                    163 	.globl _T1CC0H
                                    164 	.globl _T1CC0L
                                    165 	.globl _CLKCONSTA
                                    166 	.globl _CLKCONCMD
                                    167 	.globl _SLEEPSTA
                                    168 	.globl _SLEEPCMD
                                    169 	.globl _STLOAD
                                    170 	.globl _ST2
                                    171 	.globl _ST1
                                    172 	.globl _ST0
                                    173 	.globl _RFERRF
                                    174 	.globl _RFIRQF0
                                    175 	.globl _RFST
                                    176 	.globl _RFD
                                    177 	.globl _RFIRQF1
                                    178 	.globl _PSBANK
                                    179 	.globl _FMAP
                                    180 	.globl _MEMCTR
                                    181 	.globl __XPAGE
                                    182 	.globl _MPAGE
                                    183 	.globl _PMUX
                                    184 	.globl _P2DIR
                                    185 	.globl _P1DIR
                                    186 	.globl _P0DIR
                                    187 	.globl _P2INP
                                    188 	.globl _P1INP
                                    189 	.globl _P2SEL
                                    190 	.globl _P1SEL
                                    191 	.globl _P0SEL
                                    192 	.globl _APCFG
                                    193 	.globl _PERCFG
                                    194 	.globl _P0INP
                                    195 	.globl _P2IEN
                                    196 	.globl _P1IEN
                                    197 	.globl _P0IEN
                                    198 	.globl _PICTL
                                    199 	.globl _P2IFG
                                    200 	.globl _P1IFG
                                    201 	.globl _P0IFG
                                    202 	.globl _DMAREQ
                                    203 	.globl _DMAARM
                                    204 	.globl _DMA0CFGH
                                    205 	.globl _DMA0CFGL
                                    206 	.globl _DMA1CFGH
                                    207 	.globl _DMA1CFGL
                                    208 	.globl _DMAIRQ
                                    209 	.globl _ENCCS
                                    210 	.globl _ENCDO
                                    211 	.globl _ENCDI
                                    212 	.globl _RNDH
                                    213 	.globl _RNDL
                                    214 	.globl _ADCH
                                    215 	.globl _ADCL
                                    216 	.globl _ADCCON3
                                    217 	.globl _ADCCON2
                                    218 	.globl _ADCCON1
                                    219 	.globl _B
                                    220 	.globl _IRCON2
                                    221 	.globl _ACC
                                    222 	.globl _PSW
                                    223 	.globl _IRCON
                                    224 	.globl _IP1
                                    225 	.globl _IEN1
                                    226 	.globl _IP0
                                    227 	.globl _IEN0
                                    228 	.globl _P2
                                    229 	.globl _S1CON
                                    230 	.globl _IEN2
                                    231 	.globl _S0CON
                                    232 	.globl _DPS
                                    233 	.globl _P1
                                    234 	.globl _TCON
                                    235 	.globl _PCON
                                    236 	.globl _DPH1
                                    237 	.globl _DPL1
                                    238 	.globl _DPH0
                                    239 	.globl _DPL0
                                    240 	.globl _SP
                                    241 	.globl _P0
                                    242 	.globl _display_process
                                    243 	.globl _sensor_process
                                    244 	.globl _X_IEEE_ADDR
                                    245 	.globl _X_INFOPAGE
                                    246 	.globl _X_P2DIR
                                    247 	.globl _X_P1DIR
                                    248 	.globl _X_P0DIR
                                    249 	.globl _X_U1GCR
                                    250 	.globl _X_U1UCR
                                    251 	.globl _X_U1BAUD
                                    252 	.globl _X_U1DBUF
                                    253 	.globl _X_U1CSR
                                    254 	.globl _X_P2INP
                                    255 	.globl _X_P1INP
                                    256 	.globl _X_P2SEL
                                    257 	.globl _X_P1SEL
                                    258 	.globl _X_P0SEL
                                    259 	.globl _X_APCFG
                                    260 	.globl _X_PERCFG
                                    261 	.globl _X_T4CC1
                                    262 	.globl _X_T4CCTL1
                                    263 	.globl _X_T4CC0
                                    264 	.globl _X_T4CCTL0
                                    265 	.globl _X_T4CTL
                                    266 	.globl _X_T4CNT
                                    267 	.globl _X_RFIRQF0
                                    268 	.globl _X_T1CCTL2
                                    269 	.globl _X_T1CCTL1
                                    270 	.globl _X_T1CCTL0
                                    271 	.globl _X_T1CTL
                                    272 	.globl _X_T1CNTH
                                    273 	.globl _X_T1CNTL
                                    274 	.globl _X_RFST
                                    275 	.globl _X_T1CC2H
                                    276 	.globl _X_T1CC2L
                                    277 	.globl _X_T1CC1H
                                    278 	.globl _X_T1CC1L
                                    279 	.globl _X_T1CC0H
                                    280 	.globl _X_T1CC0L
                                    281 	.globl _X_RFD
                                    282 	.globl _X_TIMIF
                                    283 	.globl _X_DMAREQ
                                    284 	.globl _X_DMAARM
                                    285 	.globl _X_DMA0CFGH
                                    286 	.globl _X_DMA0CFGL
                                    287 	.globl _X_DMA1CFGH
                                    288 	.globl _X_DMA1CFGL
                                    289 	.globl _X_DMAIRQ
                                    290 	.globl _X_T3CC1
                                    291 	.globl _X_T3CCTL1
                                    292 	.globl _X_T3CC0
                                    293 	.globl _X_T3CCTL0
                                    294 	.globl _X_T3CTL
                                    295 	.globl _X_T3CNT
                                    296 	.globl _X_WDCTL
                                    297 	.globl _X_MEMCTR
                                    298 	.globl _X_CLKCONCMD
                                    299 	.globl _X_U0GCR
                                    300 	.globl _X_U0UCR
                                    301 	.globl _X_T2MSEL
                                    302 	.globl _X_U0BAUD
                                    303 	.globl _X_U0DBUF
                                    304 	.globl _X_RFERRF
                                    305 	.globl _X_SLEEPCMD
                                    306 	.globl _X_RNDH
                                    307 	.globl _X_RNDL
                                    308 	.globl _X_ADCH
                                    309 	.globl _X_ADCL
                                    310 	.globl _X_ADCCON3
                                    311 	.globl _X_ADCCON2
                                    312 	.globl _X_ADCCON1
                                    313 	.globl _X_ENCCS
                                    314 	.globl _X_ENCDO
                                    315 	.globl _X_ENCDI
                                    316 	.globl _X_T1STAT
                                    317 	.globl _X_PMUX
                                    318 	.globl _X_STLOAD
                                    319 	.globl _X_P2IEN
                                    320 	.globl _X_P0IEN
                                    321 	.globl _X_T2IRQM
                                    322 	.globl _X_T2MOVF2
                                    323 	.globl _X_T2MOVF1
                                    324 	.globl _X_T2MOVF0
                                    325 	.globl _X_T2M1
                                    326 	.globl _X_T2M0
                                    327 	.globl _X_T2IRQF
                                    328 	.globl _X_P2
                                    329 	.globl _X_PSBANK
                                    330 	.globl _X_FMAP
                                    331 	.globl _X_CLKCONSTA
                                    332 	.globl _X_SLEEPSTA
                                    333 	.globl _X_T2EVTCFG
                                    334 	.globl _X_ST2
                                    335 	.globl _X_ST1
                                    336 	.globl _X_ST0
                                    337 	.globl _X_T2CTRL
                                    338 	.globl _X__XPAGE
                                    339 	.globl _X_MPAGE
                                    340 	.globl _X_RFIRQF1
                                    341 	.globl _X_P1
                                    342 	.globl _X_P0INP
                                    343 	.globl _X_P1IEN
                                    344 	.globl _X_PICTL
                                    345 	.globl _X_P2IFG
                                    346 	.globl _X_P1IFG
                                    347 	.globl _X_P0IFG
                                    348 	.globl _X_U0CSR
                                    349 	.globl _X_P0
                                    350 	.globl _USBF5
                                    351 	.globl _USBF4
                                    352 	.globl _USBF3
                                    353 	.globl _USBF2
                                    354 	.globl _USBF1
                                    355 	.globl _USBF0
                                    356 	.globl _USBCNTH
                                    357 	.globl _USBCNTL
                                    358 	.globl _USBCNT0
                                    359 	.globl _USBCSOH
                                    360 	.globl _USBCSOL
                                    361 	.globl _USBMAXO
                                    362 	.globl _USBCSIH
                                    363 	.globl _USBCSIL
                                    364 	.globl _USBCS0
                                    365 	.globl _USBMAXI
                                    366 	.globl _USBCTRL
                                    367 	.globl _USBINDEX
                                    368 	.globl _USBFRMH
                                    369 	.globl _USBFRML
                                    370 	.globl _USBCIE
                                    371 	.globl _USBOIE
                                    372 	.globl _USBIIE
                                    373 	.globl _USBCIF
                                    374 	.globl _USBOIF
                                    375 	.globl _USBIIF
                                    376 	.globl _USBPOW
                                    377 	.globl _USBADDR
                                    378 	.globl _CSPT
                                    379 	.globl _CSPZ
                                    380 	.globl _CSPY
                                    381 	.globl _CSPX
                                    382 	.globl _CSPSTAT
                                    383 	.globl _CSPCTRL
                                    384 	.globl _CSPPROG23
                                    385 	.globl _CSPPROG22
                                    386 	.globl _CSPPROG21
                                    387 	.globl _CSPPROG20
                                    388 	.globl _CSPPROG19
                                    389 	.globl _CSPPROG18
                                    390 	.globl _CSPPROG17
                                    391 	.globl _CSPPROG16
                                    392 	.globl _CSPPROG15
                                    393 	.globl _CSPPROG14
                                    394 	.globl _CSPPROG13
                                    395 	.globl _CSPPROG12
                                    396 	.globl _CSPPROG11
                                    397 	.globl _CSPPROG10
                                    398 	.globl _CSPPROG9
                                    399 	.globl _CSPPROG8
                                    400 	.globl _CSPPROG7
                                    401 	.globl _CSPPROG6
                                    402 	.globl _CSPPROG5
                                    403 	.globl _CSPPROG4
                                    404 	.globl _CSPPROG3
                                    405 	.globl _CSPPROG2
                                    406 	.globl _CSPPROG1
                                    407 	.globl _CSPPROG0
                                    408 	.globl _RFC_OBS_CTRL2
                                    409 	.globl _RFC_OBS_CTRL1
                                    410 	.globl _RFC_OBS_CTRL0
                                    411 	.globl _TXFILTCFG
                                    412 	.globl _PTEST1
                                    413 	.globl _PTEST0
                                    414 	.globl _ATEST
                                    415 	.globl _DACTEST2
                                    416 	.globl _DACTEST1
                                    417 	.globl _DACTEST0
                                    418 	.globl _MDMTEST1
                                    419 	.globl _MDMTEST0
                                    420 	.globl _ADCTEST2
                                    421 	.globl _ADCTEST1
                                    422 	.globl _ADCTEST0
                                    423 	.globl _AGCCTRL3
                                    424 	.globl _AGCCTRL2
                                    425 	.globl _AGCCTRL1
                                    426 	.globl _AGCCTRL0
                                    427 	.globl _FSCAL3
                                    428 	.globl _FSCAL2
                                    429 	.globl _FSCAL1
                                    430 	.globl _FSCAL0
                                    431 	.globl _FSCTRL
                                    432 	.globl _RXCTRL
                                    433 	.globl _FREQEST
                                    434 	.globl _MDMCTRL1
                                    435 	.globl _MDMCTRL0
                                    436 	.globl _RFRND
                                    437 	.globl _RFERRM
                                    438 	.globl _RFIRQM1
                                    439 	.globl _RFIRQM0
                                    440 	.globl _TXLAST_PTR
                                    441 	.globl _TXFIRST_PTR
                                    442 	.globl _RXP1_PTR
                                    443 	.globl _RXLAST_PTR
                                    444 	.globl _RXFIRST_PTR
                                    445 	.globl _TXFIFOCNT
                                    446 	.globl _RXFIFOCNT
                                    447 	.globl _RXFIRST
                                    448 	.globl _RSSISTAT
                                    449 	.globl _RSSI
                                    450 	.globl _CCACTRL1
                                    451 	.globl _CCACTRL0
                                    452 	.globl _FSMCTRL
                                    453 	.globl _FIFOPCTRL
                                    454 	.globl _FSMSTAT1
                                    455 	.globl _FSMSTAT0
                                    456 	.globl _TXCTRL
                                    457 	.globl _TXPOWER
                                    458 	.globl _FREQCTRL
                                    459 	.globl _FREQTUNE
                                    460 	.globl _RXMASKCLR
                                    461 	.globl _RXMASKSET
                                    462 	.globl _RXENABLE
                                    463 	.globl _FRMCTRL1
                                    464 	.globl _FRMCTRL0
                                    465 	.globl _SRCEXTEN2
                                    466 	.globl _SRCEXTEN1
                                    467 	.globl _SRCEXTEN0
                                    468 	.globl _SRCSHORTEN2
                                    469 	.globl _SRCSHORTEN1
                                    470 	.globl _SRCSHORTEN0
                                    471 	.globl _SRCMATCH
                                    472 	.globl _FRMFILT1
                                    473 	.globl _FRMFILT0
                                    474 	.globl _SHORT_ADDR1
                                    475 	.globl _SHORT_ADDR0
                                    476 	.globl _PAN_ID1
                                    477 	.globl _PAN_ID0
                                    478 	.globl _EXT_ADDR7
                                    479 	.globl _EXT_ADDR6
                                    480 	.globl _EXT_ADDR5
                                    481 	.globl _EXT_ADDR4
                                    482 	.globl _EXT_ADDR3
                                    483 	.globl _EXT_ADDR2
                                    484 	.globl _EXT_ADDR1
                                    485 	.globl _EXT_ADDR0
                                    486 	.globl _SRCSHORTPENDEN2
                                    487 	.globl _SRCSHORTPENDEN1
                                    488 	.globl _SRCSHORTPENDEN0
                                    489 	.globl _SRCEXTPENDEN2
                                    490 	.globl _SRCEXTPENDEN1
                                    491 	.globl _SRCEXTPENDEN0
                                    492 	.globl _SRCRESINDEX
                                    493 	.globl _SRCRESMASK2
                                    494 	.globl _SRCRESMASK1
                                    495 	.globl _SRCRESMASK0
                                    496 	.globl _SRC_ADDR_TABLE
                                    497 	.globl _TXFIFO
                                    498 	.globl _RXFIFO
                                    499 	.globl _RFCORE_RAM
                                    500 	.globl _CMPCTL
                                    501 	.globl _OPAMPS
                                    502 	.globl _OPAMPC
                                    503 	.globl _STCV2
                                    504 	.globl _STCV1
                                    505 	.globl _STCV0
                                    506 	.globl _STCS
                                    507 	.globl _STCC
                                    508 	.globl _T1CC4H
                                    509 	.globl _T1CC4L
                                    510 	.globl _T1CC3H
                                    511 	.globl _T1CC3L
                                    512 	.globl _XX_T1CC2H
                                    513 	.globl _XX_T1CC2L
                                    514 	.globl _XX_T1CC1H
                                    515 	.globl _XX_T1CC1L
                                    516 	.globl _XX_T1CC0H
                                    517 	.globl _XX_T1CC0L
                                    518 	.globl _T1CCTL4
                                    519 	.globl _T1CCTL3
                                    520 	.globl _XX_T1CCTL2
                                    521 	.globl _XX_T1CCTL1
                                    522 	.globl _XX_T1CCTL0
                                    523 	.globl _CLD
                                    524 	.globl _IRCTL
                                    525 	.globl _CHIPINFO1
                                    526 	.globl _CHIPINFO0
                                    527 	.globl _FWDATA
                                    528 	.globl _FADDRH
                                    529 	.globl _FADDRL
                                    530 	.globl _FCTL
                                    531 	.globl _IVCTRL
                                    532 	.globl _BATTMON
                                    533 	.globl _SRCRC
                                    534 	.globl _DBGDATA
                                    535 	.globl _TESTREG0
                                    536 	.globl _CHIPID
                                    537 	.globl _CHVER
                                    538 	.globl _OBSSEL5
                                    539 	.globl _OBSSEL4
                                    540 	.globl _OBSSEL3
                                    541 	.globl _OBSSEL2
                                    542 	.globl _OBSSEL1
                                    543 	.globl _OBSSEL0
                                    544 	.globl _I2CIO
                                    545 	.globl _I2CWC
                                    546 	.globl _I2CADDR
                                    547 	.globl _I2CDATA
                                    548 	.globl _I2CSTAT
                                    549 	.globl _I2CCFG
                                    550 	.globl _OPAMPMC
                                    551 	.globl _MONMUX
                                    552 ;--------------------------------------------------------
                                    553 ; special function registers
                                    554 ;--------------------------------------------------------
                                    555 	.area RSEG    (ABS,DATA)
      000000                        556 	.org 0x0000
                           000080   557 _P0	=	0x0080
                           000081   558 _SP	=	0x0081
                           000082   559 _DPL0	=	0x0082
                           000083   560 _DPH0	=	0x0083
                           000084   561 _DPL1	=	0x0084
                           000085   562 _DPH1	=	0x0085
                           000087   563 _PCON	=	0x0087
                           000088   564 _TCON	=	0x0088
                           000090   565 _P1	=	0x0090
                           000092   566 _DPS	=	0x0092
                           000098   567 _S0CON	=	0x0098
                           00009A   568 _IEN2	=	0x009a
                           00009B   569 _S1CON	=	0x009b
                           0000A0   570 _P2	=	0x00a0
                           0000A8   571 _IEN0	=	0x00a8
                           0000A9   572 _IP0	=	0x00a9
                           0000B8   573 _IEN1	=	0x00b8
                           0000B9   574 _IP1	=	0x00b9
                           0000C0   575 _IRCON	=	0x00c0
                           0000D0   576 _PSW	=	0x00d0
                           0000E0   577 _ACC	=	0x00e0
                           0000E8   578 _IRCON2	=	0x00e8
                           0000F0   579 _B	=	0x00f0
                           0000B4   580 _ADCCON1	=	0x00b4
                           0000B5   581 _ADCCON2	=	0x00b5
                           0000B6   582 _ADCCON3	=	0x00b6
                           0000BA   583 _ADCL	=	0x00ba
                           0000BB   584 _ADCH	=	0x00bb
                           0000BC   585 _RNDL	=	0x00bc
                           0000BD   586 _RNDH	=	0x00bd
                           0000B1   587 _ENCDI	=	0x00b1
                           0000B2   588 _ENCDO	=	0x00b2
                           0000B3   589 _ENCCS	=	0x00b3
                           0000D1   590 _DMAIRQ	=	0x00d1
                           0000D2   591 _DMA1CFGL	=	0x00d2
                           0000D3   592 _DMA1CFGH	=	0x00d3
                           0000D4   593 _DMA0CFGL	=	0x00d4
                           0000D5   594 _DMA0CFGH	=	0x00d5
                           0000D6   595 _DMAARM	=	0x00d6
                           0000D7   596 _DMAREQ	=	0x00d7
                           000089   597 _P0IFG	=	0x0089
                           00008A   598 _P1IFG	=	0x008a
                           00008B   599 _P2IFG	=	0x008b
                           00008C   600 _PICTL	=	0x008c
                           0000AB   601 _P0IEN	=	0x00ab
                           00008D   602 _P1IEN	=	0x008d
                           0000AC   603 _P2IEN	=	0x00ac
                           00008F   604 _P0INP	=	0x008f
                           0000F1   605 _PERCFG	=	0x00f1
                           0000F2   606 _APCFG	=	0x00f2
                           0000F3   607 _P0SEL	=	0x00f3
                           0000F4   608 _P1SEL	=	0x00f4
                           0000F5   609 _P2SEL	=	0x00f5
                           0000F6   610 _P1INP	=	0x00f6
                           0000F7   611 _P2INP	=	0x00f7
                           0000FD   612 _P0DIR	=	0x00fd
                           0000FE   613 _P1DIR	=	0x00fe
                           0000FF   614 _P2DIR	=	0x00ff
                           0000AE   615 _PMUX	=	0x00ae
                           000093   616 _MPAGE	=	0x0093
                           000093   617 __XPAGE	=	0x0093
                           0000C7   618 _MEMCTR	=	0x00c7
                           00009F   619 _FMAP	=	0x009f
                           00009F   620 _PSBANK	=	0x009f
                           000091   621 _RFIRQF1	=	0x0091
                           0000D9   622 _RFD	=	0x00d9
                           0000E1   623 _RFST	=	0x00e1
                           0000E9   624 _RFIRQF0	=	0x00e9
                           0000BF   625 _RFERRF	=	0x00bf
                           000095   626 _ST0	=	0x0095
                           000096   627 _ST1	=	0x0096
                           000097   628 _ST2	=	0x0097
                           0000AD   629 _STLOAD	=	0x00ad
                           0000BE   630 _SLEEPCMD	=	0x00be
                           00009D   631 _SLEEPSTA	=	0x009d
                           0000C6   632 _CLKCONCMD	=	0x00c6
                           00009E   633 _CLKCONSTA	=	0x009e
                           0000DA   634 _T1CC0L	=	0x00da
                           0000DB   635 _T1CC0H	=	0x00db
                           0000DC   636 _T1CC1L	=	0x00dc
                           0000DD   637 _T1CC1H	=	0x00dd
                           0000DE   638 _T1CC2L	=	0x00de
                           0000DF   639 _T1CC2H	=	0x00df
                           0000E2   640 _T1CNTL	=	0x00e2
                           0000E3   641 _T1CNTH	=	0x00e3
                           0000E4   642 _T1CTL	=	0x00e4
                           0000E5   643 _T1CCTL0	=	0x00e5
                           0000E6   644 _T1CCTL1	=	0x00e6
                           0000E7   645 _T1CCTL2	=	0x00e7
                           0000AF   646 _T1STAT	=	0x00af
                           000094   647 _T2CTRL	=	0x0094
                           00009C   648 _T2EVTCFG	=	0x009c
                           0000A1   649 _T2IRQF	=	0x00a1
                           0000A2   650 _T2M0	=	0x00a2
                           0000A3   651 _T2M1	=	0x00a3
                           0000A4   652 _T2MOVF0	=	0x00a4
                           0000A5   653 _T2MOVF1	=	0x00a5
                           0000A6   654 _T2MOVF2	=	0x00a6
                           0000A7   655 _T2IRQM	=	0x00a7
                           0000C3   656 _T2MSEL	=	0x00c3
                           0000CA   657 _T3CNT	=	0x00ca
                           0000CB   658 _T3CTL	=	0x00cb
                           0000CC   659 _T3CCTL0	=	0x00cc
                           0000CD   660 _T3CC0	=	0x00cd
                           0000CE   661 _T3CCTL1	=	0x00ce
                           0000CF   662 _T3CC1	=	0x00cf
                           0000EA   663 _T4CNT	=	0x00ea
                           0000EB   664 _T4CTL	=	0x00eb
                           0000EC   665 _T4CCTL0	=	0x00ec
                           0000ED   666 _T4CC0	=	0x00ed
                           0000EE   667 _T4CCTL1	=	0x00ee
                           0000EF   668 _T4CC1	=	0x00ef
                           0000D8   669 _TIMIF	=	0x00d8
                           000086   670 _U0CSR	=	0x0086
                           0000C1   671 _U0DBUF	=	0x00c1
                           0000C2   672 _U0BAUD	=	0x00c2
                           0000C4   673 _U0UCR	=	0x00c4
                           0000C5   674 _U0GCR	=	0x00c5
                           0000F8   675 _U1CSR	=	0x00f8
                           0000F9   676 _U1DBUF	=	0x00f9
                           0000FA   677 _U1BAUD	=	0x00fa
                           0000FB   678 _U1UCR	=	0x00fb
                           0000FC   679 _U1GCR	=	0x00fc
                           0000C9   680 _WDCTL	=	0x00c9
                                    681 ;--------------------------------------------------------
                                    682 ; special function bits
                                    683 ;--------------------------------------------------------
                                    684 	.area RSEG    (ABS,DATA)
      000000                        685 	.org 0x0000
                           000087   686 _P0_7	=	0x0087
                           000086   687 _P0_6	=	0x0086
                           000085   688 _P0_5	=	0x0085
                           000084   689 _P0_4	=	0x0084
                           000083   690 _P0_3	=	0x0083
                           000082   691 _P0_2	=	0x0082
                           000081   692 _P0_1	=	0x0081
                           000080   693 _P0_0	=	0x0080
                           00008F   694 _URX1IF	=	0x008f
                           00008D   695 _ADCIF	=	0x008d
                           00008B   696 _URX0IF	=	0x008b
                           00008A   697 _IT1	=	0x008a
                           000089   698 _RFERRIF	=	0x0089
                           000088   699 _IT0	=	0x0088
                           000097   700 _P1_7	=	0x0097
                           000096   701 _P1_6	=	0x0096
                           000095   702 _P1_5	=	0x0095
                           000094   703 _P1_4	=	0x0094
                           000093   704 _P1_3	=	0x0093
                           000092   705 _P1_2	=	0x0092
                           000091   706 _P1_1	=	0x0091
                           000090   707 _P1_0	=	0x0090
                           000099   708 _ENCIF_1	=	0x0099
                           000098   709 _ENCIF_0	=	0x0098
                           0000A7   710 _P2_7	=	0x00a7
                           0000A6   711 _P2_6	=	0x00a6
                           0000A5   712 _P2_5	=	0x00a5
                           0000A4   713 _P2_4	=	0x00a4
                           0000A3   714 _P2_3	=	0x00a3
                           0000A2   715 _P2_2	=	0x00a2
                           0000A1   716 _P2_1	=	0x00a1
                           0000A0   717 _P2_0	=	0x00a0
                           0000AF   718 _EA	=	0x00af
                           0000AD   719 _STIE	=	0x00ad
                           0000AC   720 _ENCIE	=	0x00ac
                           0000AB   721 _URX1IE	=	0x00ab
                           0000AA   722 _URX0IE	=	0x00aa
                           0000A9   723 _ADCIE	=	0x00a9
                           0000A8   724 _RFERRIE	=	0x00a8
                           0000BD   725 _P0IE	=	0x00bd
                           0000BC   726 _T4IE	=	0x00bc
                           0000BB   727 _T3IE	=	0x00bb
                           0000BA   728 _T2IE	=	0x00ba
                           0000B9   729 _T1IE	=	0x00b9
                           0000B8   730 _DMAIE	=	0x00b8
                           0000C7   731 _STIF	=	0x00c7
                           0000C5   732 _P0IF	=	0x00c5
                           0000C4   733 _T4IF	=	0x00c4
                           0000C3   734 _T3IF	=	0x00c3
                           0000C2   735 _T2IF	=	0x00c2
                           0000C1   736 _T1IF	=	0x00c1
                           0000C0   737 _DMAIF	=	0x00c0
                           0000D7   738 _CY	=	0x00d7
                           0000D6   739 _AC	=	0x00d6
                           0000D5   740 _F0	=	0x00d5
                           0000D4   741 _RS1	=	0x00d4
                           0000D3   742 _RS0	=	0x00d3
                           0000D2   743 _OV	=	0x00d2
                           0000D1   744 _F1	=	0x00d1
                           0000D0   745 _P	=	0x00d0
                           0000E7   746 _ACC_7	=	0x00e7
                           0000E6   747 _ACC_6	=	0x00e6
                           0000E5   748 _ACC_5	=	0x00e5
                           0000E4   749 _ACC_4	=	0x00e4
                           0000E3   750 _ACC_3	=	0x00e3
                           0000E2   751 _ACC_2	=	0x00e2
                           0000E1   752 _ACC_1	=	0x00e1
                           0000E0   753 _ACC_0	=	0x00e0
                           0000EC   754 _WDTIF	=	0x00ec
                           0000EB   755 _P1IF	=	0x00eb
                           0000EA   756 _UTX1IF	=	0x00ea
                           0000E9   757 _UTX0IF	=	0x00e9
                           0000E8   758 _P2IF	=	0x00e8
                           0000F7   759 _B_7	=	0x00f7
                           0000F6   760 _B_6	=	0x00f6
                           0000F5   761 _B_5	=	0x00f5
                           0000F4   762 _B_4	=	0x00f4
                           0000F3   763 _B_3	=	0x00f3
                           0000F2   764 _B_2	=	0x00f2
                           0000F1   765 _B_1	=	0x00f1
                           0000F0   766 _B_0	=	0x00f0
                           0000DE   767 _OVFIM	=	0x00de
                           0000DD   768 _T4CH1IF	=	0x00dd
                           0000DC   769 _T4CH0IF	=	0x00dc
                           0000DB   770 _T4OVFIF	=	0x00db
                           0000DA   771 _T3CH1IF	=	0x00da
                           0000D9   772 _T3CH0IF	=	0x00d9
                           0000D8   773 _T3OVFIF	=	0x00d8
                           0000FF   774 _MODE	=	0x00ff
                           0000FE   775 _RE	=	0x00fe
                           0000FD   776 _SLAVE	=	0x00fd
                           0000FC   777 _FE	=	0x00fc
                           0000FB   778 _ERR	=	0x00fb
                           0000FA   779 _RX_BYTE	=	0x00fa
                           0000F9   780 _TX_BYTE	=	0x00f9
                           0000F8   781 _ACTIVE	=	0x00f8
                                    782 ;--------------------------------------------------------
                                    783 ; overlayable register banks
                                    784 ;--------------------------------------------------------
                                    785 	.area REG_BANK_0	(REL,OVR,DATA)
      000000                        786 	.ds 8
                                    787 ;--------------------------------------------------------
                                    788 ; internal ram data
                                    789 ;--------------------------------------------------------
                                    790 	.area DSEG    (DATA)
                                    791 ;--------------------------------------------------------
                                    792 ; overlayable items in internal ram 
                                    793 ;--------------------------------------------------------
                                    794 ;--------------------------------------------------------
                                    795 ; indirectly addressable internal ram data
                                    796 ;--------------------------------------------------------
                                    797 	.area ISEG    (DATA)
                                    798 ;--------------------------------------------------------
                                    799 ; absolute internal ram data
                                    800 ;--------------------------------------------------------
                                    801 	.area IABS    (ABS,DATA)
                                    802 	.area IABS    (ABS,DATA)
                                    803 ;--------------------------------------------------------
                                    804 ; bit data
                                    805 ;--------------------------------------------------------
                                    806 	.area BSEG    (BIT)
                                    807 ;--------------------------------------------------------
                                    808 ; paged external ram data
                                    809 ;--------------------------------------------------------
                                    810 	.area PSEG    (PAG,XDATA)
                                    811 ;--------------------------------------------------------
                                    812 ; external ram data
                                    813 ;--------------------------------------------------------
                                    814 	.area XSEG    (XDATA)
                           0061A6   815 _MONMUX	=	0x61a6
                           0061A6   816 _OPAMPMC	=	0x61a6
                           006230   817 _I2CCFG	=	0x6230
                           006231   818 _I2CSTAT	=	0x6231
                           006232   819 _I2CDATA	=	0x6232
                           006233   820 _I2CADDR	=	0x6233
                           006234   821 _I2CWC	=	0x6234
                           006235   822 _I2CIO	=	0x6235
                           006243   823 _OBSSEL0	=	0x6243
                           006244   824 _OBSSEL1	=	0x6244
                           006245   825 _OBSSEL2	=	0x6245
                           006246   826 _OBSSEL3	=	0x6246
                           006247   827 _OBSSEL4	=	0x6247
                           006248   828 _OBSSEL5	=	0x6248
                           006249   829 _CHVER	=	0x6249
                           00624A   830 _CHIPID	=	0x624a
                           00624B   831 _TESTREG0	=	0x624b
                           006260   832 _DBGDATA	=	0x6260
                           006262   833 _SRCRC	=	0x6262
                           006264   834 _BATTMON	=	0x6264
                           006265   835 _IVCTRL	=	0x6265
                           006270   836 _FCTL	=	0x6270
                           006271   837 _FADDRL	=	0x6271
                           006272   838 _FADDRH	=	0x6272
                           006273   839 _FWDATA	=	0x6273
                           006276   840 _CHIPINFO0	=	0x6276
                           006277   841 _CHIPINFO1	=	0x6277
                           006281   842 _IRCTL	=	0x6281
                           006290   843 _CLD	=	0x6290
                           0062A0   844 _XX_T1CCTL0	=	0x62a0
                           0062A1   845 _XX_T1CCTL1	=	0x62a1
                           0062A2   846 _XX_T1CCTL2	=	0x62a2
                           0062A3   847 _T1CCTL3	=	0x62a3
                           0062A4   848 _T1CCTL4	=	0x62a4
                           0062A6   849 _XX_T1CC0L	=	0x62a6
                           0062A7   850 _XX_T1CC0H	=	0x62a7
                           0062A8   851 _XX_T1CC1L	=	0x62a8
                           0062A9   852 _XX_T1CC1H	=	0x62a9
                           0062AA   853 _XX_T1CC2L	=	0x62aa
                           0062AB   854 _XX_T1CC2H	=	0x62ab
                           0062AC   855 _T1CC3L	=	0x62ac
                           0062AD   856 _T1CC3H	=	0x62ad
                           0062AE   857 _T1CC4L	=	0x62ae
                           0062AF   858 _T1CC4H	=	0x62af
                           0062B0   859 _STCC	=	0x62b0
                           0062B1   860 _STCS	=	0x62b1
                           0062B2   861 _STCV0	=	0x62b2
                           0062B3   862 _STCV1	=	0x62b3
                           0062B4   863 _STCV2	=	0x62b4
                           0062C0   864 _OPAMPC	=	0x62c0
                           0062C1   865 _OPAMPS	=	0x62c1
                           0062D0   866 _CMPCTL	=	0x62d0
                           006000   867 _RFCORE_RAM	=	0x6000
                           006000   868 _RXFIFO	=	0x6000
                           006080   869 _TXFIFO	=	0x6080
                           006100   870 _SRC_ADDR_TABLE	=	0x6100
                           006160   871 _SRCRESMASK0	=	0x6160
                           006161   872 _SRCRESMASK1	=	0x6161
                           006162   873 _SRCRESMASK2	=	0x6162
                           006163   874 _SRCRESINDEX	=	0x6163
                           006164   875 _SRCEXTPENDEN0	=	0x6164
                           006165   876 _SRCEXTPENDEN1	=	0x6165
                           006166   877 _SRCEXTPENDEN2	=	0x6166
                           006167   878 _SRCSHORTPENDEN0	=	0x6167
                           006168   879 _SRCSHORTPENDEN1	=	0x6168
                           006169   880 _SRCSHORTPENDEN2	=	0x6169
                           00616A   881 _EXT_ADDR0	=	0x616a
                           00616B   882 _EXT_ADDR1	=	0x616b
                           00616C   883 _EXT_ADDR2	=	0x616c
                           00616D   884 _EXT_ADDR3	=	0x616d
                           00616E   885 _EXT_ADDR4	=	0x616e
                           00616F   886 _EXT_ADDR5	=	0x616f
                           006170   887 _EXT_ADDR6	=	0x6170
                           006171   888 _EXT_ADDR7	=	0x6171
                           006172   889 _PAN_ID0	=	0x6172
                           006173   890 _PAN_ID1	=	0x6173
                           006174   891 _SHORT_ADDR0	=	0x6174
                           006175   892 _SHORT_ADDR1	=	0x6175
                           006180   893 _FRMFILT0	=	0x6180
                           006181   894 _FRMFILT1	=	0x6181
                           006182   895 _SRCMATCH	=	0x6182
                           006183   896 _SRCSHORTEN0	=	0x6183
                           006184   897 _SRCSHORTEN1	=	0x6184
                           006185   898 _SRCSHORTEN2	=	0x6185
                           006186   899 _SRCEXTEN0	=	0x6186
                           006187   900 _SRCEXTEN1	=	0x6187
                           006188   901 _SRCEXTEN2	=	0x6188
                           006189   902 _FRMCTRL0	=	0x6189
                           00618A   903 _FRMCTRL1	=	0x618a
                           00618B   904 _RXENABLE	=	0x618b
                           00618C   905 _RXMASKSET	=	0x618c
                           00618D   906 _RXMASKCLR	=	0x618d
                           00618E   907 _FREQTUNE	=	0x618e
                           00618F   908 _FREQCTRL	=	0x618f
                           006190   909 _TXPOWER	=	0x6190
                           006191   910 _TXCTRL	=	0x6191
                           006192   911 _FSMSTAT0	=	0x6192
                           006193   912 _FSMSTAT1	=	0x6193
                           006194   913 _FIFOPCTRL	=	0x6194
                           006195   914 _FSMCTRL	=	0x6195
                           006196   915 _CCACTRL0	=	0x6196
                           006197   916 _CCACTRL1	=	0x6197
                           006198   917 _RSSI	=	0x6198
                           006199   918 _RSSISTAT	=	0x6199
                           00619A   919 _RXFIRST	=	0x619a
                           00619B   920 _RXFIFOCNT	=	0x619b
                           00619C   921 _TXFIFOCNT	=	0x619c
                           00619D   922 _RXFIRST_PTR	=	0x619d
                           00619E   923 _RXLAST_PTR	=	0x619e
                           00619F   924 _RXP1_PTR	=	0x619f
                           0061A1   925 _TXFIRST_PTR	=	0x61a1
                           0061A2   926 _TXLAST_PTR	=	0x61a2
                           0061A3   927 _RFIRQM0	=	0x61a3
                           0061A4   928 _RFIRQM1	=	0x61a4
                           0061A5   929 _RFERRM	=	0x61a5
                           0061A7   930 _RFRND	=	0x61a7
                           0061A8   931 _MDMCTRL0	=	0x61a8
                           0061A9   932 _MDMCTRL1	=	0x61a9
                           0061AA   933 _FREQEST	=	0x61aa
                           0061AB   934 _RXCTRL	=	0x61ab
                           0061AC   935 _FSCTRL	=	0x61ac
                           0061AD   936 _FSCAL0	=	0x61ad
                           0061AE   937 _FSCAL1	=	0x61ae
                           0061AF   938 _FSCAL2	=	0x61af
                           0061B0   939 _FSCAL3	=	0x61b0
                           0061B1   940 _AGCCTRL0	=	0x61b1
                           0061B2   941 _AGCCTRL1	=	0x61b2
                           0061B3   942 _AGCCTRL2	=	0x61b3
                           0061B4   943 _AGCCTRL3	=	0x61b4
                           0061B5   944 _ADCTEST0	=	0x61b5
                           0061B6   945 _ADCTEST1	=	0x61b6
                           0061B7   946 _ADCTEST2	=	0x61b7
                           0061B8   947 _MDMTEST0	=	0x61b8
                           0061B9   948 _MDMTEST1	=	0x61b9
                           0061BA   949 _DACTEST0	=	0x61ba
                           0061BB   950 _DACTEST1	=	0x61bb
                           0061BC   951 _DACTEST2	=	0x61bc
                           0061BD   952 _ATEST	=	0x61bd
                           0061BE   953 _PTEST0	=	0x61be
                           0061BF   954 _PTEST1	=	0x61bf
                           0061FA   955 _TXFILTCFG	=	0x61fa
                           0061EB   956 _RFC_OBS_CTRL0	=	0x61eb
                           0061EC   957 _RFC_OBS_CTRL1	=	0x61ec
                           0061ED   958 _RFC_OBS_CTRL2	=	0x61ed
                           0061C0   959 _CSPPROG0	=	0x61c0
                           0061C1   960 _CSPPROG1	=	0x61c1
                           0061C2   961 _CSPPROG2	=	0x61c2
                           0061C3   962 _CSPPROG3	=	0x61c3
                           0061C4   963 _CSPPROG4	=	0x61c4
                           0061C5   964 _CSPPROG5	=	0x61c5
                           0061C6   965 _CSPPROG6	=	0x61c6
                           0061C7   966 _CSPPROG7	=	0x61c7
                           0061C8   967 _CSPPROG8	=	0x61c8
                           0061C9   968 _CSPPROG9	=	0x61c9
                           0061CA   969 _CSPPROG10	=	0x61ca
                           0061CB   970 _CSPPROG11	=	0x61cb
                           0061CC   971 _CSPPROG12	=	0x61cc
                           0061CD   972 _CSPPROG13	=	0x61cd
                           0061CE   973 _CSPPROG14	=	0x61ce
                           0061CF   974 _CSPPROG15	=	0x61cf
                           0061D0   975 _CSPPROG16	=	0x61d0
                           0061D1   976 _CSPPROG17	=	0x61d1
                           0061D2   977 _CSPPROG18	=	0x61d2
                           0061D3   978 _CSPPROG19	=	0x61d3
                           0061D4   979 _CSPPROG20	=	0x61d4
                           0061D5   980 _CSPPROG21	=	0x61d5
                           0061D6   981 _CSPPROG22	=	0x61d6
                           0061D7   982 _CSPPROG23	=	0x61d7
                           0061E0   983 _CSPCTRL	=	0x61e0
                           0061E1   984 _CSPSTAT	=	0x61e1
                           0061E2   985 _CSPX	=	0x61e2
                           0061E3   986 _CSPY	=	0x61e3
                           0061E4   987 _CSPZ	=	0x61e4
                           0061E5   988 _CSPT	=	0x61e5
                           006200   989 _USBADDR	=	0x6200
                           006201   990 _USBPOW	=	0x6201
                           006202   991 _USBIIF	=	0x6202
                           006204   992 _USBOIF	=	0x6204
                           006206   993 _USBCIF	=	0x6206
                           006207   994 _USBIIE	=	0x6207
                           006209   995 _USBOIE	=	0x6209
                           00620B   996 _USBCIE	=	0x620b
                           00620C   997 _USBFRML	=	0x620c
                           00620D   998 _USBFRMH	=	0x620d
                           00620E   999 _USBINDEX	=	0x620e
                           00620F  1000 _USBCTRL	=	0x620f
                           006210  1001 _USBMAXI	=	0x6210
                           006211  1002 _USBCS0	=	0x6211
                           006211  1003 _USBCSIL	=	0x6211
                           006212  1004 _USBCSIH	=	0x6212
                           006213  1005 _USBMAXO	=	0x6213
                           006214  1006 _USBCSOL	=	0x6214
                           006215  1007 _USBCSOH	=	0x6215
                           006216  1008 _USBCNT0	=	0x6216
                           006216  1009 _USBCNTL	=	0x6216
                           006217  1010 _USBCNTH	=	0x6217
                           006220  1011 _USBF0	=	0x6220
                           006222  1012 _USBF1	=	0x6222
                           006224  1013 _USBF2	=	0x6224
                           006226  1014 _USBF3	=	0x6226
                           006228  1015 _USBF4	=	0x6228
                           00622A  1016 _USBF5	=	0x622a
                           007080  1017 _X_P0	=	0x7080
                           007086  1018 _X_U0CSR	=	0x7086
                           007089  1019 _X_P0IFG	=	0x7089
                           00708A  1020 _X_P1IFG	=	0x708a
                           00708B  1021 _X_P2IFG	=	0x708b
                           00708C  1022 _X_PICTL	=	0x708c
                           00708D  1023 _X_P1IEN	=	0x708d
                           00708F  1024 _X_P0INP	=	0x708f
                           007090  1025 _X_P1	=	0x7090
                           007091  1026 _X_RFIRQF1	=	0x7091
                           007093  1027 _X_MPAGE	=	0x7093
                           007093  1028 _X__XPAGE	=	0x7093
                           007094  1029 _X_T2CTRL	=	0x7094
                           007095  1030 _X_ST0	=	0x7095
                           007096  1031 _X_ST1	=	0x7096
                           007097  1032 _X_ST2	=	0x7097
                           00709C  1033 _X_T2EVTCFG	=	0x709c
                           00709D  1034 _X_SLEEPSTA	=	0x709d
                           00709E  1035 _X_CLKCONSTA	=	0x709e
                           00709F  1036 _X_FMAP	=	0x709f
                           00709F  1037 _X_PSBANK	=	0x709f
                           0070A0  1038 _X_P2	=	0x70a0
                           0070A1  1039 _X_T2IRQF	=	0x70a1
                           0070A2  1040 _X_T2M0	=	0x70a2
                           0070A3  1041 _X_T2M1	=	0x70a3
                           0070A4  1042 _X_T2MOVF0	=	0x70a4
                           0070A5  1043 _X_T2MOVF1	=	0x70a5
                           0070A6  1044 _X_T2MOVF2	=	0x70a6
                           0070A7  1045 _X_T2IRQM	=	0x70a7
                           0070AB  1046 _X_P0IEN	=	0x70ab
                           0070AC  1047 _X_P2IEN	=	0x70ac
                           0070AD  1048 _X_STLOAD	=	0x70ad
                           0070AE  1049 _X_PMUX	=	0x70ae
                           0070AF  1050 _X_T1STAT	=	0x70af
                           0070B1  1051 _X_ENCDI	=	0x70b1
                           0070B2  1052 _X_ENCDO	=	0x70b2
                           0070B3  1053 _X_ENCCS	=	0x70b3
                           0070B4  1054 _X_ADCCON1	=	0x70b4
                           0070B5  1055 _X_ADCCON2	=	0x70b5
                           0070B6  1056 _X_ADCCON3	=	0x70b6
                           0070BA  1057 _X_ADCL	=	0x70ba
                           0070BB  1058 _X_ADCH	=	0x70bb
                           0070BC  1059 _X_RNDL	=	0x70bc
                           0070BD  1060 _X_RNDH	=	0x70bd
                           0070BE  1061 _X_SLEEPCMD	=	0x70be
                           0070BF  1062 _X_RFERRF	=	0x70bf
                           0070C1  1063 _X_U0DBUF	=	0x70c1
                           0070C2  1064 _X_U0BAUD	=	0x70c2
                           0070C3  1065 _X_T2MSEL	=	0x70c3
                           0070C4  1066 _X_U0UCR	=	0x70c4
                           0070C5  1067 _X_U0GCR	=	0x70c5
                           0070C6  1068 _X_CLKCONCMD	=	0x70c6
                           0070C7  1069 _X_MEMCTR	=	0x70c7
                           0070C9  1070 _X_WDCTL	=	0x70c9
                           0070CA  1071 _X_T3CNT	=	0x70ca
                           0070CB  1072 _X_T3CTL	=	0x70cb
                           0070CC  1073 _X_T3CCTL0	=	0x70cc
                           0070CD  1074 _X_T3CC0	=	0x70cd
                           0070CE  1075 _X_T3CCTL1	=	0x70ce
                           0070CF  1076 _X_T3CC1	=	0x70cf
                           0070D1  1077 _X_DMAIRQ	=	0x70d1
                           0070D2  1078 _X_DMA1CFGL	=	0x70d2
                           0070D3  1079 _X_DMA1CFGH	=	0x70d3
                           0070D4  1080 _X_DMA0CFGL	=	0x70d4
                           0070D5  1081 _X_DMA0CFGH	=	0x70d5
                           0070D6  1082 _X_DMAARM	=	0x70d6
                           0070D7  1083 _X_DMAREQ	=	0x70d7
                           0070D8  1084 _X_TIMIF	=	0x70d8
                           0070D9  1085 _X_RFD	=	0x70d9
                           0070DA  1086 _X_T1CC0L	=	0x70da
                           0070DB  1087 _X_T1CC0H	=	0x70db
                           0070DC  1088 _X_T1CC1L	=	0x70dc
                           0070DD  1089 _X_T1CC1H	=	0x70dd
                           0070DE  1090 _X_T1CC2L	=	0x70de
                           0070DF  1091 _X_T1CC2H	=	0x70df
                           0070E1  1092 _X_RFST	=	0x70e1
                           0070E2  1093 _X_T1CNTL	=	0x70e2
                           0070E3  1094 _X_T1CNTH	=	0x70e3
                           0070E4  1095 _X_T1CTL	=	0x70e4
                           0070E5  1096 _X_T1CCTL0	=	0x70e5
                           0070E6  1097 _X_T1CCTL1	=	0x70e6
                           0070E7  1098 _X_T1CCTL2	=	0x70e7
                           0070E9  1099 _X_RFIRQF0	=	0x70e9
                           0070EA  1100 _X_T4CNT	=	0x70ea
                           0070EB  1101 _X_T4CTL	=	0x70eb
                           0070EC  1102 _X_T4CCTL0	=	0x70ec
                           0070ED  1103 _X_T4CC0	=	0x70ed
                           0070EE  1104 _X_T4CCTL1	=	0x70ee
                           0070EF  1105 _X_T4CC1	=	0x70ef
                           0070F1  1106 _X_PERCFG	=	0x70f1
                           0070F2  1107 _X_APCFG	=	0x70f2
                           0070F3  1108 _X_P0SEL	=	0x70f3
                           0070F4  1109 _X_P1SEL	=	0x70f4
                           0070F5  1110 _X_P2SEL	=	0x70f5
                           0070F6  1111 _X_P1INP	=	0x70f6
                           0070F7  1112 _X_P2INP	=	0x70f7
                           0070F8  1113 _X_U1CSR	=	0x70f8
                           0070F9  1114 _X_U1DBUF	=	0x70f9
                           0070FA  1115 _X_U1BAUD	=	0x70fa
                           0070FB  1116 _X_U1UCR	=	0x70fb
                           0070FC  1117 _X_U1GCR	=	0x70fc
                           0070FD  1118 _X_P0DIR	=	0x70fd
                           0070FE  1119 _X_P1DIR	=	0x70fe
                           0070FF  1120 _X_P2DIR	=	0x70ff
                           007800  1121 _X_INFOPAGE	=	0x7800
                           00780C  1122 _X_IEEE_ADDR	=	0x780c
      000004                       1123 _sensor_data:
      000004                       1124 	.ds 2
      000006                       1125 _SENSORS_EVENT:
      000006                       1126 	.ds 1
      000007                       1127 _process_thread_sensor_process_timer_65536_135:
      000007                       1128 	.ds 10
                                   1129 ;--------------------------------------------------------
                                   1130 ; absolute external ram data
                                   1131 ;--------------------------------------------------------
                                   1132 	.area XABS    (ABS,XDATA)
                                   1133 ;--------------------------------------------------------
                                   1134 ; external initialized ram data
                                   1135 ;--------------------------------------------------------
                                   1136 	.area XISEG   (XDATA)
      001824                       1137 _sensor_temp_buf:
      001824                       1138 	.ds 14
      001832                       1139 _sensor_humidity_buf:
      001832                       1140 	.ds 14
      001840                       1141 _readseq:
      001840                       1142 	.ds 1
      001841                       1143 _sensor_process::
      001841                       1144 	.ds 13
      00184E                       1145 _display_process::
      00184E                       1146 	.ds 13
                                   1147 	.area HOME    (CODE)
                                   1148 	.area GSINIT0 (CODE)
                                   1149 	.area GSINIT1 (CODE)
                                   1150 	.area GSINIT2 (CODE)
                                   1151 	.area GSINIT3 (CODE)
                                   1152 	.area GSINIT4 (CODE)
                                   1153 	.area GSINIT5 (CODE)
                                   1154 	.area GSINIT  (CODE)
                                   1155 	.area GSFINAL (CODE)
                                   1156 	.area CSEG    (CODE)
                                   1157 ;--------------------------------------------------------
                                   1158 ; global & static initialisations
                                   1159 ;--------------------------------------------------------
                                   1160 	.area HOME    (CODE)
                                   1161 	.area GSINIT  (CODE)
                                   1162 	.area GSFINAL (CODE)
                                   1163 	.area GSINIT  (CODE)
                                   1164 ;--------------------------------------------------------
                                   1165 ; Home
                                   1166 ;--------------------------------------------------------
                                   1167 	.area HOME    (CODE)
                                   1168 	.area HOME    (CODE)
                                   1169 ;--------------------------------------------------------
                                   1170 ; code
                                   1171 ;--------------------------------------------------------
                                   1172 	.area BANK1   (CODE)
                                   1173 ;------------------------------------------------------------
                                   1174 ;Allocation info for local variables in function 'process_thread_sensor_process'
                                   1175 ;------------------------------------------------------------
                                   1176 ;ev                        Allocated to stack - sp -3
                                   1177 ;data                      Allocated to stack - sp -6
                                   1178 ;process_pt                Allocated to registers r5 r6 r7 
                                   1179 ;PT_YIELD_FLAG             Allocated to registers r4 
                                   1180 ;timer                     Allocated with name '_process_thread_sensor_process_timer_65536_135'
                                   1181 ;------------------------------------------------------------
                                   1182 ;	Even-post.c:28: PROCESS_THREAD(sensor_process, ev, data)
                                   1183 ;	-----------------------------------------
                                   1184 ;	 function process_thread_sensor_process
                                   1185 ;	-----------------------------------------
      048000                       1186 _process_thread_sensor_process:
                           000007  1187 	ar7 = 0x07
                           000006  1188 	ar6 = 0x06
                           000005  1189 	ar5 = 0x05
                           000004  1190 	ar4 = 0x04
                           000003  1191 	ar3 = 0x03
                           000002  1192 	ar2 = 0x02
                           000001  1193 	ar1 = 0x01
                           000000  1194 	ar0 = 0x00
                                   1195 ;	Even-post.c:32: PROCESS_BEGIN();
      048000 AD 82            [24] 1196 	mov	r5,dpl
      048002 AE 83            [24] 1197 	mov	r6,dph
      048004 AF F0            [24] 1198 	mov	r7,b
      048006 7C 01            [12] 1199 	mov	r4,#0x01
      048008 12 4E 55         [24] 1200 	lcall	__gptrget
      04800B FA               [12] 1201 	mov	r2,a
      04800C A3               [24] 1202 	inc	dptr
      04800D 12 4E 55         [24] 1203 	lcall	__gptrget
      048010 FB               [12] 1204 	mov	r3,a
      048011 BA 00 05         [24] 1205 	cjne	r2,#0x00,00138$
      048014 BB 00 02         [24] 1206 	cjne	r3,#0x00,00138$
      048017 80 0C            [24] 1207 	sjmp	00101$
      048019                       1208 00138$:
      048019 BA 2D 06         [24] 1209 	cjne	r2,#0x2d,00139$
      04801C BB 00 03         [24] 1210 	cjne	r3,#0x00,00139$
      04801F 02 80 B5         [24] 1211 	ljmp	00102$
      048022                       1212 00139$:
      048022 02 81 99         [24] 1213 	ljmp	00115$
      048025                       1214 00101$:
                                   1215 ;	Even-post.c:35: SENSORS_EVENT = process_alloc_event();
      048025 C0 07            [24] 1216 	push	ar7
      048027 C0 06            [24] 1217 	push	ar6
      048029 C0 05            [24] 1218 	push	ar5
      04802B 78 97            [12] 1219 	mov	r0,#_process_alloc_event
      04802D 79 8A            [12] 1220 	mov	r1,#(_process_alloc_event >> 8)
      04802F 7A 03            [12] 1221 	mov	r2,#(_process_alloc_event >> 16)
      048031 12 05 92         [24] 1222 	lcall	__sdcc_banked_call
      048034 AB 82            [24] 1223 	mov	r3,dpl
      048036 90 00 06         [24] 1224 	mov	dptr,#_SENSORS_EVENT
      048039 EB               [12] 1225 	mov	a,r3
      04803A F0               [24] 1226 	movx	@dptr,a
                                   1227 ;	Even-post.c:37: printf("Contiki allocated event ID %d.\r\n", SENSORS_EVENT);
      04803B 7A 00            [12] 1228 	mov	r2,#0x00
      04803D C0 03            [24] 1229 	push	ar3
      04803F C0 02            [24] 1230 	push	ar2
      048041 74 88            [12] 1231 	mov	a,#___str_0
      048043 C0 E0            [24] 1232 	push	acc
      048045 74 73            [12] 1233 	mov	a,#(___str_0 >> 8)
      048047 C0 E0            [24] 1234 	push	acc
      048049 74 80            [12] 1235 	mov	a,#0x80
      04804B C0 E0            [24] 1236 	push	acc
      04804D 78 09            [12] 1237 	mov	r0,#_printf
      04804F 79 4E            [12] 1238 	mov	r1,#(_printf >> 8)
      048051 7A 00            [12] 1239 	mov	r2,#(_printf >> 16)
      048053 12 05 92         [24] 1240 	lcall	__sdcc_banked_call
      048056 E5 81            [12] 1241 	mov	a,sp
      048058 24 FB            [12] 1242 	add	a,#0xfb
      04805A F5 81            [12] 1243 	mov	sp,a
                                   1244 ;	Even-post.c:39: etimer_set(&timer, CLOCK_CONF_SECOND);
      04805C 74 80            [12] 1245 	mov	a,#0x80
      04805E C0 E0            [24] 1246 	push	acc
      048060 E4               [12] 1247 	clr	a
      048061 C0 E0            [24] 1248 	push	acc
      048063 90 00 07         [24] 1249 	mov	dptr,#_process_thread_sensor_process_timer_65536_135
      048066 75 F0 00         [24] 1250 	mov	b,#0x00
      048069 78 0F            [12] 1251 	mov	r0,#_etimer_set
      04806B 79 9B            [12] 1252 	mov	r1,#(_etimer_set >> 8)
      04806D 7A 03            [12] 1253 	mov	r2,#(_etimer_set >> 16)
      04806F 12 05 92         [24] 1254 	lcall	__sdcc_banked_call
      048072 15 81            [12] 1255 	dec	sp
      048074 15 81            [12] 1256 	dec	sp
      048076 D0 05            [24] 1257 	pop	ar5
      048078 D0 06            [24] 1258 	pop	ar6
      04807A D0 07            [24] 1259 	pop	ar7
                                   1260 ;	Even-post.c:41: while(1)
      04807C                       1261 00113$:
                                   1262 ;	Even-post.c:43: printf("Sensor process: Wait for timer event...\r\n");
      04807C C0 07            [24] 1263 	push	ar7
      04807E C0 06            [24] 1264 	push	ar6
      048080 C0 05            [24] 1265 	push	ar5
      048082 74 A9            [12] 1266 	mov	a,#___str_1
      048084 C0 E0            [24] 1267 	push	acc
      048086 74 73            [12] 1268 	mov	a,#(___str_1 >> 8)
      048088 C0 E0            [24] 1269 	push	acc
      04808A 74 80            [12] 1270 	mov	a,#0x80
      04808C C0 E0            [24] 1271 	push	acc
      04808E 78 09            [12] 1272 	mov	r0,#_printf
      048090 79 4E            [12] 1273 	mov	r1,#(_printf >> 8)
      048092 7A 00            [12] 1274 	mov	r2,#(_printf >> 16)
      048094 12 05 92         [24] 1275 	lcall	__sdcc_banked_call
      048097 15 81            [12] 1276 	dec	sp
      048099 15 81            [12] 1277 	dec	sp
      04809B 15 81            [12] 1278 	dec	sp
      04809D D0 05            [24] 1279 	pop	ar5
      04809F D0 06            [24] 1280 	pop	ar6
      0480A1 D0 07            [24] 1281 	pop	ar7
                                   1282 ;	Even-post.c:45: PROCESS_WAIT_EVENT_UNTIL(ev == PROCESS_EVENT_TIMER);
      0480A3 7C 00            [12] 1283 	mov	r4,#0x00
      0480A5 8D 82            [24] 1284 	mov	dpl,r5
      0480A7 8E 83            [24] 1285 	mov	dph,r6
      0480A9 8F F0            [24] 1286 	mov	b,r7
      0480AB 74 2D            [12] 1287 	mov	a,#0x2d
      0480AD 12 49 A6         [24] 1288 	lcall	__gptrput
      0480B0 A3               [24] 1289 	inc	dptr
      0480B1 E4               [12] 1290 	clr	a
      0480B2 12 49 A6         [24] 1291 	lcall	__gptrput
      0480B5                       1292 00102$:
      0480B5 EC               [12] 1293 	mov	a,r4
      0480B6 60 0A            [24] 1294 	jz	00103$
      0480B8 E5 81            [12] 1295 	mov	a,sp
      0480BA 24 FD            [12] 1296 	add	a,#0xfd
      0480BC F8               [12] 1297 	mov	r0,a
      0480BD B6 88 02         [24] 1298 	cjne	@r0,#0x88,00141$
      0480C0 80 06            [24] 1299 	sjmp	00107$
      0480C2                       1300 00141$:
      0480C2                       1301 00103$:
      0480C2 75 82 01         [24] 1302 	mov	dpl,#0x01
      0480C5 02 05 A4         [24] 1303 	ljmp	__sdcc_banked_ret
      0480C8                       1304 00107$:
                                   1305 ;	Even-post.c:47: readseq++;
      0480C8 90 18 40         [24] 1306 	mov	dptr,#_readseq
      0480CB E0               [24] 1307 	movx	a,@dptr
      0480CC 24 01            [12] 1308 	add	a,#0x01
      0480CE F0               [24] 1309 	movx	@dptr,a
                                   1310 ;	Even-post.c:48: if(readseq%2)
      0480CF E0               [24] 1311 	movx	a,@dptr
      0480D0 30 E0 42         [24] 1312 	jnb	acc.0,00110$
                                   1313 ;	Even-post.c:50: printf("humidity read\r\n");
      0480D3 C0 07            [24] 1314 	push	ar7
      0480D5 C0 06            [24] 1315 	push	ar6
      0480D7 C0 05            [24] 1316 	push	ar5
      0480D9 74 D3            [12] 1317 	mov	a,#___str_2
      0480DB C0 E0            [24] 1318 	push	acc
      0480DD 74 73            [12] 1319 	mov	a,#(___str_2 >> 8)
      0480DF C0 E0            [24] 1320 	push	acc
      0480E1 74 80            [12] 1321 	mov	a,#0x80
      0480E3 C0 E0            [24] 1322 	push	acc
      0480E5 78 09            [12] 1323 	mov	r0,#_printf
      0480E7 79 4E            [12] 1324 	mov	r1,#(_printf >> 8)
      0480E9 7A 00            [12] 1325 	mov	r2,#(_printf >> 16)
      0480EB 12 05 92         [24] 1326 	lcall	__sdcc_banked_call
      0480EE 15 81            [12] 1327 	dec	sp
      0480F0 15 81            [12] 1328 	dec	sp
      0480F2 15 81            [12] 1329 	dec	sp
                                   1330 ;	Even-post.c:51: SHT2x_ReadHumi();
      0480F4 78 4C            [12] 1331 	mov	r0,#_SHT2x_ReadHumi
      0480F6 79 A9            [12] 1332 	mov	r1,#(_SHT2x_ReadHumi >> 8)
      0480F8 7A 03            [12] 1333 	mov	r2,#(_SHT2x_ReadHumi >> 16)
      0480FA 12 05 92         [24] 1334 	lcall	__sdcc_banked_call
                                   1335 ;	Even-post.c:52: sensor_data.humidity = (uint8_t)SHT2x_GetHumi();
      0480FD 78 31            [12] 1336 	mov	r0,#_SHT2x_GetHumi
      0480FF 79 A9            [12] 1337 	mov	r1,#(_SHT2x_GetHumi >> 8)
      048101 7A 03            [12] 1338 	mov	r2,#(_SHT2x_GetHumi >> 16)
      048103 12 05 92         [24] 1339 	lcall	__sdcc_banked_call
      048106 AC 82            [24] 1340 	mov	r4,dpl
      048108 D0 05            [24] 1341 	pop	ar5
      04810A D0 06            [24] 1342 	pop	ar6
      04810C D0 07            [24] 1343 	pop	ar7
      04810E 90 00 05         [24] 1344 	mov	dptr,#(_sensor_data + 0x0001)
      048111 EC               [12] 1345 	mov	a,r4
      048112 F0               [24] 1346 	movx	@dptr,a
      048113 80 40            [24] 1347 	sjmp	00111$
      048115                       1348 00110$:
                                   1349 ;	Even-post.c:56: printf("temp read\r\n");
      048115 C0 07            [24] 1350 	push	ar7
      048117 C0 06            [24] 1351 	push	ar6
      048119 C0 05            [24] 1352 	push	ar5
      04811B 74 E3            [12] 1353 	mov	a,#___str_3
      04811D C0 E0            [24] 1354 	push	acc
      04811F 74 73            [12] 1355 	mov	a,#(___str_3 >> 8)
      048121 C0 E0            [24] 1356 	push	acc
      048123 74 80            [12] 1357 	mov	a,#0x80
      048125 C0 E0            [24] 1358 	push	acc
      048127 78 09            [12] 1359 	mov	r0,#_printf
      048129 79 4E            [12] 1360 	mov	r1,#(_printf >> 8)
      04812B 7A 00            [12] 1361 	mov	r2,#(_printf >> 16)
      04812D 12 05 92         [24] 1362 	lcall	__sdcc_banked_call
      048130 15 81            [12] 1363 	dec	sp
      048132 15 81            [12] 1364 	dec	sp
      048134 15 81            [12] 1365 	dec	sp
                                   1366 ;	Even-post.c:57: SHT2x_ReadTemp();
      048136 78 E8            [12] 1367 	mov	r0,#_SHT2x_ReadTemp
      048138 79 A8            [12] 1368 	mov	r1,#(_SHT2x_ReadTemp >> 8)
      04813A 7A 03            [12] 1369 	mov	r2,#(_SHT2x_ReadTemp >> 16)
      04813C 12 05 92         [24] 1370 	lcall	__sdcc_banked_call
                                   1371 ;	Even-post.c:58: sensor_data.temp = (uint8_t)SHT2x_GetTemp();
      04813F 78 CD            [12] 1372 	mov	r0,#_SHT2x_GetTemp
      048141 79 A8            [12] 1373 	mov	r1,#(_SHT2x_GetTemp >> 8)
      048143 7A 03            [12] 1374 	mov	r2,#(_SHT2x_GetTemp >> 16)
      048145 12 05 92         [24] 1375 	lcall	__sdcc_banked_call
      048148 AC 82            [24] 1376 	mov	r4,dpl
      04814A D0 05            [24] 1377 	pop	ar5
      04814C D0 06            [24] 1378 	pop	ar6
      04814E D0 07            [24] 1379 	pop	ar7
      048150 90 00 04         [24] 1380 	mov	dptr,#_sensor_data
      048153 EC               [12] 1381 	mov	a,r4
      048154 F0               [24] 1382 	movx	@dptr,a
      048155                       1383 00111$:
                                   1384 ;	Even-post.c:60: etimer_restart(&timer);
      048155 90 00 07         [24] 1385 	mov	dptr,#_process_thread_sensor_process_timer_65536_135
      048158 75 F0 00         [24] 1386 	mov	b,#0x00
      04815B C0 07            [24] 1387 	push	ar7
      04815D C0 06            [24] 1388 	push	ar6
      04815F C0 05            [24] 1389 	push	ar5
      048161 78 7F            [12] 1390 	mov	r0,#_etimer_restart
      048163 79 9B            [12] 1391 	mov	r1,#(_etimer_restart >> 8)
      048165 7A 03            [12] 1392 	mov	r2,#(_etimer_restart >> 16)
      048167 12 05 92         [24] 1393 	lcall	__sdcc_banked_call
                                   1394 ;	Even-post.c:61: process_post(&display_process, SENSORS_EVENT, (uint8_t*)&sensor_data);
      04816A 74 04            [12] 1395 	mov	a,#_sensor_data
      04816C C0 E0            [24] 1396 	push	acc
      04816E 74 00            [12] 1397 	mov	a,#(_sensor_data >> 8)
      048170 C0 E0            [24] 1398 	push	acc
      048172 E4               [12] 1399 	clr	a
      048173 C0 E0            [24] 1400 	push	acc
      048175 90 00 06         [24] 1401 	mov	dptr,#_SENSORS_EVENT
      048178 E0               [24] 1402 	movx	a,@dptr
      048179 C0 E0            [24] 1403 	push	acc
      04817B 90 18 4E         [24] 1404 	mov	dptr,#_display_process
      04817E 75 F0 00         [24] 1405 	mov	b,#0x00
      048181 78 67            [12] 1406 	mov	r0,#_process_post
      048183 79 92            [12] 1407 	mov	r1,#(_process_post >> 8)
      048185 7A 03            [12] 1408 	mov	r2,#(_process_post >> 16)
      048187 12 05 92         [24] 1409 	lcall	__sdcc_banked_call
      04818A E5 81            [12] 1410 	mov	a,sp
      04818C 24 FC            [12] 1411 	add	a,#0xfc
      04818E F5 81            [12] 1412 	mov	sp,a
      048190 D0 05            [24] 1413 	pop	ar5
      048192 D0 06            [24] 1414 	pop	ar6
      048194 D0 07            [24] 1415 	pop	ar7
      048196 02 80 7C         [24] 1416 	ljmp	00113$
                                   1417 ;	Even-post.c:64: PROCESS_END();
      048199                       1418 00115$:
      048199 8D 82            [24] 1419 	mov	dpl,r5
      04819B 8E 83            [24] 1420 	mov	dph,r6
      04819D 8F F0            [24] 1421 	mov	b,r7
      04819F E4               [12] 1422 	clr	a
      0481A0 12 49 A6         [24] 1423 	lcall	__gptrput
      0481A3 A3               [24] 1424 	inc	dptr
      0481A4 12 49 A6         [24] 1425 	lcall	__gptrput
      0481A7 75 82 03         [24] 1426 	mov	dpl,#0x03
                                   1427 ;	Even-post.c:65: }
      0481AA 02 05 A4         [24] 1428 	ljmp	__sdcc_banked_ret
                                   1429 ;------------------------------------------------------------
                                   1430 ;Allocation info for local variables in function 'process_thread_display_process'
                                   1431 ;------------------------------------------------------------
                                   1432 ;ev                        Allocated to stack - sp -3
                                   1433 ;data                      Allocated to stack - sp -6
                                   1434 ;process_pt                Allocated to registers r5 r6 r7 
                                   1435 ;sd                        Allocated to registers 
                                   1436 ;PT_YIELD_FLAG             Allocated to registers r4 
                                   1437 ;------------------------------------------------------------
                                   1438 ;	Even-post.c:69: PROCESS_THREAD(display_process, ev, data)
                                   1439 ;	-----------------------------------------
                                   1440 ;	 function process_thread_display_process
                                   1441 ;	-----------------------------------------
      0481AD                       1442 _process_thread_display_process:
                                   1443 ;	Even-post.c:74: PROCESS_BEGIN();
      0481AD AD 82            [24] 1444 	mov	r5,dpl
      0481AF AE 83            [24] 1445 	mov	r6,dph
      0481B1 AF F0            [24] 1446 	mov	r7,b
      0481B3 7C 01            [12] 1447 	mov	r4,#0x01
      0481B5 12 4E 55         [24] 1448 	lcall	__gptrget
      0481B8 FA               [12] 1449 	mov	r2,a
      0481B9 A3               [24] 1450 	inc	dptr
      0481BA 12 4E 55         [24] 1451 	lcall	__gptrget
      0481BD FB               [12] 1452 	mov	r3,a
      0481BE BA 00 05         [24] 1453 	cjne	r2,#0x00,00131$
      0481C1 BB 00 02         [24] 1454 	cjne	r3,#0x00,00131$
      0481C4 80 0B            [24] 1455 	sjmp	00101$
      0481C6                       1456 00131$:
      0481C6 BA 50 05         [24] 1457 	cjne	r2,#0x50,00132$
      0481C9 BB 00 02         [24] 1458 	cjne	r3,#0x00,00132$
      0481CC 80 61            [24] 1459 	sjmp	00102$
      0481CE                       1460 00132$:
      0481CE 02 83 44         [24] 1461 	ljmp	00112$
      0481D1                       1462 00101$:
                                   1463 ;	Even-post.c:75: OLED_P8x16Str(0, 0,sensor_temp_buf);
      0481D1 C0 07            [24] 1464 	push	ar7
      0481D3 C0 06            [24] 1465 	push	ar6
      0481D5 C0 05            [24] 1466 	push	ar5
      0481D7 74 24            [12] 1467 	mov	a,#_sensor_temp_buf
      0481D9 C0 E0            [24] 1468 	push	acc
      0481DB 74 18            [12] 1469 	mov	a,#(_sensor_temp_buf >> 8)
      0481DD C0 E0            [24] 1470 	push	acc
      0481DF E4               [12] 1471 	clr	a
      0481E0 C0 E0            [24] 1472 	push	acc
      0481E2 C0 E0            [24] 1473 	push	acc
      0481E4 75 82 00         [24] 1474 	mov	dpl,#0x00
      0481E7 78 59            [12] 1475 	mov	r0,#_OLED_P8x16Str
      0481E9 79 86            [12] 1476 	mov	r1,#(_OLED_P8x16Str >> 8)
      0481EB 7A 03            [12] 1477 	mov	r2,#(_OLED_P8x16Str >> 16)
      0481ED 12 05 92         [24] 1478 	lcall	__sdcc_banked_call
      0481F0 E5 81            [12] 1479 	mov	a,sp
      0481F2 24 FC            [12] 1480 	add	a,#0xfc
      0481F4 F5 81            [12] 1481 	mov	sp,a
                                   1482 ;	Even-post.c:76: OLED_P8x16Str(0, 2,sensor_humidity_buf);
      0481F6 74 32            [12] 1483 	mov	a,#_sensor_humidity_buf
      0481F8 C0 E0            [24] 1484 	push	acc
      0481FA 74 18            [12] 1485 	mov	a,#(_sensor_humidity_buf >> 8)
      0481FC C0 E0            [24] 1486 	push	acc
      0481FE E4               [12] 1487 	clr	a
      0481FF C0 E0            [24] 1488 	push	acc
      048201 74 02            [12] 1489 	mov	a,#0x02
      048203 C0 E0            [24] 1490 	push	acc
      048205 75 82 00         [24] 1491 	mov	dpl,#0x00
      048208 78 59            [12] 1492 	mov	r0,#_OLED_P8x16Str
      04820A 79 86            [12] 1493 	mov	r1,#(_OLED_P8x16Str >> 8)
      04820C 7A 03            [12] 1494 	mov	r2,#(_OLED_P8x16Str >> 16)
      04820E 12 05 92         [24] 1495 	lcall	__sdcc_banked_call
      048211 E5 81            [12] 1496 	mov	a,sp
      048213 24 FC            [12] 1497 	add	a,#0xfc
      048215 F5 81            [12] 1498 	mov	sp,a
      048217 D0 05            [24] 1499 	pop	ar5
      048219 D0 06            [24] 1500 	pop	ar6
      04821B D0 07            [24] 1501 	pop	ar7
                                   1502 ;	Even-post.c:77: while(1)
      04821D                       1503 00110$:
                                   1504 ;	Even-post.c:80: PROCESS_WAIT_EVENT_UNTIL(ev == SENSORS_EVENT);
      04821D 7C 00            [12] 1505 	mov	r4,#0x00
      04821F 8D 82            [24] 1506 	mov	dpl,r5
      048221 8E 83            [24] 1507 	mov	dph,r6
      048223 8F F0            [24] 1508 	mov	b,r7
      048225 74 50            [12] 1509 	mov	a,#0x50
      048227 12 49 A6         [24] 1510 	lcall	__gptrput
      04822A A3               [24] 1511 	inc	dptr
      04822B E4               [12] 1512 	clr	a
      04822C 12 49 A6         [24] 1513 	lcall	__gptrput
      04822F                       1514 00102$:
      04822F EC               [12] 1515 	mov	a,r4
      048230 60 10            [24] 1516 	jz	00103$
      048232 90 00 06         [24] 1517 	mov	dptr,#_SENSORS_EVENT
      048235 E0               [24] 1518 	movx	a,@dptr
      048236 FC               [12] 1519 	mov	r4,a
      048237 E5 81            [12] 1520 	mov	a,sp
      048239 24 FD            [12] 1521 	add	a,#0xfd
      04823B F8               [12] 1522 	mov	r0,a
      04823C E6               [12] 1523 	mov	a,@r0
      04823D B5 04 02         [24] 1524 	cjne	a,ar4,00134$
      048240 80 06            [24] 1525 	sjmp	00107$
      048242                       1526 00134$:
      048242                       1527 00103$:
      048242 75 82 01         [24] 1528 	mov	dpl,#0x01
      048245 02 05 A4         [24] 1529 	ljmp	__sdcc_banked_ret
      048248                       1530 00107$:
                                   1531 ;	Even-post.c:82: printf("Print Process - Data Ready:\r\n");
      048248 C0 07            [24] 1532 	push	ar7
      04824A C0 06            [24] 1533 	push	ar6
      04824C C0 05            [24] 1534 	push	ar5
      04824E 74 EF            [12] 1535 	mov	a,#___str_4
      048250 C0 E0            [24] 1536 	push	acc
      048252 74 73            [12] 1537 	mov	a,#(___str_4 >> 8)
      048254 C0 E0            [24] 1538 	push	acc
      048256 74 80            [12] 1539 	mov	a,#0x80
      048258 C0 E0            [24] 1540 	push	acc
      04825A 78 09            [12] 1541 	mov	r0,#_printf
      04825C 79 4E            [12] 1542 	mov	r1,#(_printf >> 8)
      04825E 7A 00            [12] 1543 	mov	r2,#(_printf >> 16)
      048260 12 05 92         [24] 1544 	lcall	__sdcc_banked_call
      048263 15 81            [12] 1545 	dec	sp
      048265 15 81            [12] 1546 	dec	sp
      048267 15 81            [12] 1547 	dec	sp
                                   1548 ;	Even-post.c:84: sensor_temp_buf[5] = sensor_data.temp/10+0x30;
      048269 90 00 04         [24] 1549 	mov	dptr,#_sensor_data
      04826C E0               [24] 1550 	movx	a,@dptr
      04826D FC               [12] 1551 	mov	r4,a
      04826E 7B 00            [12] 1552 	mov	r3,#0x00
      048270 74 0A            [12] 1553 	mov	a,#0x0a
      048272 C0 E0            [24] 1554 	push	acc
      048274 E4               [12] 1555 	clr	a
      048275 C0 E0            [24] 1556 	push	acc
      048277 8C 82            [24] 1557 	mov	dpl,r4
      048279 8B 83            [24] 1558 	mov	dph,r3
      04827B 12 51 36         [24] 1559 	lcall	__divsint
      04827E AB 82            [24] 1560 	mov	r3,dpl
      048280 15 81            [12] 1561 	dec	sp
      048282 15 81            [12] 1562 	dec	sp
      048284 74 30            [12] 1563 	mov	a,#0x30
      048286 2B               [12] 1564 	add	a,r3
      048287 90 18 29         [24] 1565 	mov	dptr,#(_sensor_temp_buf + 0x0005)
      04828A F0               [24] 1566 	movx	@dptr,a
                                   1567 ;	Even-post.c:85: sensor_temp_buf[6] = sensor_data.temp%10+0x30;
      04828B 90 00 04         [24] 1568 	mov	dptr,#_sensor_data
      04828E E0               [24] 1569 	movx	a,@dptr
      04828F FC               [12] 1570 	mov	r4,a
      048290 7B 00            [12] 1571 	mov	r3,#0x00
      048292 74 0A            [12] 1572 	mov	a,#0x0a
      048294 C0 E0            [24] 1573 	push	acc
      048296 E4               [12] 1574 	clr	a
      048297 C0 E0            [24] 1575 	push	acc
      048299 8C 82            [24] 1576 	mov	dpl,r4
      04829B 8B 83            [24] 1577 	mov	dph,r3
      04829D 12 50 36         [24] 1578 	lcall	__modsint
      0482A0 AB 82            [24] 1579 	mov	r3,dpl
      0482A2 15 81            [12] 1580 	dec	sp
      0482A4 15 81            [12] 1581 	dec	sp
      0482A6 74 30            [12] 1582 	mov	a,#0x30
      0482A8 2B               [12] 1583 	add	a,r3
      0482A9 90 18 2A         [24] 1584 	mov	dptr,#(_sensor_temp_buf + 0x0006)
      0482AC F0               [24] 1585 	movx	@dptr,a
                                   1586 ;	Even-post.c:86: sensor_temp_buf[7] = 0;
      0482AD 90 18 2B         [24] 1587 	mov	dptr,#(_sensor_temp_buf + 0x0007)
      0482B0 E4               [12] 1588 	clr	a
      0482B1 F0               [24] 1589 	movx	@dptr,a
                                   1590 ;	Even-post.c:87: OLED_P8x16Str(0, 0,sensor_temp_buf);
      0482B2 74 24            [12] 1591 	mov	a,#_sensor_temp_buf
      0482B4 C0 E0            [24] 1592 	push	acc
      0482B6 74 18            [12] 1593 	mov	a,#(_sensor_temp_buf >> 8)
      0482B8 C0 E0            [24] 1594 	push	acc
      0482BA E4               [12] 1595 	clr	a
      0482BB C0 E0            [24] 1596 	push	acc
      0482BD C0 E0            [24] 1597 	push	acc
      0482BF 75 82 00         [24] 1598 	mov	dpl,#0x00
      0482C2 78 59            [12] 1599 	mov	r0,#_OLED_P8x16Str
      0482C4 79 86            [12] 1600 	mov	r1,#(_OLED_P8x16Str >> 8)
      0482C6 7A 03            [12] 1601 	mov	r2,#(_OLED_P8x16Str >> 16)
      0482C8 12 05 92         [24] 1602 	lcall	__sdcc_banked_call
      0482CB E5 81            [12] 1603 	mov	a,sp
      0482CD 24 FC            [12] 1604 	add	a,#0xfc
      0482CF F5 81            [12] 1605 	mov	sp,a
                                   1606 ;	Even-post.c:89: sensor_humidity_buf[9] = sensor_data.humidity/10+0x30;
      0482D1 90 00 05         [24] 1607 	mov	dptr,#(_sensor_data + 0x0001)
      0482D4 E0               [24] 1608 	movx	a,@dptr
      0482D5 FC               [12] 1609 	mov	r4,a
      0482D6 7B 00            [12] 1610 	mov	r3,#0x00
      0482D8 74 0A            [12] 1611 	mov	a,#0x0a
      0482DA C0 E0            [24] 1612 	push	acc
      0482DC E4               [12] 1613 	clr	a
      0482DD C0 E0            [24] 1614 	push	acc
      0482DF 8C 82            [24] 1615 	mov	dpl,r4
      0482E1 8B 83            [24] 1616 	mov	dph,r3
      0482E3 12 51 36         [24] 1617 	lcall	__divsint
      0482E6 AB 82            [24] 1618 	mov	r3,dpl
      0482E8 15 81            [12] 1619 	dec	sp
      0482EA 15 81            [12] 1620 	dec	sp
      0482EC 74 30            [12] 1621 	mov	a,#0x30
      0482EE 2B               [12] 1622 	add	a,r3
      0482EF 90 18 3B         [24] 1623 	mov	dptr,#(_sensor_humidity_buf + 0x0009)
      0482F2 F0               [24] 1624 	movx	@dptr,a
                                   1625 ;	Even-post.c:90: sensor_humidity_buf[10] = sensor_data.humidity%10+0x30;
      0482F3 90 00 05         [24] 1626 	mov	dptr,#(_sensor_data + 0x0001)
      0482F6 E0               [24] 1627 	movx	a,@dptr
      0482F7 FC               [12] 1628 	mov	r4,a
      0482F8 7B 00            [12] 1629 	mov	r3,#0x00
      0482FA 74 0A            [12] 1630 	mov	a,#0x0a
      0482FC C0 E0            [24] 1631 	push	acc
      0482FE E4               [12] 1632 	clr	a
      0482FF C0 E0            [24] 1633 	push	acc
      048301 8C 82            [24] 1634 	mov	dpl,r4
      048303 8B 83            [24] 1635 	mov	dph,r3
      048305 12 50 36         [24] 1636 	lcall	__modsint
      048308 AB 82            [24] 1637 	mov	r3,dpl
      04830A 15 81            [12] 1638 	dec	sp
      04830C 15 81            [12] 1639 	dec	sp
      04830E 74 30            [12] 1640 	mov	a,#0x30
      048310 2B               [12] 1641 	add	a,r3
      048311 90 18 3C         [24] 1642 	mov	dptr,#(_sensor_humidity_buf + 0x000a)
      048314 F0               [24] 1643 	movx	@dptr,a
                                   1644 ;	Even-post.c:91: sensor_humidity_buf[11] = 0;		
      048315 90 18 3D         [24] 1645 	mov	dptr,#(_sensor_humidity_buf + 0x000b)
      048318 E4               [12] 1646 	clr	a
      048319 F0               [24] 1647 	movx	@dptr,a
                                   1648 ;	Even-post.c:92: OLED_P8x16Str(0, 2,sensor_humidity_buf);
      04831A 74 32            [12] 1649 	mov	a,#_sensor_humidity_buf
      04831C C0 E0            [24] 1650 	push	acc
      04831E 74 18            [12] 1651 	mov	a,#(_sensor_humidity_buf >> 8)
      048320 C0 E0            [24] 1652 	push	acc
      048322 E4               [12] 1653 	clr	a
      048323 C0 E0            [24] 1654 	push	acc
      048325 74 02            [12] 1655 	mov	a,#0x02
      048327 C0 E0            [24] 1656 	push	acc
      048329 75 82 00         [24] 1657 	mov	dpl,#0x00
      04832C 78 59            [12] 1658 	mov	r0,#_OLED_P8x16Str
      04832E 79 86            [12] 1659 	mov	r1,#(_OLED_P8x16Str >> 8)
      048330 7A 03            [12] 1660 	mov	r2,#(_OLED_P8x16Str >> 16)
      048332 12 05 92         [24] 1661 	lcall	__sdcc_banked_call
      048335 E5 81            [12] 1662 	mov	a,sp
      048337 24 FC            [12] 1663 	add	a,#0xfc
      048339 F5 81            [12] 1664 	mov	sp,a
      04833B D0 05            [24] 1665 	pop	ar5
      04833D D0 06            [24] 1666 	pop	ar6
      04833F D0 07            [24] 1667 	pop	ar7
      048341 02 82 1D         [24] 1668 	ljmp	00110$
                                   1669 ;	Even-post.c:96: PROCESS_END();
      048344                       1670 00112$:
      048344 8D 82            [24] 1671 	mov	dpl,r5
      048346 8E 83            [24] 1672 	mov	dph,r6
      048348 8F F0            [24] 1673 	mov	b,r7
      04834A E4               [12] 1674 	clr	a
      04834B 12 49 A6         [24] 1675 	lcall	__gptrput
      04834E A3               [24] 1676 	inc	dptr
      04834F 12 49 A6         [24] 1677 	lcall	__gptrput
      048352 75 82 03         [24] 1678 	mov	dpl,#0x03
                                   1679 ;	Even-post.c:97: }
      048355 02 05 A4         [24] 1680 	ljmp	__sdcc_banked_ret
                                   1681 	.area CSEG    (CODE)
                                   1682 	.area CONST   (CODE)
      00737F                       1683 _autostart_processes:
      00737F 41 18 00              1684 	.byte _sensor_process, (_sensor_process >> 8),#0x00
      007382 4E 18 00              1685 	.byte _display_process, (_display_process >> 8),#0x00
                                   1686 ; generic printIvalPtr
      007385 00 00 00              1687 	.byte #0x00,#0x00,#0x00
      007388                       1688 ___str_0:
      007388 43 6F 6E 74 69 6B 69  1689 	.ascii "Contiki allocated event ID %d."
             20 61 6C 6C 6F 63 61
             74 65 64 20 65 76 65
             6E 74 20 49 44 20 25
             64 2E
      0073A6 0D                    1690 	.db 0x0d
      0073A7 0A                    1691 	.db 0x0a
      0073A8 00                    1692 	.db 0x00
      0073A9                       1693 ___str_1:
      0073A9 53 65 6E 73 6F 72 20  1694 	.ascii "Sensor process: Wait for timer event..."
             70 72 6F 63 65 73 73
             3A 20 57 61 69 74 20
             66 6F 72 20 74 69 6D
             65 72 20 65 76 65 6E
             74 2E 2E 2E
      0073D0 0D                    1695 	.db 0x0d
      0073D1 0A                    1696 	.db 0x0a
      0073D2 00                    1697 	.db 0x00
      0073D3                       1698 ___str_2:
      0073D3 68 75 6D 69 64 69 74  1699 	.ascii "humidity read"
             79 20 72 65 61 64
      0073E0 0D                    1700 	.db 0x0d
      0073E1 0A                    1701 	.db 0x0a
      0073E2 00                    1702 	.db 0x00
      0073E3                       1703 ___str_3:
      0073E3 74 65 6D 70 20 72 65  1704 	.ascii "temp read"
             61 64
      0073EC 0D                    1705 	.db 0x0d
      0073ED 0A                    1706 	.db 0x0a
      0073EE 00                    1707 	.db 0x00
      0073EF                       1708 ___str_4:
      0073EF 50 72 69 6E 74 20 50  1709 	.ascii "Print Process - Data Ready:"
             72 6F 63 65 73 73 20
             2D 20 44 61 74 61 20
             52 65 61 64 79 3A
      00740A 0D                    1710 	.db 0x0d
      00740B 0A                    1711 	.db 0x0a
      00740C 00                    1712 	.db 0x00
      00740D                       1713 ___str_9:
      00740D 53 65 6E 73 6F 72 20  1714 	.ascii "Sensor process"
             70 72 6F 63 65 73 73
      00741B 00                    1715 	.db 0x00
      00741C                       1716 ___str_10:
      00741C 50 72 69 6E 74 20 70  1717 	.ascii "Print process"
             72 6F 63 65 73 73
      007429 00                    1718 	.db 0x00
                                   1719 	.area XINIT   (CODE)
      007E13                       1720 __xinit__sensor_temp_buf:
      007E13 74 65 6D 70 3A 78 78  1721 	.ascii "temp:xx"
      007E1A 00                    1722 	.db 0x00
      007E1B 00                    1723 	.db 0x00
      007E1C 00                    1724 	.db 0x00
      007E1D 00                    1725 	.db 0x00
      007E1E 00                    1726 	.db 0x00
      007E1F 00                    1727 	.db 0x00
      007E20 00                    1728 	.db 0x00
      007E21                       1729 __xinit__sensor_humidity_buf:
      007E21 68 75 6D 69 64 69 74  1730 	.ascii "humidity:xx"
             79 3A 78 78
      007E2C 00                    1731 	.db 0x00
      007E2D 00                    1732 	.db 0x00
      007E2E 00                    1733 	.db 0x00
      007E2F                       1734 __xinit__readseq:
      007E2F 00                    1735 	.db #0x00	; 0
      007E30                       1736 __xinit__sensor_process:
                                   1737 ; generic printIvalPtr
      007E30 00 00 00              1738 	.byte #0x00,#0x00,#0x00
      007E33 0D 74 80              1739 	.byte ___str_9, (___str_9 >> 8),#0x80
      007E36 00 80 04              1740 	.byte _process_thread_sensor_process, (_process_thread_sensor_process >> 8), (_process_thread_sensor_process >> 16)
      007E39 00 00                 1741 	.byte #0x00, #0x00
      007E3B 00                    1742 	.db #0x00	; 0
      007E3C 00                    1743 	.db #0x00	; 0
      007E3D                       1744 __xinit__display_process:
                                   1745 ; generic printIvalPtr
      007E3D 00 00 00              1746 	.byte #0x00,#0x00,#0x00
      007E40 1C 74 80              1747 	.byte ___str_10, (___str_10 >> 8),#0x80
      007E43 AD 81 04              1748 	.byte _process_thread_display_process, (_process_thread_display_process >> 8), (_process_thread_display_process >> 16)
      007E46 00 00                 1749 	.byte #0x00, #0x00
      007E48 00                    1750 	.db #0x00	; 0
      007E49 00                    1751 	.db #0x00	; 0
                                   1752 	.area CABS    (ABS,CODE)
