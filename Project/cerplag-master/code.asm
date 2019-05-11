    global main
section .bss
data:
    resb 8

section .text
main:
    mov rbx, data
    xor rsi, rsi
    xor rdi, rdi
    lea rcx, [rbx + 0]
    mov rdx, 1
    call read_integer_array
    lea rcx, [rbx + 2]
    mov rdx, 1
    call read_integer_array
    mov ax, [rbx + 0]
    add ax, [rbx + 2]
    mov [rbx + 4], ax
    mov cx, [rbx + 4]
    call print_integer
    mov rax, 0
    ret

section .bss
temp_integer:
    resb 8
section .data
integer_format:
    db "%hd", 0
float_format:
    db "%f", 0
string_format:
    db "%s", 0
string_false:
    db "0", 0
string_true:
    db "1", 0
integer_format2:
    db "%hd", 10, 0
float_format2:
    db "%f", 10, 0
string_format2:
    db "%s", 10, 0
string_false2:
    db "0", 10, 0
string_true2:
    db "1", 10, 0

section .text
extern printf
print_integer:
    ; value in cx
    push rbx
    push rbx ; push twice to match 16-byte alignment requirement
    mov rdi, integer_format2
    mov si, cx
    xor rax, rax
    call printf
    pop rbx
    pop rbx
    xor rsi, rsi
    xor rdi, rdi
    ret

section .text
extern scanf
read_integer_array:
    ; base addr in rcx, size in rdx
    push rbx
    push rbx ; push twice to match 16-byte alignment requirement
read_integer_beg:
    mov rdi, integer_format
    mov rsi, rcx
    xor rax, rax
    push rcx
    push rdx
    call scanf
    pop rdx
    pop rcx
    add rcx, 2
    dec rdx
    cmp rdx, 0
    jnz read_integer_beg
    pop rbx
    pop rbx
    xor rsi, rsi
    xor rdi, rdi
    ret
