vivod macro str
 mov ah,09h
 lea dx,str
 int 21h
 pop dx
endm
 
.model small
.stack 100h
.data
mesg db "sravnivaem takie stroki:$" 
str1 db "kuku$"
str2 db "kuki$"
str db "simvol$"
str_ravno db "stroki ravnue$"
.code
assume ds:@data,es:@data
main:
 mov ax,03;ochistka ekrana
 int 10h
 
 mov ax,@data
 mov ds,ax
 mov es,ax
 
   vivod mesg
   mov dl,10
   mov ah,2
   int 21h
 
   vivod str1
   
   mov dl,10
   mov ah,2
   int 21h
   
   vivod str2
   mov dl,10
   mov ah,2
   int 21h
 
 cld
 lea si,str1
 lea di,str2
 mov cx,4
 mov ax,1
srav:
 cmpsb
 je neravno
 cmp ax,4
  je vivod_sim
   jmp konkat
  vivod_sim:
   jmp vivsim   
 neravno:
  cmp ax,4
  je da
   inc ax
  jmp end_ 
  da:
   vivod str_ravno
 end_:  
 loop srav 
 
konkat: 
 lea di,str1
 add di,4
 lea si,str2
 mov cx,5
 rep movsb
 vivod str1
 jmp exit
 
vivsim:
 cld
 lea si,str1-строка,где есть нужный символ
 mov bx,ax-сохран€ю позицию(нашла ее при сравнении 2х строк,первыйе неравные символы)
 mov ax,0B800h-сегментный адрес видеобуфера
 mov es,ax-адрессую через es
 
 mov ah,31h-јтрибут символов-синий по голубому(вз€ла из примера)
 lods si[bx]-это попытка вз€ть в строке si символ в позиции bx
 
exit:  
 mov ah,01;ogidanie nagatiya klavishi
 int 21h
 
 mov ax,4c00h;vihod
 int 21h
end main