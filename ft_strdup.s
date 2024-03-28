section .text
    global _ft_strdup
    extern malloc
    extern __errno_location  ; Obtient l'adresse de errno

_ft_strdup:
    ; Vérifier si la chaîne source est NULL
    cmp rdi, 0
    je .error                ; Si la chaîne source est NULL, saute à l'erreur

    push rdi                ; Sauvegarder rdi (adresse de la chaîne source) sur la pile

    ; Calculer la longueur de la chaîne source
    xor rcx, rcx            ; rcx est utilisé pour compter la longueur
.calculate_length:
    cmp byte [rdi + rcx], 0 ; Compare le caractère actuel à 0 (fin de chaîne)
    je .length_found         ; Si trouvé, saute à length_found
    inc rcx                 ; Sinon, incrémente le compteur et continue
    jmp .calculate_length

.length_found:
    inc rcx                 ; Incrémente la longueur pour inclure le caractère nul

    ; Allouer de la mémoire pour la nouvelle chaîne
    mov rdi, rcx            ; Met la longueur calculée dans rdi pour malloc
    call malloc             ; Appelle malloc
    cmp rax, 0
    je .error_after_malloc   ; Si malloc échoue (retourne NULL), gère l'erreur

    pop rsi                 ; Restaurer rsi (adresse de la chaîne source) depuis la pile
    mov rdi, rax            ; rdi est maintenant l'adresse de la mémoire allouée
    xor rcx, rcx            ; Réinitialise le compteur pour la copie

.copy_loop:
    mov dl, [rsi + rcx]     ; Charge le caractère de la source
    mov [rdi + rcx], dl     ; Écrit le caractère dans la destination
    inc rcx                 ; Incrémente le compteur
    test dl, dl             ; Vérifie si le caractère est le nul
    jnz .copy_loop           ; Si non, continue la boucle

    jmp .finish              ; Saute à la fin de la fonction

.error_after_malloc:
    ; malloc définit errno pour nous en cas d'échec
    pop rdi                 ; Restaure rdi si malloc échoue
    jmp .finish

.error:
    call __errno_location   ; Appelle __errno_location pour obtenir l'adresse de errno
    mov dword [rax], 22     ; Définit errno à EINVAL (22)
    xor rax, rax            ; Met 0 dans rax pour signaler une erreur

.finish:
    ret                     ; Retourne avec le résultat dans rax
