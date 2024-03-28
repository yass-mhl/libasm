section .text
    global _ft_strcmp
    extern __errno_location  ; Importe la fonction pour obtenir l'adresse de errno

_ft_strcmp:
    ; Vérifier si l'une des chaînes est NULL
    test rdi, rdi
    jnz .not_first_null
    test rsi, rsi
    jnz .one_null

    ; Si les deux chaînes sont NULL, elles sont considérées comme égales
    xor eax, eax
    ret

.not_first_null:
    test rsi, rsi
    jnz .compare_loop

.one_null:
    ; Une chaîne est NULL, définir errno à EINVAL
    call __errno_location
    mov dword [rax], 22 ; 22 est souvent le numéro pour EINVAL
    ; Retourner une valeur spéciale, ici -1, pour indiquer l'erreur
    mov eax, -1
    ret

    ; Début de la comparaison des chaînes si aucune n'est NULL
.compare_loop:
    mov al, [rdi] ; Charge le caractère courant de la première chaîne dans AL
    mov bl, [rsi] ; Charge le caractère courant de la deuxième chaîne dans BL
    
    cmp al, bl ; Compare les deux caractères
    jne .difference_found ; Sauter jusqu'à difference_found si différence trouvée
    
    test al, al ; Vérifier si la fin de la chaîne est atteinte (caractère nul)
    jz .strings_equal ; Si oui, les chaînes sont égales
    
    inc rdi ; Passe au caractère suivant dans la première chaîne
    inc rsi ; Passe au caractère suivant dans la deuxième chaîne
    jmp .compare_loop ; Répéter la boucle

.difference_found:
    sub al, bl ; Soustrait BL de AL et stocke le résultat dans AL
    movsx rax, al ; Étend le résultat à 64 bits pour le retour
    ret ; Retourne avec la différence comme résultat

.strings_equal:
    xor eax, eax ; Met à 0 EAX pour indiquer l'égalité
    ret ; Retourne avec 0 comme résultat

.check_second_string:
    ; Si la première chaîne est NULL, vérifier si la seconde l'est aussi
    test rsi, rsi
    jz .strings_equal ; Si les deux sont NULL, elles sont considérées égales
    ; Sinon, considérer la chaîne NULL comme inférieure
    mov eax, -1
    ret

.first_not_null_second_null:
    ; Si la seconde chaîne est NULL mais pas la première, considérer la seconde comme inférieure
    mov eax, 1
    ret
