SECTION .bss
	lpBuffer: resb 18
	Buf_Len: equ $-lpBuffer
lft: RESW 8
FOR_CTRL: RESW 8
OUT: RESW 10
temp: RESW 1
rgt: RESW 1
u2_cb: RESB 1
v2_cb: RESB 1
w2_cb: RESB 1
x2_cb: RESB 1
y2_cb: RESB 1
z2_cb: RESB 1
a2_cb: RESW 1
b2_cb: RESW 3
c2_cb: RESW 3
d2_cb: RESW 3
e2_cb: RESW 1
f2_cb: RESW 5
res2_cb: RESW 1
SECTION .text
global _start

_start:
MOV AX, 4
MOV [res2_cb], AX
MOV AX, 4
MOV [c2_cb], AX
MOV AX, [a2_cb]
MOV [lft+0],AX
MOV AX, 4
MOV [rgt], AX
MOV AX,[lft+0]
ADD AX,[rgt]
MOV [d2_cb], AX
MOV AX, [d2_cb]
MOV [res2_cb], AX
call exit

printStr:
    push    eax
    push    ebx
    mov     ebx, 1
    mov     eax, 4
    int     80H
    pop     ebx
    pop     eax
    ret
     
readStr:
    push    ebx
    mov     ebx, 0
    mov     eax, 3
    int     80H
    pop     ebx
    ret

printInt:
    push eax
    push ebx
    push ecx
    push edx
    push esi
    movsx eax,ax
    mov esi, lpBuffer
    add esi, Buf_Len
    mov ecx,10
    mov edx, eax 
    cmp eax,0
    jge .non_neg
    mov eax,0
    sub eax,edx
    push '-'
    mov ecx,esp
    mov edx,1
    call printStr
    add esp, 4
    mov ecx,10

.non_neg:
    mov edx,0
    idiv ecx
    add dl,0x30
    mov [esi],dl
    dec esi
    cmp eax,0
    jnz .non_neg

    mov edx, lpBuffer
    add edx, Buf_Len
    mov ecx,esi
    sub edx,ecx
    inc ecx
    call printStr
    push 10
    mov ecx,esp
    mov edx,1
    call printStr
    add esp, 4
    pop esi
    pop edx
    pop ecx
    pop ebx
    pop eax
    ret

readInt:
    push ecx
    push edx
    push esi
    mov     ecx, lpBuffer
    mov     edx, Buf_Len
    call    readStr
    mov     esi,eax
    mov     byte [lpBuffer+esi], 0
    mov     eax, lpBuffer
    call    atoi
    pop     esi
    pop     edx
    pop     ecx
    ret

atoi:
    push    ebx
    push    ecx
    push    edx
    push    esi
    mov     esi, eax        
    mov     eax, 0          
    mov     ecx, 0          
    
    mov     bl, [esi+ecx]   
    cmp     bl,'-'          
    jne     .multiplyLoop
    inc     ecx

.multiplyLoop:
    mov     ebx, 10         
    mul     ebx             
    mov     bl, [esi+ecx]   
    cmp     bl, 48          
    jl      .finished       
    cmp     bl, 57          
    jg      .finished       
 
    sub     bl, 48          
    add     eax, ebx        
    inc     ecx             
    jmp     .multiplyLoop   

.finished:
    mov     ebx,10
    div     ebx
    mov     bl, [esi]
    cmp     bl,'-'
    jne     .fin2
    mov     ebx,eax
    mov     eax,0
    sub     eax,ebx
    
.fin2:
    pop     esi             
    pop     edx
    pop     ecx             
    pop     ebx             
    ret
    
exit: 
    mov     eax,1
    xor     ebx,ebx
    int     80H

