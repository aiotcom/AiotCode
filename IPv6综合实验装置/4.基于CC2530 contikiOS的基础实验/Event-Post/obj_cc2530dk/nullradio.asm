;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 3.8.4 #10774 (Linux)
;--------------------------------------------------------
	.module nullradio
	.optsdcc -mmcs51 --model-huge
	
;--------------------------------------------------------
; Public variables in this module
;--------------------------------------------------------
	.globl _nullradio_driver
;--------------------------------------------------------
; special function registers
;--------------------------------------------------------
	.area RSEG    (ABS,DATA)
	.org 0x0000
;--------------------------------------------------------
; special function bits
;--------------------------------------------------------
	.area RSEG    (ABS,DATA)
	.org 0x0000
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
;--------------------------------------------------------
; absolute external ram data
;--------------------------------------------------------
	.area XABS    (ABS,XDATA)
;--------------------------------------------------------
; external initialized ram data
;--------------------------------------------------------
	.area XISEG   (XDATA)
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
;Allocation info for local variables in function 'init'
;------------------------------------------------------------
;	../../../core/dev/nullradio.c:6: init(void)
;	-----------------------------------------
;	 function init
;	-----------------------------------------
_init:
	ar7 = 0x07
	ar6 = 0x06
	ar5 = 0x05
	ar4 = 0x04
	ar3 = 0x03
	ar2 = 0x02
	ar1 = 0x01
	ar0 = 0x00
;	../../../core/dev/nullradio.c:8: return 0;
	mov	dptr,#0x0000
;	../../../core/dev/nullradio.c:9: }
	ljmp	__sdcc_banked_ret
;------------------------------------------------------------
;Allocation info for local variables in function 'prepare'
;------------------------------------------------------------
;payload_len               Allocated to stack - sp -4
;payload                   Allocated to registers 
;------------------------------------------------------------
;	../../../core/dev/nullradio.c:12: prepare(const void *payload, unsigned short payload_len)
;	-----------------------------------------
;	 function prepare
;	-----------------------------------------
_prepare:
;	../../../core/dev/nullradio.c:14: return 1;
	mov	dptr,#0x0001
;	../../../core/dev/nullradio.c:15: }
	ljmp	__sdcc_banked_ret
;------------------------------------------------------------
;Allocation info for local variables in function 'transmit'
;------------------------------------------------------------
;transmit_len              Allocated to registers 
;------------------------------------------------------------
;	../../../core/dev/nullradio.c:18: transmit(unsigned short transmit_len)
;	-----------------------------------------
;	 function transmit
;	-----------------------------------------
_transmit:
;	../../../core/dev/nullradio.c:20: return RADIO_TX_OK;
	mov	dptr,#0x0000
;	../../../core/dev/nullradio.c:21: }
	ljmp	__sdcc_banked_ret
;------------------------------------------------------------
;Allocation info for local variables in function 'send'
;------------------------------------------------------------
;payload_len               Allocated to stack - sp -4
;payload                   Allocated to registers r5 r6 r7 
;------------------------------------------------------------
;	../../../core/dev/nullradio.c:24: send(const void *payload, unsigned short payload_len)
;	-----------------------------------------
;	 function send
;	-----------------------------------------
_send:
	mov	r5,dpl
	mov	r6,dph
	mov	r7,b
;	../../../core/dev/nullradio.c:26: prepare(payload, payload_len);
	mov	a,sp
	add	a,#0xfc
	mov	r0,a
	mov	a,@r0
	push	acc
	inc	r0
	mov	a,@r0
	push	acc
	mov	dpl,r5
	mov	dph,r6
	mov	b,r7
	mov	r0,#_prepare
	mov	r1,#(_prepare >> 8)
	mov	r2,#(_prepare >> 16)
	lcall	__sdcc_banked_call
	dec	sp
	dec	sp
;	../../../core/dev/nullradio.c:27: return transmit(payload_len);
	mov	a,sp
	add	a,#0xfc
	mov	r0,a
	mov	dpl,@r0
	inc	r0
	mov	dph,@r0
	mov	r0,#_transmit
	mov	r1,#(_transmit >> 8)
	mov	r2,#(_transmit >> 16)
	lcall	__sdcc_banked_call
	mov	r6,dpl
	mov  r7,dph
;	../../../core/dev/nullradio.c:28: }
	ljmp	__sdcc_banked_ret
;------------------------------------------------------------
;Allocation info for local variables in function 'read'
;------------------------------------------------------------
;buf_len                   Allocated to stack - sp -4
;buf                       Allocated to registers 
;------------------------------------------------------------
;	../../../core/dev/nullradio.c:31: read(void *buf, unsigned short buf_len)
;	-----------------------------------------
;	 function read
;	-----------------------------------------
_read:
;	../../../core/dev/nullradio.c:33: return 0;
	mov	dptr,#0x0000
;	../../../core/dev/nullradio.c:34: }
	ljmp	__sdcc_banked_ret
;------------------------------------------------------------
;Allocation info for local variables in function 'channel_clear'
;------------------------------------------------------------
;	../../../core/dev/nullradio.c:37: channel_clear(void)
;	-----------------------------------------
;	 function channel_clear
;	-----------------------------------------
_channel_clear:
;	../../../core/dev/nullradio.c:39: return 1;
	mov	dptr,#0x0001
;	../../../core/dev/nullradio.c:40: }
	ljmp	__sdcc_banked_ret
;------------------------------------------------------------
;Allocation info for local variables in function 'receiving_packet'
;------------------------------------------------------------
;	../../../core/dev/nullradio.c:43: receiving_packet(void)
;	-----------------------------------------
;	 function receiving_packet
;	-----------------------------------------
_receiving_packet:
;	../../../core/dev/nullradio.c:45: return 0;
	mov	dptr,#0x0000
;	../../../core/dev/nullradio.c:46: }
	ljmp	__sdcc_banked_ret
;------------------------------------------------------------
;Allocation info for local variables in function 'pending_packet'
;------------------------------------------------------------
;	../../../core/dev/nullradio.c:49: pending_packet(void)
;	-----------------------------------------
;	 function pending_packet
;	-----------------------------------------
_pending_packet:
;	../../../core/dev/nullradio.c:51: return 0;
	mov	dptr,#0x0000
;	../../../core/dev/nullradio.c:52: }
	ljmp	__sdcc_banked_ret
;------------------------------------------------------------
;Allocation info for local variables in function 'on'
;------------------------------------------------------------
;	../../../core/dev/nullradio.c:55: on(void)
;	-----------------------------------------
;	 function on
;	-----------------------------------------
_on:
;	../../../core/dev/nullradio.c:57: return 0;
	mov	dptr,#0x0000
;	../../../core/dev/nullradio.c:58: }
	ljmp	__sdcc_banked_ret
;------------------------------------------------------------
;Allocation info for local variables in function 'off'
;------------------------------------------------------------
;	../../../core/dev/nullradio.c:61: off(void)
;	-----------------------------------------
;	 function off
;	-----------------------------------------
_off:
;	../../../core/dev/nullradio.c:63: return 0;
	mov	dptr,#0x0000
;	../../../core/dev/nullradio.c:64: }
	ljmp	__sdcc_banked_ret
	.area CSEG    (CODE)
	.area CONST   (CODE)
_nullradio_driver:
	.byte _init, (_init >> 8), (_init >> 16)
	.byte _prepare, (_prepare >> 8), (_prepare >> 16)
	.byte _transmit, (_transmit >> 8), (_transmit >> 16)
	.byte _send, (_send >> 8), (_send >> 16)
	.byte _read, (_read >> 8), (_read >> 16)
	.byte _channel_clear, (_channel_clear >> 8), (_channel_clear >> 16)
	.byte _receiving_packet, (_receiving_packet >> 8), (_receiving_packet >> 16)
	.byte _pending_packet, (_pending_packet >> 8), (_pending_packet >> 16)
	.byte _on, (_on >> 8), (_on >> 16)
	.byte _off, (_off >> 8), (_off >> 16)
	.area XINIT   (CODE)
	.area CABS    (ABS,CODE)
