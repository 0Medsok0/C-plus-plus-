begin
  asm
{сохраняем ссегментный регистр и ставим режим}
      push es
      mov  ax,13h
      int  10h
{будем писать прямо в видео-буфер}
      mov  ax,0a000h
      mov  es,ax
      cld
{пропускаем нулевую строку}
      mov  di,320
      mov  bx,0ffffh
      mov  cx,8
{количество строк по 16-ть пикселей по вертикали}
 001: push cx
      mov  cx,16
{количество пикселей в одной строке по вертикали}
 002: push cx
      mov  cx,8
{количество клеток в одной строке}
 003: mov  dx,bx
      push cx
      mov  cx,16
{количество пикселей в одной клетке, по горизонтали}
 004: xor  ax,ax
      shr  dx,1
      jc   @005
      add  al,100
 005: stosb
      loop @004
{меняем цвет}
      xor  bx,0ffffh
      pop  cx
      loop @003
{корректируем на начало экрана}
      add  di,192
      pop  cx
      loop @002
{меняем цвет повторно}
      xor  bx,0ffffh
      pop  cx
      loop @001
      pop  es
{нажмите любую клавишу}
      xor  ax,ax
      int 16h
  end;
end.