.model small
.data
    input01 db "Read A = $"
    input02 db "Read B = $"
    final db "A + B = $"

    num01 db 3 dup('$') 
    num02 db 3 dup('$')
.code

print macro text
    lea dx, text
    mov ah, 09h
    int 21h
endm

read macro addr
    mov ah, 01h
    int 21h
    mov addr[1], al

    mov ah, 01h
    int 21h
    mov addr[0], al
endm

print_newline macro
    mov dl, 10
    mov ah, 02h
    int 21h
endm

main:
    mov ax, @data
    mov ds, ax

    mov cx, 0

    print input01
    read num01
    print_newline

    print input02
    read num02 
    print_newline

    mov bx, [num02]
    mov ax, [num01]

    add bx,ax
    jnc finish 
    inc cx

finish:
    print final
    sub bx, 48

    mov dx, bx
    mov ah, 02h
    int 21h

    mov ah, 4ch
    int 21h

end main
