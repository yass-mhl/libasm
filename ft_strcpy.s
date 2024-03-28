section .text
    global _ft_strcpy
    extern __errno_location

_ft_strcpy:
    test rsi, rsi ; Teste si src (RSI) est NULL
    jnz .start_copy ; Si non NULL, commence la copie
    ; Si src est NULL, définit errno à EINVAL et sort
    call __errno_location ; Obtient l'adresse de errno
    mov dword [rax], 22 ; 22 est le code pour EINVAL
    ; Optionnellement, initialise le tampon de destination à une chaîne vide
    mov byte [rdi], 0 ; Assurez-vous que la destination est une chaîne vide
    xor rax, rax ; Retourne NULL (ou 0) pour signaler l'erreur
    ret

.start_copy:
    mov rax, rdi ; Initialise la valeur de retour à dest

.copy:
    mov al, [rsi] ; Copie le caractère de src à dest
    mov [rdi], al
    inc rsi ; Incrémente le pointeur source
    inc rdi ; Incrémente le pointeur destination
    test al, al ; Teste si le caractère est le caractère nul
    jnz .copy ; Si non, continue la copie
    ret
