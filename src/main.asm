[org 0x7C00]       ; BIOS loads the bootloader at memory address 0x7C00
[bits 16]          ; 16-bit real mode


jmp short start
nop

; bpb

oem db 'AW_SS_OS'
bytes_per_sector dw 0x200
secotrs_per_cluster db 1
reserved_sectors dw 1
FATs_count db 2
root_dir_entries dw 0xe0
total_sectors dw 0xb40
media_descriptor db 0xF0
sectors_per_FAT dw 9
sectors_per_track dw 0X12
heads_count dw 2
hidden_sectors_count dd 0
large_sectors_count dd 0

; ebr
drive_number db 0
flags_reserved db 0
signature db 0x29
volume_id dd 0xBDE952E3
volume_lable db 'AW_SS_OS   '
system_identifier db 'AW_SS_OS'




start:
    ; Set up video mode: 0x03 is 80x25 text mode
    mov ah, 0x00      ; Function to set video mode
    mov al, 0x03      ; 80x25 color text mode
    int 0x10          ; BIOS interrupt to change video mode

    ; Display "Hello, World!" at the top-left of the screen
    mov si, hello_msg ; Point SI to the "Hello, World!" string

print_char:
    lodsb             ; Load next byte (character) from [SI] into AL
    or al, al         ; Check if it's the null terminator (0x00)
    jz done           ; If it's 0, we're done printing
    mov ah, 0x0E      ; BIOS teletype function (prints char to screen)
    int 0x10          ; Call BIOS interrupt to print the character
    jmp print_char    ; Repeat for the next character

done:
    ; Infinite loop to stop the bootloader from halting
    jmp $

hello_msg db 'Hello, World!', 0 ; Null-terminated string

times 510 - ($ - $$) db 0 ; Fill the rest of the sector with zeroes
dw 0xAA55                 ; Bootloader signature (required for boot sector)
