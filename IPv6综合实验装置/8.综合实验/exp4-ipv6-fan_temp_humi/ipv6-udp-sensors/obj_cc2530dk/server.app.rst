                                      1 ;--------------------------------------------------------
                                      2 ; File Created by SDCC : free open source ANSI-C Compiler
                                      3 ; Version 3.8.4 #10774 (Linux)
                                      4 ;--------------------------------------------------------
                                      5 	.module server
                                      6 	.optsdcc -mmcs51 --model-huge
                                      7 	
                                      8 ;--------------------------------------------------------
                                      9 ; Public variables in this module
                                     10 ;--------------------------------------------------------
                                     11 	.globl _autostart_processes
                                     12 	.globl _OLED_P8x16Str
                                     13 	.globl _printf
                                     14 	.globl _udp_new
                                     15 	.globl ___memcpy
                                     16 	.globl _memset
                                     17 	.globl _ACTIVE
                                     18 	.globl _TX_BYTE
                                     19 	.globl _RX_BYTE
                                     20 	.globl _ERR
                                     21 	.globl _FE
                                     22 	.globl _SLAVE
                                     23 	.globl _RE
                                     24 	.globl _MODE
                                     25 	.globl _T3OVFIF
                                     26 	.globl _T3CH0IF
                                     27 	.globl _T3CH1IF
                                     28 	.globl _T4OVFIF
                                     29 	.globl _T4CH0IF
                                     30 	.globl _T4CH1IF
                                     31 	.globl _OVFIM
                                     32 	.globl _B_0
                                     33 	.globl _B_1
                                     34 	.globl _B_2
                                     35 	.globl _B_3
                                     36 	.globl _B_4
                                     37 	.globl _B_5
                                     38 	.globl _B_6
                                     39 	.globl _B_7
                                     40 	.globl _P2IF
                                     41 	.globl _UTX0IF
                                     42 	.globl _UTX1IF
                                     43 	.globl _P1IF
                                     44 	.globl _WDTIF
                                     45 	.globl _ACC_0
                                     46 	.globl _ACC_1
                                     47 	.globl _ACC_2
                                     48 	.globl _ACC_3
                                     49 	.globl _ACC_4
                                     50 	.globl _ACC_5
                                     51 	.globl _ACC_6
                                     52 	.globl _ACC_7
                                     53 	.globl _P
                                     54 	.globl _F1
                                     55 	.globl _OV
                                     56 	.globl _RS0
                                     57 	.globl _RS1
                                     58 	.globl _F0
                                     59 	.globl _AC
                                     60 	.globl _CY
                                     61 	.globl _DMAIF
                                     62 	.globl _T1IF
                                     63 	.globl _T2IF
                                     64 	.globl _T3IF
                                     65 	.globl _T4IF
                                     66 	.globl _P0IF
                                     67 	.globl _STIF
                                     68 	.globl _DMAIE
                                     69 	.globl _T1IE
                                     70 	.globl _T2IE
                                     71 	.globl _T3IE
                                     72 	.globl _T4IE
                                     73 	.globl _P0IE
                                     74 	.globl _RFERRIE
                                     75 	.globl _ADCIE
                                     76 	.globl _URX0IE
                                     77 	.globl _URX1IE
                                     78 	.globl _ENCIE
                                     79 	.globl _STIE
                                     80 	.globl _EA
                                     81 	.globl _P2_0
                                     82 	.globl _P2_1
                                     83 	.globl _P2_2
                                     84 	.globl _P2_3
                                     85 	.globl _P2_4
                                     86 	.globl _P2_5
                                     87 	.globl _P2_6
                                     88 	.globl _P2_7
                                     89 	.globl _ENCIF_0
                                     90 	.globl _ENCIF_1
                                     91 	.globl _P1_0
                                     92 	.globl _P1_1
                                     93 	.globl _P1_2
                                     94 	.globl _P1_3
                                     95 	.globl _P1_4
                                     96 	.globl _P1_5
                                     97 	.globl _P1_6
                                     98 	.globl _P1_7
                                     99 	.globl _IT0
                                    100 	.globl _RFERRIF
                                    101 	.globl _IT1
                                    102 	.globl _URX0IF
                                    103 	.globl _ADCIF
                                    104 	.globl _URX1IF
                                    105 	.globl _P0_0
                                    106 	.globl _P0_1
                                    107 	.globl _P0_2
                                    108 	.globl _P0_3
                                    109 	.globl _P0_4
                                    110 	.globl _P0_5
                                    111 	.globl _P0_6
                                    112 	.globl _P0_7
                                    113 	.globl _WDCTL
                                    114 	.globl _U1GCR
                                    115 	.globl _U1UCR
                                    116 	.globl _U1BAUD
                                    117 	.globl _U1DBUF
                                    118 	.globl _U1CSR
                                    119 	.globl _U0GCR
                                    120 	.globl _U0UCR
                                    121 	.globl _U0BAUD
                                    122 	.globl _U0DBUF
                                    123 	.globl _U0CSR
                                    124 	.globl _TIMIF
                                    125 	.globl _T4CC1
                                    126 	.globl _T4CCTL1
                                    127 	.globl _T4CC0
                                    128 	.globl _T4CCTL0
                                    129 	.globl _T4CTL
                                    130 	.globl _T4CNT
                                    131 	.globl _T3CC1
                                    132 	.globl _T3CCTL1
                                    133 	.globl _T3CC0
                                    134 	.globl _T3CCTL0
                                    135 	.globl _T3CTL
                                    136 	.globl _T3CNT
                                    137 	.globl _T2MSEL
                                    138 	.globl _T2IRQM
                                    139 	.globl _T2MOVF2
                                    140 	.globl _T2MOVF1
                                    141 	.globl _T2MOVF0
                                    142 	.globl _T2M1
                                    143 	.globl _T2M0
                                    144 	.globl _T2IRQF
                                    145 	.globl _T2EVTCFG
                                    146 	.globl _T2CTRL
                                    147 	.globl _T1STAT
                                    148 	.globl _T1CCTL2
                                    149 	.globl _T1CCTL1
                                    150 	.globl _T1CCTL0
                                    151 	.globl _T1CTL
                                    152 	.globl _T1CNTH
                                    153 	.globl _T1CNTL
                                    154 	.globl _T1CC2H
                                    155 	.globl _T1CC2L
                                    156 	.globl _T1CC1H
                                    157 	.globl _T1CC1L
                                    158 	.globl _T1CC0H
                                    159 	.globl _T1CC0L
                                    160 	.globl _CLKCONSTA
                                    161 	.globl _CLKCONCMD
                                    162 	.globl _SLEEPSTA
                                    163 	.globl _SLEEPCMD
                                    164 	.globl _STLOAD
                                    165 	.globl _ST2
                                    166 	.globl _ST1
                                    167 	.globl _ST0
                                    168 	.globl _RFERRF
                                    169 	.globl _RFIRQF0
                                    170 	.globl _RFST
                                    171 	.globl _RFD
                                    172 	.globl _RFIRQF1
                                    173 	.globl _PSBANK
                                    174 	.globl _FMAP
                                    175 	.globl _MEMCTR
                                    176 	.globl __XPAGE
                                    177 	.globl _MPAGE
                                    178 	.globl _PMUX
                                    179 	.globl _P2DIR
                                    180 	.globl _P1DIR
                                    181 	.globl _P0DIR
                                    182 	.globl _P2INP
                                    183 	.globl _P1INP
                                    184 	.globl _P2SEL
                                    185 	.globl _P1SEL
                                    186 	.globl _P0SEL
                                    187 	.globl _APCFG
                                    188 	.globl _PERCFG
                                    189 	.globl _P0INP
                                    190 	.globl _P2IEN
                                    191 	.globl _P1IEN
                                    192 	.globl _P0IEN
                                    193 	.globl _PICTL
                                    194 	.globl _P2IFG
                                    195 	.globl _P1IFG
                                    196 	.globl _P0IFG
                                    197 	.globl _DMAREQ
                                    198 	.globl _DMAARM
                                    199 	.globl _DMA0CFGH
                                    200 	.globl _DMA0CFGL
                                    201 	.globl _DMA1CFGH
                                    202 	.globl _DMA1CFGL
                                    203 	.globl _DMAIRQ
                                    204 	.globl _ENCCS
                                    205 	.globl _ENCDO
                                    206 	.globl _ENCDI
                                    207 	.globl _RNDH
                                    208 	.globl _RNDL
                                    209 	.globl _ADCH
                                    210 	.globl _ADCL
                                    211 	.globl _ADCCON3
                                    212 	.globl _ADCCON2
                                    213 	.globl _ADCCON1
                                    214 	.globl _B
                                    215 	.globl _IRCON2
                                    216 	.globl _ACC
                                    217 	.globl _PSW
                                    218 	.globl _IRCON
                                    219 	.globl _IP1
                                    220 	.globl _IEN1
                                    221 	.globl _IP0
                                    222 	.globl _IEN0
                                    223 	.globl _P2
                                    224 	.globl _S1CON
                                    225 	.globl _IEN2
                                    226 	.globl _S0CON
                                    227 	.globl _DPS
                                    228 	.globl _P1
                                    229 	.globl _TCON
                                    230 	.globl _PCON
                                    231 	.globl _DPH1
                                    232 	.globl _DPL1
                                    233 	.globl _DPH0
                                    234 	.globl _DPL0
                                    235 	.globl _SP
                                    236 	.globl _P0
                                    237 	.globl _udp_server_process
                                    238 	.globl _vibra
                                    239 	.globl _optoc_smoke
                                    240 	.globl _TempHumidity
                                    241 	.globl _atmophere_press
                                    242 	.globl _sensor_flag
                                    243 	.globl _i
                                    244 	.globl _ptr
                                    245 	.globl _temp
                                    246 	.globl _u32_data
                                    247 	.globl _X_IEEE_ADDR
                                    248 	.globl _X_INFOPAGE
                                    249 	.globl _X_P2DIR
                                    250 	.globl _X_P1DIR
                                    251 	.globl _X_P0DIR
                                    252 	.globl _X_U1GCR
                                    253 	.globl _X_U1UCR
                                    254 	.globl _X_U1BAUD
                                    255 	.globl _X_U1DBUF
                                    256 	.globl _X_U1CSR
                                    257 	.globl _X_P2INP
                                    258 	.globl _X_P1INP
                                    259 	.globl _X_P2SEL
                                    260 	.globl _X_P1SEL
                                    261 	.globl _X_P0SEL
                                    262 	.globl _X_APCFG
                                    263 	.globl _X_PERCFG
                                    264 	.globl _X_T4CC1
                                    265 	.globl _X_T4CCTL1
                                    266 	.globl _X_T4CC0
                                    267 	.globl _X_T4CCTL0
                                    268 	.globl _X_T4CTL
                                    269 	.globl _X_T4CNT
                                    270 	.globl _X_RFIRQF0
                                    271 	.globl _X_T1CCTL2
                                    272 	.globl _X_T1CCTL1
                                    273 	.globl _X_T1CCTL0
                                    274 	.globl _X_T1CTL
                                    275 	.globl _X_T1CNTH
                                    276 	.globl _X_T1CNTL
                                    277 	.globl _X_RFST
                                    278 	.globl _X_T1CC2H
                                    279 	.globl _X_T1CC2L
                                    280 	.globl _X_T1CC1H
                                    281 	.globl _X_T1CC1L
                                    282 	.globl _X_T1CC0H
                                    283 	.globl _X_T1CC0L
                                    284 	.globl _X_RFD
                                    285 	.globl _X_TIMIF
                                    286 	.globl _X_DMAREQ
                                    287 	.globl _X_DMAARM
                                    288 	.globl _X_DMA0CFGH
                                    289 	.globl _X_DMA0CFGL
                                    290 	.globl _X_DMA1CFGH
                                    291 	.globl _X_DMA1CFGL
                                    292 	.globl _X_DMAIRQ
                                    293 	.globl _X_T3CC1
                                    294 	.globl _X_T3CCTL1
                                    295 	.globl _X_T3CC0
                                    296 	.globl _X_T3CCTL0
                                    297 	.globl _X_T3CTL
                                    298 	.globl _X_T3CNT
                                    299 	.globl _X_WDCTL
                                    300 	.globl _X_MEMCTR
                                    301 	.globl _X_CLKCONCMD
                                    302 	.globl _X_U0GCR
                                    303 	.globl _X_U0UCR
                                    304 	.globl _X_T2MSEL
                                    305 	.globl _X_U0BAUD
                                    306 	.globl _X_U0DBUF
                                    307 	.globl _X_RFERRF
                                    308 	.globl _X_SLEEPCMD
                                    309 	.globl _X_RNDH
                                    310 	.globl _X_RNDL
                                    311 	.globl _X_ADCH
                                    312 	.globl _X_ADCL
                                    313 	.globl _X_ADCCON3
                                    314 	.globl _X_ADCCON2
                                    315 	.globl _X_ADCCON1
                                    316 	.globl _X_ENCCS
                                    317 	.globl _X_ENCDO
                                    318 	.globl _X_ENCDI
                                    319 	.globl _X_T1STAT
                                    320 	.globl _X_PMUX
                                    321 	.globl _X_STLOAD
                                    322 	.globl _X_P2IEN
                                    323 	.globl _X_P0IEN
                                    324 	.globl _X_T2IRQM
                                    325 	.globl _X_T2MOVF2
                                    326 	.globl _X_T2MOVF1
                                    327 	.globl _X_T2MOVF0
                                    328 	.globl _X_T2M1
                                    329 	.globl _X_T2M0
                                    330 	.globl _X_T2IRQF
                                    331 	.globl _X_P2
                                    332 	.globl _X_PSBANK
                                    333 	.globl _X_FMAP
                                    334 	.globl _X_CLKCONSTA
                                    335 	.globl _X_SLEEPSTA
                                    336 	.globl _X_T2EVTCFG
                                    337 	.globl _X_ST2
                                    338 	.globl _X_ST1
                                    339 	.globl _X_ST0
                                    340 	.globl _X_T2CTRL
                                    341 	.globl _X__XPAGE
                                    342 	.globl _X_MPAGE
                                    343 	.globl _X_RFIRQF1
                                    344 	.globl _X_P1
                                    345 	.globl _X_P0INP
                                    346 	.globl _X_P1IEN
                                    347 	.globl _X_PICTL
                                    348 	.globl _X_P2IFG
                                    349 	.globl _X_P1IFG
                                    350 	.globl _X_P0IFG
                                    351 	.globl _X_U0CSR
                                    352 	.globl _X_P0
                                    353 	.globl _USBF5
                                    354 	.globl _USBF4
                                    355 	.globl _USBF3
                                    356 	.globl _USBF2
                                    357 	.globl _USBF1
                                    358 	.globl _USBF0
                                    359 	.globl _USBCNTH
                                    360 	.globl _USBCNTL
                                    361 	.globl _USBCNT0
                                    362 	.globl _USBCSOH
                                    363 	.globl _USBCSOL
                                    364 	.globl _USBMAXO
                                    365 	.globl _USBCSIH
                                    366 	.globl _USBCSIL
                                    367 	.globl _USBCS0
                                    368 	.globl _USBMAXI
                                    369 	.globl _USBCTRL
                                    370 	.globl _USBINDEX
                                    371 	.globl _USBFRMH
                                    372 	.globl _USBFRML
                                    373 	.globl _USBCIE
                                    374 	.globl _USBOIE
                                    375 	.globl _USBIIE
                                    376 	.globl _USBCIF
                                    377 	.globl _USBOIF
                                    378 	.globl _USBIIF
                                    379 	.globl _USBPOW
                                    380 	.globl _USBADDR
                                    381 	.globl _CSPT
                                    382 	.globl _CSPZ
                                    383 	.globl _CSPY
                                    384 	.globl _CSPX
                                    385 	.globl _CSPSTAT
                                    386 	.globl _CSPCTRL
                                    387 	.globl _CSPPROG23
                                    388 	.globl _CSPPROG22
                                    389 	.globl _CSPPROG21
                                    390 	.globl _CSPPROG20
                                    391 	.globl _CSPPROG19
                                    392 	.globl _CSPPROG18
                                    393 	.globl _CSPPROG17
                                    394 	.globl _CSPPROG16
                                    395 	.globl _CSPPROG15
                                    396 	.globl _CSPPROG14
                                    397 	.globl _CSPPROG13
                                    398 	.globl _CSPPROG12
                                    399 	.globl _CSPPROG11
                                    400 	.globl _CSPPROG10
                                    401 	.globl _CSPPROG9
                                    402 	.globl _CSPPROG8
                                    403 	.globl _CSPPROG7
                                    404 	.globl _CSPPROG6
                                    405 	.globl _CSPPROG5
                                    406 	.globl _CSPPROG4
                                    407 	.globl _CSPPROG3
                                    408 	.globl _CSPPROG2
                                    409 	.globl _CSPPROG1
                                    410 	.globl _CSPPROG0
                                    411 	.globl _RFC_OBS_CTRL2
                                    412 	.globl _RFC_OBS_CTRL1
                                    413 	.globl _RFC_OBS_CTRL0
                                    414 	.globl _TXFILTCFG
                                    415 	.globl _PTEST1
                                    416 	.globl _PTEST0
                                    417 	.globl _ATEST
                                    418 	.globl _DACTEST2
                                    419 	.globl _DACTEST1
                                    420 	.globl _DACTEST0
                                    421 	.globl _MDMTEST1
                                    422 	.globl _MDMTEST0
                                    423 	.globl _ADCTEST2
                                    424 	.globl _ADCTEST1
                                    425 	.globl _ADCTEST0
                                    426 	.globl _AGCCTRL3
                                    427 	.globl _AGCCTRL2
                                    428 	.globl _AGCCTRL1
                                    429 	.globl _AGCCTRL0
                                    430 	.globl _FSCAL3
                                    431 	.globl _FSCAL2
                                    432 	.globl _FSCAL1
                                    433 	.globl _FSCAL0
                                    434 	.globl _FSCTRL
                                    435 	.globl _RXCTRL
                                    436 	.globl _FREQEST
                                    437 	.globl _MDMCTRL1
                                    438 	.globl _MDMCTRL0
                                    439 	.globl _RFRND
                                    440 	.globl _RFERRM
                                    441 	.globl _RFIRQM1
                                    442 	.globl _RFIRQM0
                                    443 	.globl _TXLAST_PTR
                                    444 	.globl _TXFIRST_PTR
                                    445 	.globl _RXP1_PTR
                                    446 	.globl _RXLAST_PTR
                                    447 	.globl _RXFIRST_PTR
                                    448 	.globl _TXFIFOCNT
                                    449 	.globl _RXFIFOCNT
                                    450 	.globl _RXFIRST
                                    451 	.globl _RSSISTAT
                                    452 	.globl _RSSI
                                    453 	.globl _CCACTRL1
                                    454 	.globl _CCACTRL0
                                    455 	.globl _FSMCTRL
                                    456 	.globl _FIFOPCTRL
                                    457 	.globl _FSMSTAT1
                                    458 	.globl _FSMSTAT0
                                    459 	.globl _TXCTRL
                                    460 	.globl _TXPOWER
                                    461 	.globl _FREQCTRL
                                    462 	.globl _FREQTUNE
                                    463 	.globl _RXMASKCLR
                                    464 	.globl _RXMASKSET
                                    465 	.globl _RXENABLE
                                    466 	.globl _FRMCTRL1
                                    467 	.globl _FRMCTRL0
                                    468 	.globl _SRCEXTEN2
                                    469 	.globl _SRCEXTEN1
                                    470 	.globl _SRCEXTEN0
                                    471 	.globl _SRCSHORTEN2
                                    472 	.globl _SRCSHORTEN1
                                    473 	.globl _SRCSHORTEN0
                                    474 	.globl _SRCMATCH
                                    475 	.globl _FRMFILT1
                                    476 	.globl _FRMFILT0
                                    477 	.globl _SHORT_ADDR1
                                    478 	.globl _SHORT_ADDR0
                                    479 	.globl _PAN_ID1
                                    480 	.globl _PAN_ID0
                                    481 	.globl _EXT_ADDR7
                                    482 	.globl _EXT_ADDR6
                                    483 	.globl _EXT_ADDR5
                                    484 	.globl _EXT_ADDR4
                                    485 	.globl _EXT_ADDR3
                                    486 	.globl _EXT_ADDR2
                                    487 	.globl _EXT_ADDR1
                                    488 	.globl _EXT_ADDR0
                                    489 	.globl _SRCSHORTPENDEN2
                                    490 	.globl _SRCSHORTPENDEN1
                                    491 	.globl _SRCSHORTPENDEN0
                                    492 	.globl _SRCEXTPENDEN2
                                    493 	.globl _SRCEXTPENDEN1
                                    494 	.globl _SRCEXTPENDEN0
                                    495 	.globl _SRCRESINDEX
                                    496 	.globl _SRCRESMASK2
                                    497 	.globl _SRCRESMASK1
                                    498 	.globl _SRCRESMASK0
                                    499 	.globl _SRC_ADDR_TABLE
                                    500 	.globl _TXFIFO
                                    501 	.globl _RXFIFO
                                    502 	.globl _RFCORE_RAM
                                    503 	.globl _CMPCTL
                                    504 	.globl _OPAMPS
                                    505 	.globl _OPAMPC
                                    506 	.globl _STCV2
                                    507 	.globl _STCV1
                                    508 	.globl _STCV0
                                    509 	.globl _STCS
                                    510 	.globl _STCC
                                    511 	.globl _T1CC4H
                                    512 	.globl _T1CC4L
                                    513 	.globl _T1CC3H
                                    514 	.globl _T1CC3L
                                    515 	.globl _XX_T1CC2H
                                    516 	.globl _XX_T1CC2L
                                    517 	.globl _XX_T1CC1H
                                    518 	.globl _XX_T1CC1L
                                    519 	.globl _XX_T1CC0H
                                    520 	.globl _XX_T1CC0L
                                    521 	.globl _T1CCTL4
                                    522 	.globl _T1CCTL3
                                    523 	.globl _XX_T1CCTL2
                                    524 	.globl _XX_T1CCTL1
                                    525 	.globl _XX_T1CCTL0
                                    526 	.globl _CLD
                                    527 	.globl _IRCTL
                                    528 	.globl _CHIPINFO1
                                    529 	.globl _CHIPINFO0
                                    530 	.globl _FWDATA
                                    531 	.globl _FADDRH
                                    532 	.globl _FADDRL
                                    533 	.globl _FCTL
                                    534 	.globl _IVCTRL
                                    535 	.globl _BATTMON
                                    536 	.globl _SRCRC
                                    537 	.globl _DBGDATA
                                    538 	.globl _TESTREG0
                                    539 	.globl _CHIPID
                                    540 	.globl _CHVER
                                    541 	.globl _OBSSEL5
                                    542 	.globl _OBSSEL4
                                    543 	.globl _OBSSEL3
                                    544 	.globl _OBSSEL2
                                    545 	.globl _OBSSEL1
                                    546 	.globl _OBSSEL0
                                    547 	.globl _I2CIO
                                    548 	.globl _I2CWC
                                    549 	.globl _I2CADDR
                                    550 	.globl _I2CDATA
                                    551 	.globl _I2CSTAT
                                    552 	.globl _I2CCFG
                                    553 	.globl _OPAMPMC
                                    554 	.globl _MONMUX
                                    555 ;--------------------------------------------------------
                                    556 ; special function registers
                                    557 ;--------------------------------------------------------
                                    558 	.area RSEG    (ABS,DATA)
      000000                        559 	.org 0x0000
                           000080   560 _P0	=	0x0080
                           000081   561 _SP	=	0x0081
                           000082   562 _DPL0	=	0x0082
                           000083   563 _DPH0	=	0x0083
                           000084   564 _DPL1	=	0x0084
                           000085   565 _DPH1	=	0x0085
                           000087   566 _PCON	=	0x0087
                           000088   567 _TCON	=	0x0088
                           000090   568 _P1	=	0x0090
                           000092   569 _DPS	=	0x0092
                           000098   570 _S0CON	=	0x0098
                           00009A   571 _IEN2	=	0x009a
                           00009B   572 _S1CON	=	0x009b
                           0000A0   573 _P2	=	0x00a0
                           0000A8   574 _IEN0	=	0x00a8
                           0000A9   575 _IP0	=	0x00a9
                           0000B8   576 _IEN1	=	0x00b8
                           0000B9   577 _IP1	=	0x00b9
                           0000C0   578 _IRCON	=	0x00c0
                           0000D0   579 _PSW	=	0x00d0
                           0000E0   580 _ACC	=	0x00e0
                           0000E8   581 _IRCON2	=	0x00e8
                           0000F0   582 _B	=	0x00f0
                           0000B4   583 _ADCCON1	=	0x00b4
                           0000B5   584 _ADCCON2	=	0x00b5
                           0000B6   585 _ADCCON3	=	0x00b6
                           0000BA   586 _ADCL	=	0x00ba
                           0000BB   587 _ADCH	=	0x00bb
                           0000BC   588 _RNDL	=	0x00bc
                           0000BD   589 _RNDH	=	0x00bd
                           0000B1   590 _ENCDI	=	0x00b1
                           0000B2   591 _ENCDO	=	0x00b2
                           0000B3   592 _ENCCS	=	0x00b3
                           0000D1   593 _DMAIRQ	=	0x00d1
                           0000D2   594 _DMA1CFGL	=	0x00d2
                           0000D3   595 _DMA1CFGH	=	0x00d3
                           0000D4   596 _DMA0CFGL	=	0x00d4
                           0000D5   597 _DMA0CFGH	=	0x00d5
                           0000D6   598 _DMAARM	=	0x00d6
                           0000D7   599 _DMAREQ	=	0x00d7
                           000089   600 _P0IFG	=	0x0089
                           00008A   601 _P1IFG	=	0x008a
                           00008B   602 _P2IFG	=	0x008b
                           00008C   603 _PICTL	=	0x008c
                           0000AB   604 _P0IEN	=	0x00ab
                           00008D   605 _P1IEN	=	0x008d
                           0000AC   606 _P2IEN	=	0x00ac
                           00008F   607 _P0INP	=	0x008f
                           0000F1   608 _PERCFG	=	0x00f1
                           0000F2   609 _APCFG	=	0x00f2
                           0000F3   610 _P0SEL	=	0x00f3
                           0000F4   611 _P1SEL	=	0x00f4
                           0000F5   612 _P2SEL	=	0x00f5
                           0000F6   613 _P1INP	=	0x00f6
                           0000F7   614 _P2INP	=	0x00f7
                           0000FD   615 _P0DIR	=	0x00fd
                           0000FE   616 _P1DIR	=	0x00fe
                           0000FF   617 _P2DIR	=	0x00ff
                           0000AE   618 _PMUX	=	0x00ae
                           000093   619 _MPAGE	=	0x0093
                           000093   620 __XPAGE	=	0x0093
                           0000C7   621 _MEMCTR	=	0x00c7
                           00009F   622 _FMAP	=	0x009f
                           00009F   623 _PSBANK	=	0x009f
                           000091   624 _RFIRQF1	=	0x0091
                           0000D9   625 _RFD	=	0x00d9
                           0000E1   626 _RFST	=	0x00e1
                           0000E9   627 _RFIRQF0	=	0x00e9
                           0000BF   628 _RFERRF	=	0x00bf
                           000095   629 _ST0	=	0x0095
                           000096   630 _ST1	=	0x0096
                           000097   631 _ST2	=	0x0097
                           0000AD   632 _STLOAD	=	0x00ad
                           0000BE   633 _SLEEPCMD	=	0x00be
                           00009D   634 _SLEEPSTA	=	0x009d
                           0000C6   635 _CLKCONCMD	=	0x00c6
                           00009E   636 _CLKCONSTA	=	0x009e
                           0000DA   637 _T1CC0L	=	0x00da
                           0000DB   638 _T1CC0H	=	0x00db
                           0000DC   639 _T1CC1L	=	0x00dc
                           0000DD   640 _T1CC1H	=	0x00dd
                           0000DE   641 _T1CC2L	=	0x00de
                           0000DF   642 _T1CC2H	=	0x00df
                           0000E2   643 _T1CNTL	=	0x00e2
                           0000E3   644 _T1CNTH	=	0x00e3
                           0000E4   645 _T1CTL	=	0x00e4
                           0000E5   646 _T1CCTL0	=	0x00e5
                           0000E6   647 _T1CCTL1	=	0x00e6
                           0000E7   648 _T1CCTL2	=	0x00e7
                           0000AF   649 _T1STAT	=	0x00af
                           000094   650 _T2CTRL	=	0x0094
                           00009C   651 _T2EVTCFG	=	0x009c
                           0000A1   652 _T2IRQF	=	0x00a1
                           0000A2   653 _T2M0	=	0x00a2
                           0000A3   654 _T2M1	=	0x00a3
                           0000A4   655 _T2MOVF0	=	0x00a4
                           0000A5   656 _T2MOVF1	=	0x00a5
                           0000A6   657 _T2MOVF2	=	0x00a6
                           0000A7   658 _T2IRQM	=	0x00a7
                           0000C3   659 _T2MSEL	=	0x00c3
                           0000CA   660 _T3CNT	=	0x00ca
                           0000CB   661 _T3CTL	=	0x00cb
                           0000CC   662 _T3CCTL0	=	0x00cc
                           0000CD   663 _T3CC0	=	0x00cd
                           0000CE   664 _T3CCTL1	=	0x00ce
                           0000CF   665 _T3CC1	=	0x00cf
                           0000EA   666 _T4CNT	=	0x00ea
                           0000EB   667 _T4CTL	=	0x00eb
                           0000EC   668 _T4CCTL0	=	0x00ec
                           0000ED   669 _T4CC0	=	0x00ed
                           0000EE   670 _T4CCTL1	=	0x00ee
                           0000EF   671 _T4CC1	=	0x00ef
                           0000D8   672 _TIMIF	=	0x00d8
                           000086   673 _U0CSR	=	0x0086
                           0000C1   674 _U0DBUF	=	0x00c1
                           0000C2   675 _U0BAUD	=	0x00c2
                           0000C4   676 _U0UCR	=	0x00c4
                           0000C5   677 _U0GCR	=	0x00c5
                           0000F8   678 _U1CSR	=	0x00f8
                           0000F9   679 _U1DBUF	=	0x00f9
                           0000FA   680 _U1BAUD	=	0x00fa
                           0000FB   681 _U1UCR	=	0x00fb
                           0000FC   682 _U1GCR	=	0x00fc
                           0000C9   683 _WDCTL	=	0x00c9
                                    684 ;--------------------------------------------------------
                                    685 ; special function bits
                                    686 ;--------------------------------------------------------
                                    687 	.area RSEG    (ABS,DATA)
      000000                        688 	.org 0x0000
                           000087   689 _P0_7	=	0x0087
                           000086   690 _P0_6	=	0x0086
                           000085   691 _P0_5	=	0x0085
                           000084   692 _P0_4	=	0x0084
                           000083   693 _P0_3	=	0x0083
                           000082   694 _P0_2	=	0x0082
                           000081   695 _P0_1	=	0x0081
                           000080   696 _P0_0	=	0x0080
                           00008F   697 _URX1IF	=	0x008f
                           00008D   698 _ADCIF	=	0x008d
                           00008B   699 _URX0IF	=	0x008b
                           00008A   700 _IT1	=	0x008a
                           000089   701 _RFERRIF	=	0x0089
                           000088   702 _IT0	=	0x0088
                           000097   703 _P1_7	=	0x0097
                           000096   704 _P1_6	=	0x0096
                           000095   705 _P1_5	=	0x0095
                           000094   706 _P1_4	=	0x0094
                           000093   707 _P1_3	=	0x0093
                           000092   708 _P1_2	=	0x0092
                           000091   709 _P1_1	=	0x0091
                           000090   710 _P1_0	=	0x0090
                           000099   711 _ENCIF_1	=	0x0099
                           000098   712 _ENCIF_0	=	0x0098
                           0000A7   713 _P2_7	=	0x00a7
                           0000A6   714 _P2_6	=	0x00a6
                           0000A5   715 _P2_5	=	0x00a5
                           0000A4   716 _P2_4	=	0x00a4
                           0000A3   717 _P2_3	=	0x00a3
                           0000A2   718 _P2_2	=	0x00a2
                           0000A1   719 _P2_1	=	0x00a1
                           0000A0   720 _P2_0	=	0x00a0
                           0000AF   721 _EA	=	0x00af
                           0000AD   722 _STIE	=	0x00ad
                           0000AC   723 _ENCIE	=	0x00ac
                           0000AB   724 _URX1IE	=	0x00ab
                           0000AA   725 _URX0IE	=	0x00aa
                           0000A9   726 _ADCIE	=	0x00a9
                           0000A8   727 _RFERRIE	=	0x00a8
                           0000BD   728 _P0IE	=	0x00bd
                           0000BC   729 _T4IE	=	0x00bc
                           0000BB   730 _T3IE	=	0x00bb
                           0000BA   731 _T2IE	=	0x00ba
                           0000B9   732 _T1IE	=	0x00b9
                           0000B8   733 _DMAIE	=	0x00b8
                           0000C7   734 _STIF	=	0x00c7
                           0000C5   735 _P0IF	=	0x00c5
                           0000C4   736 _T4IF	=	0x00c4
                           0000C3   737 _T3IF	=	0x00c3
                           0000C2   738 _T2IF	=	0x00c2
                           0000C1   739 _T1IF	=	0x00c1
                           0000C0   740 _DMAIF	=	0x00c0
                           0000D7   741 _CY	=	0x00d7
                           0000D6   742 _AC	=	0x00d6
                           0000D5   743 _F0	=	0x00d5
                           0000D4   744 _RS1	=	0x00d4
                           0000D3   745 _RS0	=	0x00d3
                           0000D2   746 _OV	=	0x00d2
                           0000D1   747 _F1	=	0x00d1
                           0000D0   748 _P	=	0x00d0
                           0000E7   749 _ACC_7	=	0x00e7
                           0000E6   750 _ACC_6	=	0x00e6
                           0000E5   751 _ACC_5	=	0x00e5
                           0000E4   752 _ACC_4	=	0x00e4
                           0000E3   753 _ACC_3	=	0x00e3
                           0000E2   754 _ACC_2	=	0x00e2
                           0000E1   755 _ACC_1	=	0x00e1
                           0000E0   756 _ACC_0	=	0x00e0
                           0000EC   757 _WDTIF	=	0x00ec
                           0000EB   758 _P1IF	=	0x00eb
                           0000EA   759 _UTX1IF	=	0x00ea
                           0000E9   760 _UTX0IF	=	0x00e9
                           0000E8   761 _P2IF	=	0x00e8
                           0000F7   762 _B_7	=	0x00f7
                           0000F6   763 _B_6	=	0x00f6
                           0000F5   764 _B_5	=	0x00f5
                           0000F4   765 _B_4	=	0x00f4
                           0000F3   766 _B_3	=	0x00f3
                           0000F2   767 _B_2	=	0x00f2
                           0000F1   768 _B_1	=	0x00f1
                           0000F0   769 _B_0	=	0x00f0
                           0000DE   770 _OVFIM	=	0x00de
                           0000DD   771 _T4CH1IF	=	0x00dd
                           0000DC   772 _T4CH0IF	=	0x00dc
                           0000DB   773 _T4OVFIF	=	0x00db
                           0000DA   774 _T3CH1IF	=	0x00da
                           0000D9   775 _T3CH0IF	=	0x00d9
                           0000D8   776 _T3OVFIF	=	0x00d8
                           0000FF   777 _MODE	=	0x00ff
                           0000FE   778 _RE	=	0x00fe
                           0000FD   779 _SLAVE	=	0x00fd
                           0000FC   780 _FE	=	0x00fc
                           0000FB   781 _ERR	=	0x00fb
                           0000FA   782 _RX_BYTE	=	0x00fa
                           0000F9   783 _TX_BYTE	=	0x00f9
                           0000F8   784 _ACTIVE	=	0x00f8
                                    785 ;--------------------------------------------------------
                                    786 ; overlayable register banks
                                    787 ;--------------------------------------------------------
                                    788 	.area REG_BANK_0	(REL,OVR,DATA)
      000000                        789 	.ds 8
                                    790 ;--------------------------------------------------------
                                    791 ; internal ram data
                                    792 ;--------------------------------------------------------
                                    793 	.area DSEG    (DATA)
                                    794 ;--------------------------------------------------------
                                    795 ; overlayable items in internal ram 
                                    796 ;--------------------------------------------------------
                                    797 ;--------------------------------------------------------
                                    798 ; indirectly addressable internal ram data
                                    799 ;--------------------------------------------------------
                                    800 	.area ISEG    (DATA)
                                    801 ;--------------------------------------------------------
                                    802 ; absolute internal ram data
                                    803 ;--------------------------------------------------------
                                    804 	.area IABS    (ABS,DATA)
                                    805 	.area IABS    (ABS,DATA)
                                    806 ;--------------------------------------------------------
                                    807 ; bit data
                                    808 ;--------------------------------------------------------
                                    809 	.area BSEG    (BIT)
                                    810 ;--------------------------------------------------------
                                    811 ; paged external ram data
                                    812 ;--------------------------------------------------------
                                    813 	.area PSEG    (PAG,XDATA)
                                    814 ;--------------------------------------------------------
                                    815 ; external ram data
                                    816 ;--------------------------------------------------------
                                    817 	.area XSEG    (XDATA)
                           0061A6   818 _MONMUX	=	0x61a6
                           0061A6   819 _OPAMPMC	=	0x61a6
                           006230   820 _I2CCFG	=	0x6230
                           006231   821 _I2CSTAT	=	0x6231
                           006232   822 _I2CDATA	=	0x6232
                           006233   823 _I2CADDR	=	0x6233
                           006234   824 _I2CWC	=	0x6234
                           006235   825 _I2CIO	=	0x6235
                           006243   826 _OBSSEL0	=	0x6243
                           006244   827 _OBSSEL1	=	0x6244
                           006245   828 _OBSSEL2	=	0x6245
                           006246   829 _OBSSEL3	=	0x6246
                           006247   830 _OBSSEL4	=	0x6247
                           006248   831 _OBSSEL5	=	0x6248
                           006249   832 _CHVER	=	0x6249
                           00624A   833 _CHIPID	=	0x624a
                           00624B   834 _TESTREG0	=	0x624b
                           006260   835 _DBGDATA	=	0x6260
                           006262   836 _SRCRC	=	0x6262
                           006264   837 _BATTMON	=	0x6264
                           006265   838 _IVCTRL	=	0x6265
                           006270   839 _FCTL	=	0x6270
                           006271   840 _FADDRL	=	0x6271
                           006272   841 _FADDRH	=	0x6272
                           006273   842 _FWDATA	=	0x6273
                           006276   843 _CHIPINFO0	=	0x6276
                           006277   844 _CHIPINFO1	=	0x6277
                           006281   845 _IRCTL	=	0x6281
                           006290   846 _CLD	=	0x6290
                           0062A0   847 _XX_T1CCTL0	=	0x62a0
                           0062A1   848 _XX_T1CCTL1	=	0x62a1
                           0062A2   849 _XX_T1CCTL2	=	0x62a2
                           0062A3   850 _T1CCTL3	=	0x62a3
                           0062A4   851 _T1CCTL4	=	0x62a4
                           0062A6   852 _XX_T1CC0L	=	0x62a6
                           0062A7   853 _XX_T1CC0H	=	0x62a7
                           0062A8   854 _XX_T1CC1L	=	0x62a8
                           0062A9   855 _XX_T1CC1H	=	0x62a9
                           0062AA   856 _XX_T1CC2L	=	0x62aa
                           0062AB   857 _XX_T1CC2H	=	0x62ab
                           0062AC   858 _T1CC3L	=	0x62ac
                           0062AD   859 _T1CC3H	=	0x62ad
                           0062AE   860 _T1CC4L	=	0x62ae
                           0062AF   861 _T1CC4H	=	0x62af
                           0062B0   862 _STCC	=	0x62b0
                           0062B1   863 _STCS	=	0x62b1
                           0062B2   864 _STCV0	=	0x62b2
                           0062B3   865 _STCV1	=	0x62b3
                           0062B4   866 _STCV2	=	0x62b4
                           0062C0   867 _OPAMPC	=	0x62c0
                           0062C1   868 _OPAMPS	=	0x62c1
                           0062D0   869 _CMPCTL	=	0x62d0
                           006000   870 _RFCORE_RAM	=	0x6000
                           006000   871 _RXFIFO	=	0x6000
                           006080   872 _TXFIFO	=	0x6080
                           006100   873 _SRC_ADDR_TABLE	=	0x6100
                           006160   874 _SRCRESMASK0	=	0x6160
                           006161   875 _SRCRESMASK1	=	0x6161
                           006162   876 _SRCRESMASK2	=	0x6162
                           006163   877 _SRCRESINDEX	=	0x6163
                           006164   878 _SRCEXTPENDEN0	=	0x6164
                           006165   879 _SRCEXTPENDEN1	=	0x6165
                           006166   880 _SRCEXTPENDEN2	=	0x6166
                           006167   881 _SRCSHORTPENDEN0	=	0x6167
                           006168   882 _SRCSHORTPENDEN1	=	0x6168
                           006169   883 _SRCSHORTPENDEN2	=	0x6169
                           00616A   884 _EXT_ADDR0	=	0x616a
                           00616B   885 _EXT_ADDR1	=	0x616b
                           00616C   886 _EXT_ADDR2	=	0x616c
                           00616D   887 _EXT_ADDR3	=	0x616d
                           00616E   888 _EXT_ADDR4	=	0x616e
                           00616F   889 _EXT_ADDR5	=	0x616f
                           006170   890 _EXT_ADDR6	=	0x6170
                           006171   891 _EXT_ADDR7	=	0x6171
                           006172   892 _PAN_ID0	=	0x6172
                           006173   893 _PAN_ID1	=	0x6173
                           006174   894 _SHORT_ADDR0	=	0x6174
                           006175   895 _SHORT_ADDR1	=	0x6175
                           006180   896 _FRMFILT0	=	0x6180
                           006181   897 _FRMFILT1	=	0x6181
                           006182   898 _SRCMATCH	=	0x6182
                           006183   899 _SRCSHORTEN0	=	0x6183
                           006184   900 _SRCSHORTEN1	=	0x6184
                           006185   901 _SRCSHORTEN2	=	0x6185
                           006186   902 _SRCEXTEN0	=	0x6186
                           006187   903 _SRCEXTEN1	=	0x6187
                           006188   904 _SRCEXTEN2	=	0x6188
                           006189   905 _FRMCTRL0	=	0x6189
                           00618A   906 _FRMCTRL1	=	0x618a
                           00618B   907 _RXENABLE	=	0x618b
                           00618C   908 _RXMASKSET	=	0x618c
                           00618D   909 _RXMASKCLR	=	0x618d
                           00618E   910 _FREQTUNE	=	0x618e
                           00618F   911 _FREQCTRL	=	0x618f
                           006190   912 _TXPOWER	=	0x6190
                           006191   913 _TXCTRL	=	0x6191
                           006192   914 _FSMSTAT0	=	0x6192
                           006193   915 _FSMSTAT1	=	0x6193
                           006194   916 _FIFOPCTRL	=	0x6194
                           006195   917 _FSMCTRL	=	0x6195
                           006196   918 _CCACTRL0	=	0x6196
                           006197   919 _CCACTRL1	=	0x6197
                           006198   920 _RSSI	=	0x6198
                           006199   921 _RSSISTAT	=	0x6199
                           00619A   922 _RXFIRST	=	0x619a
                           00619B   923 _RXFIFOCNT	=	0x619b
                           00619C   924 _TXFIFOCNT	=	0x619c
                           00619D   925 _RXFIRST_PTR	=	0x619d
                           00619E   926 _RXLAST_PTR	=	0x619e
                           00619F   927 _RXP1_PTR	=	0x619f
                           0061A1   928 _TXFIRST_PTR	=	0x61a1
                           0061A2   929 _TXLAST_PTR	=	0x61a2
                           0061A3   930 _RFIRQM0	=	0x61a3
                           0061A4   931 _RFIRQM1	=	0x61a4
                           0061A5   932 _RFERRM	=	0x61a5
                           0061A7   933 _RFRND	=	0x61a7
                           0061A8   934 _MDMCTRL0	=	0x61a8
                           0061A9   935 _MDMCTRL1	=	0x61a9
                           0061AA   936 _FREQEST	=	0x61aa
                           0061AB   937 _RXCTRL	=	0x61ab
                           0061AC   938 _FSCTRL	=	0x61ac
                           0061AD   939 _FSCAL0	=	0x61ad
                           0061AE   940 _FSCAL1	=	0x61ae
                           0061AF   941 _FSCAL2	=	0x61af
                           0061B0   942 _FSCAL3	=	0x61b0
                           0061B1   943 _AGCCTRL0	=	0x61b1
                           0061B2   944 _AGCCTRL1	=	0x61b2
                           0061B3   945 _AGCCTRL2	=	0x61b3
                           0061B4   946 _AGCCTRL3	=	0x61b4
                           0061B5   947 _ADCTEST0	=	0x61b5
                           0061B6   948 _ADCTEST1	=	0x61b6
                           0061B7   949 _ADCTEST2	=	0x61b7
                           0061B8   950 _MDMTEST0	=	0x61b8
                           0061B9   951 _MDMTEST1	=	0x61b9
                           0061BA   952 _DACTEST0	=	0x61ba
                           0061BB   953 _DACTEST1	=	0x61bb
                           0061BC   954 _DACTEST2	=	0x61bc
                           0061BD   955 _ATEST	=	0x61bd
                           0061BE   956 _PTEST0	=	0x61be
                           0061BF   957 _PTEST1	=	0x61bf
                           0061FA   958 _TXFILTCFG	=	0x61fa
                           0061EB   959 _RFC_OBS_CTRL0	=	0x61eb
                           0061EC   960 _RFC_OBS_CTRL1	=	0x61ec
                           0061ED   961 _RFC_OBS_CTRL2	=	0x61ed
                           0061C0   962 _CSPPROG0	=	0x61c0
                           0061C1   963 _CSPPROG1	=	0x61c1
                           0061C2   964 _CSPPROG2	=	0x61c2
                           0061C3   965 _CSPPROG3	=	0x61c3
                           0061C4   966 _CSPPROG4	=	0x61c4
                           0061C5   967 _CSPPROG5	=	0x61c5
                           0061C6   968 _CSPPROG6	=	0x61c6
                           0061C7   969 _CSPPROG7	=	0x61c7
                           0061C8   970 _CSPPROG8	=	0x61c8
                           0061C9   971 _CSPPROG9	=	0x61c9
                           0061CA   972 _CSPPROG10	=	0x61ca
                           0061CB   973 _CSPPROG11	=	0x61cb
                           0061CC   974 _CSPPROG12	=	0x61cc
                           0061CD   975 _CSPPROG13	=	0x61cd
                           0061CE   976 _CSPPROG14	=	0x61ce
                           0061CF   977 _CSPPROG15	=	0x61cf
                           0061D0   978 _CSPPROG16	=	0x61d0
                           0061D1   979 _CSPPROG17	=	0x61d1
                           0061D2   980 _CSPPROG18	=	0x61d2
                           0061D3   981 _CSPPROG19	=	0x61d3
                           0061D4   982 _CSPPROG20	=	0x61d4
                           0061D5   983 _CSPPROG21	=	0x61d5
                           0061D6   984 _CSPPROG22	=	0x61d6
                           0061D7   985 _CSPPROG23	=	0x61d7
                           0061E0   986 _CSPCTRL	=	0x61e0
                           0061E1   987 _CSPSTAT	=	0x61e1
                           0061E2   988 _CSPX	=	0x61e2
                           0061E3   989 _CSPY	=	0x61e3
                           0061E4   990 _CSPZ	=	0x61e4
                           0061E5   991 _CSPT	=	0x61e5
                           006200   992 _USBADDR	=	0x6200
                           006201   993 _USBPOW	=	0x6201
                           006202   994 _USBIIF	=	0x6202
                           006204   995 _USBOIF	=	0x6204
                           006206   996 _USBCIF	=	0x6206
                           006207   997 _USBIIE	=	0x6207
                           006209   998 _USBOIE	=	0x6209
                           00620B   999 _USBCIE	=	0x620b
                           00620C  1000 _USBFRML	=	0x620c
                           00620D  1001 _USBFRMH	=	0x620d
                           00620E  1002 _USBINDEX	=	0x620e
                           00620F  1003 _USBCTRL	=	0x620f
                           006210  1004 _USBMAXI	=	0x6210
                           006211  1005 _USBCS0	=	0x6211
                           006211  1006 _USBCSIL	=	0x6211
                           006212  1007 _USBCSIH	=	0x6212
                           006213  1008 _USBMAXO	=	0x6213
                           006214  1009 _USBCSOL	=	0x6214
                           006215  1010 _USBCSOH	=	0x6215
                           006216  1011 _USBCNT0	=	0x6216
                           006216  1012 _USBCNTL	=	0x6216
                           006217  1013 _USBCNTH	=	0x6217
                           006220  1014 _USBF0	=	0x6220
                           006222  1015 _USBF1	=	0x6222
                           006224  1016 _USBF2	=	0x6224
                           006226  1017 _USBF3	=	0x6226
                           006228  1018 _USBF4	=	0x6228
                           00622A  1019 _USBF5	=	0x622a
                           007080  1020 _X_P0	=	0x7080
                           007086  1021 _X_U0CSR	=	0x7086
                           007089  1022 _X_P0IFG	=	0x7089
                           00708A  1023 _X_P1IFG	=	0x708a
                           00708B  1024 _X_P2IFG	=	0x708b
                           00708C  1025 _X_PICTL	=	0x708c
                           00708D  1026 _X_P1IEN	=	0x708d
                           00708F  1027 _X_P0INP	=	0x708f
                           007090  1028 _X_P1	=	0x7090
                           007091  1029 _X_RFIRQF1	=	0x7091
                           007093  1030 _X_MPAGE	=	0x7093
                           007093  1031 _X__XPAGE	=	0x7093
                           007094  1032 _X_T2CTRL	=	0x7094
                           007095  1033 _X_ST0	=	0x7095
                           007096  1034 _X_ST1	=	0x7096
                           007097  1035 _X_ST2	=	0x7097
                           00709C  1036 _X_T2EVTCFG	=	0x709c
                           00709D  1037 _X_SLEEPSTA	=	0x709d
                           00709E  1038 _X_CLKCONSTA	=	0x709e
                           00709F  1039 _X_FMAP	=	0x709f
                           00709F  1040 _X_PSBANK	=	0x709f
                           0070A0  1041 _X_P2	=	0x70a0
                           0070A1  1042 _X_T2IRQF	=	0x70a1
                           0070A2  1043 _X_T2M0	=	0x70a2
                           0070A3  1044 _X_T2M1	=	0x70a3
                           0070A4  1045 _X_T2MOVF0	=	0x70a4
                           0070A5  1046 _X_T2MOVF1	=	0x70a5
                           0070A6  1047 _X_T2MOVF2	=	0x70a6
                           0070A7  1048 _X_T2IRQM	=	0x70a7
                           0070AB  1049 _X_P0IEN	=	0x70ab
                           0070AC  1050 _X_P2IEN	=	0x70ac
                           0070AD  1051 _X_STLOAD	=	0x70ad
                           0070AE  1052 _X_PMUX	=	0x70ae
                           0070AF  1053 _X_T1STAT	=	0x70af
                           0070B1  1054 _X_ENCDI	=	0x70b1
                           0070B2  1055 _X_ENCDO	=	0x70b2
                           0070B3  1056 _X_ENCCS	=	0x70b3
                           0070B4  1057 _X_ADCCON1	=	0x70b4
                           0070B5  1058 _X_ADCCON2	=	0x70b5
                           0070B6  1059 _X_ADCCON3	=	0x70b6
                           0070BA  1060 _X_ADCL	=	0x70ba
                           0070BB  1061 _X_ADCH	=	0x70bb
                           0070BC  1062 _X_RNDL	=	0x70bc
                           0070BD  1063 _X_RNDH	=	0x70bd
                           0070BE  1064 _X_SLEEPCMD	=	0x70be
                           0070BF  1065 _X_RFERRF	=	0x70bf
                           0070C1  1066 _X_U0DBUF	=	0x70c1
                           0070C2  1067 _X_U0BAUD	=	0x70c2
                           0070C3  1068 _X_T2MSEL	=	0x70c3
                           0070C4  1069 _X_U0UCR	=	0x70c4
                           0070C5  1070 _X_U0GCR	=	0x70c5
                           0070C6  1071 _X_CLKCONCMD	=	0x70c6
                           0070C7  1072 _X_MEMCTR	=	0x70c7
                           0070C9  1073 _X_WDCTL	=	0x70c9
                           0070CA  1074 _X_T3CNT	=	0x70ca
                           0070CB  1075 _X_T3CTL	=	0x70cb
                           0070CC  1076 _X_T3CCTL0	=	0x70cc
                           0070CD  1077 _X_T3CC0	=	0x70cd
                           0070CE  1078 _X_T3CCTL1	=	0x70ce
                           0070CF  1079 _X_T3CC1	=	0x70cf
                           0070D1  1080 _X_DMAIRQ	=	0x70d1
                           0070D2  1081 _X_DMA1CFGL	=	0x70d2
                           0070D3  1082 _X_DMA1CFGH	=	0x70d3
                           0070D4  1083 _X_DMA0CFGL	=	0x70d4
                           0070D5  1084 _X_DMA0CFGH	=	0x70d5
                           0070D6  1085 _X_DMAARM	=	0x70d6
                           0070D7  1086 _X_DMAREQ	=	0x70d7
                           0070D8  1087 _X_TIMIF	=	0x70d8
                           0070D9  1088 _X_RFD	=	0x70d9
                           0070DA  1089 _X_T1CC0L	=	0x70da
                           0070DB  1090 _X_T1CC0H	=	0x70db
                           0070DC  1091 _X_T1CC1L	=	0x70dc
                           0070DD  1092 _X_T1CC1H	=	0x70dd
                           0070DE  1093 _X_T1CC2L	=	0x70de
                           0070DF  1094 _X_T1CC2H	=	0x70df
                           0070E1  1095 _X_RFST	=	0x70e1
                           0070E2  1096 _X_T1CNTL	=	0x70e2
                           0070E3  1097 _X_T1CNTH	=	0x70e3
                           0070E4  1098 _X_T1CTL	=	0x70e4
                           0070E5  1099 _X_T1CCTL0	=	0x70e5
                           0070E6  1100 _X_T1CCTL1	=	0x70e6
                           0070E7  1101 _X_T1CCTL2	=	0x70e7
                           0070E9  1102 _X_RFIRQF0	=	0x70e9
                           0070EA  1103 _X_T4CNT	=	0x70ea
                           0070EB  1104 _X_T4CTL	=	0x70eb
                           0070EC  1105 _X_T4CCTL0	=	0x70ec
                           0070ED  1106 _X_T4CC0	=	0x70ed
                           0070EE  1107 _X_T4CCTL1	=	0x70ee
                           0070EF  1108 _X_T4CC1	=	0x70ef
                           0070F1  1109 _X_PERCFG	=	0x70f1
                           0070F2  1110 _X_APCFG	=	0x70f2
                           0070F3  1111 _X_P0SEL	=	0x70f3
                           0070F4  1112 _X_P1SEL	=	0x70f4
                           0070F5  1113 _X_P2SEL	=	0x70f5
                           0070F6  1114 _X_P1INP	=	0x70f6
                           0070F7  1115 _X_P2INP	=	0x70f7
                           0070F8  1116 _X_U1CSR	=	0x70f8
                           0070F9  1117 _X_U1DBUF	=	0x70f9
                           0070FA  1118 _X_U1BAUD	=	0x70fa
                           0070FB  1119 _X_U1UCR	=	0x70fb
                           0070FC  1120 _X_U1GCR	=	0x70fc
                           0070FD  1121 _X_P0DIR	=	0x70fd
                           0070FE  1122 _X_P1DIR	=	0x70fe
                           0070FF  1123 _X_P2DIR	=	0x70ff
                           007800  1124 _X_INFOPAGE	=	0x7800
                           00780C  1125 _X_IEEE_ADDR	=	0x780c
      000004                       1126 _server_conn:
      000004                       1127 	.ds 3
      000007                       1128 _recv_buf:
      000007                       1129 	.ds 20
      00001B                       1130 _u32_data::
      00001B                       1131 	.ds 4
      00001F                       1132 _temp::
      00001F                       1133 	.ds 4
      000023                       1134 _recv_len:
      000023                       1135 	.ds 1
      000024                       1136 _ptr::
      000024                       1137 	.ds 3
      000027                       1138 _i::
      000027                       1139 	.ds 1
      000028                       1140 _sensor_flag::
      000028                       1141 	.ds 4
                                   1142 ;--------------------------------------------------------
                                   1143 ; absolute external ram data
                                   1144 ;--------------------------------------------------------
                                   1145 	.area XABS    (ABS,XDATA)
                                   1146 ;--------------------------------------------------------
                                   1147 ; external initialized ram data
                                   1148 ;--------------------------------------------------------
                                   1149 	.area XISEG   (XDATA)
      00181C                       1150 _atmophere_press::
      00181C                       1151 	.ds 4
      001820                       1152 _TempHumidity::
      001820                       1153 	.ds 11
      00182B                       1154 _optoc_smoke::
      00182B                       1155 	.ds 17
      00183C                       1156 _vibra::
      00183C                       1157 	.ds 17
      00184D                       1158 _udp_server_process::
      00184D                       1159 	.ds 13
                                   1160 	.area HOME    (CODE)
                                   1161 	.area GSINIT0 (CODE)
                                   1162 	.area GSINIT1 (CODE)
                                   1163 	.area GSINIT2 (CODE)
                                   1164 	.area GSINIT3 (CODE)
                                   1165 	.area GSINIT4 (CODE)
                                   1166 	.area GSINIT5 (CODE)
                                   1167 	.area GSINIT  (CODE)
                                   1168 	.area GSFINAL (CODE)
                                   1169 	.area CSEG    (CODE)
                                   1170 ;--------------------------------------------------------
                                   1171 ; global & static initialisations
                                   1172 ;--------------------------------------------------------
                                   1173 	.area HOME    (CODE)
                                   1174 	.area GSINIT  (CODE)
                                   1175 	.area GSFINAL (CODE)
                                   1176 	.area GSINIT  (CODE)
                                   1177 ;--------------------------------------------------------
                                   1178 ; Home
                                   1179 ;--------------------------------------------------------
                                   1180 	.area HOME    (CODE)
                                   1181 	.area HOME    (CODE)
                                   1182 ;--------------------------------------------------------
                                   1183 ; code
                                   1184 ;--------------------------------------------------------
                                   1185 	.area BANK1   (CODE)
                                   1186 ;------------------------------------------------------------
                                   1187 ;Allocation info for local variables in function 'tcpip_handler'
                                   1188 ;------------------------------------------------------------
                                   1189 ;temp                      Allocated to registers r6 
                                   1190 ;------------------------------------------------------------
                                   1191 ;	server.c:75: static void tcpip_handler(void)
                                   1192 ;	-----------------------------------------
                                   1193 ;	 function tcpip_handler
                                   1194 ;	-----------------------------------------
      048000                       1195 _tcpip_handler:
                           000007  1196 	ar7 = 0x07
                           000006  1197 	ar6 = 0x06
                           000005  1198 	ar5 = 0x05
                           000004  1199 	ar4 = 0x04
                           000003  1200 	ar3 = 0x03
                           000002  1201 	ar2 = 0x02
                           000001  1202 	ar1 = 0x01
                           000000  1203 	ar0 = 0x00
                                   1204 ;	server.c:78: memset(recv_buf, 0, MAX_PAYLOAD_LEN);
      048000 74 14            [12] 1205 	mov	a,#0x14
      048002 C0 E0            [24] 1206 	push	acc
      048004 E4               [12] 1207 	clr	a
      048005 C0 E0            [24] 1208 	push	acc
      048007 C0 E0            [24] 1209 	push	acc
      048009 90 00 07         [24] 1210 	mov	dptr,#_recv_buf
      04800C 75 F0 00         [24] 1211 	mov	b,#0x00
      04800F 78 5C            [12] 1212 	mov	r0,#_memset
      048011 79 4F            [12] 1213 	mov	r1,#(_memset >> 8)
      048013 7A 00            [12] 1214 	mov	r2,#(_memset >> 16)
      048015 12 05 65         [24] 1215 	lcall	__sdcc_banked_call
      048018 15 81            [12] 1216 	dec	sp
      04801A 15 81            [12] 1217 	dec	sp
      04801C 15 81            [12] 1218 	dec	sp
                                   1219 ;	server.c:79: if(uip_newdata()) 
      04801E 90 06 F8         [24] 1220 	mov	dptr,#_uip_flags
      048021 E0               [24] 1221 	movx	a,@dptr
      048022 20 E1 03         [24] 1222 	jb	acc.1,00135$
      048025 02 81 DD         [24] 1223 	ljmp	00107$
      048028                       1224 00135$:
                                   1225 ;	server.c:81: recv_len = uip_datalen();		
      048028 90 06 F4         [24] 1226 	mov	dptr,#_uip_len
      04802B E0               [24] 1227 	movx	a,@dptr
      04802C FE               [12] 1228 	mov	r6,a
      04802D A3               [24] 1229 	inc	dptr
      04802E E0               [24] 1230 	movx	a,@dptr
      04802F 90 00 23         [24] 1231 	mov	dptr,#_recv_len
      048032 EE               [12] 1232 	mov	a,r6
      048033 F0               [24] 1233 	movx	@dptr,a
                                   1234 ;	server.c:82: memcpy(recv_buf, (uint8_t*)uip_appdata, recv_len);
      048034 7F 00            [12] 1235 	mov	r7,#0x00
      048036 90 06 EE         [24] 1236 	mov	dptr,#_uip_appdata
      048039 E0               [24] 1237 	movx	a,@dptr
      04803A FB               [12] 1238 	mov	r3,a
      04803B A3               [24] 1239 	inc	dptr
      04803C E0               [24] 1240 	movx	a,@dptr
      04803D FC               [12] 1241 	mov	r4,a
      04803E A3               [24] 1242 	inc	dptr
      04803F E0               [24] 1243 	movx	a,@dptr
      048040 FD               [12] 1244 	mov	r5,a
      048041 C0 06            [24] 1245 	push	ar6
      048043 C0 07            [24] 1246 	push	ar7
      048045 C0 03            [24] 1247 	push	ar3
      048047 C0 04            [24] 1248 	push	ar4
      048049 C0 05            [24] 1249 	push	ar5
      04804B 90 00 07         [24] 1250 	mov	dptr,#_recv_buf
      04804E 75 F0 00         [24] 1251 	mov	b,#0x00
      048051 78 C7            [12] 1252 	mov	r0,#___memcpy
      048053 79 4E            [12] 1253 	mov	r1,#(___memcpy >> 8)
      048055 7A 00            [12] 1254 	mov	r2,#(___memcpy >> 16)
      048057 12 05 65         [24] 1255 	lcall	__sdcc_banked_call
      04805A E5 81            [12] 1256 	mov	a,sp
      04805C 24 FB            [12] 1257 	add	a,#0xfb
      04805E F5 81            [12] 1258 	mov	sp,a
                                   1259 ;	server.c:83: switch(recv_buf[0])
      048060 90 00 07         [24] 1260 	mov	dptr,#_recv_buf
      048063 E0               [24] 1261 	movx	a,@dptr
      048064 FF               [12] 1262 	mov	r7,a
      048065 BF 81 02         [24] 1263 	cjne	r7,#0x81,00136$
      048068 80 15            [24] 1264 	sjmp	00101$
      04806A                       1265 00136$:
      04806A BF 82 03         [24] 1266 	cjne	r7,#0x82,00137$
      04806D 02 81 3D         [24] 1267 	ljmp	00102$
      048070                       1268 00137$:
      048070 BF 83 03         [24] 1269 	cjne	r7,#0x83,00138$
      048073 02 81 48         [24] 1270 	ljmp	00103$
      048076                       1271 00138$:
      048076 BF 84 03         [24] 1272 	cjne	r7,#0x84,00139$
      048079 02 81 53         [24] 1273 	ljmp	00104$
      04807C                       1274 00139$:
      04807C 02 81 5C         [24] 1275 	ljmp	00105$
                                   1276 ;	server.c:85: case 0x81:
      04807F                       1277 00101$:
                                   1278 ;	server.c:87: printf("\r\nT:%d H:%d",recv_buf[2],recv_buf[3]);
      04807F 90 00 0A         [24] 1279 	mov	dptr,#(_recv_buf + 0x0003)
      048082 E0               [24] 1280 	movx	a,@dptr
      048083 FF               [12] 1281 	mov	r7,a
      048084 7E 00            [12] 1282 	mov	r6,#0x00
      048086 90 00 09         [24] 1283 	mov	dptr,#(_recv_buf + 0x0002)
      048089 E0               [24] 1284 	movx	a,@dptr
      04808A FD               [12] 1285 	mov	r5,a
      04808B 7C 00            [12] 1286 	mov	r4,#0x00
      04808D C0 07            [24] 1287 	push	ar7
      04808F C0 06            [24] 1288 	push	ar6
      048091 C0 05            [24] 1289 	push	ar5
      048093 C0 04            [24] 1290 	push	ar4
      048095 74 FF            [12] 1291 	mov	a,#___str_0
      048097 C0 E0            [24] 1292 	push	acc
      048099 74 73            [12] 1293 	mov	a,#(___str_0 >> 8)
      04809B C0 E0            [24] 1294 	push	acc
      04809D 74 80            [12] 1295 	mov	a,#0x80
      04809F C0 E0            [24] 1296 	push	acc
      0480A1 78 21            [12] 1297 	mov	r0,#_printf
      0480A3 79 50            [12] 1298 	mov	r1,#(_printf >> 8)
      0480A5 7A 00            [12] 1299 	mov	r2,#(_printf >> 16)
      0480A7 12 05 65         [24] 1300 	lcall	__sdcc_banked_call
      0480AA E5 81            [12] 1301 	mov	a,sp
      0480AC 24 F9            [12] 1302 	add	a,#0xf9
      0480AE F5 81            [12] 1303 	mov	sp,a
                                   1304 ;	server.c:90: temp = recv_buf[2]/10;
      0480B0 90 00 09         [24] 1305 	mov	dptr,#(_recv_buf + 0x0002)
      0480B3 E0               [24] 1306 	movx	a,@dptr
      0480B4 FF               [12] 1307 	mov	r7,a
      0480B5 7E 00            [12] 1308 	mov	r6,#0x00
      0480B7 74 0A            [12] 1309 	mov	a,#0x0a
      0480B9 C0 E0            [24] 1310 	push	acc
      0480BB E4               [12] 1311 	clr	a
      0480BC C0 E0            [24] 1312 	push	acc
      0480BE 8F 82            [24] 1313 	mov	dpl,r7
      0480C0 8E 83            [24] 1314 	mov	dph,r6
      0480C2 12 53 33         [24] 1315 	lcall	__divsint
      0480C5 AE 82            [24] 1316 	mov	r6,dpl
      0480C7 15 81            [12] 1317 	dec	sp
      0480C9 15 81            [12] 1318 	dec	sp
                                   1319 ;	server.c:91: TempHumidity[2] = temp+0x30;
      0480CB 74 30            [12] 1320 	mov	a,#0x30
      0480CD 2E               [12] 1321 	add	a,r6
      0480CE 90 18 22         [24] 1322 	mov	dptr,#(_TempHumidity + 0x0002)
      0480D1 F0               [24] 1323 	movx	@dptr,a
                                   1324 ;	server.c:93: temp = recv_buf[2]%10;
      0480D2 90 00 09         [24] 1325 	mov	dptr,#(_recv_buf + 0x0002)
      0480D5 E0               [24] 1326 	movx	a,@dptr
      0480D6 FF               [12] 1327 	mov	r7,a
      0480D7 7E 00            [12] 1328 	mov	r6,#0x00
      0480D9 74 0A            [12] 1329 	mov	a,#0x0a
      0480DB C0 E0            [24] 1330 	push	acc
      0480DD E4               [12] 1331 	clr	a
      0480DE C0 E0            [24] 1332 	push	acc
      0480E0 8F 82            [24] 1333 	mov	dpl,r7
      0480E2 8E 83            [24] 1334 	mov	dph,r6
      0480E4 12 52 46         [24] 1335 	lcall	__modsint
      0480E7 AE 82            [24] 1336 	mov	r6,dpl
      0480E9 15 81            [12] 1337 	dec	sp
      0480EB 15 81            [12] 1338 	dec	sp
                                   1339 ;	server.c:94: TempHumidity[3] = temp+0x30;		
      0480ED 74 30            [12] 1340 	mov	a,#0x30
      0480EF 2E               [12] 1341 	add	a,r6
      0480F0 90 18 23         [24] 1342 	mov	dptr,#(_TempHumidity + 0x0003)
      0480F3 F0               [24] 1343 	movx	@dptr,a
                                   1344 ;	server.c:97: temp = recv_buf[3]/10;
      0480F4 90 00 0A         [24] 1345 	mov	dptr,#(_recv_buf + 0x0003)
      0480F7 E0               [24] 1346 	movx	a,@dptr
      0480F8 FF               [12] 1347 	mov	r7,a
      0480F9 7E 00            [12] 1348 	mov	r6,#0x00
      0480FB 74 0A            [12] 1349 	mov	a,#0x0a
      0480FD C0 E0            [24] 1350 	push	acc
      0480FF E4               [12] 1351 	clr	a
      048100 C0 E0            [24] 1352 	push	acc
      048102 8F 82            [24] 1353 	mov	dpl,r7
      048104 8E 83            [24] 1354 	mov	dph,r6
      048106 12 53 33         [24] 1355 	lcall	__divsint
      048109 AE 82            [24] 1356 	mov	r6,dpl
      04810B 15 81            [12] 1357 	dec	sp
      04810D 15 81            [12] 1358 	dec	sp
                                   1359 ;	server.c:98: TempHumidity[8] = temp+0x30;
      04810F 74 30            [12] 1360 	mov	a,#0x30
      048111 2E               [12] 1361 	add	a,r6
      048112 90 18 28         [24] 1362 	mov	dptr,#(_TempHumidity + 0x0008)
      048115 F0               [24] 1363 	movx	@dptr,a
                                   1364 ;	server.c:100: temp = recv_buf[3]%10;
      048116 90 00 0A         [24] 1365 	mov	dptr,#(_recv_buf + 0x0003)
      048119 E0               [24] 1366 	movx	a,@dptr
      04811A FF               [12] 1367 	mov	r7,a
      04811B 7E 00            [12] 1368 	mov	r6,#0x00
      04811D 74 0A            [12] 1369 	mov	a,#0x0a
      04811F C0 E0            [24] 1370 	push	acc
      048121 E4               [12] 1371 	clr	a
      048122 C0 E0            [24] 1372 	push	acc
      048124 8F 82            [24] 1373 	mov	dpl,r7
      048126 8E 83            [24] 1374 	mov	dph,r6
      048128 12 52 46         [24] 1375 	lcall	__modsint
      04812B AE 82            [24] 1376 	mov	r6,dpl
      04812D AF 83            [24] 1377 	mov	r7,dph
      04812F 15 81            [12] 1378 	dec	sp
      048131 15 81            [12] 1379 	dec	sp
                                   1380 ;	server.c:101: TempHumidity[9] = temp+0x30;
      048133 74 30            [12] 1381 	mov	a,#0x30
      048135 2E               [12] 1382 	add	a,r6
      048136 FE               [12] 1383 	mov	r6,a
      048137 90 18 29         [24] 1384 	mov	dptr,#(_TempHumidity + 0x0009)
      04813A F0               [24] 1385 	movx	@dptr,a
                                   1386 ;	server.c:103: break;
                                   1387 ;	server.c:104: case 0x82:
      04813B 80 1F            [24] 1388 	sjmp	00105$
      04813D                       1389 00102$:
                                   1390 ;	server.c:107: sensor_flag[1] = recv_buf[2];
      04813D 90 00 09         [24] 1391 	mov	dptr,#(_recv_buf + 0x0002)
      048140 E0               [24] 1392 	movx	a,@dptr
      048141 FF               [12] 1393 	mov	r7,a
      048142 90 00 29         [24] 1394 	mov	dptr,#(_sensor_flag + 0x0001)
      048145 F0               [24] 1395 	movx	@dptr,a
                                   1396 ;	server.c:108: break;
                                   1397 ;	server.c:109: case 0x83:
      048146 80 14            [24] 1398 	sjmp	00105$
      048148                       1399 00103$:
                                   1400 ;	server.c:112: sensor_flag[2] = recv_buf[2];
      048148 90 00 09         [24] 1401 	mov	dptr,#(_recv_buf + 0x0002)
      04814B E0               [24] 1402 	movx	a,@dptr
      04814C FF               [12] 1403 	mov	r7,a
      04814D 90 00 2A         [24] 1404 	mov	dptr,#(_sensor_flag + 0x0002)
      048150 F0               [24] 1405 	movx	@dptr,a
                                   1406 ;	server.c:113: break;
                                   1407 ;	server.c:114: case 0x84:
      048151 80 09            [24] 1408 	sjmp	00105$
      048153                       1409 00104$:
                                   1410 ;	server.c:117: sensor_flag[3] = recv_buf[2];
      048153 90 00 09         [24] 1411 	mov	dptr,#(_recv_buf + 0x0002)
      048156 E0               [24] 1412 	movx	a,@dptr
      048157 FF               [12] 1413 	mov	r7,a
      048158 90 00 2B         [24] 1414 	mov	dptr,#(_sensor_flag + 0x0003)
      04815B F0               [24] 1415 	movx	@dptr,a
                                   1416 ;	server.c:119: } 	
      04815C                       1417 00105$:
                                   1418 ;	server.c:120: OLED_P8x16Str(0,2,TempHumidity);
      04815C 74 20            [12] 1419 	mov	a,#_TempHumidity
      04815E C0 E0            [24] 1420 	push	acc
      048160 74 18            [12] 1421 	mov	a,#(_TempHumidity >> 8)
      048162 C0 E0            [24] 1422 	push	acc
      048164 E4               [12] 1423 	clr	a
      048165 C0 E0            [24] 1424 	push	acc
      048167 74 02            [12] 1425 	mov	a,#0x02
      048169 C0 E0            [24] 1426 	push	acc
      04816B 75 82 00         [24] 1427 	mov	dpl,#0x00
      04816E 78 FF            [12] 1428 	mov	r0,#_OLED_P8x16Str
      048170 79 B5            [12] 1429 	mov	r1,#(_OLED_P8x16Str >> 8)
      048172 7A 02            [12] 1430 	mov	r2,#(_OLED_P8x16Str >> 16)
      048174 12 05 65         [24] 1431 	lcall	__sdcc_banked_call
      048177 E5 81            [12] 1432 	mov	a,sp
      048179 24 FC            [12] 1433 	add	a,#0xfc
      04817B F5 81            [12] 1434 	mov	sp,a
                                   1435 ;	server.c:122: optoc_smoke[6]  = sensor_flag[1] + 0x30;
      04817D 90 00 29         [24] 1436 	mov	dptr,#(_sensor_flag + 0x0001)
      048180 E0               [24] 1437 	movx	a,@dptr
      048181 24 30            [12] 1438 	add	a,#0x30
      048183 90 18 31         [24] 1439 	mov	dptr,#(_optoc_smoke + 0x0006)
      048186 F0               [24] 1440 	movx	@dptr,a
                                   1441 ;	server.c:123: optoc_smoke[15] = sensor_flag[3] + 0x30;
      048187 90 00 2B         [24] 1442 	mov	dptr,#(_sensor_flag + 0x0003)
      04818A E0               [24] 1443 	movx	a,@dptr
      04818B 24 30            [12] 1444 	add	a,#0x30
      04818D 90 18 3A         [24] 1445 	mov	dptr,#(_optoc_smoke + 0x000f)
      048190 F0               [24] 1446 	movx	@dptr,a
                                   1447 ;	server.c:124: OLED_P8x16Str(0,4,optoc_smoke);
      048191 74 2B            [12] 1448 	mov	a,#_optoc_smoke
      048193 C0 E0            [24] 1449 	push	acc
      048195 74 18            [12] 1450 	mov	a,#(_optoc_smoke >> 8)
      048197 C0 E0            [24] 1451 	push	acc
      048199 E4               [12] 1452 	clr	a
      04819A C0 E0            [24] 1453 	push	acc
      04819C 74 04            [12] 1454 	mov	a,#0x04
      04819E C0 E0            [24] 1455 	push	acc
      0481A0 75 82 00         [24] 1456 	mov	dpl,#0x00
      0481A3 78 FF            [12] 1457 	mov	r0,#_OLED_P8x16Str
      0481A5 79 B5            [12] 1458 	mov	r1,#(_OLED_P8x16Str >> 8)
      0481A7 7A 02            [12] 1459 	mov	r2,#(_OLED_P8x16Str >> 16)
      0481A9 12 05 65         [24] 1460 	lcall	__sdcc_banked_call
      0481AC E5 81            [12] 1461 	mov	a,sp
      0481AE 24 FC            [12] 1462 	add	a,#0xfc
      0481B0 F5 81            [12] 1463 	mov	sp,a
                                   1464 ;	server.c:126: vibra[6]  = sensor_flag[2] + 0x30;			
      0481B2 90 00 2A         [24] 1465 	mov	dptr,#(_sensor_flag + 0x0002)
      0481B5 E0               [24] 1466 	movx	a,@dptr
      0481B6 24 30            [12] 1467 	add	a,#0x30
      0481B8 90 18 42         [24] 1468 	mov	dptr,#(_vibra + 0x0006)
      0481BB F0               [24] 1469 	movx	@dptr,a
                                   1470 ;	server.c:127: OLED_P8x16Str(0,6,vibra);
      0481BC 74 3C            [12] 1471 	mov	a,#_vibra
      0481BE C0 E0            [24] 1472 	push	acc
      0481C0 74 18            [12] 1473 	mov	a,#(_vibra >> 8)
      0481C2 C0 E0            [24] 1474 	push	acc
      0481C4 E4               [12] 1475 	clr	a
      0481C5 C0 E0            [24] 1476 	push	acc
      0481C7 74 06            [12] 1477 	mov	a,#0x06
      0481C9 C0 E0            [24] 1478 	push	acc
      0481CB 75 82 00         [24] 1479 	mov	dpl,#0x00
      0481CE 78 FF            [12] 1480 	mov	r0,#_OLED_P8x16Str
      0481D0 79 B5            [12] 1481 	mov	r1,#(_OLED_P8x16Str >> 8)
      0481D2 7A 02            [12] 1482 	mov	r2,#(_OLED_P8x16Str >> 16)
      0481D4 12 05 65         [24] 1483 	lcall	__sdcc_banked_call
      0481D7 E5 81            [12] 1484 	mov	a,sp
      0481D9 24 FC            [12] 1485 	add	a,#0xfc
      0481DB F5 81            [12] 1486 	mov	sp,a
      0481DD                       1487 00107$:
                                   1488 ;	server.c:129: return;
                                   1489 ;	server.c:130: }
      0481DD 02 05 77         [24] 1490 	ljmp	__sdcc_banked_ret
                                   1491 ;------------------------------------------------------------
                                   1492 ;Allocation info for local variables in function 'process_thread_udp_server_process'
                                   1493 ;------------------------------------------------------------
                                   1494 ;ev                        Allocated to stack - sp -3
                                   1495 ;data                      Allocated to stack - sp -6
                                   1496 ;process_pt                Allocated to registers r5 r6 r7 
                                   1497 ;PT_YIELD_FLAG             Allocated to registers r4 
                                   1498 ;------------------------------------------------------------
                                   1499 ;	server.c:136: PROCESS_THREAD(udp_server_process, ev, data)
                                   1500 ;	-----------------------------------------
                                   1501 ;	 function process_thread_udp_server_process
                                   1502 ;	-----------------------------------------
      0481E0                       1503 _process_thread_udp_server_process:
                                   1504 ;	server.c:138: PROCESS_BEGIN();
      0481E0 AD 82            [24] 1505 	mov	r5,dpl
      0481E2 AE 83            [24] 1506 	mov	r6,dph
      0481E4 AF F0            [24] 1507 	mov	r7,b
      0481E6 7C 01            [12] 1508 	mov	r4,#0x01
      0481E8 12 50 65         [24] 1509 	lcall	__gptrget
      0481EB FA               [12] 1510 	mov	r2,a
      0481EC A3               [24] 1511 	inc	dptr
      0481ED 12 50 65         [24] 1512 	lcall	__gptrget
      0481F0 FB               [12] 1513 	mov	r3,a
      0481F1 BA 00 05         [24] 1514 	cjne	r2,#0x00,00136$
      0481F4 BB 00 02         [24] 1515 	cjne	r3,#0x00,00136$
      0481F7 80 0C            [24] 1516 	sjmp	00101$
      0481F9                       1517 00136$:
      0481F9 BA 98 06         [24] 1518 	cjne	r2,#0x98,00137$
      0481FC BB 00 03         [24] 1519 	cjne	r3,#0x00,00137$
      0481FF 02 83 22         [24] 1520 	ljmp	00102$
      048202                       1521 00137$:
      048202 02 83 4F         [24] 1522 	ljmp	00113$
      048205                       1523 00101$:
                                   1524 ;	server.c:140: server_conn = udp_new(NULL, UIP_HTONS(0), NULL);
      048205 C0 05            [24] 1525 	push	ar5
      048207 C0 06            [24] 1526 	push	ar6
      048209 C0 07            [24] 1527 	push	ar7
      04820B C0 06            [24] 1528 	push	ar6
      04820D C0 05            [24] 1529 	push	ar5
      04820F E4               [12] 1530 	clr	a
      048210 C0 E0            [24] 1531 	push	acc
      048212 C0 E0            [24] 1532 	push	acc
      048214 C0 E0            [24] 1533 	push	acc
      048216 C0 E0            [24] 1534 	push	acc
      048218 C0 E0            [24] 1535 	push	acc
      04821A 90 00 00         [24] 1536 	mov	dptr,#0x0000
      04821D 75 F0 00         [24] 1537 	mov	b,#0x00
      048220 78 FD            [12] 1538 	mov	r0,#_udp_new
      048222 79 83            [12] 1539 	mov	r1,#(_udp_new >> 8)
      048224 7A 02            [12] 1540 	mov	r2,#(_udp_new >> 16)
      048226 12 05 65         [24] 1541 	lcall	__sdcc_banked_call
      048229 AA 82            [24] 1542 	mov	r2,dpl
      04822B AB 83            [24] 1543 	mov	r3,dph
      04822D AF F0            [24] 1544 	mov	r7,b
      04822F E5 81            [12] 1545 	mov	a,sp
      048231 24 FB            [12] 1546 	add	a,#0xfb
      048233 F5 81            [12] 1547 	mov	sp,a
      048235 D0 05            [24] 1548 	pop	ar5
      048237 D0 06            [24] 1549 	pop	ar6
      048239 90 00 04         [24] 1550 	mov	dptr,#_server_conn
      04823C EA               [12] 1551 	mov	a,r2
      04823D F0               [24] 1552 	movx	@dptr,a
      04823E EB               [12] 1553 	mov	a,r3
      04823F A3               [24] 1554 	inc	dptr
      048240 F0               [24] 1555 	movx	@dptr,a
      048241 EF               [12] 1556 	mov	a,r7
      048242 A3               [24] 1557 	inc	dptr
      048243 F0               [24] 1558 	movx	@dptr,a
                                   1559 ;	server.c:141: udp_bind(server_conn, UIP_HTONS(3000));
      048244 74 10            [12] 1560 	mov	a,#0x10
      048246 2A               [12] 1561 	add	a,r2
      048247 FA               [12] 1562 	mov	r2,a
      048248 E4               [12] 1563 	clr	a
      048249 3B               [12] 1564 	addc	a,r3
      04824A FB               [12] 1565 	mov	r3,a
      04824B 8A 82            [24] 1566 	mov	dpl,r2
      04824D 8B 83            [24] 1567 	mov	dph,r3
      04824F 8F F0            [24] 1568 	mov	b,r7
      048251 74 0B            [12] 1569 	mov	a,#0x0b
      048253 12 4A 47         [24] 1570 	lcall	__gptrput
      048256 A3               [24] 1571 	inc	dptr
      048257 74 B8            [12] 1572 	mov	a,#0xb8
      048259 12 4A 47         [24] 1573 	lcall	__gptrput
                                   1574 ;	server.c:143: memset(&sensor_flag[0],0,4);
      04825C C0 07            [24] 1575 	push	ar7
      04825E C0 06            [24] 1576 	push	ar6
      048260 C0 05            [24] 1577 	push	ar5
      048262 74 04            [12] 1578 	mov	a,#0x04
      048264 C0 E0            [24] 1579 	push	acc
      048266 E4               [12] 1580 	clr	a
      048267 C0 E0            [24] 1581 	push	acc
      048269 C0 E0            [24] 1582 	push	acc
      04826B 90 00 28         [24] 1583 	mov	dptr,#_sensor_flag
      04826E 75 F0 00         [24] 1584 	mov	b,#0x00
      048271 78 5C            [12] 1585 	mov	r0,#_memset
      048273 79 4F            [12] 1586 	mov	r1,#(_memset >> 8)
      048275 7A 00            [12] 1587 	mov	r2,#(_memset >> 16)
      048277 12 05 65         [24] 1588 	lcall	__sdcc_banked_call
      04827A 15 81            [12] 1589 	dec	sp
      04827C 15 81            [12] 1590 	dec	sp
      04827E 15 81            [12] 1591 	dec	sp
                                   1592 ;	server.c:145: OLED_P8x16Str(0,0,"I am server!");//显示屏显示		
      048280 74 11            [12] 1593 	mov	a,#___str_1
      048282 C0 E0            [24] 1594 	push	acc
      048284 74 74            [12] 1595 	mov	a,#(___str_1 >> 8)
      048286 C0 E0            [24] 1596 	push	acc
      048288 74 80            [12] 1597 	mov	a,#0x80
      04828A C0 E0            [24] 1598 	push	acc
      04828C E4               [12] 1599 	clr	a
      04828D C0 E0            [24] 1600 	push	acc
      04828F 75 82 00         [24] 1601 	mov	dpl,#0x00
      048292 78 FF            [12] 1602 	mov	r0,#_OLED_P8x16Str
      048294 79 B5            [12] 1603 	mov	r1,#(_OLED_P8x16Str >> 8)
      048296 7A 02            [12] 1604 	mov	r2,#(_OLED_P8x16Str >> 16)
      048298 12 05 65         [24] 1605 	lcall	__sdcc_banked_call
      04829B E5 81            [12] 1606 	mov	a,sp
      04829D 24 FC            [12] 1607 	add	a,#0xfc
      04829F F5 81            [12] 1608 	mov	sp,a
                                   1609 ;	server.c:146: OLED_P8x16Str(0,2,TempHumidity);//显示温湿度提示信息	
      0482A1 74 20            [12] 1610 	mov	a,#_TempHumidity
      0482A3 C0 E0            [24] 1611 	push	acc
      0482A5 74 18            [12] 1612 	mov	a,#(_TempHumidity >> 8)
      0482A7 C0 E0            [24] 1613 	push	acc
      0482A9 E4               [12] 1614 	clr	a
      0482AA C0 E0            [24] 1615 	push	acc
      0482AC 74 02            [12] 1616 	mov	a,#0x02
      0482AE C0 E0            [24] 1617 	push	acc
      0482B0 75 82 00         [24] 1618 	mov	dpl,#0x00
      0482B3 78 FF            [12] 1619 	mov	r0,#_OLED_P8x16Str
      0482B5 79 B5            [12] 1620 	mov	r1,#(_OLED_P8x16Str >> 8)
      0482B7 7A 02            [12] 1621 	mov	r2,#(_OLED_P8x16Str >> 16)
      0482B9 12 05 65         [24] 1622 	lcall	__sdcc_banked_call
      0482BC E5 81            [12] 1623 	mov	a,sp
      0482BE 24 FC            [12] 1624 	add	a,#0xfc
      0482C0 F5 81            [12] 1625 	mov	sp,a
                                   1626 ;	server.c:147: OLED_P8x16Str(0,4,optoc_smoke);//显示光电开关及烟雾传感器提示信息		
      0482C2 74 2B            [12] 1627 	mov	a,#_optoc_smoke
      0482C4 C0 E0            [24] 1628 	push	acc
      0482C6 74 18            [12] 1629 	mov	a,#(_optoc_smoke >> 8)
      0482C8 C0 E0            [24] 1630 	push	acc
      0482CA E4               [12] 1631 	clr	a
      0482CB C0 E0            [24] 1632 	push	acc
      0482CD 74 04            [12] 1633 	mov	a,#0x04
      0482CF C0 E0            [24] 1634 	push	acc
      0482D1 75 82 00         [24] 1635 	mov	dpl,#0x00
      0482D4 78 FF            [12] 1636 	mov	r0,#_OLED_P8x16Str
      0482D6 79 B5            [12] 1637 	mov	r1,#(_OLED_P8x16Str >> 8)
      0482D8 7A 02            [12] 1638 	mov	r2,#(_OLED_P8x16Str >> 16)
      0482DA 12 05 65         [24] 1639 	lcall	__sdcc_banked_call
      0482DD E5 81            [12] 1640 	mov	a,sp
      0482DF 24 FC            [12] 1641 	add	a,#0xfc
      0482E1 F5 81            [12] 1642 	mov	sp,a
                                   1643 ;	server.c:148: OLED_P8x16Str(0,6,vibra);//显示振动提示信息
      0482E3 74 3C            [12] 1644 	mov	a,#_vibra
      0482E5 C0 E0            [24] 1645 	push	acc
      0482E7 74 18            [12] 1646 	mov	a,#(_vibra >> 8)
      0482E9 C0 E0            [24] 1647 	push	acc
      0482EB E4               [12] 1648 	clr	a
      0482EC C0 E0            [24] 1649 	push	acc
      0482EE 74 06            [12] 1650 	mov	a,#0x06
      0482F0 C0 E0            [24] 1651 	push	acc
      0482F2 75 82 00         [24] 1652 	mov	dpl,#0x00
      0482F5 78 FF            [12] 1653 	mov	r0,#_OLED_P8x16Str
      0482F7 79 B5            [12] 1654 	mov	r1,#(_OLED_P8x16Str >> 8)
      0482F9 7A 02            [12] 1655 	mov	r2,#(_OLED_P8x16Str >> 16)
      0482FB 12 05 65         [24] 1656 	lcall	__sdcc_banked_call
      0482FE E5 81            [12] 1657 	mov	a,sp
      048300 24 FC            [12] 1658 	add	a,#0xfc
      048302 F5 81            [12] 1659 	mov	sp,a
      048304 D0 05            [24] 1660 	pop	ar5
      048306 D0 06            [24] 1661 	pop	ar6
      048308 D0 07            [24] 1662 	pop	ar7
                                   1663 ;	server.c:158: PROCESS_END();
      04830A D0 07            [24] 1664 	pop	ar7
      04830C D0 06            [24] 1665 	pop	ar6
      04830E D0 05            [24] 1666 	pop	ar5
                                   1667 ;	server.c:150: while(1) 
      048310                       1668 00111$:
                                   1669 ;	server.c:152: PROCESS_YIELD();
      048310 7C 00            [12] 1670 	mov	r4,#0x00
      048312 8D 82            [24] 1671 	mov	dpl,r5
      048314 8E 83            [24] 1672 	mov	dph,r6
      048316 8F F0            [24] 1673 	mov	b,r7
      048318 74 98            [12] 1674 	mov	a,#0x98
      04831A 12 4A 47         [24] 1675 	lcall	__gptrput
      04831D A3               [24] 1676 	inc	dptr
      04831E E4               [12] 1677 	clr	a
      04831F 12 4A 47         [24] 1678 	lcall	__gptrput
      048322                       1679 00102$:
      048322 EC               [12] 1680 	mov	a,r4
      048323 70 05            [24] 1681 	jnz	00106$
      048325 75 82 01         [24] 1682 	mov	dpl,#0x01
      048328 80 36            [24] 1683 	sjmp	00114$
      04832A                       1684 00106$:
                                   1685 ;	server.c:153: if(ev == tcpip_event) 
      04832A 90 00 2C         [24] 1686 	mov	dptr,#_tcpip_event
      04832D E0               [24] 1687 	movx	a,@dptr
      04832E FC               [12] 1688 	mov	r4,a
      04832F E5 81            [12] 1689 	mov	a,sp
      048331 24 FD            [12] 1690 	add	a,#0xfd
      048333 F8               [12] 1691 	mov	r0,a
      048334 E6               [12] 1692 	mov	a,@r0
      048335 B5 04 D8         [24] 1693 	cjne	a,ar4,00111$
                                   1694 ;	server.c:155: tcpip_handler();
      048338 C0 07            [24] 1695 	push	ar7
      04833A C0 06            [24] 1696 	push	ar6
      04833C C0 05            [24] 1697 	push	ar5
      04833E 78 00            [12] 1698 	mov	r0,#_tcpip_handler
      048340 79 80            [12] 1699 	mov	r1,#(_tcpip_handler >> 8)
      048342 7A 04            [12] 1700 	mov	r2,#(_tcpip_handler >> 16)
      048344 12 05 65         [24] 1701 	lcall	__sdcc_banked_call
      048347 D0 05            [24] 1702 	pop	ar5
      048349 D0 06            [24] 1703 	pop	ar6
      04834B D0 07            [24] 1704 	pop	ar7
                                   1705 ;	server.c:158: PROCESS_END();
      04834D 80 C1            [24] 1706 	sjmp	00111$
      04834F                       1707 00113$:
      04834F 8D 82            [24] 1708 	mov	dpl,r5
      048351 8E 83            [24] 1709 	mov	dph,r6
      048353 8F F0            [24] 1710 	mov	b,r7
      048355 E4               [12] 1711 	clr	a
      048356 12 4A 47         [24] 1712 	lcall	__gptrput
      048359 A3               [24] 1713 	inc	dptr
      04835A 12 4A 47         [24] 1714 	lcall	__gptrput
      04835D 75 82 03         [24] 1715 	mov	dpl,#0x03
      048360                       1716 00114$:
                                   1717 ;	server.c:159: }
      048360 02 05 77         [24] 1718 	ljmp	__sdcc_banked_ret
                                   1719 	.area CSEG    (CODE)
                                   1720 	.area CONST   (CODE)
      0073FF                       1721 ___str_0:
      0073FF 0D                    1722 	.db 0x0d
      007400 0A                    1723 	.db 0x0a
      007401 54 3A 25 64 20 48 3A  1724 	.ascii "T:%d H:%d"
             25 64
      00740A 00                    1725 	.db 0x00
      00740B                       1726 _autostart_processes:
      00740B 4D 18 00              1727 	.byte _udp_server_process, (_udp_server_process >> 8),#0x00
                                   1728 ; generic printIvalPtr
      00740E 00 00 00              1729 	.byte #0x00,#0x00,#0x00
      007411                       1730 ___str_1:
      007411 49 20 61 6D 20 73 65  1731 	.ascii "I am server!"
             72 76 65 72 21
      00741D 00                    1732 	.db 0x00
      00741E                       1733 ___str_8:
      00741E 55 44 50 20 73 65 72  1734 	.ascii "UDP server process"
             76 65 72 20 70 72 6F
             63 65 73 73
      007430 00                    1735 	.db 0x00
                                   1736 	.area XINIT   (CODE)
      007E1A                       1737 __xinit__atmophere_press:
      007E1A 00 00 00 00           1738 	.byte #0x00,#0x00,#0x00,#0x00	;  0.000000e+00
      007E1E                       1739 __xinit__TempHumidity:
      007E1E 48 3A 32 32 20 20 54  1740 	.ascii "H:22  T:33"
             3A 33 33
      007E28 00                    1741 	.db 0x00
      007E29                       1742 __xinit__optoc_smoke:
      007E29 6F 70 74 6F 63 3A 30  1743 	.ascii "optoc:0  smoke:0"
             20 20 73 6D 6F 6B 65
             3A 30
      007E39 00                    1744 	.db 0x00
      007E3A                       1745 __xinit__vibra:
      007E3A 76 69 62 72 61 3A 31  1746 	.ascii "vibra:1         "
             20 20 20 20 20 20 20
             20 20
      007E4A 00                    1747 	.db 0x00
      007E4B                       1748 __xinit__udp_server_process:
                                   1749 ; generic printIvalPtr
      007E4B 00 00 00              1750 	.byte #0x00,#0x00,#0x00
      007E4E 1E 74 80              1751 	.byte ___str_8, (___str_8 >> 8),#0x80
      007E51 E0 81 04              1752 	.byte _process_thread_udp_server_process, (_process_thread_udp_server_process >> 8), (_process_thread_udp_server_process >> 16)
      007E54 00 00                 1753 	.byte #0x00, #0x00
      007E56 00                    1754 	.db #0x00	; 0
      007E57 00                    1755 	.db #0x00	; 0
                                   1756 	.area CABS    (ABS,CODE)
