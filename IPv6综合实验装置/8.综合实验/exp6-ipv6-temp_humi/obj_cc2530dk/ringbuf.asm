;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 3.8.4 #10774 (Linux)
;--------------------------------------------------------
	.module ringbuf
	.optsdcc -mmcs51 --model-huge
	
;--------------------------------------------------------
; Public variables in this module
;--------------------------------------------------------
	.globl _ringbuf_init
	.globl _ringbuf_put
	.globl _ringbuf_get
	.globl _ringbuf_size
	.globl _ringbuf_elements
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
;Allocation info for local variables in function 'ringbuf_init'
;------------------------------------------------------------
;dataptr                   Allocated to stack - sp -8
;size                      Allocated to stack - sp -9
;r                         Allocated to stack - sp -2
;------------------------------------------------------------
;	../../../core/lib/ringbuf.c:43: ringbuf_init(struct ringbuf *r, uint8_t *dataptr, uint8_t size)
;	-----------------------------------------
;	 function ringbuf_init
;	-----------------------------------------
_ringbuf_init:
	ar7 = 0x07
	ar6 = 0x06
	ar5 = 0x05
	ar4 = 0x04
	ar3 = 0x03
	ar2 = 0x02
	ar1 = 0x01
	ar0 = 0x00
	push	dpl
	push	dph
	push	b
;	../../../core/lib/ringbuf.c:45: r->data = dataptr;
	mov	r0,sp
	dec	r0
	dec	r0
	mov	dpl,@r0
	inc	r0
	mov	dph,@r0
	inc	r0
	mov	b,@r0
	mov	a,sp
	add	a,#0xf8
	mov	r1,a
	mov	a,@r1
	lcall	__gptrput
	inc	dptr
	inc	r1
	mov	a,@r1
	lcall	__gptrput
	inc	dptr
	inc	r1
	mov	a,@r1
	lcall	__gptrput
;	../../../core/lib/ringbuf.c:46: r->mask = size - 1;
	mov	r0,sp
	dec	r0
	dec	r0
	mov	a,#0x03
	add	a,@r0
	mov	r2,a
	clr	a
	inc	r0
	addc	a,@r0
	mov	r3,a
	inc	r0
	mov	ar4,@r0
	mov	a,sp
	add	a,#0xf7
	mov	r0,a
	mov	ar7,@r0
	dec	r7
	mov	dpl,r2
	mov	dph,r3
	mov	b,r4
	mov	a,r7
	lcall	__gptrput
;	../../../core/lib/ringbuf.c:47: r->put_ptr = 0;
	mov	r0,sp
	dec	r0
	dec	r0
	mov	a,#0x04
	add	a,@r0
	mov	r5,a
	clr	a
	inc	r0
	addc	a,@r0
	mov	r6,a
	inc	r0
	mov	ar7,@r0
	mov	dpl,r5
	mov	dph,r6
	mov	b,r7
	clr	a
	lcall	__gptrput
;	../../../core/lib/ringbuf.c:48: r->get_ptr = 0;
	mov	r0,sp
	dec	r0
	dec	r0
	mov	a,#0x05
	add	a,@r0
	mov	r5,a
	clr	a
	inc	r0
	addc	a,@r0
	mov	r6,a
	inc	r0
	mov	ar7,@r0
	mov	dpl,r5
	mov	dph,r6
	mov	b,r7
	clr	a
	lcall	__gptrput
;	../../../core/lib/ringbuf.c:49: }
	dec	sp
	dec	sp
	dec	sp
	ljmp	__sdcc_banked_ret
;------------------------------------------------------------
;Allocation info for local variables in function 'ringbuf_put'
;------------------------------------------------------------
;c                         Allocated to stack - sp -9
;r                         Allocated to stack - sp -5
;sloc0                     Allocated to stack - sp -2
;------------------------------------------------------------
;	../../../core/lib/ringbuf.c:52: ringbuf_put(struct ringbuf *r, uint8_t c)
;	-----------------------------------------
;	 function ringbuf_put
;	-----------------------------------------
_ringbuf_put:
	push	dpl
	push	dph
	push	b
	inc	sp
	inc	sp
	inc	sp
;	../../../core/lib/ringbuf.c:63: if(((r->put_ptr - r->get_ptr) & r->mask) == r->mask) {
	mov	a,sp
	add	a,#0xfb
	mov	r0,a
	mov	a,#0x04
	add	a,@r0
	mov	r2,a
	clr	a
	inc	r0
	addc	a,@r0
	mov	r3,a
	inc	r0
	mov	ar4,@r0
	mov	dpl,r2
	mov	dph,r3
	mov	b,r4
	lcall	__gptrget
	mov	r2,a
	mov	r4,#0x00
	mov	a,sp
	add	a,#0xfb
	mov	r0,a
	mov	a,#0x05
	add	a,@r0
	mov	r3,a
	clr	a
	inc	r0
	addc	a,@r0
	mov	r6,a
	inc	r0
	mov	ar7,@r0
	mov	dpl,r3
	mov	dph,r6
	mov	b,r7
	lcall	__gptrget
	mov	r3,a
	mov	r7,#0x00
	mov	a,r2
	clr	c
	subb	a,r3
	mov	r2,a
	mov	a,r4
	subb	a,r7
	mov	r4,a
	mov	a,sp
	add	a,#0xfb
	mov	r0,a
	mov	a,#0x03
	add	a,@r0
	mov	r5,a
	clr	a
	inc	r0
	addc	a,@r0
	mov	r6,a
	inc	r0
	mov	ar7,@r0
	mov	dpl,r5
	mov	dph,r6
	mov	b,r7
	lcall	__gptrget
	mov	r5,a
	mov	r7,#0x00
	anl	ar2,a
	mov	a,r7
	anl	ar4,a
	mov	a,r2
	cjne	a,ar5,00102$
	mov	a,r4
	cjne	a,ar7,00102$
;	../../../core/lib/ringbuf.c:64: return 0;
	mov	dptr,#0x0000
	ljmp	00103$
00102$:
;	../../../core/lib/ringbuf.c:66: r->data[r->put_ptr] = c;
	mov	a,sp
	add	a,#0xfb
	mov	r0,a
	mov	dpl,@r0
	inc	r0
	mov	dph,@r0
	inc	r0
	mov	b,@r0
	mov	r1,sp
	dec	r1
	dec	r1
	lcall	__gptrget
	mov	@r1,a
	inc	dptr
	lcall	__gptrget
	inc	r1
	mov	@r1,a
	inc	dptr
	lcall	__gptrget
	inc	r1
	mov	@r1,a
	mov	a,sp
	add	a,#0xfb
	mov	r0,a
	mov	a,#0x04
	add	a,@r0
	mov	r2,a
	clr	a
	inc	r0
	addc	a,@r0
	mov	r3,a
	inc	r0
	mov	ar4,@r0
	mov	dpl,r2
	mov	dph,r3
	mov	b,r4
	lcall	__gptrget
	mov	r7,a
	mov	r0,sp
	dec	r0
	dec	r0
	mov	a,r7
	add	a,@r0
	mov	r7,a
	clr	a
	inc	r0
	addc	a,@r0
	mov	r6,a
	inc	r0
	mov	ar5,@r0
	mov	dpl,r7
	mov	dph,r6
	mov	b,r5
	mov	a,sp
	add	a,#0xf7
	mov	r0,a
	mov	a,@r0
	lcall	__gptrput
;	../../../core/lib/ringbuf.c:67: r->put_ptr = (r->put_ptr + 1) & r->mask;
	mov	dpl,r2
	mov	dph,r3
	mov	b,r4
	lcall	__gptrget
	mov	r7,a
	mov	r0,sp
	dec	r0
	dec	r0
	mov	a,r7
	inc	a
	mov	@r0,a
	mov	a,sp
	add	a,#0xfb
	mov	r0,a
	mov	a,#0x03
	add	a,@r0
	mov	r5,a
	clr	a
	inc	r0
	addc	a,@r0
	mov	r6,a
	inc	r0
	mov	ar7,@r0
	mov	dpl,r5
	mov	dph,r6
	mov	b,r7
	lcall	__gptrget
	mov	r5,a
	mov	r0,sp
	dec	r0
	dec	r0
	mov	a,@r0
	anl	ar5,a
	mov	dpl,r2
	mov	dph,r3
	mov	b,r4
	mov	a,r5
	lcall	__gptrput
;	../../../core/lib/ringbuf.c:68: return 1;
	mov	dptr,#0x0001
00103$:
;	../../../core/lib/ringbuf.c:69: }
	mov	a,sp
	add	a,#0xfa
	mov	sp,a
	ljmp	__sdcc_banked_ret
;------------------------------------------------------------
;Allocation info for local variables in function 'ringbuf_get'
;------------------------------------------------------------
;r                         Allocated to stack - sp -4
;c                         Allocated to stack - sp +0
;sloc0                     Allocated to stack - sp +0
;sloc1                     Allocated to stack - sp -1
;------------------------------------------------------------
;	../../../core/lib/ringbuf.c:72: ringbuf_get(struct ringbuf *r)
;	-----------------------------------------
;	 function ringbuf_get
;	-----------------------------------------
_ringbuf_get:
	push	dpl
	push	dph
	push	b
	inc	sp
	inc	sp
;	../../../core/lib/ringbuf.c:86: if(((r->put_ptr - r->get_ptr) & r->mask) > 0) {
	mov	a,sp
	add	a,#0xfc
	mov	r0,a
	mov	a,#0x04
	add	a,@r0
	mov	r2,a
	clr	a
	inc	r0
	addc	a,@r0
	mov	r3,a
	inc	r0
	mov	ar4,@r0
	mov	dpl,r2
	mov	dph,r3
	mov	b,r4
	lcall	__gptrget
	mov	r2,a
	mov	r4,#0x00
	mov	a,sp
	add	a,#0xfc
	mov	r0,a
	mov	a,#0x05
	add	a,@r0
	mov	r3,a
	clr	a
	inc	r0
	addc	a,@r0
	mov	r6,a
	inc	r0
	mov	ar7,@r0
	mov	dpl,r3
	mov	dph,r6
	mov	b,r7
	lcall	__gptrget
	mov	r3,a
	mov	r7,#0x00
	mov	a,r2
	clr	c
	subb	a,r3
	mov	r2,a
	mov	a,r4
	subb	a,r7
	mov	r4,a
	mov	a,sp
	add	a,#0xfc
	mov	r0,a
	mov	a,#0x03
	add	a,@r0
	mov	r5,a
	clr	a
	inc	r0
	addc	a,@r0
	mov	r6,a
	inc	r0
	mov	ar7,@r0
	mov	dpl,r5
	mov	dph,r6
	mov	b,r7
	lcall	__gptrget
	mov	r5,a
	mov	r7,#0x00
	anl	ar2,a
	mov	a,r7
	anl	ar4,a
	clr	c
	clr	a
	subb	a,r2
	mov	a,#(0x00 ^ 0x80)
	mov	b,r4
	xrl	b,#0x80
	subb	a,b
	jc	00110$
	ljmp	00102$
00110$:
;	../../../core/lib/ringbuf.c:87: c = r->data[r->get_ptr];
	mov	a,sp
	add	a,#0xfc
	mov	r0,a
	mov	dpl,@r0
	inc	r0
	mov	dph,@r0
	inc	r0
	mov	b,@r0
	lcall	__gptrget
	mov	r5,a
	inc	dptr
	lcall	__gptrget
	mov	r6,a
	inc	dptr
	lcall	__gptrget
	mov	r7,a
	mov	a,sp
	add	a,#0xfc
	mov	r0,a
	mov	a,#0x05
	add	a,@r0
	mov	r2,a
	clr	a
	inc	r0
	addc	a,@r0
	mov	r3,a
	inc	r0
	mov	ar4,@r0
	mov	dpl,r2
	mov	dph,r3
	mov	b,r4
	mov	r0,sp
	dec	r0
	lcall	__gptrget
	mov	@r0,a
	mov	r0,sp
	dec	r0
	mov	a,@r0
	add	a,r5
	mov	r5,a
	clr	a
	addc	a,r6
	mov	r6,a
	mov	dpl,r5
	mov	dph,r6
	mov	b,r7
	mov	r0,sp
	lcall	__gptrget
	mov	@r0,a
;	../../../core/lib/ringbuf.c:88: r->get_ptr = (r->get_ptr + 1) & r->mask;
	mov	r0,sp
	dec	r0
	mov	ar7,@r0
	mov	r0,sp
	dec	r0
	mov	a,r7
	inc	a
	mov	@r0,a
	mov	a,sp
	add	a,#0xfc
	mov	r0,a
	mov	a,#0x03
	add	a,@r0
	mov	r5,a
	clr	a
	inc	r0
	addc	a,@r0
	mov	r6,a
	inc	r0
	mov	ar7,@r0
	mov	dpl,r5
	mov	dph,r6
	mov	b,r7
	lcall	__gptrget
	mov	r5,a
	mov	r0,sp
	dec	r0
	mov	a,@r0
	anl	ar5,a
	mov	dpl,r2
	mov	dph,r3
	mov	b,r4
	mov	a,r5
	lcall	__gptrput
;	../../../core/lib/ringbuf.c:89: return c;
	mov	r0,sp
	mov	ar5,@r0
	mov	r7,#0x00
	mov	dpl,r5
	mov	dph,r7
	sjmp	00104$
00102$:
;	../../../core/lib/ringbuf.c:91: return -1;
	mov	dptr,#0xffff
00104$:
;	../../../core/lib/ringbuf.c:93: }
	mov	a,sp
	add	a,#0xfb
	mov	sp,a
	ljmp	__sdcc_banked_ret
;------------------------------------------------------------
;Allocation info for local variables in function 'ringbuf_size'
;------------------------------------------------------------
;r                         Allocated to registers r5 r6 r7 
;------------------------------------------------------------
;	../../../core/lib/ringbuf.c:96: ringbuf_size(struct ringbuf *r)
;	-----------------------------------------
;	 function ringbuf_size
;	-----------------------------------------
_ringbuf_size:
	mov	r5,dpl
	mov	r6,dph
	mov	r7,b
;	../../../core/lib/ringbuf.c:98: return r->mask + 1;
	mov	a,#0x03
	add	a,r5
	mov	r5,a
	clr	a
	addc	a,r6
	mov	r6,a
	mov	dpl,r5
	mov	dph,r6
	mov	b,r7
	lcall	__gptrget
	mov	r5,a
	mov	r7,#0x00
	inc	r5
	cjne	r5,#0x00,00103$
	inc	r7
00103$:
	mov	dpl,r5
	mov	dph,r7
;	../../../core/lib/ringbuf.c:99: }
	ljmp	__sdcc_banked_ret
;------------------------------------------------------------
;Allocation info for local variables in function 'ringbuf_elements'
;------------------------------------------------------------
;r                         Allocated to registers r5 r6 r7 
;------------------------------------------------------------
;	../../../core/lib/ringbuf.c:102: ringbuf_elements(struct ringbuf *r)
;	-----------------------------------------
;	 function ringbuf_elements
;	-----------------------------------------
_ringbuf_elements:
	mov	r5,dpl
	mov	r6,dph
	mov	r7,b
;	../../../core/lib/ringbuf.c:104: return (r->put_ptr - r->get_ptr) & r->mask;
	mov	a,#0x04
	add	a,r5
	mov	r2,a
	clr	a
	addc	a,r6
	mov	r3,a
	mov	ar4,r7
	mov	dpl,r2
	mov	dph,r3
	mov	b,r4
	lcall	__gptrget
	mov	r2,a
	mov	r4,#0x00
	mov	a,#0x05
	add	a,r5
	mov	r0,a
	clr	a
	addc	a,r6
	mov	r1,a
	mov	ar3,r7
	mov	dpl,r0
	mov	dph,r1
	mov	b,r3
	lcall	__gptrget
	mov	r0,a
	mov	r3,#0x00
	mov	a,r2
	clr	c
	subb	a,r0
	mov	r2,a
	mov	a,r4
	subb	a,r3
	mov	r4,a
	mov	a,#0x03
	add	a,r5
	mov	r5,a
	clr	a
	addc	a,r6
	mov	r6,a
	mov	dpl,r5
	mov	dph,r6
	mov	b,r7
	lcall	__gptrget
	mov	r5,a
	mov	r7,#0x00
	anl	ar2,a
	mov	a,r7
	anl	ar4,a
	mov	dpl,r2
	mov	dph,r4
;	../../../core/lib/ringbuf.c:105: }
	ljmp	__sdcc_banked_ret
	.area CSEG    (CODE)
	.area CONST   (CODE)
	.area XINIT   (CODE)
	.area CABS    (ABS,CODE)
