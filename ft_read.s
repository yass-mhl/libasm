section .text
    global _ft_read
    extern __errno_location

_ft_read:
    mov rax, 0          ; Syscall number pour read
    syscall             ; Effectue l'appel système
    cmp rax, 0          ; Vérifier si l'appel système a retourné une erreur (rax < 0)
    jge .success        ; Si rax est positif ou zéro, l'appel a réussi

    ; Gérer l'erreur
    neg rax             ; Convertit rax en une valeur positive, qui est le code d'erreur
    mov rdi, rax        ; Sauvegarde le code d'erreur dans rdi pour utilisation après __errno_location
    call __errno_location ; Appelle __errno_location pour obtenir l'adresse de errno
    mov [rax], edi      ; Stocke le code d'erreur dans errno
    mov rax, -1         ; Prépare -1 pour le retour afin de signaler une erreur
    ret

.success:
    ret
