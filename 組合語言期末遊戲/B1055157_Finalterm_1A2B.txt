
               AREA     HelloW,CODE,READONLY  
RAN1		DCD	16,5,91,13,39,587
RAN2		DCD	3,8,45,81,16,31
MASK		DCD	&FFFF
SWI_WriteC	EQU	&0
SWI_Time	EQU	&63
SWI_Clock	EQU	&61
SWI_Write0	EQU	&2
SWI_ReadC	EQU	&4
SWI_Exit		EQU	&11
TEXT	=	&0a,&0a,&0d,"START*****1A2B Guess 4digits Number*****START",&0a,&0d
TEXT1	=	"A : digits&positions right.  B : only digits right.",&0a,&0d,0
TEXT2	=	&0a,&0d,"Please input 4 different digits.",&0a,&0d
TEXT2_2	=	"The valid input characters are : ",0
TEXT5	=	&0a,&0d,"Show answer, and game over. => Input 'H'(Uppercase)",&0a,&0d,0
TEXT7	=	&0a,&0d,"Input '1' to restart. Input any other button to exit. ",0
TEXT8	=	&0a,&0d,"THE END.",0
WINTEXT	=	"You WIN!     You WIN!     You WIN!",&0a,&0d,0
	ALIGN
	ENTRY

START
		ADR	r0,TEXT
		SWI	SWI_Write0
		BL	MODE
		BL	GENERATE
		ADR	r0,TEXT2
		SWI	SWI_Write0
		ADR	r0,DIGITCOPY
		SWI	SWI_Write0
		ADR	r0,TEXT5
		SWI	SWI_Write0
;show answer
		;ADR	r0,ANSWER
		;SWI	SWI_Write0

		MOV	r11,#0	;guess round num
GUESS
		MOV	r0,#&0a
		SWI	SWI_WriteC
		ADD 	r11,r11,#1
		BL	ROUNDH
		BL	INPUT
		BL	RESULT
		ADR	r0,TEXT4
		SWI	SWI_Write0
		CMP	r3,#&34
		BNE	GUESS

		MOV	r2,#&57 ;過關r2存字元'W'
		BL	SHOWANS	
		ADR	r0,WINTEXT
		MOV	r1,#10
CONGRATULATIONS
		SWI	SWI_Write0
		SUB	r1,r1,#1
		CMP	r1,#0
		BGT	CONGRATULATIONS
BYE		ADR	r0,TEXT7
		SWI	SWI_Write0
		SWI	SWI_ReadC

		CMP	r0,#&31
		BEQ	RESET
		ADR	r0,TEXT8
		SWI	SWI_Write0
	    	SWI   	SWI_Exit

		ALIGN
RETURN		
		MOV	pc,r14
;
;
;
RESULT
		ADR	r5,INTEXT
		MOV	r3,#&30	;A
		MOV	r4,#&30	;B
		MOV	r9,#0	;INTEXT index
RLOOP1
		ADD	r9,r9,#1
		LDRB	r0,[r5],#1
		MOV	r7,r0	;load INTEXT c
		ADR	r6,ANSWER
		MOV	r10,#0	;ANSWER index
RLOOP2
		ADD	r10,r10,#1
		LDRB	r0,[r6],#1
		MOV	r8,r0	;load ANSWER c
		CMP	r7,r8
		BEQ	RCHECK
RCONT		CMP	r10,#4
		BNE	RLOOP2
		CMP	r9,#4
		BNE	RLOOP1
		ADR	r5,MESSAGE
		STRB	r3,[r5],#2
		STRB	r4,[r5],#2
		B	RETURN	
RCHECK
		CMP	r9,r10
		ADDEQ	r3,r3,#1
		ADDNE	r4,r4,#1
		B	RCONT
TEXT4		=	"      "
MESSAGE		=	"xAxB",&0a,&0d,0
ANSWER		=	"oooo",&0a,&0d,0
	ALIGN
;
;
;
SHOWANS	
		ADR	r0,TEXT6
		SWI	SWI_Write0
		ADR	r0,ANSWER
		SWI	SWI_Write0
		CMP	r2,#&57
		BEQ	RETURN
		BNE	BYE	

TEXT6		=	&0a,&0d,"The answer is ",0	
	ALIGN	
;
;
;
GENERATE
		ADR	r10,ANSWER
		MOV	r2,#0
		MOV	r9,#0
HERE		SWI	SWI_Time
		ADD	r9,r9,r0
		SWI	SWI_Clock
		ADD	r9,r9,r0
		ADR	r1,MASK
		LDR	r8,[r1]
		AND	r7,r9,r8
		B	DIVIDE
GCONT1		MOV	r0,r5
		B	NOREPEAT
GCONT2		ADD	r9,r9,r4
		ADD	r9,r9,r8
		STRB	r4,[r10],#1
		ADD	r2,r2,#1
		CMP	r2,#4
		BEQ	RETURN
		B	HERE

DIGITCOPY		=	"xxxxxxxxxxxxxxxx",0
		ALIGN
;
DIVIDE		MOV	r8,#0
		MOV	r5,r7
LOOPDIV		CMP	r5,r6
		BLT	GCONT1
		SUB	r5,r5,r6
		ADD	r8,r8,#1
		B	LOOPDIV               
NOREPEAT
		ADR	r3,DIGIT
		CMP	r12,#&32
		ADREQ	r3,DIGIT_PORKER
		CMP	r12,#&33
		ADREQ	r3,DIGIT_HEX
		ADR	r1,TEMP
		MOV	r4,r0
		MOV	r11,#0
		CMP	r4,#0
		BEQ	ZERO

NRLOOP1		LDRB	r0,[r3],#1
		ADD	r11,r11,#1
		CMP	r11,r4
		BLT	NRLOOP1	

ZERO		LDRB	r0,[r3],#1
		MOV	r4,r0
NRLOOP2		LDRB	r0,[r3],#1
		STRB	r0,[r1],#1
		CMP	r0,#0	
		BNE	NRLOOP2

		ADR	r3,DIGIT
		CMP	r12,#&32
		ADREQ	r3,DIGIT_PORKER
		CMP	r12,#&33
		ADREQ	r3,DIGIT_HEX
		ADR	r1,TEMP
		CMP	r11,#0
		BEQ	NRLOOP4

NRLOOP3		LDRB	r0,[r3],#1
		SUB	r11,r11,#1
		CMP	r11,#0
		BGT	NRLOOP3
NRLOOP4		LDRB	r0,[r1],#1
		STRB	r0,[r3],#1
		CMP	r0,#0	
		BNE	NRLOOP4
		SUB	r6,r6,#1	
		B	GCONT2	
DIGIT		=	"0123456789",0
DIGIT_PORKER	=	"A23456789XJQK",0
DIGIT_HEX	=	"0123456789ABCDEF",0
TEMP			=	"xxxxxxxxxxxxxxxx",0
	ALIGN
;
;
;
RESET
		ADR	r1,DIGIT
		CMP	r12,#&32
		ADREQ	r1,DIGIT_PORKER
		CMP	r12,#&33
		ADREQ	r1,DIGIT_HEX
		ADR	r2,DIGITCOPY
RESLOOP		LDRB	r0,[r2],#1
		STRB	r0,[r1],#1
		CMP	r0,#0
		BNE	RESLOOP
		MOV	r11,#0
		B	START
;
;
;
MODE
		ADR	r0,MODEMSG
		SWI	SWI_Write0
MCONT		SWI	SWI_ReadC
		SWI	SWI_WriteC
		CMP	r0,#&31
		BLT	MODEERR
		CMP	r0,#&33
		BGT	MODEERR
		MOV	r12,r0
		ADR	r2,DIGITCOPY
		CMP	r12,#&31
		BEQ	MODENORMAL
		CMP	r12,#&32
		BEQ	MODEPORKER
		CMP	r12,#&33
		BEQ	MODEHEX
		
MLOOP		LDRB	r0,[r1],#1
		STRB	r0,[r2],#1
		CMP	r0,#0
		BNE	MLOOP			
		B	RETURN	
MODEERR
		ADR	r0,MERRMSG
		SWI	SWI_Write0
		B	MCONT
MODENORMAL	
		ADR	r1,DIGIT
		MOV	r6,#10
		B	MLOOP	
MODEPORKER	
		ADR	r1,DIGIT_PORKER
		MOV	r6,#13
		B	MLOOP
MODEHEX	
		ADR	r1,DIGIT_HEX
		MOV	r6,#16
		B	MLOOP			
MODEMSG			=	&0a,&0d,"Please input game mode.",&0a,&0d
MODEMSG1		=	"Input '1' Normal Mode=>guess range 0~9",&0a,&0d
MODEMSG2		=	"Input '2' Porker Mode=>guess range A,2~9,X,J,Q,K",&0a,&0d
MODEMSG3		=	"Input '3' Hex Mode=>guess range 0~9,A~F",&0a,&0d,0
MERRMSG			=	&0a,&0d,"Wrong Mode input. Please input again.",&0a,&0d,0
		ALIGN		
;
;
;
INPUT
		ADR	r1,INTEXT
		ADR	r0,TEXT3
		SWI	SWI_Write0
		MOV	r2,#0
INLOOP		SWI	SWI_ReadC
		SWI	SWI_WriteC
		CMP	r0,#&48
		BEQ	SHOWANS
		CMP	r12,#&32
		BEQ	INPORKER
		CMP	r12,#&33
		BEQ	INHEX
		CMP	r0,#&30
		BLT	ERR
		CMP	r0,#&39
		BGT	ERR
		B	INCHECK
INCONT		STRB	r0,[r1],#1		
		ADD	r2,r2,#1
		CMP	r2,#4
		BEQ	RETURN	
		B	INLOOP
INTEXT		=	"oooo",&0a,&0d,0
		ALIGN
INCHECK
		MOV	r3,#0
		ADR	r4,INTEXT
INCLOOP		CMP	r3,r2
		BGE	INCONT	

		LDRB	r5,[r4],#1
		CMP	r5,r0
		BEQ	ERR
		ADD	r3,r3,#1
		B	INCLOOP

TEXT3	=	"   Guess :  ",0
ERMSG	=	&0a,&0d,"Wrong input. Please input 4 DIFFERENT DIGITS(0~9).",&0a,&0d,0
ERMSGPK	=	&0a,&0d,"Wrong input. Please input 4 DIFFERENT DIGITS(A,2~9,X,J,Q,K).",&0a,&0d,0
ERMSGHEX	=	&0a,&0d,"Wrong input. Please input 4 DIFFERENT DIGITS(0~9,A~F).",&0a,&0d,0
		ALIGN				
ERR
		CMP	r12,#&31
		ADREQ	r0,ERMSG
		CMP	r12,#&32
		ADREQ	r0,ERMSGPK
		CMP	r12,#&33
		ADREQ	r0,ERMSGHEX
		SWI	SWI_Write0
		B	GUESS	
INPORKER	
		CMP	r0,#&32
		BLT	ERR
		CMP	r0,#&39
		BLE	INCHECK
		CMP	r0,#&60
		SUBGT	r0,r0,#&20
		CMP	r0,#&41
		BLT	ERR
		BEQ	INCHECK
		CMP	r0,#&4A
		BLT	ERR
		CMP	r0,#&4B
		BLE	INCHECK
		CMP	r0,#&51
		BEQ	INCHECK
		CMP	r0,#&58
		BEQ	INCHECK
		B	ERR	
INHEX		
		CMP	r0,#&30
		BLT	ERR
		CMP	r0,#&39
		BLE	INCHECK
		CMP	r0,#&60
		SUBGT	r0,r0,#&20
		CMP	r0,#&41
		BLT	ERR
		CMP	r0,#&46
		BGT	ERR
		B	INCHECK		
ROUNDH
	MOV	r2,#8
	MOV	r1,r11
	MOV	r3,#0
LOOP	ADD	r3,r3,#1
	MOV	r0,r1,LSR #28
	CMP	r0,#9
	ADDGT	r0,r0,#"A"-10
	ADDLE	r0,r0,#"0"
	CMP	r3,#6
	SWIGT	SWI_WriteC
	MOV	r1,r1,LSL #4
	SUBS	r2,r2,#1
	BNE	LOOP
	MOV	pc,r14



		END