section .text
    global _ft_strlen
    extern __errno_location ; Pour obtenir l'adresse de errno

_ft_strlen:
    test rdi, rdi
    jnz .loop ; Si rdi n'est pas NULL, continue la fonction

    ; Si rdi est NULL, définit errno à EINVAL et retourne une valeur spéciale
    call __errno_location
    mov dword [rax], 22 ; EINVAL est souvent 22, mais cela peut varier
    xor rax, rax ; Retourne 0, ou une autre valeur spéciale pour indiquer l'erreur
    ret

.loop:
    xor rax, rax

.compare_loop:
    cmp byte [rdi + rax], 0
    je .done
    inc rax
    jmp .compare_loop

.done:
    ret
