                                      1 ;--------------------------------------------------------
                                      2 ; File Created by SDCC : free open source ANSI-C Compiler
                                      3 ; Version 3.8.4 #10774 (Linux)
                                      4 ;--------------------------------------------------------
                                      5 	.module client_temp_humi
                                      6 	.optsdcc -mmcs51 --model-huge
                                      7 	
                                      8 ;--------------------------------------------------------
                                      9 ; Public variables in this module
                                     10 ;--------------------------------------------------------
                                     11 	.globl _autostart_processes
                                     12 	.globl _send_cmd
                                     13 	.globl _SHT2x_ReadTemp
                                     14 	.globl _SHT2x_ReadHumi
                                     15 	.globl _SHT2x_GetHumi
                                     16 	.globl _SHT2x_GetTemp
                                     17 	.globl _printf
                                     18 	.globl _udp_new
                                     19 	.globl _etimer_expired
                                     20 	.globl _etimer_restart
                                     21 	.globl _etimer_set
                                     22 	.globl _memset
                                     23 	.globl _ACTIVE
                                     24 	.globl _TX_BYTE
                                     25 	.globl _RX_BYTE
                                     26 	.globl _ERR
                                     27 	.globl _FE
                                     28 	.globl _SLAVE
                                     29 	.globl _RE
                                     30 	.globl _MODE
                                     31 	.globl _T3OVFIF
                                     32 	.globl _T3CH0IF
                                     33 	.globl _T3CH1IF
                                     34 	.globl _T4OVFIF
                                     35 	.globl _T4CH0IF
                                     36 	.globl _T4CH1IF
                                     37 	.globl _OVFIM
                                     38 	.globl _B_0
                                     39 	.globl _B_1
                                     40 	.globl _B_2
                                     41 	.globl _B_3
                                     42 	.globl _B_4
                                     43 	.globl _B_5
                                     44 	.globl _B_6
                                     45 	.globl _B_7
                                     46 	.globl _P2IF
                                     47 	.globl _UTX0IF
                                     48 	.globl _UTX1IF
                                     49 	.globl _P1IF
                                     50 	.globl _WDTIF
                                     51 	.globl _ACC_0
                                     52 	.globl _ACC_1
                                     53 	.globl _ACC_2
                                     54 	.globl _ACC_3
                                     55 	.globl _ACC_4
                                     56 	.globl _ACC_5
                                     57 	.globl _ACC_6
                                     58 	.globl _ACC_7
                                     59 	.globl _P
                                     60 	.globl _F1
                                     61 	.globl _OV
                                     62 	.globl _RS0
                                     63 	.globl _RS1
                                     64 	.globl _F0
                                     65 	.globl _AC
                                     66 	.globl _CY
                                     67 	.globl _DMAIF
                                     68 	.globl _T1IF
                                     69 	.globl _T2IF
                                     70 	.globl _T3IF
                                     71 	.globl _T4IF
                                     72 	.globl _P0IF
                                     73 	.globl _STIF
                                     74 	.globl _DMAIE
                                     75 	.globl _T1IE
                                     76 	.globl _T2IE
                                     77 	.globl _T3IE
                                     78 	.globl _T4IE
                                     79 	.globl _P0IE
                                     80 	.globl _RFERRIE
                                     81 	.globl _ADCIE
                                     82 	.globl _URX0IE
                                     83 	.globl _URX1IE
                                     84 	.globl _ENCIE
                                     85 	.globl _STIE
                                     86 	.globl _EA
                                     87 	.globl _P2_0
                                     88 	.globl _P2_1
                                     89 	.globl _P2_2
                                     90 	.globl _P2_3
                                     91 	.globl _P2_4
                                     92 	.globl _P2_5
                                     93 	.globl _P2_6
                                     94 	.globl _P2_7
                                     95 	.globl _ENCIF_0
                                     96 	.globl _ENCIF_1
                                     97 	.globl _P1_0
                                     98 	.globl _P1_1
                                     99 	.globl _P1_2
                                    100 	.globl _P1_3
                                    101 	.globl _P1_4
                                    102 	.globl _P1_5
                                    103 	.globl _P1_6
                                    104 	.globl _P1_7
                                    105 	.globl _IT0
                                    106 	.globl _RFERRIF
                                    107 	.globl _IT1
                                    108 	.globl _URX0IF
                                    109 	.globl _ADCIF
                                    110 	.globl _URX1IF
                                    111 	.globl _P0_0
                                    112 	.globl _P0_1
                                    113 	.globl _P0_2
                                    114 	.globl _P0_3
                                    115 	.globl _P0_4
                                    116 	.globl _P0_5
                                    117 	.globl _P0_6
                                    118 	.globl _P0_7
                                    119 	.globl _WDCTL
                                    120 	.globl _U1GCR
                                    121 	.globl _U1UCR
                                    122 	.globl _U1BAUD
                                    123 	.globl _U1DBUF
                                    124 	.globl _U1CSR
                                    125 	.globl _U0GCR
                                    126 	.globl _U0UCR
                                    127 	.globl _U0BAUD
                                    128 	.globl _U0DBUF
                                    129 	.globl _U0CSR
                                    130 	.globl _TIMIF
                                    131 	.globl _T4CC1
                                    132 	.globl _T4CCTL1
                                    133 	.globl _T4CC0
                                    134 	.globl _T4CCTL0
                                    135 	.globl _T4CTL
                                    136 	.globl _T4CNT
                                    137 	.globl _T3CC1
                                    138 	.globl _T3CCTL1
                                    139 	.globl _T3CC0
                                    140 	.globl _T3CCTL0
                                    141 	.globl _T3CTL
                                    142 	.globl _T3CNT
                                    143 	.globl _T2MSEL
                                    144 	.globl _T2IRQM
                                    145 	.globl _T2MOVF2
                                    146 	.globl _T2MOVF1
                                    147 	.globl _T2MOVF0
                                    148 	.globl _T2M1
                                    149 	.globl _T2M0
                                    150 	.globl _T2IRQF
                                    151 	.globl _T2EVTCFG
                                    152 	.globl _T2CTRL
                                    153 	.globl _T1STAT
                                    154 	.globl _T1CCTL2
                                    155 	.globl _T1CCTL1
                                    156 	.globl _T1CCTL0
                                    157 	.globl _T1CTL
                                    158 	.globl _T1CNTH
                                    159 	.globl _T1CNTL
                                    160 	.globl _T1CC2H
                                    161 	.globl _T1CC2L
                                    162 	.globl _T1CC1H
                                    163 	.globl _T1CC1L
                                    164 	.globl _T1CC0H
                                    165 	.globl _T1CC0L
                                    166 	.globl _CLKCONSTA
                                    167 	.globl _CLKCONCMD
                                    168 	.globl _SLEEPSTA
                                    169 	.globl _SLEEPCMD
                                    170 	.globl _STLOAD
                                    171 	.globl _ST2
                                    172 	.globl _ST1
                                    173 	.globl _ST0
                                    174 	.globl _RFERRF
                                    175 	.globl _RFIRQF0
                                    176 	.globl _RFST
                                    177 	.globl _RFD
                                    178 	.globl _RFIRQF1
                                    179 	.globl _PSBANK
                                    180 	.globl _FMAP
                                    181 	.globl _MEMCTR
                                    182 	.globl __XPAGE
                                    183 	.globl _MPAGE
                                    184 	.globl _PMUX
                                    185 	.globl _P2DIR
                                    186 	.globl _P1DIR
                                    187 	.globl _P0DIR
                                    188 	.globl _P2INP
                                    189 	.globl _P1INP
                                    190 	.globl _P2SEL
                                    191 	.globl _P1SEL
                                    192 	.globl _P0SEL
                                    193 	.globl _APCFG
                                    194 	.globl _PERCFG
                                    195 	.globl _P0INP
                                    196 	.globl _P2IEN
                                    197 	.globl _P1IEN
                                    198 	.globl _P0IEN
                                    199 	.globl _PICTL
                                    200 	.globl _P2IFG
                                    201 	.globl _P1IFG
                                    202 	.globl _P0IFG
                                    203 	.globl _DMAREQ
                                    204 	.globl _DMAARM
                                    205 	.globl _DMA0CFGH
                                    206 	.globl _DMA0CFGL
                                    207 	.globl _DMA1CFGH
                                    208 	.globl _DMA1CFGL
                                    209 	.globl _DMAIRQ
                                    210 	.globl _ENCCS
                                    211 	.globl _ENCDO
                                    212 	.globl _ENCDI
                                    213 	.globl _RNDH
                                    214 	.globl _RNDL
                                    215 	.globl _ADCH
                                    216 	.globl _ADCL
                                    217 	.globl _ADCCON3
                                    218 	.globl _ADCCON2
                                    219 	.globl _ADCCON1
                                    220 	.globl _B
                                    221 	.globl _IRCON2
                                    222 	.globl _ACC
                                    223 	.globl _PSW
                                    224 	.globl _IRCON
                                    225 	.globl _IP1
                                    226 	.globl _IEN1
                                    227 	.globl _IP0
                                    228 	.globl _IEN0
                                    229 	.globl _P2
                                    230 	.globl _S1CON
                                    231 	.globl _IEN2
                                    232 	.globl _S0CON
                                    233 	.globl _DPS
                                    234 	.globl _P1
                                    235 	.globl _TCON
                                    236 	.globl _PCON
                                    237 	.globl _DPH1
                                    238 	.globl _DPL1
                                    239 	.globl _DPH0
                                    240 	.globl _DPL0
                                    241 	.globl _SP
                                    242 	.globl _P0
                                    243 	.globl _udp_client_process
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
      000004                       1123 _buf:
      000004                       1124 	.ds 50
      000036                       1125 _l_conn:
      000036                       1126 	.ds 3
      000039                       1127 _timeout_handler_readseq_65536_524:
      000039                       1128 	.ds 1
      00003A                       1129 _timeout_handler_temp_humi_buf_65536_524:
      00003A                       1130 	.ds 2
      00003C                       1131 _process_thread_udp_client_process_et_65536_529:
      00003C                       1132 	.ds 10
                                   1133 ;--------------------------------------------------------
                                   1134 ; absolute external ram data
                                   1135 ;--------------------------------------------------------
                                   1136 	.area XABS    (ABS,XDATA)
                                   1137 ;--------------------------------------------------------
                                   1138 ; external initialized ram data
                                   1139 ;--------------------------------------------------------
                                   1140 	.area XISEG   (XDATA)
      001878                       1141 _udp_client_process::
      001878                       1142 	.ds 13
                                   1143 	.area HOME    (CODE)
                                   1144 	.area GSINIT0 (CODE)
                                   1145 	.area GSINIT1 (CODE)
                                   1146 	.area GSINIT2 (CODE)
                                   1147 	.area GSINIT3 (CODE)
                                   1148 	.area GSINIT4 (CODE)
                                   1149 	.area GSINIT5 (CODE)
                                   1150 	.area GSINIT  (CODE)
                                   1151 	.area GSFINAL (CODE)
                                   1152 	.area CSEG    (CODE)
                                   1153 ;--------------------------------------------------------
                                   1154 ; global & static initialisations
                                   1155 ;--------------------------------------------------------
                                   1156 	.area HOME    (CODE)
                                   1157 	.area GSINIT  (CODE)
                                   1158 	.area GSFINAL (CODE)
                                   1159 	.area GSINIT  (CODE)
                                   1160 ;------------------------------------------------------------
                                   1161 ;Allocation info for local variables in function 'timeout_handler'
                                   1162 ;------------------------------------------------------------
                                   1163 ;len                       Allocated to stack - sp +3
                                   1164 ;readseq                   Allocated with name '_timeout_handler_readseq_65536_524'
                                   1165 ;temp_humi_buf             Allocated with name '_timeout_handler_temp_humi_buf_65536_524'
                                   1166 ;------------------------------------------------------------
                                   1167 ;	client_temp_humi.c:76: static unsigned char readseq =0; 
      0049A9 90 00 39         [24] 1168 	mov	dptr,#_timeout_handler_readseq_65536_524
      0049AC E4               [12] 1169 	clr	a
      0049AD F0               [24] 1170 	movx	@dptr,a
                                   1171 ;--------------------------------------------------------
                                   1172 ; Home
                                   1173 ;--------------------------------------------------------
                                   1174 	.area HOME    (CODE)
                                   1175 	.area HOME    (CODE)
                                   1176 ;--------------------------------------------------------
                                   1177 ; code
                                   1178 ;--------------------------------------------------------
                                   1179 	.area BANK1   (CODE)
                                   1180 ;------------------------------------------------------------
                                   1181 ;Allocation info for local variables in function 'tcpip_handler'
                                   1182 ;------------------------------------------------------------
                                   1183 ;	client_temp_humi.c:64: static void tcpip_handler(void)
                                   1184 ;	-----------------------------------------
                                   1185 ;	 function tcpip_handler
                                   1186 ;	-----------------------------------------
      048000                       1187 _tcpip_handler:
                           000007  1188 	ar7 = 0x07
                           000006  1189 	ar6 = 0x06
                           000005  1190 	ar5 = 0x05
                           000004  1191 	ar4 = 0x04
                           000003  1192 	ar3 = 0x03
                           000002  1193 	ar2 = 0x02
                           000001  1194 	ar1 = 0x01
                           000000  1195 	ar0 = 0x00
                                   1196 ;	client_temp_humi.c:71: return;
                                   1197 ;	client_temp_humi.c:72: }
      048000 02 05 AD         [24] 1198 	ljmp	__sdcc_banked_ret
                                   1199 ;------------------------------------------------------------
                                   1200 ;Allocation info for local variables in function 'timeout_handler'
                                   1201 ;------------------------------------------------------------
                                   1202 ;len                       Allocated to stack - sp +1
                                   1203 ;readseq                   Allocated with name '_timeout_handler_readseq_65536_524'
                                   1204 ;temp_humi_buf             Allocated with name '_timeout_handler_temp_humi_buf_65536_524'
                                   1205 ;------------------------------------------------------------
                                   1206 ;	client_temp_humi.c:74: static void timeout_handler(void)
                                   1207 ;	-----------------------------------------
                                   1208 ;	 function timeout_handler
                                   1209 ;	-----------------------------------------
      048003                       1210 _timeout_handler:
                                   1211 ;	client_temp_humi.c:79: memset(buf, 0, MAX_PAYLOAD_LEN);
      048003 74 32            [12] 1212 	mov	a,#0x32
      048005 C0 E0            [24] 1213 	push	acc
      048007 E4               [12] 1214 	clr	a
      048008 C0 E0            [24] 1215 	push	acc
      04800A C0 E0            [24] 1216 	push	acc
      04800C 90 00 04         [24] 1217 	mov	dptr,#_buf
      04800F 75 F0 00         [24] 1218 	mov	b,#0x00
      048012 78 01            [12] 1219 	mov	r0,#_memset
      048014 79 4F            [12] 1220 	mov	r1,#(_memset >> 8)
      048016 7A 00            [12] 1221 	mov	r2,#(_memset >> 16)
      048018 12 05 9B         [24] 1222 	lcall	__sdcc_banked_call
      04801B 15 81            [12] 1223 	dec	sp
      04801D 15 81            [12] 1224 	dec	sp
      04801F 15 81            [12] 1225 	dec	sp
                                   1226 ;	client_temp_humi.c:80: readseq++;
      048021 90 00 39         [24] 1227 	mov	dptr,#_timeout_handler_readseq_65536_524
      048024 E0               [24] 1228 	movx	a,@dptr
      048025 24 01            [12] 1229 	add	a,#0x01
      048027 F0               [24] 1230 	movx	@dptr,a
                                   1231 ;	client_temp_humi.c:81: if(readseq%2)
      048028 E0               [24] 1232 	movx	a,@dptr
      048029 30 E0 1B         [24] 1233 	jnb	acc.0,00102$
                                   1234 ;	client_temp_humi.c:83: SHT2x_ReadHumi();
      04802C 78 6B            [12] 1235 	mov	r0,#_SHT2x_ReadHumi
      04802E 79 C6            [12] 1236 	mov	r1,#(_SHT2x_ReadHumi >> 8)
      048030 7A 03            [12] 1237 	mov	r2,#(_SHT2x_ReadHumi >> 16)
      048032 12 05 9B         [24] 1238 	lcall	__sdcc_banked_call
                                   1239 ;	client_temp_humi.c:84: temp_humi_buf[0] = SHT2x_GetHumi();
      048035 78 50            [12] 1240 	mov	r0,#_SHT2x_GetHumi
      048037 79 C6            [12] 1241 	mov	r1,#(_SHT2x_GetHumi >> 8)
      048039 7A 03            [12] 1242 	mov	r2,#(_SHT2x_GetHumi >> 16)
      04803B 12 05 9B         [24] 1243 	lcall	__sdcc_banked_call
      04803E AF 82            [24] 1244 	mov	r7,dpl
      048040 90 00 3A         [24] 1245 	mov	dptr,#_timeout_handler_temp_humi_buf_65536_524
      048043 EF               [12] 1246 	mov	a,r7
      048044 F0               [24] 1247 	movx	@dptr,a
      048045 80 69            [24] 1248 	sjmp	00104$
      048047                       1249 00102$:
                                   1250 ;	client_temp_humi.c:88: printf("temp_humi:send\r\n");
      048047 74 B9            [12] 1251 	mov	a,#___str_0
      048049 C0 E0            [24] 1252 	push	acc
      04804B 74 73            [12] 1253 	mov	a,#(___str_0 >> 8)
      04804D C0 E0            [24] 1254 	push	acc
      04804F 74 80            [12] 1255 	mov	a,#0x80
      048051 C0 E0            [24] 1256 	push	acc
      048053 78 C6            [12] 1257 	mov	r0,#_printf
      048055 79 4F            [12] 1258 	mov	r1,#(_printf >> 8)
      048057 7A 00            [12] 1259 	mov	r2,#(_printf >> 16)
      048059 12 05 9B         [24] 1260 	lcall	__sdcc_banked_call
      04805C 15 81            [12] 1261 	dec	sp
      04805E 15 81            [12] 1262 	dec	sp
      048060 15 81            [12] 1263 	dec	sp
                                   1264 ;	client_temp_humi.c:89: SHT2x_ReadTemp();
      048062 78 07            [12] 1265 	mov	r0,#_SHT2x_ReadTemp
      048064 79 C6            [12] 1266 	mov	r1,#(_SHT2x_ReadTemp >> 8)
      048066 7A 03            [12] 1267 	mov	r2,#(_SHT2x_ReadTemp >> 16)
      048068 12 05 9B         [24] 1268 	lcall	__sdcc_banked_call
                                   1269 ;	client_temp_humi.c:90: temp_humi_buf[1] = SHT2x_GetTemp();
      04806B 78 EC            [12] 1270 	mov	r0,#_SHT2x_GetTemp
      04806D 79 C5            [12] 1271 	mov	r1,#(_SHT2x_GetTemp >> 8)
      04806F 7A 03            [12] 1272 	mov	r2,#(_SHT2x_GetTemp >> 16)
      048071 12 05 9B         [24] 1273 	lcall	__sdcc_banked_call
      048074 AF 82            [24] 1274 	mov	r7,dpl
      048076 90 00 3B         [24] 1275 	mov	dptr,#(_timeout_handler_temp_humi_buf_65536_524 + 0x0001)
      048079 EF               [12] 1276 	mov	a,r7
      04807A F0               [24] 1277 	movx	@dptr,a
                                   1278 ;	client_temp_humi.c:91: send_cmd(l_conn,0x82,0x02,2,&temp_humi_buf[0]);
      04807B 90 00 36         [24] 1279 	mov	dptr,#_l_conn
      04807E E0               [24] 1280 	movx	a,@dptr
      04807F FD               [12] 1281 	mov	r5,a
      048080 A3               [24] 1282 	inc	dptr
      048081 E0               [24] 1283 	movx	a,@dptr
      048082 FE               [12] 1284 	mov	r6,a
      048083 A3               [24] 1285 	inc	dptr
      048084 E0               [24] 1286 	movx	a,@dptr
      048085 FF               [12] 1287 	mov	r7,a
      048086 74 3A            [12] 1288 	mov	a,#_timeout_handler_temp_humi_buf_65536_524
      048088 C0 E0            [24] 1289 	push	acc
      04808A 74 00            [12] 1290 	mov	a,#(_timeout_handler_temp_humi_buf_65536_524 >> 8)
      04808C C0 E0            [24] 1291 	push	acc
      04808E E4               [12] 1292 	clr	a
      04808F C0 E0            [24] 1293 	push	acc
      048091 74 02            [12] 1294 	mov	a,#0x02
      048093 C0 E0            [24] 1295 	push	acc
      048095 C0 E0            [24] 1296 	push	acc
      048097 74 82            [12] 1297 	mov	a,#0x82
      048099 C0 E0            [24] 1298 	push	acc
      04809B 8D 82            [24] 1299 	mov	dpl,r5
      04809D 8E 83            [24] 1300 	mov	dph,r6
      04809F 8F F0            [24] 1301 	mov	b,r7
      0480A1 78 5D            [12] 1302 	mov	r0,#_send_cmd
      0480A3 79 AC            [12] 1303 	mov	r1,#(_send_cmd >> 8)
      0480A5 7A 04            [12] 1304 	mov	r2,#(_send_cmd >> 16)
      0480A7 12 05 9B         [24] 1305 	lcall	__sdcc_banked_call
      0480AA E5 81            [12] 1306 	mov	a,sp
      0480AC 24 FA            [12] 1307 	add	a,#0xfa
      0480AE F5 81            [12] 1308 	mov	sp,a
      0480B0                       1309 00104$:
                                   1310 ;	client_temp_humi.c:93: }
      0480B0 02 05 AD         [24] 1311 	ljmp	__sdcc_banked_ret
                                   1312 ;------------------------------------------------------------
                                   1313 ;Allocation info for local variables in function 'process_thread_udp_client_process'
                                   1314 ;------------------------------------------------------------
                                   1315 ;ev                        Allocated to stack - sp -22
                                   1316 ;data                      Allocated to stack - sp -25
                                   1317 ;process_pt                Allocated to registers r5 r6 r7 
                                   1318 ;ipaddr                    Allocated to stack - sp -15
                                   1319 ;PT_YIELD_FLAG             Allocated to registers r4 
                                   1320 ;sloc0                     Allocated to stack - sp -18
                                   1321 ;et                        Allocated with name '_process_thread_udp_client_process_et_65536_529'
                                   1322 ;------------------------------------------------------------
                                   1323 ;	client_temp_humi.c:97: PROCESS_THREAD(udp_client_process, ev, data)
                                   1324 ;	-----------------------------------------
                                   1325 ;	 function process_thread_udp_client_process
                                   1326 ;	-----------------------------------------
      0480B3                       1327 _process_thread_udp_client_process:
      0480B3 E5 81            [12] 1328 	mov	a,sp
      0480B5 24 13            [12] 1329 	add	a,#0x13
      0480B7 F5 81            [12] 1330 	mov	sp,a
                                   1331 ;	client_temp_humi.c:101: PROCESS_BEGIN();
      0480B9 AD 82            [24] 1332 	mov	r5,dpl
      0480BB AE 83            [24] 1333 	mov	r6,dph
      0480BD AF F0            [24] 1334 	mov	r7,b
      0480BF 7C 01            [12] 1335 	mov	r4,#0x01
      0480C1 12 50 12         [24] 1336 	lcall	__gptrget
      0480C4 FA               [12] 1337 	mov	r2,a
      0480C5 A3               [24] 1338 	inc	dptr
      0480C6 12 50 12         [24] 1339 	lcall	__gptrget
      0480C9 FB               [12] 1340 	mov	r3,a
      0480CA BA 00 05         [24] 1341 	cjne	r2,#0x00,00146$
      0480CD BB 00 02         [24] 1342 	cjne	r3,#0x00,00146$
      0480D0 80 0C            [24] 1343 	sjmp	00101$
      0480D2                       1344 00146$:
      0480D2 BA 7F 06         [24] 1345 	cjne	r2,#0x7f,00147$
      0480D5 BB 00 03         [24] 1346 	cjne	r3,#0x00,00147$
      0480D8 02 82 C3         [24] 1347 	ljmp	00105$
      0480DB                       1348 00147$:
      0480DB 02 83 3C         [24] 1349 	ljmp	00119$
      0480DE                       1350 00101$:
                                   1351 ;	client_temp_humi.c:102: printf("UDP client process started\n");
      0480DE C0 05            [24] 1352 	push	ar5
      0480E0 C0 06            [24] 1353 	push	ar6
      0480E2 C0 07            [24] 1354 	push	ar7
      0480E4 C0 07            [24] 1355 	push	ar7
      0480E6 C0 06            [24] 1356 	push	ar6
      0480E8 C0 05            [24] 1357 	push	ar5
      0480EA 74 D0            [12] 1358 	mov	a,#___str_1
      0480EC C0 E0            [24] 1359 	push	acc
      0480EE 74 73            [12] 1360 	mov	a,#(___str_1 >> 8)
      0480F0 C0 E0            [24] 1361 	push	acc
      0480F2 74 80            [12] 1362 	mov	a,#0x80
      0480F4 C0 E0            [24] 1363 	push	acc
      0480F6 78 C6            [12] 1364 	mov	r0,#_printf
      0480F8 79 4F            [12] 1365 	mov	r1,#(_printf >> 8)
      0480FA 7A 00            [12] 1366 	mov	r2,#(_printf >> 16)
      0480FC 12 05 9B         [24] 1367 	lcall	__sdcc_banked_call
      0480FF 15 81            [12] 1368 	dec	sp
      048101 15 81            [12] 1369 	dec	sp
      048103 15 81            [12] 1370 	dec	sp
      048105 D0 05            [24] 1371 	pop	ar5
      048107 D0 06            [24] 1372 	pop	ar6
      048109 D0 07            [24] 1373 	pop	ar7
                                   1374 ;	client_temp_humi.c:107: uip_ip6addr(&ipaddr, 0xfe80, 0, 0, 0,0x0212,0x4B00,0x094A,0xE320);
      04810B E5 81            [12] 1375 	mov	a,sp
      04810D 24 EE            [12] 1376 	add	a,#0xee
      04810F F8               [12] 1377 	mov	r0,a
      048110 76 FE            [12] 1378 	mov	@r0,#0xfe
      048112 08               [12] 1379 	inc	r0
      048113 76 80            [12] 1380 	mov	@r0,#0x80
      048115 E5 81            [12] 1381 	mov	a,sp
      048117 24 EE            [12] 1382 	add	a,#0xee
      048119 FB               [12] 1383 	mov	r3,a
      04811A 24 02            [12] 1384 	add	a,#0x02
      04811C F8               [12] 1385 	mov	r0,a
      04811D 76 00            [12] 1386 	mov	@r0,#0x00
      04811F 08               [12] 1387 	inc	r0
      048120 76 00            [12] 1388 	mov	@r0,#0x00
      048122 74 04            [12] 1389 	mov	a,#0x04
      048124 2B               [12] 1390 	add	a,r3
      048125 F8               [12] 1391 	mov	r0,a
      048126 76 00            [12] 1392 	mov	@r0,#0x00
      048128 08               [12] 1393 	inc	r0
      048129 76 00            [12] 1394 	mov	@r0,#0x00
      04812B 74 06            [12] 1395 	mov	a,#0x06
      04812D 2B               [12] 1396 	add	a,r3
      04812E F8               [12] 1397 	mov	r0,a
      04812F 76 00            [12] 1398 	mov	@r0,#0x00
      048131 08               [12] 1399 	inc	r0
      048132 76 00            [12] 1400 	mov	@r0,#0x00
      048134 74 08            [12] 1401 	mov	a,#0x08
      048136 2B               [12] 1402 	add	a,r3
      048137 F8               [12] 1403 	mov	r0,a
      048138 76 02            [12] 1404 	mov	@r0,#0x02
      04813A 08               [12] 1405 	inc	r0
      04813B 76 12            [12] 1406 	mov	@r0,#0x12
      04813D 74 0A            [12] 1407 	mov	a,#0x0a
      04813F 2B               [12] 1408 	add	a,r3
      048140 F8               [12] 1409 	mov	r0,a
      048141 76 4B            [12] 1410 	mov	@r0,#0x4b
      048143 08               [12] 1411 	inc	r0
      048144 76 00            [12] 1412 	mov	@r0,#0x00
      048146 74 0C            [12] 1413 	mov	a,#0x0c
      048148 2B               [12] 1414 	add	a,r3
      048149 F8               [12] 1415 	mov	r0,a
      04814A 76 09            [12] 1416 	mov	@r0,#0x09
      04814C 08               [12] 1417 	inc	r0
      04814D 76 4A            [12] 1418 	mov	@r0,#0x4a
      04814F 74 0E            [12] 1419 	mov	a,#0x0e
      048151 2B               [12] 1420 	add	a,r3
      048152 F8               [12] 1421 	mov	r0,a
      048153 76 E3            [12] 1422 	mov	@r0,#0xe3
      048155 08               [12] 1423 	inc	r0
      048156 76 20            [12] 1424 	mov	@r0,#0x20
                                   1425 ;	client_temp_humi.c:109: l_conn = udp_new(&ipaddr, UIP_HTONS(3000), NULL);
      048158 E5 81            [12] 1426 	mov	a,sp
      04815A 24 EE            [12] 1427 	add	a,#0xee
      04815C FA               [12] 1428 	mov	r2,a
      04815D 7B 00            [12] 1429 	mov	r3,#0x00
      04815F 7F 40            [12] 1430 	mov	r7,#0x40
      048161 E4               [12] 1431 	clr	a
      048162 C0 E0            [24] 1432 	push	acc
      048164 C0 E0            [24] 1433 	push	acc
      048166 C0 E0            [24] 1434 	push	acc
      048168 74 0B            [12] 1435 	mov	a,#0x0b
      04816A C0 E0            [24] 1436 	push	acc
      04816C 74 B8            [12] 1437 	mov	a,#0xb8
      04816E C0 E0            [24] 1438 	push	acc
      048170 8A 82            [24] 1439 	mov	dpl,r2
      048172 8B 83            [24] 1440 	mov	dph,r3
      048174 8F F0            [24] 1441 	mov	b,r7
      048176 78 FD            [12] 1442 	mov	r0,#_udp_new
      048178 79 83            [12] 1443 	mov	r1,#(_udp_new >> 8)
      04817A 7A 02            [12] 1444 	mov	r2,#(_udp_new >> 16)
      04817C 12 05 9B         [24] 1445 	lcall	__sdcc_banked_call
      04817F AD 82            [24] 1446 	mov	r5,dpl
      048181 AE 83            [24] 1447 	mov	r6,dph
      048183 AF F0            [24] 1448 	mov	r7,b
      048185 E5 81            [12] 1449 	mov	a,sp
      048187 24 FB            [12] 1450 	add	a,#0xfb
      048189 F5 81            [12] 1451 	mov	sp,a
      04818B 90 00 36         [24] 1452 	mov	dptr,#_l_conn
      04818E ED               [12] 1453 	mov	a,r5
      04818F F0               [24] 1454 	movx	@dptr,a
      048190 EE               [12] 1455 	mov	a,r6
      048191 A3               [24] 1456 	inc	dptr
      048192 F0               [24] 1457 	movx	@dptr,a
      048193 EF               [12] 1458 	mov	a,r7
      048194 A3               [24] 1459 	inc	dptr
      048195 F0               [24] 1460 	movx	@dptr,a
                                   1461 ;	client_temp_humi.c:114: udp_bind(l_conn, UIP_HTONS(LOCAL_CONN_PORT));
      048196 74 10            [12] 1462 	mov	a,#0x10
      048198 2D               [12] 1463 	add	a,r5
      048199 FD               [12] 1464 	mov	r5,a
      04819A E4               [12] 1465 	clr	a
      04819B 3E               [12] 1466 	addc	a,r6
      04819C FE               [12] 1467 	mov	r6,a
      04819D 8D 82            [24] 1468 	mov	dpl,r5
      04819F 8E 83            [24] 1469 	mov	dph,r6
      0481A1 8F F0            [24] 1470 	mov	b,r7
      0481A3 74 0B            [12] 1471 	mov	a,#0x0b
      0481A5 12 49 E0         [24] 1472 	lcall	__gptrput
      0481A8 A3               [24] 1473 	inc	dptr
      0481A9 74 B9            [12] 1474 	mov	a,#0xb9
      0481AB 12 49 E0         [24] 1475 	lcall	__gptrput
                                   1476 ;	client_temp_humi.c:116: printf("Link-Local connection with ");
      0481AE C0 07            [24] 1477 	push	ar7
      0481B0 C0 06            [24] 1478 	push	ar6
      0481B2 C0 05            [24] 1479 	push	ar5
      0481B4 74 EC            [12] 1480 	mov	a,#___str_2
      0481B6 C0 E0            [24] 1481 	push	acc
      0481B8 74 73            [12] 1482 	mov	a,#(___str_2 >> 8)
      0481BA C0 E0            [24] 1483 	push	acc
      0481BC 74 80            [12] 1484 	mov	a,#0x80
      0481BE C0 E0            [24] 1485 	push	acc
      0481C0 78 C6            [12] 1486 	mov	r0,#_printf
      0481C2 79 4F            [12] 1487 	mov	r1,#(_printf >> 8)
      0481C4 7A 00            [12] 1488 	mov	r2,#(_printf >> 16)
      0481C6 12 05 9B         [24] 1489 	lcall	__sdcc_banked_call
      0481C9 15 81            [12] 1490 	dec	sp
      0481CB 15 81            [12] 1491 	dec	sp
      0481CD 15 81            [12] 1492 	dec	sp
      0481CF D0 05            [24] 1493 	pop	ar5
      0481D1 D0 06            [24] 1494 	pop	ar6
      0481D3 D0 07            [24] 1495 	pop	ar7
                                   1496 ;	client_temp_humi.c:118: printf(" local/remote port %u/%u\n",UIP_HTONS(l_conn->lport), UIP_HTONS(l_conn->rport));
      0481D5 90 00 36         [24] 1497 	mov	dptr,#_l_conn
      0481D8 E5 81            [12] 1498 	mov	a,sp
      0481DA 24 EB            [12] 1499 	add	a,#0xeb
      0481DC F8               [12] 1500 	mov	r0,a
      0481DD E0               [24] 1501 	movx	a,@dptr
      0481DE F6               [12] 1502 	mov	@r0,a
      0481DF A3               [24] 1503 	inc	dptr
      0481E0 E0               [24] 1504 	movx	a,@dptr
      0481E1 08               [12] 1505 	inc	r0
      0481E2 F6               [12] 1506 	mov	@r0,a
      0481E3 A3               [24] 1507 	inc	dptr
      0481E4 E0               [24] 1508 	movx	a,@dptr
      0481E5 08               [12] 1509 	inc	r0
      0481E6 F6               [12] 1510 	mov	@r0,a
      0481E7 E5 81            [12] 1511 	mov	a,sp
      0481E9 24 EB            [12] 1512 	add	a,#0xeb
      0481EB F8               [12] 1513 	mov	r0,a
      0481EC 74 12            [12] 1514 	mov	a,#0x12
      0481EE 26               [12] 1515 	add	a,@r0
      0481EF FA               [12] 1516 	mov	r2,a
      0481F0 E4               [12] 1517 	clr	a
      0481F1 08               [12] 1518 	inc	r0
      0481F2 36               [12] 1519 	addc	a,@r0
      0481F3 FB               [12] 1520 	mov	r3,a
      0481F4 08               [12] 1521 	inc	r0
      0481F5 86 07            [24] 1522 	mov	ar7,@r0
      0481F7 8A 82            [24] 1523 	mov	dpl,r2
      0481F9 8B 83            [24] 1524 	mov	dph,r3
      0481FB 8F F0            [24] 1525 	mov	b,r7
      0481FD 12 50 12         [24] 1526 	lcall	__gptrget
      048200 FA               [12] 1527 	mov	r2,a
      048201 A3               [24] 1528 	inc	dptr
      048202 12 50 12         [24] 1529 	lcall	__gptrget
      048205 FB               [12] 1530 	mov	r3,a
      048206 EA               [12] 1531 	mov	a,r2
      048207 8B 02            [24] 1532 	mov	ar2,r3
      048209 FB               [12] 1533 	mov	r3,a
      04820A E5 81            [12] 1534 	mov	a,sp
      04820C 24 EB            [12] 1535 	add	a,#0xeb
      04820E F8               [12] 1536 	mov	r0,a
      04820F 74 10            [12] 1537 	mov	a,#0x10
      048211 26               [12] 1538 	add	a,@r0
      048212 FD               [12] 1539 	mov	r5,a
      048213 E4               [12] 1540 	clr	a
      048214 08               [12] 1541 	inc	r0
      048215 36               [12] 1542 	addc	a,@r0
      048216 FE               [12] 1543 	mov	r6,a
      048217 08               [12] 1544 	inc	r0
      048218 86 07            [24] 1545 	mov	ar7,@r0
      04821A 8D 82            [24] 1546 	mov	dpl,r5
      04821C 8E 83            [24] 1547 	mov	dph,r6
      04821E 8F F0            [24] 1548 	mov	b,r7
      048220 12 50 12         [24] 1549 	lcall	__gptrget
      048223 FD               [12] 1550 	mov	r5,a
      048224 A3               [24] 1551 	inc	dptr
      048225 12 50 12         [24] 1552 	lcall	__gptrget
      048228 FE               [12] 1553 	mov	r6,a
      048229 ED               [12] 1554 	mov	a,r5
      04822A 8E 05            [24] 1555 	mov	ar5,r6
      04822C FE               [12] 1556 	mov	r6,a
      04822D C0 07            [24] 1557 	push	ar7
      04822F C0 06            [24] 1558 	push	ar6
      048231 C0 05            [24] 1559 	push	ar5
      048233 C0 02            [24] 1560 	push	ar2
      048235 C0 03            [24] 1561 	push	ar3
      048237 C0 05            [24] 1562 	push	ar5
      048239 C0 06            [24] 1563 	push	ar6
      04823B 74 08            [12] 1564 	mov	a,#___str_3
      04823D C0 E0            [24] 1565 	push	acc
      04823F 74 74            [12] 1566 	mov	a,#(___str_3 >> 8)
      048241 C0 E0            [24] 1567 	push	acc
      048243 74 80            [12] 1568 	mov	a,#0x80
      048245 C0 E0            [24] 1569 	push	acc
      048247 78 C6            [12] 1570 	mov	r0,#_printf
      048249 79 4F            [12] 1571 	mov	r1,#(_printf >> 8)
      04824B 7A 00            [12] 1572 	mov	r2,#(_printf >> 16)
      04824D 12 05 9B         [24] 1573 	lcall	__sdcc_banked_call
      048250 E5 81            [12] 1574 	mov	a,sp
      048252 24 F9            [12] 1575 	add	a,#0xf9
      048254 F5 81            [12] 1576 	mov	sp,a
                                   1577 ;	client_temp_humi.c:120: printf("Client to: ");
      048256 74 22            [12] 1578 	mov	a,#___str_4
      048258 C0 E0            [24] 1579 	push	acc
      04825A 74 74            [12] 1580 	mov	a,#(___str_4 >> 8)
      04825C C0 E0            [24] 1581 	push	acc
      04825E 74 80            [12] 1582 	mov	a,#0x80
      048260 C0 E0            [24] 1583 	push	acc
      048262 78 C6            [12] 1584 	mov	r0,#_printf
      048264 79 4F            [12] 1585 	mov	r1,#(_printf >> 8)
      048266 7A 00            [12] 1586 	mov	r2,#(_printf >> 16)
      048268 12 05 9B         [24] 1587 	lcall	__sdcc_banked_call
      04826B 15 81            [12] 1588 	dec	sp
      04826D 15 81            [12] 1589 	dec	sp
      04826F 15 81            [12] 1590 	dec	sp
                                   1591 ;	client_temp_humi.c:122: printf("\r\n");
      048271 74 2E            [12] 1592 	mov	a,#___str_5
      048273 C0 E0            [24] 1593 	push	acc
      048275 74 74            [12] 1594 	mov	a,#(___str_5 >> 8)
      048277 C0 E0            [24] 1595 	push	acc
      048279 74 80            [12] 1596 	mov	a,#0x80
      04827B C0 E0            [24] 1597 	push	acc
      04827D 78 C6            [12] 1598 	mov	r0,#_printf
      04827F 79 4F            [12] 1599 	mov	r1,#(_printf >> 8)
      048281 7A 00            [12] 1600 	mov	r2,#(_printf >> 16)
      048283 12 05 9B         [24] 1601 	lcall	__sdcc_banked_call
      048286 15 81            [12] 1602 	dec	sp
      048288 15 81            [12] 1603 	dec	sp
      04828A 15 81            [12] 1604 	dec	sp
                                   1605 ;	client_temp_humi.c:124: etimer_set(&et, SEND_INTERVAL);
      04828C E4               [12] 1606 	clr	a
      04828D C0 E0            [24] 1607 	push	acc
      04828F 04               [12] 1608 	inc	a
      048290 C0 E0            [24] 1609 	push	acc
      048292 90 00 3C         [24] 1610 	mov	dptr,#_process_thread_udp_client_process_et_65536_529
      048295 75 F0 00         [24] 1611 	mov	b,#0x00
      048298 78 CC            [12] 1612 	mov	r0,#_etimer_set
      04829A 79 9A            [12] 1613 	mov	r1,#(_etimer_set >> 8)
      04829C 7A 03            [12] 1614 	mov	r2,#(_etimer_set >> 16)
      04829E 12 05 9B         [24] 1615 	lcall	__sdcc_banked_call
      0482A1 15 81            [12] 1616 	dec	sp
      0482A3 15 81            [12] 1617 	dec	sp
      0482A5 D0 05            [24] 1618 	pop	ar5
      0482A7 D0 06            [24] 1619 	pop	ar6
      0482A9 D0 07            [24] 1620 	pop	ar7
                                   1621 ;	client_temp_humi.c:138: PROCESS_END();
      0482AB D0 07            [24] 1622 	pop	ar7
      0482AD D0 06            [24] 1623 	pop	ar6
      0482AF D0 05            [24] 1624 	pop	ar5
                                   1625 ;	client_temp_humi.c:125: while(1) 
      0482B1                       1626 00117$:
                                   1627 ;	client_temp_humi.c:127: PROCESS_YIELD();
      0482B1 7C 00            [12] 1628 	mov	r4,#0x00
      0482B3 8D 82            [24] 1629 	mov	dpl,r5
      0482B5 8E 83            [24] 1630 	mov	dph,r6
      0482B7 8F F0            [24] 1631 	mov	b,r7
      0482B9 74 7F            [12] 1632 	mov	a,#0x7f
      0482BB 12 49 E0         [24] 1633 	lcall	__gptrput
      0482BE A3               [24] 1634 	inc	dptr
      0482BF E4               [12] 1635 	clr	a
      0482C0 12 49 E0         [24] 1636 	lcall	__gptrput
      0482C3                       1637 00105$:
      0482C3 EC               [12] 1638 	mov	a,r4
      0482C4 70 06            [24] 1639 	jnz	00109$
      0482C6 75 82 01         [24] 1640 	mov	dpl,#0x01
      0482C9 02 83 4D         [24] 1641 	ljmp	00120$
      0482CC                       1642 00109$:
                                   1643 ;	client_temp_humi.c:128: if(etimer_expired(&et)) 
      0482CC 90 00 3C         [24] 1644 	mov	dptr,#_process_thread_udp_client_process_et_65536_529
      0482CF 75 F0 00         [24] 1645 	mov	b,#0x00
      0482D2 C0 07            [24] 1646 	push	ar7
      0482D4 C0 06            [24] 1647 	push	ar6
      0482D6 C0 05            [24] 1648 	push	ar5
      0482D8 78 BB            [12] 1649 	mov	r0,#_etimer_expired
      0482DA 79 9B            [12] 1650 	mov	r1,#(_etimer_expired >> 8)
      0482DC 7A 03            [12] 1651 	mov	r2,#(_etimer_expired >> 16)
      0482DE 12 05 9B         [24] 1652 	lcall	__sdcc_banked_call
      0482E1 E5 82            [12] 1653 	mov	a,dpl
      0482E3 85 83 F0         [24] 1654 	mov	b,dph
      0482E6 D0 05            [24] 1655 	pop	ar5
      0482E8 D0 06            [24] 1656 	pop	ar6
      0482EA D0 07            [24] 1657 	pop	ar7
      0482EC 45 F0            [12] 1658 	orl	a,b
      0482EE 60 26            [24] 1659 	jz	00114$
                                   1660 ;	client_temp_humi.c:130: timeout_handler();
      0482F0 C0 07            [24] 1661 	push	ar7
      0482F2 C0 06            [24] 1662 	push	ar6
      0482F4 C0 05            [24] 1663 	push	ar5
      0482F6 78 03            [12] 1664 	mov	r0,#_timeout_handler
      0482F8 79 80            [12] 1665 	mov	r1,#(_timeout_handler >> 8)
      0482FA 7A 04            [12] 1666 	mov	r2,#(_timeout_handler >> 16)
      0482FC 12 05 9B         [24] 1667 	lcall	__sdcc_banked_call
                                   1668 ;	client_temp_humi.c:131: etimer_restart(&et);
      0482FF 90 00 3C         [24] 1669 	mov	dptr,#_process_thread_udp_client_process_et_65536_529
      048302 75 F0 00         [24] 1670 	mov	b,#0x00
      048305 78 3C            [12] 1671 	mov	r0,#_etimer_restart
      048307 79 9B            [12] 1672 	mov	r1,#(_etimer_restart >> 8)
      048309 7A 03            [12] 1673 	mov	r2,#(_etimer_restart >> 16)
      04830B 12 05 9B         [24] 1674 	lcall	__sdcc_banked_call
      04830E D0 05            [24] 1675 	pop	ar5
      048310 D0 06            [24] 1676 	pop	ar6
      048312 D0 07            [24] 1677 	pop	ar7
      048314 80 9B            [24] 1678 	sjmp	00117$
      048316                       1679 00114$:
                                   1680 ;	client_temp_humi.c:133: else if(ev == tcpip_event) 
      048316 90 00 46         [24] 1681 	mov	dptr,#_tcpip_event
      048319 E0               [24] 1682 	movx	a,@dptr
      04831A FC               [12] 1683 	mov	r4,a
      04831B E5 81            [12] 1684 	mov	a,sp
      04831D 24 EA            [12] 1685 	add	a,#0xea
      04831F F8               [12] 1686 	mov	r0,a
      048320 E6               [12] 1687 	mov	a,@r0
      048321 B5 04 8D         [24] 1688 	cjne	a,ar4,00117$
                                   1689 ;	client_temp_humi.c:135: tcpip_handler();
      048324 C0 07            [24] 1690 	push	ar7
      048326 C0 06            [24] 1691 	push	ar6
      048328 C0 05            [24] 1692 	push	ar5
      04832A 78 00            [12] 1693 	mov	r0,#_tcpip_handler
      04832C 79 80            [12] 1694 	mov	r1,#(_tcpip_handler >> 8)
      04832E 7A 04            [12] 1695 	mov	r2,#(_tcpip_handler >> 16)
      048330 12 05 9B         [24] 1696 	lcall	__sdcc_banked_call
      048333 D0 05            [24] 1697 	pop	ar5
      048335 D0 06            [24] 1698 	pop	ar6
      048337 D0 07            [24] 1699 	pop	ar7
      048339 02 82 B1         [24] 1700 	ljmp	00117$
                                   1701 ;	client_temp_humi.c:138: PROCESS_END();
      04833C                       1702 00119$:
      04833C 8D 82            [24] 1703 	mov	dpl,r5
      04833E 8E 83            [24] 1704 	mov	dph,r6
      048340 8F F0            [24] 1705 	mov	b,r7
      048342 E4               [12] 1706 	clr	a
      048343 12 49 E0         [24] 1707 	lcall	__gptrput
      048346 A3               [24] 1708 	inc	dptr
      048347 12 49 E0         [24] 1709 	lcall	__gptrput
      04834A 75 82 03         [24] 1710 	mov	dpl,#0x03
      04834D                       1711 00120$:
                                   1712 ;	client_temp_humi.c:139: }
      04834D E5 81            [12] 1713 	mov	a,sp
      04834F 24 ED            [12] 1714 	add	a,#0xed
      048351 F5 81            [12] 1715 	mov	sp,a
      048353 02 05 AD         [24] 1716 	ljmp	__sdcc_banked_ret
                                   1717 	.area CSEG    (CODE)
                                   1718 	.area CONST   (CODE)
      0073B9                       1719 ___str_0:
      0073B9 74 65 6D 70 5F 68 75  1720 	.ascii "temp_humi:send"
             6D 69 3A 73 65 6E 64
      0073C7 0D                    1721 	.db 0x0d
      0073C8 0A                    1722 	.db 0x0a
      0073C9 00                    1723 	.db 0x00
      0073CA                       1724 _autostart_processes:
      0073CA 78 18 00              1725 	.byte _udp_client_process, (_udp_client_process >> 8),#0x00
                                   1726 ; generic printIvalPtr
      0073CD 00 00 00              1727 	.byte #0x00,#0x00,#0x00
      0073D0                       1728 ___str_1:
      0073D0 55 44 50 20 63 6C 69  1729 	.ascii "UDP client process started"
             65 6E 74 20 70 72 6F
             63 65 73 73 20 73 74
             61 72 74 65 64
      0073EA 0A                    1730 	.db 0x0a
      0073EB 00                    1731 	.db 0x00
      0073EC                       1732 ___str_2:
      0073EC 4C 69 6E 6B 2D 4C 6F  1733 	.ascii "Link-Local connection with "
             63 61 6C 20 63 6F 6E
             6E 65 63 74 69 6F 6E
             20 77 69 74 68 20
      007407 00                    1734 	.db 0x00
      007408                       1735 ___str_3:
      007408 20 6C 6F 63 61 6C 2F  1736 	.ascii " local/remote port %u/%u"
             72 65 6D 6F 74 65 20
             70 6F 72 74 20 25 75
             2F 25 75
      007420 0A                    1737 	.db 0x0a
      007421 00                    1738 	.db 0x00
      007422                       1739 ___str_4:
      007422 43 6C 69 65 6E 74 20  1740 	.ascii "Client to: "
             74 6F 3A 20
      00742D 00                    1741 	.db 0x00
      00742E                       1742 ___str_5:
      00742E 0D                    1743 	.db 0x0d
      00742F 0A                    1744 	.db 0x0a
      007430 00                    1745 	.db 0x00
      007431                       1746 ___str_6:
      007431 55 44 50 20 63 6C 69  1747 	.ascii "UDP client process"
             65 6E 74 20 70 72 6F
             63 65 73 73
      007443 00                    1748 	.db 0x00
                                   1749 	.area XINIT   (CODE)
      007E3D                       1750 __xinit__udp_client_process:
                                   1751 ; generic printIvalPtr
      007E3D 00 00 00              1752 	.byte #0x00,#0x00,#0x00
      007E40 31 74 80              1753 	.byte ___str_6, (___str_6 >> 8),#0x80
      007E43 B3 80 04              1754 	.byte _process_thread_udp_client_process, (_process_thread_udp_client_process >> 8), (_process_thread_udp_client_process >> 16)
      007E46 00 00                 1755 	.byte #0x00, #0x00
      007E48 00                    1756 	.db #0x00	; 0
      007E49 00                    1757 	.db #0x00	; 0
                                   1758 	.area CABS    (ABS,CODE)
