bits 16

mov bx, 3482h
mov si, bx
mov di, si
mov sp, di
mov bp, sp
mov ax, bp

; ax ax C0
; ax cx C8
; ax dx D0
; ax bx D8
; ax sp E0
; ax bp E8
; ax si F0
; ax di F8

; cx ax C1
; cx cx C9
; cx dx D1
; cx bx D9
; cx sp E1
; cx bp E9
; cx si F1
; cx di F9

; sp ax C4
; sp cx CC
; sp dx D4
; sp bx DC
; sp sp E4
; sp bp EC
; sp si F4
; sp di FC


; dest
; a  = 0 . 8
; c  = 1 . 9
; d  = 2 . A
; b  = 3 . B
; sp = 4 . C
; bp = 5 . D
; si = 6 . E
; di = 7 . F
