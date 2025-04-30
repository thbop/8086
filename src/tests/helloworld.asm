bits 16

; mov bx, 0x7F02
; add cl, bl
; add cl, bh

; mov ax, cx

mov bx, 0x7FFF
mov ax, 1
add ax, bx

hlt


