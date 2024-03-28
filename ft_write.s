section .text
    global _ft_write
    extern __errno_location

_ft_write:
    mov rax, 1          ; sys_write syscall number
    syscall             ; Effectue l'appel système
    cmp rax, 0          ; Vérifier si l'appel système a retourné une erreur (rax < 0)
    jge .success        ; Si rax est positif ou zéro, l'appel a réussi

    ; Si nous sommes ici, rax est négatif, indiquant une erreur
    neg rax             ; Convertit rax en une valeur positive, qui est le code d'erreur
    mov rdi, rax        ; Sauvegarde le code d'erreur dans rdi pour utilisation après __errno_location
    call __errno_location ; Appelle __errno_location pour obtenir l'adresse de errno
    mov [rax], edi      ; Stocke le code d'erreur dans errno
    mov rax, -1         ; Retourne -1 pour signaler une erreur
    ret

.success:
    ret
