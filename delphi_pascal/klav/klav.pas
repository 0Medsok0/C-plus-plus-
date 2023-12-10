Program TestScancode;
Uses Dos,CRT;{CRT здесь существеннен - не следует пользоваться функциями dos
              из обработчика клавиатурного прерывания}
var OldKbdHandler:Pointer;
Procedure Int9;interrupt;
var Scancode:Byte;
begin
 ScanCode:=Port[$60];
 Write(ScanCode:4);
 asm
  Pushf
  Call DWORD PTR OldKbdHandler;
 end;
end;
begin
 GetIntVec($9,OldKbdHandler);
 SetIntVec($9,@Int9);
 Repeat
 Until Readkey=#27;
 SetIntVec($9,OldKbdHandler);
end;
