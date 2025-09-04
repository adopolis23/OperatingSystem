global outb
global inb

; outb - send a byte to an I/O port
; stack: [esp + 8] the data byte
;        [esp + 4] the I/O port
;        [esp ] return address

; first thing pushed onto stack is data byte last thing is return address right before the call.

outb:
    mov al, [esp + 8] ; move data into al
    mov dx, [esp + 4] ; move io port addr into dx
    out dx, al        ; send data to IO port
    ret               ; return to address at [esp]