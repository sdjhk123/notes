mov ax,bx
; 将bx的内容送到ax中 
; mov ax,bx ax = bx
add ax,bx
; 将ax和bx中的数值相加,结果存在ax中
; add ax,bx ax = ax + bx(ax += bx)

jmp 2AE3:3
; CS=2AE3H IP=0003H CPU将从2AE3H*16+0003H=2AE33H处读取指令

jmp ax
; mov IP,ax