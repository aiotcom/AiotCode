;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 3.8.4 #10774 (Linux)
;--------------------------------------------------------
	.module TM1640
	.optsdcc -mmcs51 --model-huge
	
;--------------------------------------------------------
; Public variables in this module
;--------------------------------------------------------
	.globl _send
	.globl _send_z
	.globl _init_tm1640_NEW
	.globl _write
	.globl _stop
	.globl _start
	.globl _delay_ms
	.globl _ACTIVE
	.globl _TX_BYTE
	.globl _RX_BYTE
	.globl _ERR
	.globl _FE
	.globl _SLAVE
	.globl _RE
	.globl _MODE
	.globl _T3OVFIF
	.globl _T3CH0IF
	.globl _T3CH1IF
	.globl _T4OVFIF
	.globl _T4CH0IF
	.globl _T4CH1IF
	.globl _OVFIM
	.globl _B_0
	.globl _B_1
	.globl _B_2
	.globl _B_3
	.globl _B_4
	.globl _B_5
	.globl _B_6
	.globl _B_7
	.globl _P2IF
	.globl _UTX0IF
	.globl _UTX1IF
	.globl _P1IF
	.globl _WDTIF
	.globl _ACC_0
	.globl _ACC_1
	.globl _ACC_2
	.globl _ACC_3
	.globl _ACC_4
	.globl _ACC_5
	.globl _ACC_6
	.globl _ACC_7
	.globl _P
	.globl _F1
	.globl _OV
	.globl _RS0
	.globl _RS1
	.globl _F0
	.globl _AC
	.globl _CY
	.globl _DMAIF
	.globl _T1IF
	.globl _T2IF
	.globl _T3IF
	.globl _T4IF
	.globl _P0IF
	.globl _STIF
	.globl _DMAIE
	.globl _T1IE
	.globl _T2IE
	.globl _T3IE
	.globl _T4IE
	.globl _P0IE
	.globl _RFERRIE
	.globl _ADCIE
	.globl _URX0IE
	.globl _URX1IE
	.globl _ENCIE
	.globl _STIE
	.globl _EA
	.globl _P2_0
	.globl _P2_1
	.globl _P2_2
	.globl _P2_3
	.globl _P2_4
	.globl _P2_5
	.globl _P2_6
	.globl _P2_7
	.globl _ENCIF_0
	.globl _ENCIF_1
	.globl _P1_0
	.globl _P1_1
	.globl _P1_2
	.globl _P1_3
	.globl _P1_4
	.globl _P1_5
	.globl _P1_6
	.globl _P1_7
	.globl _IT0
	.globl _RFERRIF
	.globl _IT1
	.globl _URX0IF
	.globl _ADCIF
	.globl _URX1IF
	.globl _P0_0
	.globl _P0_1
	.globl _P0_2
	.globl _P0_3
	.globl _P0_4
	.globl _P0_5
	.globl _P0_6
	.globl _P0_7
	.globl _WDCTL
	.globl _U1GCR
	.globl _U1UCR
	.globl _U1BAUD
	.globl _U1DBUF
	.globl _U1CSR
	.globl _U0GCR
	.globl _U0UCR
	.globl _U0BAUD
	.globl _U0DBUF
	.globl _U0CSR
	.globl _TIMIF
	.globl _T4CC1
	.globl _T4CCTL1
	.globl _T4CC0
	.globl _T4CCTL0
	.globl _T4CTL
	.globl _T4CNT
	.globl _T3CC1
	.globl _T3CCTL1
	.globl _T3CC0
	.globl _T3CCTL0
	.globl _T3CTL
	.globl _T3CNT
	.globl _T2MSEL
	.globl _T2IRQM
	.globl _T2MOVF2
	.globl _T2MOVF1
	.globl _T2MOVF0
	.globl _T2M1
	.globl _T2M0
	.globl _T2IRQF
	.globl _T2EVTCFG
	.globl _T2CTRL
	.globl _T1STAT
	.globl _T1CCTL2
	.globl _T1CCTL1
	.globl _T1CCTL0
	.globl _T1CTL
	.globl _T1CNTH
	.globl _T1CNTL
	.globl _T1CC2H
	.globl _T1CC2L
	.globl _T1CC1H
	.globl _T1CC1L
	.globl _T1CC0H
	.globl _T1CC0L
	.globl _CLKCONSTA
	.globl _CLKCONCMD
	.globl _SLEEPSTA
	.globl _SLEEPCMD
	.globl _STLOAD
	.globl _ST2
	.globl _ST1
	.globl _ST0
	.globl _RFERRF
	.globl _RFIRQF0
	.globl _RFST
	.globl _RFD
	.globl _RFIRQF1
	.globl _PSBANK
	.globl _FMAP
	.globl _MEMCTR
	.globl __XPAGE
	.globl _MPAGE
	.globl _PMUX
	.globl _P2DIR
	.globl _P1DIR
	.globl _P0DIR
	.globl _P2INP
	.globl _P1INP
	.globl _P2SEL
	.globl _P1SEL
	.globl _P0SEL
	.globl _APCFG
	.globl _PERCFG
	.globl _P0INP
	.globl _P2IEN
	.globl _P1IEN
	.globl _P0IEN
	.globl _PICTL
	.globl _P2IFG
	.globl _P1IFG
	.globl _P0IFG
	.globl _DMAREQ
	.globl _DMAARM
	.globl _DMA0CFGH
	.globl _DMA0CFGL
	.globl _DMA1CFGH
	.globl _DMA1CFGL
	.globl _DMAIRQ
	.globl _ENCCS
	.globl _ENCDO
	.globl _ENCDI
	.globl _RNDH
	.globl _RNDL
	.globl _ADCH
	.globl _ADCL
	.globl _ADCCON3
	.globl _ADCCON2
	.globl _ADCCON1
	.globl _B
	.globl _IRCON2
	.globl _ACC
	.globl _PSW
	.globl _IRCON
	.globl _IP1
	.globl _IEN1
	.globl _IP0
	.globl _IEN0
	.globl _P2
	.globl _S1CON
	.globl _IEN2
	.globl _S0CON
	.globl _DPS
	.globl _P1
	.globl _TCON
	.globl _PCON
	.globl _DPH1
	.globl _DPL1
	.globl _DPH0
	.globl _DPL0
	.globl _SP
	.globl _P0
	.globl _TM164_SIG
	.globl _TM164_DATA
	.globl _X_IEEE_ADDR
	.globl _X_INFOPAGE
	.globl _X_P2DIR
	.globl _X_P1DIR
	.globl _X_P0DIR
	.globl _X_U1GCR
	.globl _X_U1UCR
	.globl _X_U1BAUD
	.globl _X_U1DBUF
	.globl _X_U1CSR
	.globl _X_P2INP
	.globl _X_P1INP
	.globl _X_P2SEL
	.globl _X_P1SEL
	.globl _X_P0SEL
	.globl _X_APCFG
	.globl _X_PERCFG
	.globl _X_T4CC1
	.globl _X_T4CCTL1
	.globl _X_T4CC0
	.globl _X_T4CCTL0
	.globl _X_T4CTL
	.globl _X_T4CNT
	.globl _X_RFIRQF0
	.globl _X_T1CCTL2
	.globl _X_T1CCTL1
	.globl _X_T1CCTL0
	.globl _X_T1CTL
	.globl _X_T1CNTH
	.globl _X_T1CNTL
	.globl _X_RFST
	.globl _X_T1CC2H
	.globl _X_T1CC2L
	.globl _X_T1CC1H
	.globl _X_T1CC1L
	.globl _X_T1CC0H
	.globl _X_T1CC0L
	.globl _X_RFD
	.globl _X_TIMIF
	.globl _X_DMAREQ
	.globl _X_DMAARM
	.globl _X_DMA0CFGH
	.globl _X_DMA0CFGL
	.globl _X_DMA1CFGH
	.globl _X_DMA1CFGL
	.globl _X_DMAIRQ
	.globl _X_T3CC1
	.globl _X_T3CCTL1
	.globl _X_T3CC0
	.globl _X_T3CCTL0
	.globl _X_T3CTL
	.globl _X_T3CNT
	.globl _X_WDCTL
	.globl _X_MEMCTR
	.globl _X_CLKCONCMD
	.globl _X_U0GCR
	.globl _X_U0UCR
	.globl _X_T2MSEL
	.globl _X_U0BAUD
	.globl _X_U0DBUF
	.globl _X_RFERRF
	.globl _X_SLEEPCMD
	.globl _X_RNDH
	.globl _X_RNDL
	.globl _X_ADCH
	.globl _X_ADCL
	.globl _X_ADCCON3
	.globl _X_ADCCON2
	.globl _X_ADCCON1
	.globl _X_ENCCS
	.globl _X_ENCDO
	.globl _X_ENCDI
	.globl _X_T1STAT
	.globl _X_PMUX
	.globl _X_STLOAD
	.globl _X_P2IEN
	.globl _X_P0IEN
	.globl _X_T2IRQM
	.globl _X_T2MOVF2
	.globl _X_T2MOVF1
	.globl _X_T2MOVF0
	.globl _X_T2M1
	.globl _X_T2M0
	.globl _X_T2IRQF
	.globl _X_P2
	.globl _X_PSBANK
	.globl _X_FMAP
	.globl _X_CLKCONSTA
	.globl _X_SLEEPSTA
	.globl _X_T2EVTCFG
	.globl _X_ST2
	.globl _X_ST1
	.globl _X_ST0
	.globl _X_T2CTRL
	.globl _X__XPAGE
	.globl _X_MPAGE
	.globl _X_RFIRQF1
	.globl _X_P1
	.globl _X_P0INP
	.globl _X_P1IEN
	.globl _X_PICTL
	.globl _X_P2IFG
	.globl _X_P1IFG
	.globl _X_P0IFG
	.globl _X_U0CSR
	.globl _X_P0
	.globl _USBF5
	.globl _USBF4
	.globl _USBF3
	.globl _USBF2
	.globl _USBF1
	.globl _USBF0
	.globl _USBCNTH
	.globl _USBCNTL
	.globl _USBCNT0
	.globl _USBCSOH
	.globl _USBCSOL
	.globl _USBMAXO
	.globl _USBCSIH
	.globl _USBCSIL
	.globl _USBCS0
	.globl _USBMAXI
	.globl _USBCTRL
	.globl _USBINDEX
	.globl _USBFRMH
	.globl _USBFRML
	.globl _USBCIE
	.globl _USBOIE
	.globl _USBIIE
	.globl _USBCIF
	.globl _USBOIF
	.globl _USBIIF
	.globl _USBPOW
	.globl _USBADDR
	.globl _CSPT
	.globl _CSPZ
	.globl _CSPY
	.globl _CSPX
	.globl _CSPSTAT
	.globl _CSPCTRL
	.globl _CSPPROG23
	.globl _CSPPROG22
	.globl _CSPPROG21
	.globl _CSPPROG20
	.globl _CSPPROG19
	.globl _CSPPROG18
	.globl _CSPPROG17
	.globl _CSPPROG16
	.globl _CSPPROG15
	.globl _CSPPROG14
	.globl _CSPPROG13
	.globl _CSPPROG12
	.globl _CSPPROG11
	.globl _CSPPROG10
	.globl _CSPPROG9
	.globl _CSPPROG8
	.globl _CSPPROG7
	.globl _CSPPROG6
	.globl _CSPPROG5
	.globl _CSPPROG4
	.globl _CSPPROG3
	.globl _CSPPROG2
	.globl _CSPPROG1
	.globl _CSPPROG0
	.globl _RFC_OBS_CTRL2
	.globl _RFC_OBS_CTRL1
	.globl _RFC_OBS_CTRL0
	.globl _TXFILTCFG
	.globl _PTEST1
	.globl _PTEST0
	.globl _ATEST
	.globl _DACTEST2
	.globl _DACTEST1
	.globl _DACTEST0
	.globl _MDMTEST1
	.globl _MDMTEST0
	.globl _ADCTEST2
	.globl _ADCTEST1
	.globl _ADCTEST0
	.globl _AGCCTRL3
	.globl _AGCCTRL2
	.globl _AGCCTRL1
	.globl _AGCCTRL0
	.globl _FSCAL3
	.globl _FSCAL2
	.globl _FSCAL1
	.globl _FSCAL0
	.globl _FSCTRL
	.globl _RXCTRL
	.globl _FREQEST
	.globl _MDMCTRL1
	.globl _MDMCTRL0
	.globl _RFRND
	.globl _RFERRM
	.globl _RFIRQM1
	.globl _RFIRQM0
	.globl _TXLAST_PTR
	.globl _TXFIRST_PTR
	.globl _RXP1_PTR
	.globl _RXLAST_PTR
	.globl _RXFIRST_PTR
	.globl _TXFIFOCNT
	.globl _RXFIFOCNT
	.globl _RXFIRST
	.globl _RSSISTAT
	.globl _RSSI
	.globl _CCACTRL1
	.globl _CCACTRL0
	.globl _FSMCTRL
	.globl _FIFOPCTRL
	.globl _FSMSTAT1
	.globl _FSMSTAT0
	.globl _TXCTRL
	.globl _TXPOWER
	.globl _FREQCTRL
	.globl _FREQTUNE
	.globl _RXMASKCLR
	.globl _RXMASKSET
	.globl _RXENABLE
	.globl _FRMCTRL1
	.globl _FRMCTRL0
	.globl _SRCEXTEN2
	.globl _SRCEXTEN1
	.globl _SRCEXTEN0
	.globl _SRCSHORTEN2
	.globl _SRCSHORTEN1
	.globl _SRCSHORTEN0
	.globl _SRCMATCH
	.globl _FRMFILT1
	.globl _FRMFILT0
	.globl _SHORT_ADDR1
	.globl _SHORT_ADDR0
	.globl _PAN_ID1
	.globl _PAN_ID0
	.globl _EXT_ADDR7
	.globl _EXT_ADDR6
	.globl _EXT_ADDR5
	.globl _EXT_ADDR4
	.globl _EXT_ADDR3
	.globl _EXT_ADDR2
	.globl _EXT_ADDR1
	.globl _EXT_ADDR0
	.globl _SRCSHORTPENDEN2
	.globl _SRCSHORTPENDEN1
	.globl _SRCSHORTPENDEN0
	.globl _SRCEXTPENDEN2
	.globl _SRCEXTPENDEN1
	.globl _SRCEXTPENDEN0
	.globl _SRCRESINDEX
	.globl _SRCRESMASK2
	.globl _SRCRESMASK1
	.globl _SRCRESMASK0
	.globl _SRC_ADDR_TABLE
	.globl _TXFIFO
	.globl _RXFIFO
	.globl _RFCORE_RAM
	.globl _CMPCTL
	.globl _OPAMPS
	.globl _OPAMPC
	.globl _STCV2
	.globl _STCV1
	.globl _STCV0
	.globl _STCS
	.globl _STCC
	.globl _T1CC4H
	.globl _T1CC4L
	.globl _T1CC3H
	.globl _T1CC3L
	.globl _XX_T1CC2H
	.globl _XX_T1CC2L
	.globl _XX_T1CC1H
	.globl _XX_T1CC1L
	.globl _XX_T1CC0H
	.globl _XX_T1CC0L
	.globl _T1CCTL4
	.globl _T1CCTL3
	.globl _XX_T1CCTL2
	.globl _XX_T1CCTL1
	.globl _XX_T1CCTL0
	.globl _CLD
	.globl _IRCTL
	.globl _CHIPINFO1
	.globl _CHIPINFO0
	.globl _FWDATA
	.globl _FADDRH
	.globl _FADDRL
	.globl _FCTL
	.globl _IVCTRL
	.globl _BATTMON
	.globl _SRCRC
	.globl _DBGDATA
	.globl _TESTREG0
	.globl _CHIPID
	.globl _CHVER
	.globl _OBSSEL5
	.globl _OBSSEL4
	.globl _OBSSEL3
	.globl _OBSSEL2
	.globl _OBSSEL1
	.globl _OBSSEL0
	.globl _I2CIO
	.globl _I2CWC
	.globl _I2CADDR
	.globl _I2CDATA
	.globl _I2CSTAT
	.globl _I2CCFG
	.globl _OPAMPMC
	.globl _MONMUX
	.globl _TM1640_Init
	.globl _init_tm1640
	.globl _send_LED_Display
	.globl _LED_DisplayClear
;--------------------------------------------------------
; special function registers
;--------------------------------------------------------
	.area RSEG    (ABS,DATA)
	.org 0x0000
_P0	=	0x0080
_SP	=	0x0081
_DPL0	=	0x0082
_DPH0	=	0x0083
_DPL1	=	0x0084
_DPH1	=	0x0085
_PCON	=	0x0087
_TCON	=	0x0088
_P1	=	0x0090
_DPS	=	0x0092
_S0CON	=	0x0098
_IEN2	=	0x009a
_S1CON	=	0x009b
_P2	=	0x00a0
_IEN0	=	0x00a8
_IP0	=	0x00a9
_IEN1	=	0x00b8
_IP1	=	0x00b9
_IRCON	=	0x00c0
_PSW	=	0x00d0
_ACC	=	0x00e0
_IRCON2	=	0x00e8
_B	=	0x00f0
_ADCCON1	=	0x00b4
_ADCCON2	=	0x00b5
_ADCCON3	=	0x00b6
_ADCL	=	0x00ba
_ADCH	=	0x00bb
_RNDL	=	0x00bc
_RNDH	=	0x00bd
_ENCDI	=	0x00b1
_ENCDO	=	0x00b2
_ENCCS	=	0x00b3
_DMAIRQ	=	0x00d1
_DMA1CFGL	=	0x00d2
_DMA1CFGH	=	0x00d3
_DMA0CFGL	=	0x00d4
_DMA0CFGH	=	0x00d5
_DMAARM	=	0x00d6
_DMAREQ	=	0x00d7
_P0IFG	=	0x0089
_P1IFG	=	0x008a
_P2IFG	=	0x008b
_PICTL	=	0x008c
_P0IEN	=	0x00ab
_P1IEN	=	0x008d
_P2IEN	=	0x00ac
_P0INP	=	0x008f
_PERCFG	=	0x00f1
_APCFG	=	0x00f2
_P0SEL	=	0x00f3
_P1SEL	=	0x00f4
_P2SEL	=	0x00f5
_P1INP	=	0x00f6
_P2INP	=	0x00f7
_P0DIR	=	0x00fd
_P1DIR	=	0x00fe
_P2DIR	=	0x00ff
_PMUX	=	0x00ae
_MPAGE	=	0x0093
__XPAGE	=	0x0093
_MEMCTR	=	0x00c7
_FMAP	=	0x009f
_PSBANK	=	0x009f
_RFIRQF1	=	0x0091
_RFD	=	0x00d9
_RFST	=	0x00e1
_RFIRQF0	=	0x00e9
_RFERRF	=	0x00bf
_ST0	=	0x0095
_ST1	=	0x0096
_ST2	=	0x0097
_STLOAD	=	0x00ad
_SLEEPCMD	=	0x00be
_SLEEPSTA	=	0x009d
_CLKCONCMD	=	0x00c6
_CLKCONSTA	=	0x009e
_T1CC0L	=	0x00da
_T1CC0H	=	0x00db
_T1CC1L	=	0x00dc
_T1CC1H	=	0x00dd
_T1CC2L	=	0x00de
_T1CC2H	=	0x00df
_T1CNTL	=	0x00e2
_T1CNTH	=	0x00e3
_T1CTL	=	0x00e4
_T1CCTL0	=	0x00e5
_T1CCTL1	=	0x00e6
_T1CCTL2	=	0x00e7
_T1STAT	=	0x00af
_T2CTRL	=	0x0094
_T2EVTCFG	=	0x009c
_T2IRQF	=	0x00a1
_T2M0	=	0x00a2
_T2M1	=	0x00a3
_T2MOVF0	=	0x00a4
_T2MOVF1	=	0x00a5
_T2MOVF2	=	0x00a6
_T2IRQM	=	0x00a7
_T2MSEL	=	0x00c3
_T3CNT	=	0x00ca
_T3CTL	=	0x00cb
_T3CCTL0	=	0x00cc
_T3CC0	=	0x00cd
_T3CCTL1	=	0x00ce
_T3CC1	=	0x00cf
_T4CNT	=	0x00ea
_T4CTL	=	0x00eb
_T4CCTL0	=	0x00ec
_T4CC0	=	0x00ed
_T4CCTL1	=	0x00ee
_T4CC1	=	0x00ef
_TIMIF	=	0x00d8
_U0CSR	=	0x0086
_U0DBUF	=	0x00c1
_U0BAUD	=	0x00c2
_U0UCR	=	0x00c4
_U0GCR	=	0x00c5
_U1CSR	=	0x00f8
_U1DBUF	=	0x00f9
_U1BAUD	=	0x00fa
_U1UCR	=	0x00fb
_U1GCR	=	0x00fc
_WDCTL	=	0x00c9
;--------------------------------------------------------
; special function bits
;--------------------------------------------------------
	.area RSEG    (ABS,DATA)
	.org 0x0000
_P0_7	=	0x0087
_P0_6	=	0x0086
_P0_5	=	0x0085
_P0_4	=	0x0084
_P0_3	=	0x0083
_P0_2	=	0x0082
_P0_1	=	0x0081
_P0_0	=	0x0080
_URX1IF	=	0x008f
_ADCIF	=	0x008d
_URX0IF	=	0x008b
_IT1	=	0x008a
_RFERRIF	=	0x0089
_IT0	=	0x0088
_P1_7	=	0x0097
_P1_6	=	0x0096
_P1_5	=	0x0095
_P1_4	=	0x0094
_P1_3	=	0x0093
_P1_2	=	0x0092
_P1_1	=	0x0091
_P1_0	=	0x0090
_ENCIF_1	=	0x0099
_ENCIF_0	=	0x0098
_P2_7	=	0x00a7
_P2_6	=	0x00a6
_P2_5	=	0x00a5
_P2_4	=	0x00a4
_P2_3	=	0x00a3
_P2_2	=	0x00a2
_P2_1	=	0x00a1
_P2_0	=	0x00a0
_EA	=	0x00af
_STIE	=	0x00ad
_ENCIE	=	0x00ac
_URX1IE	=	0x00ab
_URX0IE	=	0x00aa
_ADCIE	=	0x00a9
_RFERRIE	=	0x00a8
_P0IE	=	0x00bd
_T4IE	=	0x00bc
_T3IE	=	0x00bb
_T2IE	=	0x00ba
_T1IE	=	0x00b9
_DMAIE	=	0x00b8
_STIF	=	0x00c7
_P0IF	=	0x00c5
_T4IF	=	0x00c4
_T3IF	=	0x00c3
_T2IF	=	0x00c2
_T1IF	=	0x00c1
_DMAIF	=	0x00c0
_CY	=	0x00d7
_AC	=	0x00d6
_F0	=	0x00d5
_RS1	=	0x00d4
_RS0	=	0x00d3
_OV	=	0x00d2
_F1	=	0x00d1
_P	=	0x00d0
_ACC_7	=	0x00e7
_ACC_6	=	0x00e6
_ACC_5	=	0x00e5
_ACC_4	=	0x00e4
_ACC_3	=	0x00e3
_ACC_2	=	0x00e2
_ACC_1	=	0x00e1
_ACC_0	=	0x00e0
_WDTIF	=	0x00ec
_P1IF	=	0x00eb
_UTX1IF	=	0x00ea
_UTX0IF	=	0x00e9
_P2IF	=	0x00e8
_B_7	=	0x00f7
_B_6	=	0x00f6
_B_5	=	0x00f5
_B_4	=	0x00f4
_B_3	=	0x00f3
_B_2	=	0x00f2
_B_1	=	0x00f1
_B_0	=	0x00f0
_OVFIM	=	0x00de
_T4CH1IF	=	0x00dd
_T4CH0IF	=	0x00dc
_T4OVFIF	=	0x00db
_T3CH1IF	=	0x00da
_T3CH0IF	=	0x00d9
_T3OVFIF	=	0x00d8
_MODE	=	0x00ff
_RE	=	0x00fe
_SLAVE	=	0x00fd
_FE	=	0x00fc
_ERR	=	0x00fb
_RX_BYTE	=	0x00fa
_TX_BYTE	=	0x00f9
_ACTIVE	=	0x00f8
;--------------------------------------------------------
; overlayable register banks
;--------------------------------------------------------
	.area REG_BANK_0	(REL,OVR,DATA)
	.ds 8
;--------------------------------------------------------
; internal ram data
;--------------------------------------------------------
	.area DSEG    (DATA)
;--------------------------------------------------------
; overlayable items in internal ram 
;--------------------------------------------------------
;--------------------------------------------------------
; indirectly addressable internal ram data
;--------------------------------------------------------
	.area ISEG    (DATA)
;--------------------------------------------------------
; absolute internal ram data
;--------------------------------------------------------
	.area IABS    (ABS,DATA)
	.area IABS    (ABS,DATA)
;--------------------------------------------------------
; bit data
;--------------------------------------------------------
	.area BSEG    (BIT)
;--------------------------------------------------------
; paged external ram data
;--------------------------------------------------------
	.area PSEG    (PAG,XDATA)
;--------------------------------------------------------
; external ram data
;--------------------------------------------------------
	.area XSEG    (XDATA)
_MONMUX	=	0x61a6
_OPAMPMC	=	0x61a6
_I2CCFG	=	0x6230
_I2CSTAT	=	0x6231
_I2CDATA	=	0x6232
_I2CADDR	=	0x6233
_I2CWC	=	0x6234
_I2CIO	=	0x6235
_OBSSEL0	=	0x6243
_OBSSEL1	=	0x6244
_OBSSEL2	=	0x6245
_OBSSEL3	=	0x6246
_OBSSEL4	=	0x6247
_OBSSEL5	=	0x6248
_CHVER	=	0x6249
_CHIPID	=	0x624a
_TESTREG0	=	0x624b
_DBGDATA	=	0x6260
_SRCRC	=	0x6262
_BATTMON	=	0x6264
_IVCTRL	=	0x6265
_FCTL	=	0x6270
_FADDRL	=	0x6271
_FADDRH	=	0x6272
_FWDATA	=	0x6273
_CHIPINFO0	=	0x6276
_CHIPINFO1	=	0x6277
_IRCTL	=	0x6281
_CLD	=	0x6290
_XX_T1CCTL0	=	0x62a0
_XX_T1CCTL1	=	0x62a1
_XX_T1CCTL2	=	0x62a2
_T1CCTL3	=	0x62a3
_T1CCTL4	=	0x62a4
_XX_T1CC0L	=	0x62a6
_XX_T1CC0H	=	0x62a7
_XX_T1CC1L	=	0x62a8
_XX_T1CC1H	=	0x62a9
_XX_T1CC2L	=	0x62aa
_XX_T1CC2H	=	0x62ab
_T1CC3L	=	0x62ac
_T1CC3H	=	0x62ad
_T1CC4L	=	0x62ae
_T1CC4H	=	0x62af
_STCC	=	0x62b0
_STCS	=	0x62b1
_STCV0	=	0x62b2
_STCV1	=	0x62b3
_STCV2	=	0x62b4
_OPAMPC	=	0x62c0
_OPAMPS	=	0x62c1
_CMPCTL	=	0x62d0
_RFCORE_RAM	=	0x6000
_RXFIFO	=	0x6000
_TXFIFO	=	0x6080
_SRC_ADDR_TABLE	=	0x6100
_SRCRESMASK0	=	0x6160
_SRCRESMASK1	=	0x6161
_SRCRESMASK2	=	0x6162
_SRCRESINDEX	=	0x6163
_SRCEXTPENDEN0	=	0x6164
_SRCEXTPENDEN1	=	0x6165
_SRCEXTPENDEN2	=	0x6166
_SRCSHORTPENDEN0	=	0x6167
_SRCSHORTPENDEN1	=	0x6168
_SRCSHORTPENDEN2	=	0x6169
_EXT_ADDR0	=	0x616a
_EXT_ADDR1	=	0x616b
_EXT_ADDR2	=	0x616c
_EXT_ADDR3	=	0x616d
_EXT_ADDR4	=	0x616e
_EXT_ADDR5	=	0x616f
_EXT_ADDR6	=	0x6170
_EXT_ADDR7	=	0x6171
_PAN_ID0	=	0x6172
_PAN_ID1	=	0x6173
_SHORT_ADDR0	=	0x6174
_SHORT_ADDR1	=	0x6175
_FRMFILT0	=	0x6180
_FRMFILT1	=	0x6181
_SRCMATCH	=	0x6182
_SRCSHORTEN0	=	0x6183
_SRCSHORTEN1	=	0x6184
_SRCSHORTEN2	=	0x6185
_SRCEXTEN0	=	0x6186
_SRCEXTEN1	=	0x6187
_SRCEXTEN2	=	0x6188
_FRMCTRL0	=	0x6189
_FRMCTRL1	=	0x618a
_RXENABLE	=	0x618b
_RXMASKSET	=	0x618c
_RXMASKCLR	=	0x618d
_FREQTUNE	=	0x618e
_FREQCTRL	=	0x618f
_TXPOWER	=	0x6190
_TXCTRL	=	0x6191
_FSMSTAT0	=	0x6192
_FSMSTAT1	=	0x6193
_FIFOPCTRL	=	0x6194
_FSMCTRL	=	0x6195
_CCACTRL0	=	0x6196
_CCACTRL1	=	0x6197
_RSSI	=	0x6198
_RSSISTAT	=	0x6199
_RXFIRST	=	0x619a
_RXFIFOCNT	=	0x619b
_TXFIFOCNT	=	0x619c
_RXFIRST_PTR	=	0x619d
_RXLAST_PTR	=	0x619e
_RXP1_PTR	=	0x619f
_TXFIRST_PTR	=	0x61a1
_TXLAST_PTR	=	0x61a2
_RFIRQM0	=	0x61a3
_RFIRQM1	=	0x61a4
_RFERRM	=	0x61a5
_RFRND	=	0x61a7
_MDMCTRL0	=	0x61a8
_MDMCTRL1	=	0x61a9
_FREQEST	=	0x61aa
_RXCTRL	=	0x61ab
_FSCTRL	=	0x61ac
_FSCAL0	=	0x61ad
_FSCAL1	=	0x61ae
_FSCAL2	=	0x61af
_FSCAL3	=	0x61b0
_AGCCTRL0	=	0x61b1
_AGCCTRL1	=	0x61b2
_AGCCTRL2	=	0x61b3
_AGCCTRL3	=	0x61b4
_ADCTEST0	=	0x61b5
_ADCTEST1	=	0x61b6
_ADCTEST2	=	0x61b7
_MDMTEST0	=	0x61b8
_MDMTEST1	=	0x61b9
_DACTEST0	=	0x61ba
_DACTEST1	=	0x61bb
_DACTEST2	=	0x61bc
_ATEST	=	0x61bd
_PTEST0	=	0x61be
_PTEST1	=	0x61bf
_TXFILTCFG	=	0x61fa
_RFC_OBS_CTRL0	=	0x61eb
_RFC_OBS_CTRL1	=	0x61ec
_RFC_OBS_CTRL2	=	0x61ed
_CSPPROG0	=	0x61c0
_CSPPROG1	=	0x61c1
_CSPPROG2	=	0x61c2
_CSPPROG3	=	0x61c3
_CSPPROG4	=	0x61c4
_CSPPROG5	=	0x61c5
_CSPPROG6	=	0x61c6
_CSPPROG7	=	0x61c7
_CSPPROG8	=	0x61c8
_CSPPROG9	=	0x61c9
_CSPPROG10	=	0x61ca
_CSPPROG11	=	0x61cb
_CSPPROG12	=	0x61cc
_CSPPROG13	=	0x61cd
_CSPPROG14	=	0x61ce
_CSPPROG15	=	0x61cf
_CSPPROG16	=	0x61d0
_CSPPROG17	=	0x61d1
_CSPPROG18	=	0x61d2
_CSPPROG19	=	0x61d3
_CSPPROG20	=	0x61d4
_CSPPROG21	=	0x61d5
_CSPPROG22	=	0x61d6
_CSPPROG23	=	0x61d7
_CSPCTRL	=	0x61e0
_CSPSTAT	=	0x61e1
_CSPX	=	0x61e2
_CSPY	=	0x61e3
_CSPZ	=	0x61e4
_CSPT	=	0x61e5
_USBADDR	=	0x6200
_USBPOW	=	0x6201
_USBIIF	=	0x6202
_USBOIF	=	0x6204
_USBCIF	=	0x6206
_USBIIE	=	0x6207
_USBOIE	=	0x6209
_USBCIE	=	0x620b
_USBFRML	=	0x620c
_USBFRMH	=	0x620d
_USBINDEX	=	0x620e
_USBCTRL	=	0x620f
_USBMAXI	=	0x6210
_USBCS0	=	0x6211
_USBCSIL	=	0x6211
_USBCSIH	=	0x6212
_USBMAXO	=	0x6213
_USBCSOL	=	0x6214
_USBCSOH	=	0x6215
_USBCNT0	=	0x6216
_USBCNTL	=	0x6216
_USBCNTH	=	0x6217
_USBF0	=	0x6220
_USBF1	=	0x6222
_USBF2	=	0x6224
_USBF3	=	0x6226
_USBF4	=	0x6228
_USBF5	=	0x622a
_X_P0	=	0x7080
_X_U0CSR	=	0x7086
_X_P0IFG	=	0x7089
_X_P1IFG	=	0x708a
_X_P2IFG	=	0x708b
_X_PICTL	=	0x708c
_X_P1IEN	=	0x708d
_X_P0INP	=	0x708f
_X_P1	=	0x7090
_X_RFIRQF1	=	0x7091
_X_MPAGE	=	0x7093
_X__XPAGE	=	0x7093
_X_T2CTRL	=	0x7094
_X_ST0	=	0x7095
_X_ST1	=	0x7096
_X_ST2	=	0x7097
_X_T2EVTCFG	=	0x709c
_X_SLEEPSTA	=	0x709d
_X_CLKCONSTA	=	0x709e
_X_FMAP	=	0x709f
_X_PSBANK	=	0x709f
_X_P2	=	0x70a0
_X_T2IRQF	=	0x70a1
_X_T2M0	=	0x70a2
_X_T2M1	=	0x70a3
_X_T2MOVF0	=	0x70a4
_X_T2MOVF1	=	0x70a5
_X_T2MOVF2	=	0x70a6
_X_T2IRQM	=	0x70a7
_X_P0IEN	=	0x70ab
_X_P2IEN	=	0x70ac
_X_STLOAD	=	0x70ad
_X_PMUX	=	0x70ae
_X_T1STAT	=	0x70af
_X_ENCDI	=	0x70b1
_X_ENCDO	=	0x70b2
_X_ENCCS	=	0x70b3
_X_ADCCON1	=	0x70b4
_X_ADCCON2	=	0x70b5
_X_ADCCON3	=	0x70b6
_X_ADCL	=	0x70ba
_X_ADCH	=	0x70bb
_X_RNDL	=	0x70bc
_X_RNDH	=	0x70bd
_X_SLEEPCMD	=	0x70be
_X_RFERRF	=	0x70bf
_X_U0DBUF	=	0x70c1
_X_U0BAUD	=	0x70c2
_X_T2MSEL	=	0x70c3
_X_U0UCR	=	0x70c4
_X_U0GCR	=	0x70c5
_X_CLKCONCMD	=	0x70c6
_X_MEMCTR	=	0x70c7
_X_WDCTL	=	0x70c9
_X_T3CNT	=	0x70ca
_X_T3CTL	=	0x70cb
_X_T3CCTL0	=	0x70cc
_X_T3CC0	=	0x70cd
_X_T3CCTL1	=	0x70ce
_X_T3CC1	=	0x70cf
_X_DMAIRQ	=	0x70d1
_X_DMA1CFGL	=	0x70d2
_X_DMA1CFGH	=	0x70d3
_X_DMA0CFGL	=	0x70d4
_X_DMA0CFGH	=	0x70d5
_X_DMAARM	=	0x70d6
_X_DMAREQ	=	0x70d7
_X_TIMIF	=	0x70d8
_X_RFD	=	0x70d9
_X_T1CC0L	=	0x70da
_X_T1CC0H	=	0x70db
_X_T1CC1L	=	0x70dc
_X_T1CC1H	=	0x70dd
_X_T1CC2L	=	0x70de
_X_T1CC2H	=	0x70df
_X_RFST	=	0x70e1
_X_T1CNTL	=	0x70e2
_X_T1CNTH	=	0x70e3
_X_T1CTL	=	0x70e4
_X_T1CCTL0	=	0x70e5
_X_T1CCTL1	=	0x70e6
_X_T1CCTL2	=	0x70e7
_X_RFIRQF0	=	0x70e9
_X_T4CNT	=	0x70ea
_X_T4CTL	=	0x70eb
_X_T4CCTL0	=	0x70ec
_X_T4CC0	=	0x70ed
_X_T4CCTL1	=	0x70ee
_X_T4CC1	=	0x70ef
_X_PERCFG	=	0x70f1
_X_APCFG	=	0x70f2
_X_P0SEL	=	0x70f3
_X_P1SEL	=	0x70f4
_X_P2SEL	=	0x70f5
_X_P1INP	=	0x70f6
_X_P2INP	=	0x70f7
_X_U1CSR	=	0x70f8
_X_U1DBUF	=	0x70f9
_X_U1BAUD	=	0x70fa
_X_U1UCR	=	0x70fb
_X_U1GCR	=	0x70fc
_X_P0DIR	=	0x70fd
_X_P1DIR	=	0x70fe
_X_P2DIR	=	0x70ff
_X_INFOPAGE	=	0x7800
_X_IEEE_ADDR	=	0x780c
;--------------------------------------------------------
; absolute external ram data
;--------------------------------------------------------
	.area XABS    (ABS,XDATA)
;--------------------------------------------------------
; external initialized ram data
;--------------------------------------------------------
	.area XISEG   (XDATA)
_TM164_DATA::
	.ds 14
_TM164_SIG::
	.ds 4
	.area HOME    (CODE)
	.area GSINIT0 (CODE)
	.area GSINIT1 (CODE)
	.area GSINIT2 (CODE)
	.area GSINIT3 (CODE)
	.area GSINIT4 (CODE)
	.area GSINIT5 (CODE)
	.area GSINIT  (CODE)
	.area GSFINAL (CODE)
	.area CSEG    (CODE)
;--------------------------------------------------------
; global & static initialisations
;--------------------------------------------------------
	.area HOME    (CODE)
	.area GSINIT  (CODE)
	.area GSFINAL (CODE)
	.area GSINIT  (CODE)
;--------------------------------------------------------
; Home
;--------------------------------------------------------
	.area HOME    (CODE)
	.area HOME    (CODE)
;--------------------------------------------------------
; code
;--------------------------------------------------------
	.area BANK1   (CODE)
;------------------------------------------------------------
;Allocation info for local variables in function 'TM1640_Init'
;------------------------------------------------------------
;	../../../platform/cc2530dk/SHT20/TM1640.c:8: void TM1640_Init(void)
;	-----------------------------------------
;	 function TM1640_Init
;	-----------------------------------------
_TM1640_Init:
	ar7 = 0x07
	ar6 = 0x06
	ar5 = 0x05
	ar4 = 0x04
	ar3 = 0x03
	ar2 = 0x02
	ar1 = 0x01
	ar0 = 0x00
;	../../../platform/cc2530dk/SHT20/TM1640.c:10: P1SEL &= ~0x30;     //����P1.4��P1.5Ϊ��ͨIO��  
	anl	_P1SEL,#0xcf
;	../../../platform/cc2530dk/SHT20/TM1640.c:11: P1DIR |= 0x30;      //P1.4��P1.5����Ϊ���
	orl	_P1DIR,#0x30
;	../../../platform/cc2530dk/SHT20/TM1640.c:12: init_tm1640();  
	mov	r0,#_init_tm1640
	mov	r1,#(_init_tm1640 >> 8)
	mov	r2,#(_init_tm1640 >> 16)
	lcall	__sdcc_banked_call
;	../../../platform/cc2530dk/SHT20/TM1640.c:13: LED_DisplayClear();//�����ʾ
	mov	r0,#_LED_DisplayClear
	mov	r1,#(_LED_DisplayClear >> 8)
	mov	r2,#(_LED_DisplayClear >> 16)
	lcall	__sdcc_banked_call
;	../../../platform/cc2530dk/SHT20/TM1640.c:14: }
	ljmp	__sdcc_banked_ret
;------------------------------------------------------------
;Allocation info for local variables in function 'start'
;------------------------------------------------------------
;	../../../platform/cc2530dk/SHT20/TM1640.c:32: void start(void)
;	-----------------------------------------
;	 function start
;	-----------------------------------------
_start:
;	../../../platform/cc2530dk/SHT20/TM1640.c:34: sda_H;
;	assignBit
	setb	_P1_5
;	assignBit
	setb	_P1_5
;	../../../platform/cc2530dk/SHT20/TM1640.c:35: scl_H;
;	assignBit
	setb	_P1_4
;	assignBit
	setb	_P1_4
;	../../../platform/cc2530dk/SHT20/TM1640.c:36: delay_ms(2);
	mov	dptr,#0x0002
	mov	r0,#_delay_ms
	mov	r1,#(_delay_ms >> 8)
	mov	r2,#(_delay_ms >> 16)
	lcall	__sdcc_banked_call
;	../../../platform/cc2530dk/SHT20/TM1640.c:37: sda_L;
;	assignBit
	clr	_P1_5
;	assignBit
	clr	_P1_5
;	../../../platform/cc2530dk/SHT20/TM1640.c:38: delay_ms(2);
	mov	dptr,#0x0002
	mov	r0,#_delay_ms
	mov	r1,#(_delay_ms >> 8)
	mov	r2,#(_delay_ms >> 16)
	lcall	__sdcc_banked_call
;	../../../platform/cc2530dk/SHT20/TM1640.c:39: scl_L;
;	assignBit
	clr	_P1_4
;	assignBit
	clr	_P1_4
;	../../../platform/cc2530dk/SHT20/TM1640.c:40: delay_ms(2);
	mov	dptr,#0x0002
	mov	r0,#_delay_ms
	mov	r1,#(_delay_ms >> 8)
	mov	r2,#(_delay_ms >> 16)
	lcall	__sdcc_banked_call
;	../../../platform/cc2530dk/SHT20/TM1640.c:41: }
	ljmp	__sdcc_banked_ret
;------------------------------------------------------------
;Allocation info for local variables in function 'stop'
;------------------------------------------------------------
;	../../../platform/cc2530dk/SHT20/TM1640.c:54: void stop(void)
;	-----------------------------------------
;	 function stop
;	-----------------------------------------
_stop:
;	../../../platform/cc2530dk/SHT20/TM1640.c:56: sda_L;
;	assignBit
	clr	_P1_5
;	assignBit
	clr	_P1_5
;	../../../platform/cc2530dk/SHT20/TM1640.c:57: scl_H;
;	assignBit
	setb	_P1_4
;	assignBit
	setb	_P1_4
;	../../../platform/cc2530dk/SHT20/TM1640.c:58: delay_ms(2);
	mov	dptr,#0x0002
	mov	r0,#_delay_ms
	mov	r1,#(_delay_ms >> 8)
	mov	r2,#(_delay_ms >> 16)
	lcall	__sdcc_banked_call
;	../../../platform/cc2530dk/SHT20/TM1640.c:59: sda_H;
;	assignBit
	setb	_P1_5
;	assignBit
	setb	_P1_5
;	../../../platform/cc2530dk/SHT20/TM1640.c:60: delay_ms(2);
	mov	dptr,#0x0002
	mov	r0,#_delay_ms
	mov	r1,#(_delay_ms >> 8)
	mov	r2,#(_delay_ms >> 16)
	lcall	__sdcc_banked_call
;	../../../platform/cc2530dk/SHT20/TM1640.c:61: scl_L;
;	assignBit
	clr	_P1_4
;	assignBit
	clr	_P1_4
;	../../../platform/cc2530dk/SHT20/TM1640.c:62: delay_ms(2);
	mov	dptr,#0x0002
	mov	r0,#_delay_ms
	mov	r1,#(_delay_ms >> 8)
	mov	r2,#(_delay_ms >> 16)
	lcall	__sdcc_banked_call
;	../../../platform/cc2530dk/SHT20/TM1640.c:63: }
	ljmp	__sdcc_banked_ret
;------------------------------------------------------------
;Allocation info for local variables in function 'write'
;------------------------------------------------------------
;date                      Allocated to registers r7 
;i                         Allocated to registers 
;aa                        Allocated to registers r7 
;------------------------------------------------------------
;	../../../platform/cc2530dk/SHT20/TM1640.c:77: void write(unsigned char date)
;	-----------------------------------------
;	 function write
;	-----------------------------------------
_write:
	mov	r7,dpl
;	../../../platform/cc2530dk/SHT20/TM1640.c:80: aa=date;
;	../../../platform/cc2530dk/SHT20/TM1640.c:81: sda_L;
;	assignBit
	clr	_P1_5
;	assignBit
	clr	_P1_5
;	../../../platform/cc2530dk/SHT20/TM1640.c:82: scl_L;
;	assignBit
	clr	_P1_4
;	assignBit
	clr	_P1_4
;	../../../platform/cc2530dk/SHT20/TM1640.c:83: for(i=0;i<8;i++)
	mov	r6,#0x00
00105$:
;	../../../platform/cc2530dk/SHT20/TM1640.c:85: scl_L;
;	assignBit
	clr	_P1_4
;	assignBit
	clr	_P1_4
;	../../../platform/cc2530dk/SHT20/TM1640.c:86: if(aa&0x01)
	mov	a,r7
	jnb	acc.0,00102$
;	../../../platform/cc2530dk/SHT20/TM1640.c:88: sda_H;
;	assignBit
	setb	_P1_5
;	assignBit
	setb	_P1_5
;	../../../platform/cc2530dk/SHT20/TM1640.c:89: delay_ms(2);
	mov	dptr,#0x0002
	push	ar7
	push	ar6
	mov	r0,#_delay_ms
	mov	r1,#(_delay_ms >> 8)
	mov	r2,#(_delay_ms >> 16)
	lcall	__sdcc_banked_call
	pop	ar6
	pop	ar7
	sjmp	00103$
00102$:
;	../../../platform/cc2530dk/SHT20/TM1640.c:93: sda_L
;	assignBit
	clr	_P1_5
;	assignBit
	clr	_P1_5
;	../../../platform/cc2530dk/SHT20/TM1640.c:94: delay_ms(2);
	mov	dptr,#0x0002
	push	ar7
	push	ar6
	mov	r0,#_delay_ms
	mov	r1,#(_delay_ms >> 8)
	mov	r2,#(_delay_ms >> 16)
	lcall	__sdcc_banked_call
	pop	ar6
	pop	ar7
00103$:
;	../../../platform/cc2530dk/SHT20/TM1640.c:96: scl_H;
;	assignBit
	setb	_P1_4
;	assignBit
	setb	_P1_4
;	../../../platform/cc2530dk/SHT20/TM1640.c:97: aa=aa>>1;
	mov	a,r7
	clr	c
	rrc	a
	mov	r7,a
;	../../../platform/cc2530dk/SHT20/TM1640.c:83: for(i=0;i<8;i++)
	inc	r6
	cjne	r6,#0x08,00123$
00123$:
	jc	00105$
;	../../../platform/cc2530dk/SHT20/TM1640.c:99: scl_L;
;	assignBit
	clr	_P1_4
;	assignBit
	clr	_P1_4
;	../../../platform/cc2530dk/SHT20/TM1640.c:101: sda_L;
;	assignBit
	clr	_P1_5
;	assignBit
	clr	_P1_5
;	../../../platform/cc2530dk/SHT20/TM1640.c:103: }
	ljmp	__sdcc_banked_ret
;------------------------------------------------------------
;Allocation info for local variables in function 'init_tm1640'
;------------------------------------------------------------
;	../../../platform/cc2530dk/SHT20/TM1640.c:116: void init_tm1640(void)
;	-----------------------------------------
;	 function init_tm1640
;	-----------------------------------------
_init_tm1640:
;	../../../platform/cc2530dk/SHT20/TM1640.c:118: sda_H;
;	assignBit
	setb	_P1_5
;	assignBit
	setb	_P1_5
;	../../../platform/cc2530dk/SHT20/TM1640.c:119: scl_H;
;	assignBit
	setb	_P1_4
;	assignBit
	setb	_P1_4
;	../../../platform/cc2530dk/SHT20/TM1640.c:120: start();
	mov	r0,#_start
	mov	r1,#(_start >> 8)
	mov	r2,#(_start >> 16)
	lcall	__sdcc_banked_call
;	../../../platform/cc2530dk/SHT20/TM1640.c:121: write(SET_DATA_ORDER);//�������ݣ�0x40,0x44�ֱ��Ӧ��ַ�Զ���һ�͹̶���ַģʽ
	mov	dpl,#0x40
	mov	r0,#_write
	mov	r1,#(_write >> 8)
	mov	r2,#(_write >> 16)
	lcall	__sdcc_banked_call
;	../../../platform/cc2530dk/SHT20/TM1640.c:122: stop();
	mov	r0,#_stop
	mov	r1,#(_stop >> 8)
	mov	r2,#(_stop >> 16)
	lcall	__sdcc_banked_call
;	../../../platform/cc2530dk/SHT20/TM1640.c:123: start();
	mov	r0,#_start
	mov	r1,#(_start >> 8)
	mov	r2,#(_start >> 16)
	lcall	__sdcc_banked_call
;	../../../platform/cc2530dk/SHT20/TM1640.c:124: write(SET_DISPLAY);	  //������ʾ������ʾ0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f�ֱ��Ӧ������
	mov	dpl,#0x8c
	mov	r0,#_write
	mov	r1,#(_write >> 8)
	mov	r2,#(_write >> 16)
	lcall	__sdcc_banked_call
;	../../../platform/cc2530dk/SHT20/TM1640.c:127: stop();
	mov	r0,#_stop
	mov	r1,#(_stop >> 8)
	mov	r2,#(_stop >> 16)
	lcall	__sdcc_banked_call
;	../../../platform/cc2530dk/SHT20/TM1640.c:129: }
	ljmp	__sdcc_banked_ret
;------------------------------------------------------------
;Allocation info for local variables in function 'init_tm1640_NEW'
;------------------------------------------------------------
;i                         Allocated to registers 
;------------------------------------------------------------
;	../../../platform/cc2530dk/SHT20/TM1640.c:142: void init_tm1640_NEW(void)
;	-----------------------------------------
;	 function init_tm1640_NEW
;	-----------------------------------------
_init_tm1640_NEW:
;	../../../platform/cc2530dk/SHT20/TM1640.c:145: sda_H;
;	assignBit
	setb	_P1_5
;	assignBit
	setb	_P1_5
;	../../../platform/cc2530dk/SHT20/TM1640.c:146: scl_H;
;	assignBit
	setb	_P1_4
;	assignBit
	setb	_P1_4
;	../../../platform/cc2530dk/SHT20/TM1640.c:148: start();
	mov	r0,#_start
	mov	r1,#(_start >> 8)
	mov	r2,#(_start >> 16)
	lcall	__sdcc_banked_call
;	../../../platform/cc2530dk/SHT20/TM1640.c:149: write(SET_DATA_ORDER);	//�������ݣ�0x40,0x44�ֱ��Ӧ��ַ�Զ���һ�͹̶���ַģʽ
	mov	dpl,#0x40
	mov	r0,#_write
	mov	r1,#(_write >> 8)
	mov	r2,#(_write >> 16)
	lcall	__sdcc_banked_call
;	../../../platform/cc2530dk/SHT20/TM1640.c:150: stop();
	mov	r0,#_stop
	mov	r1,#(_stop >> 8)
	mov	r2,#(_stop >> 16)
	lcall	__sdcc_banked_call
;	../../../platform/cc2530dk/SHT20/TM1640.c:152: start();
	mov	r0,#_start
	mov	r1,#(_start >> 8)
	mov	r2,#(_start >> 16)
	lcall	__sdcc_banked_call
;	../../../platform/cc2530dk/SHT20/TM1640.c:153: write(0x00);		//���õ�ַ
	mov	dpl,#0x00
	mov	r0,#_write
	mov	r1,#(_write >> 8)
	mov	r2,#(_write >> 16)
	lcall	__sdcc_banked_call
;	../../../platform/cc2530dk/SHT20/TM1640.c:154: for(i=0;i<4;i++)
	mov	r7,#0x00
00102$:
;	../../../platform/cc2530dk/SHT20/TM1640.c:156: write(TM164_DATA[i]);
	mov	a,r7
	add	a,#_TM164_DATA
	mov	dpl,a
	clr	a
	addc	a,#(_TM164_DATA >> 8)
	mov	dph,a
	movx	a,@dptr
	mov	dpl,a
	push	ar7
	mov	r0,#_write
	mov	r1,#(_write >> 8)
	mov	r2,#(_write >> 16)
	lcall	__sdcc_banked_call
	pop	ar7
;	../../../platform/cc2530dk/SHT20/TM1640.c:154: for(i=0;i<4;i++)
	inc	r7
	cjne	r7,#0x04,00115$
00115$:
	jc	00102$
;	../../../platform/cc2530dk/SHT20/TM1640.c:158: stop();
	mov	r0,#_stop
	mov	r1,#(_stop >> 8)
	mov	r2,#(_stop >> 16)
	lcall	__sdcc_banked_call
;	../../../platform/cc2530dk/SHT20/TM1640.c:160: start();
	mov	r0,#_start
	mov	r1,#(_start >> 8)
	mov	r2,#(_start >> 16)
	lcall	__sdcc_banked_call
;	../../../platform/cc2530dk/SHT20/TM1640.c:161: write(SET_DISPLAY);	       //������ʾ������ʾ0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f�ֱ��Ӧ������
	mov	dpl,#0x8c
	mov	r0,#_write
	mov	r1,#(_write >> 8)
	mov	r2,#(_write >> 16)
	lcall	__sdcc_banked_call
;	../../../platform/cc2530dk/SHT20/TM1640.c:164: stop();
	mov	r0,#_stop
	mov	r1,#(_stop >> 8)
	mov	r2,#(_stop >> 16)
	lcall	__sdcc_banked_call
;	../../../platform/cc2530dk/SHT20/TM1640.c:166: }
	ljmp	__sdcc_banked_ret
;------------------------------------------------------------
;Allocation info for local variables in function 'send_LED_Display'
;------------------------------------------------------------
;data                      Allocated to stack - sp -5
;type                      Allocated to stack - sp -6
;address                   Allocated to registers r7 
;SEG_1                     Allocated to registers r4 
;SEG_2                     Allocated to registers r3 
;SEG_3                     Allocated to registers r2 
;SEG_4                     Allocated to stack - sp +0
;------------------------------------------------------------
;	../../../platform/cc2530dk/SHT20/TM1640.c:179: void send_LED_Display(unsigned char address,unsigned short data,unsigned char type)  
;	-----------------------------------------
;	 function send_LED_Display
;	-----------------------------------------
_send_LED_Display:
	inc	sp
	mov	r7,dpl
;	../../../platform/cc2530dk/SHT20/TM1640.c:182: if(type == 1)//��ʾ�¶ȵ�����
	mov	a,sp
	add	a,#0xfa
	mov	r0,a
	cjne	@r0,#0x01,00110$
;	../../../platform/cc2530dk/SHT20/TM1640.c:184: SEG_4 = 11;
	mov	r6,#0x0b
	sjmp	00111$
00110$:
;	../../../platform/cc2530dk/SHT20/TM1640.c:186: else if(type == 2)//��ʾʪ�ȵ�����
	mov	a,sp
	add	a,#0xfa
	mov	r0,a
	cjne	@r0,#0x02,00107$
;	../../../platform/cc2530dk/SHT20/TM1640.c:188: SEG_4 = 12;
	mov	r6,#0x0c
	sjmp	00111$
00107$:
;	../../../platform/cc2530dk/SHT20/TM1640.c:190: else if(type == 3)//��ʾ��ǿ������
	mov	a,sp
	add	a,#0xfa
	mov	r0,a
	cjne	@r0,#0x03,00104$
;	../../../platform/cc2530dk/SHT20/TM1640.c:192: SEG_4 = data%10;
	push	ar7
	mov	a,#0x0a
	push	acc
	clr	a
	push	acc
	mov	a,sp
	add	a,#0xf8
	mov	r0,a
	mov	dpl,@r0
	inc	r0
	mov	dph,@r0
	lcall	__moduint
	mov	r4,dpl
	mov	r5,dph
	dec	sp
	dec	sp
	pop	ar7
	mov	ar6,r4
	sjmp	00111$
00104$:
;	../../../platform/cc2530dk/SHT20/TM1640.c:194: else if(type == 4)//�������ģ����ʾ
	mov	a,sp
	add	a,#0xfa
	mov	r0,a
	cjne	@r0,#0x04,00111$
;	../../../platform/cc2530dk/SHT20/TM1640.c:199: SEG_4 = data%10;
	push	ar7
	mov	a,#0x0a
	push	acc
	clr	a
	push	acc
	mov	a,sp
	add	a,#0xf8
	mov	r0,a
	mov	dpl,@r0
	inc	r0
	mov	dph,@r0
	lcall	__moduint
	mov	r4,dpl
	mov	r5,dph
	dec	sp
	dec	sp
	pop	ar7
	mov	ar6,r4
00111$:
;	../../../platform/cc2530dk/SHT20/TM1640.c:201: if(data > 1000)
	mov	a,sp
	add	a,#0xfb
	mov	r0,a
	clr	c
	mov	a,#0xe8
	subb	a,@r0
	mov	a,#0x03
	inc	r0
	subb	a,@r0
	jc	00152$
	ljmp	00116$
00152$:
;	../../../platform/cc2530dk/SHT20/TM1640.c:203: SEG_1 = data/1000;
	push	ar7
	push	ar6
	mov	a,#0xe8
	push	acc
	mov	a,#0x03
	push	acc
	mov	a,sp
	add	a,#0xf7
	mov	r0,a
	mov	dpl,@r0
	inc	r0
	mov	dph,@r0
	lcall	__divuint
	mov	r4,dpl
	dec	sp
	dec	sp
;	../../../platform/cc2530dk/SHT20/TM1640.c:204: SEG_2 = (data/100)%10;
	push	ar4
	mov	a,#0x64
	push	acc
	clr	a
	push	acc
	mov	a,sp
	add	a,#0xf6
	mov	r0,a
	mov	dpl,@r0
	inc	r0
	mov	dph,@r0
	lcall	__divuint
	mov	r3,dpl
	mov	r5,dph
	dec	sp
	dec	sp
	mov	a,#0x0a
	push	acc
	clr	a
	push	acc
	mov	dpl,r3
	mov	dph,r5
	lcall	__moduint
	mov	r3,dpl
	dec	sp
	dec	sp
;	../../../platform/cc2530dk/SHT20/TM1640.c:205: SEG_3 = (data/10)%10;
	push	ar3
	mov	a,#0x0a
	push	acc
	clr	a
	push	acc
	mov	a,sp
	add	a,#0xf5
	mov	r0,a
	mov	dpl,@r0
	inc	r0
	mov	dph,@r0
	lcall	__divuint
	mov	r2,dpl
	mov	r5,dph
	dec	sp
	dec	sp
	mov	a,#0x0a
	push	acc
	clr	a
	push	acc
	mov	dpl,r2
	mov	dph,r5
	lcall	__moduint
	mov	r2,dpl
	mov	r5,dph
	dec	sp
	dec	sp
	pop	ar3
	pop	ar4
	pop	ar6
	pop	ar7
	sjmp	00117$
00116$:
;	../../../platform/cc2530dk/SHT20/TM1640.c:207: else if(data > 9)
	mov	a,sp
	add	a,#0xfb
	mov	r0,a
	clr	c
	mov	a,#0x09
	subb	a,@r0
	clr	a
	inc	r0
	subb	a,@r0
	jnc	00113$
;	../../../platform/cc2530dk/SHT20/TM1640.c:209: SEG_1 = data/10; 
	push	ar6
	push	ar7
	mov	a,#0x0a
	push	acc
	clr	a
	push	acc
	mov	a,sp
	add	a,#0xf7
	mov	r0,a
	mov	dpl,@r0
	inc	r0
	mov	dph,@r0
	lcall	__divuint
	mov	r5,dpl
	dec	sp
	dec	sp
	mov	ar4,r5
;	../../../platform/cc2530dk/SHT20/TM1640.c:210: SEG_2 = data%10;
	push	ar4
	mov	a,#0x0a
	push	acc
	clr	a
	push	acc
	mov	a,sp
	add	a,#0xf6
	mov	r0,a
	mov	dpl,@r0
	inc	r0
	mov	dph,@r0
	lcall	__moduint
	mov	r5,dpl
	dec	sp
	dec	sp
	pop	ar4
	pop	ar7
	mov	ar3,r5
;	../../../platform/cc2530dk/SHT20/TM1640.c:211: SEG_3 = 10;
	mov	r2,#0x0a
	pop	ar6
	sjmp	00117$
00113$:
;	../../../platform/cc2530dk/SHT20/TM1640.c:215: SEG_1 = 0x00;
	mov	r4,#0x00
;	../../../platform/cc2530dk/SHT20/TM1640.c:216: SEG_2 = data;
	mov	a,sp
	add	a,#0xfb
	mov	r0,a
	mov	ar3,@r0
;	../../../platform/cc2530dk/SHT20/TM1640.c:217: SEG_3 = 10;
	mov	r2,#0x0a
00117$:
;	../../../platform/cc2530dk/SHT20/TM1640.c:220: sda_H;
;	assignBit
	setb	_P1_5
;	assignBit
	setb	_P1_5
;	../../../platform/cc2530dk/SHT20/TM1640.c:221: scl_H;
;	assignBit
	setb	_P1_4
;	assignBit
	setb	_P1_4
;	../../../platform/cc2530dk/SHT20/TM1640.c:223: start();
	push	ar7
	push	ar6
	push	ar4
	push	ar3
	push	ar2
	mov	r0,#_start
	mov	r1,#(_start >> 8)
	mov	r2,#(_start >> 16)
	lcall	__sdcc_banked_call
;	../../../platform/cc2530dk/SHT20/TM1640.c:224: write(SET_DATA_ORDER);	//�������ݣ�0x40,0x44�ֱ��Ӧ��ַ�Զ���һ�͹̶���ַģʽ
	mov	dpl,#0x40
	mov	r0,#_write
	mov	r1,#(_write >> 8)
	mov	r2,#(_write >> 16)
	lcall	__sdcc_banked_call
;	../../../platform/cc2530dk/SHT20/TM1640.c:225: stop();
	mov	r0,#_stop
	mov	r1,#(_stop >> 8)
	mov	r2,#(_stop >> 16)
	lcall	__sdcc_banked_call
;	../../../platform/cc2530dk/SHT20/TM1640.c:227: start();
	mov	r0,#_start
	mov	r1,#(_start >> 8)
	mov	r2,#(_start >> 16)
	lcall	__sdcc_banked_call
	pop	ar2
	pop	ar3
	pop	ar4
	pop	ar6
	pop	ar7
;	../../../platform/cc2530dk/SHT20/TM1640.c:228: write(address);	//������ʼ��ַ
	mov	dpl,r7
	push	ar6
	push	ar4
	push	ar3
	push	ar2
	mov	r0,#_write
	mov	r1,#(_write >> 8)
	mov	r2,#(_write >> 16)
	lcall	__sdcc_banked_call
	pop	ar2
	pop	ar3
	pop	ar4
;	../../../platform/cc2530dk/SHT20/TM1640.c:229: write(TM164_DATA[SEG_1]);
	mov	a,r4
	add	a,#_TM164_DATA
	mov	dpl,a
	clr	a
	addc	a,#(_TM164_DATA >> 8)
	mov	dph,a
	movx	a,@dptr
	mov	dpl,a
	push	ar3
	push	ar2
	mov	r0,#_write
	mov	r1,#(_write >> 8)
	mov	r2,#(_write >> 16)
	lcall	__sdcc_banked_call
	pop	ar2
	pop	ar3
;	../../../platform/cc2530dk/SHT20/TM1640.c:230: write(TM164_DATA[SEG_2]);
	mov	a,r3
	add	a,#_TM164_DATA
	mov	dpl,a
	clr	a
	addc	a,#(_TM164_DATA >> 8)
	mov	dph,a
	movx	a,@dptr
	mov	dpl,a
	push	ar2
	mov	r0,#_write
	mov	r1,#(_write >> 8)
	mov	r2,#(_write >> 16)
	lcall	__sdcc_banked_call
	pop	ar2
;	../../../platform/cc2530dk/SHT20/TM1640.c:231: write(TM164_DATA[SEG_3]);
	mov	a,r2
	add	a,#_TM164_DATA
	mov	dpl,a
	clr	a
	addc	a,#(_TM164_DATA >> 8)
	mov	dph,a
	movx	a,@dptr
	mov	dpl,a
	mov	r0,#_write
	mov	r1,#(_write >> 8)
	mov	r2,#(_write >> 16)
	lcall	__sdcc_banked_call
	pop	ar6
;	../../../platform/cc2530dk/SHT20/TM1640.c:232: write(TM164_DATA[SEG_4]);
	mov	a,r6
	add	a,#_TM164_DATA
	mov	dpl,a
	clr	a
	addc	a,#(_TM164_DATA >> 8)
	mov	dph,a
	movx	a,@dptr
	mov	dpl,a
	mov	r0,#_write
	mov	r1,#(_write >> 8)
	mov	r2,#(_write >> 16)
	lcall	__sdcc_banked_call
;	../../../platform/cc2530dk/SHT20/TM1640.c:234: stop();
	mov	r0,#_stop
	mov	r1,#(_stop >> 8)
	mov	r2,#(_stop >> 16)
	lcall	__sdcc_banked_call
;	../../../platform/cc2530dk/SHT20/TM1640.c:236: start();
	mov	r0,#_start
	mov	r1,#(_start >> 8)
	mov	r2,#(_start >> 16)
	lcall	__sdcc_banked_call
;	../../../platform/cc2530dk/SHT20/TM1640.c:237: write(SET_DISPLAY);	//������ʾ������ʾ0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f�ֱ��Ӧ������
	mov	dpl,#0x8c
	mov	r0,#_write
	mov	r1,#(_write >> 8)
	mov	r2,#(_write >> 16)
	lcall	__sdcc_banked_call
;	../../../platform/cc2530dk/SHT20/TM1640.c:240: stop();
	mov	r0,#_stop
	mov	r1,#(_stop >> 8)
	mov	r2,#(_stop >> 16)
	lcall	__sdcc_banked_call
;	../../../platform/cc2530dk/SHT20/TM1640.c:241: }
	dec	sp
	ljmp	__sdcc_banked_ret
;------------------------------------------------------------
;Allocation info for local variables in function 'LED_DisplayClear'
;------------------------------------------------------------
;SEG_1                     Allocated to registers 
;SEG_2                     Allocated to registers 
;SEG_3                     Allocated to registers 
;SEG_4                     Allocated to registers 
;------------------------------------------------------------
;	../../../platform/cc2530dk/SHT20/TM1640.c:253: void LED_DisplayClear(void)  
;	-----------------------------------------
;	 function LED_DisplayClear
;	-----------------------------------------
_LED_DisplayClear:
;	../../../platform/cc2530dk/SHT20/TM1640.c:257: sda_H;
;	assignBit
	setb	_P1_5
;	assignBit
	setb	_P1_5
;	../../../platform/cc2530dk/SHT20/TM1640.c:258: scl_H;
;	assignBit
	setb	_P1_4
;	assignBit
	setb	_P1_4
;	../../../platform/cc2530dk/SHT20/TM1640.c:260: start();
	mov	r0,#_start
	mov	r1,#(_start >> 8)
	mov	r2,#(_start >> 16)
	lcall	__sdcc_banked_call
;	../../../platform/cc2530dk/SHT20/TM1640.c:261: write(SET_DATA_ORDER);	//�������ݣ�0x40,0x44�ֱ��Ӧ��ַ�Զ���һ�͹̶���ַģʽ
	mov	dpl,#0x40
	mov	r0,#_write
	mov	r1,#(_write >> 8)
	mov	r2,#(_write >> 16)
	lcall	__sdcc_banked_call
;	../../../platform/cc2530dk/SHT20/TM1640.c:262: stop();
	mov	r0,#_stop
	mov	r1,#(_stop >> 8)
	mov	r2,#(_stop >> 16)
	lcall	__sdcc_banked_call
;	../../../platform/cc2530dk/SHT20/TM1640.c:264: start();
	mov	r0,#_start
	mov	r1,#(_start >> 8)
	mov	r2,#(_start >> 16)
	lcall	__sdcc_banked_call
;	../../../platform/cc2530dk/SHT20/TM1640.c:265: write(0xc0);	//������ʼ��ַ
	mov	dpl,#0xc0
	mov	r0,#_write
	mov	r1,#(_write >> 8)
	mov	r2,#(_write >> 16)
	lcall	__sdcc_banked_call
;	../../../platform/cc2530dk/SHT20/TM1640.c:266: write(TM164_DATA[SEG_1]);
	mov	dptr,#(_TM164_DATA + 0x000a)
	movx	a,@dptr
	mov	dpl,a
	mov	r0,#_write
	mov	r1,#(_write >> 8)
	mov	r2,#(_write >> 16)
	lcall	__sdcc_banked_call
;	../../../platform/cc2530dk/SHT20/TM1640.c:267: write(TM164_DATA[SEG_2]);
	mov	dptr,#(_TM164_DATA + 0x000a)
	movx	a,@dptr
	mov	dpl,a
	mov	r0,#_write
	mov	r1,#(_write >> 8)
	mov	r2,#(_write >> 16)
	lcall	__sdcc_banked_call
;	../../../platform/cc2530dk/SHT20/TM1640.c:268: write(TM164_DATA[SEG_3]);
	mov	dptr,#(_TM164_DATA + 0x000a)
	movx	a,@dptr
	mov	dpl,a
	mov	r0,#_write
	mov	r1,#(_write >> 8)
	mov	r2,#(_write >> 16)
	lcall	__sdcc_banked_call
;	../../../platform/cc2530dk/SHT20/TM1640.c:269: write(TM164_DATA[SEG_4]);
	mov	dptr,#(_TM164_DATA + 0x000a)
	movx	a,@dptr
	mov	dpl,a
	mov	r0,#_write
	mov	r1,#(_write >> 8)
	mov	r2,#(_write >> 16)
	lcall	__sdcc_banked_call
;	../../../platform/cc2530dk/SHT20/TM1640.c:271: stop();
	mov	r0,#_stop
	mov	r1,#(_stop >> 8)
	mov	r2,#(_stop >> 16)
	lcall	__sdcc_banked_call
;	../../../platform/cc2530dk/SHT20/TM1640.c:273: start();
	mov	r0,#_start
	mov	r1,#(_start >> 8)
	mov	r2,#(_start >> 16)
	lcall	__sdcc_banked_call
;	../../../platform/cc2530dk/SHT20/TM1640.c:274: write(SET_DISPLAY);	//������ʾ������ʾ0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f�ֱ��Ӧ������
	mov	dpl,#0x8c
	mov	r0,#_write
	mov	r1,#(_write >> 8)
	mov	r2,#(_write >> 16)
	lcall	__sdcc_banked_call
;	../../../platform/cc2530dk/SHT20/TM1640.c:277: stop();
	mov	r0,#_stop
	mov	r1,#(_stop >> 8)
	mov	r2,#(_stop >> 16)
	lcall	__sdcc_banked_call
;	../../../platform/cc2530dk/SHT20/TM1640.c:278: }
	ljmp	__sdcc_banked_ret
;------------------------------------------------------------
;Allocation info for local variables in function 'send_z'
;------------------------------------------------------------
;date                      Allocated to stack - sp -3
;address                   Allocated to registers r7 
;i                         Allocated to registers 
;------------------------------------------------------------
;	../../../platform/cc2530dk/SHT20/TM1640.c:281: void send_z(unsigned char address,unsigned char date)
;	-----------------------------------------
;	 function send_z
;	-----------------------------------------
_send_z:
	mov	r7,dpl
;	../../../platform/cc2530dk/SHT20/TM1640.c:284: start();
	push	ar7
	mov	r0,#_start
	mov	r1,#(_start >> 8)
	mov	r2,#(_start >> 16)
	lcall	__sdcc_banked_call
	pop	ar7
;	../../../platform/cc2530dk/SHT20/TM1640.c:285: write(address);	//������ʼ��ַ
	mov	dpl,r7
	mov	r0,#_write
	mov	r1,#(_write >> 8)
	mov	r2,#(_write >> 16)
	lcall	__sdcc_banked_call
;	../../../platform/cc2530dk/SHT20/TM1640.c:286: for(i=0;i<4;i++)
	mov	r7,#0x00
00102$:
;	../../../platform/cc2530dk/SHT20/TM1640.c:288: write(TM164_DATA[i]);
	mov	a,r7
	add	a,#_TM164_DATA
	mov	dpl,a
	clr	a
	addc	a,#(_TM164_DATA >> 8)
	mov	dph,a
	movx	a,@dptr
	mov	dpl,a
	push	ar7
	mov	r0,#_write
	mov	r1,#(_write >> 8)
	mov	r2,#(_write >> 16)
	lcall	__sdcc_banked_call
	pop	ar7
;	../../../platform/cc2530dk/SHT20/TM1640.c:286: for(i=0;i<4;i++)
	inc	r7
	cjne	r7,#0x04,00115$
00115$:
	jc	00102$
;	../../../platform/cc2530dk/SHT20/TM1640.c:290: stop();
	mov	r0,#_stop
	mov	r1,#(_stop >> 8)
	mov	r2,#(_stop >> 16)
	lcall	__sdcc_banked_call
;	../../../platform/cc2530dk/SHT20/TM1640.c:291: }
	ljmp	__sdcc_banked_ret
;------------------------------------------------------------
;Allocation info for local variables in function 'send'
;------------------------------------------------------------
;date                      Allocated to stack - sp -3
;address                   Allocated to registers r7 
;------------------------------------------------------------
;	../../../platform/cc2530dk/SHT20/TM1640.c:295: void send(unsigned char address, unsigned char date)
;	-----------------------------------------
;	 function send
;	-----------------------------------------
_send:
	mov	r7,dpl
;	../../../platform/cc2530dk/SHT20/TM1640.c:298: start();
	push	ar7
	mov	r0,#_start
	mov	r1,#(_start >> 8)
	mov	r2,#(_start >> 16)
	lcall	__sdcc_banked_call
	pop	ar7
;	../../../platform/cc2530dk/SHT20/TM1640.c:299: write(address);	//����ʾ���ݶ�Ӧ��ַ
	mov	dpl,r7
	mov	r0,#_write
	mov	r1,#(_write >> 8)
	mov	r2,#(_write >> 16)
	lcall	__sdcc_banked_call
;	../../../platform/cc2530dk/SHT20/TM1640.c:300: write(date);	//��BYTE��ʾ����
	mov	a,sp
	add	a,#0xfd
	mov	r0,a
	mov	dpl,@r0
	mov	r0,#_write
	mov	r1,#(_write >> 8)
	mov	r2,#(_write >> 16)
	lcall	__sdcc_banked_call
;	../../../platform/cc2530dk/SHT20/TM1640.c:301: stop();
	mov	r0,#_stop
	mov	r1,#(_stop >> 8)
	mov	r2,#(_stop >> 16)
	lcall	__sdcc_banked_call
;	../../../platform/cc2530dk/SHT20/TM1640.c:302: }
	ljmp	__sdcc_banked_ret
	.area CSEG    (CODE)
	.area CONST   (CODE)
	.area XINIT   (CODE)
__xinit__TM164_DATA:
	.db #0x3f	; 63
	.db #0x06	; 6
	.db #0x5b	; 91
	.db #0x4f	; 79	'O'
	.db #0x66	; 102	'f'
	.db #0x6d	; 109	'm'
	.db #0x7d	; 125
	.db #0x07	; 7
	.db #0x7f	; 127
	.db #0x6f	; 111	'o'
	.db #0x00	; 0
	.db #0x39	; 57	'9'
	.db #0x76	; 118	'v'
	.db #0x80	; 128
__xinit__TM164_SIG:
	.db #0x01	; 1
	.db #0x02	; 2
	.db #0x04	; 4
	.db #0x08	; 8
	.area CABS    (ABS,CODE)
