uses    tpcrt,hex;

const
TM      : string ='BIOS';

type
BufType         = array[0..$3F] of byte;

var
addr,d          : byte;
ff              : file;
Buf,buf1        : buftype;
str             : string;

function inCMOS(addr:byte):byte;
begin
  port[$70]:=addr;
  delay(1);
  inCMOS:=port[$71];
end;

procedure outCMOS(addr,bt:byte);
begin
  port[$70]:=addr;
  delay(1);
  port[$71]:=bt;
end;

procedure ReadCmosBuf(var buf:buftype);
var
 i      : byte;
begin
  for i:=0 to $3F do buf[i]:=InCmos(i);
end;

procedure Display(var buf,buf1:buftype);
var
i,j     : byte;
bt      : byte;
begin
  for j:=0 to 3 do
    begin
      textcolor(7);
      write(hexbyte(j*16),' ');
      for i:=0 to 15 do
        begin
          textcolor(7);
          if i and 3 = 0 then write('³ ');
          bt:=buf[j*16+i];
          if bt<>buf1[j*16+i] then textcolor(14);
          write(hexbyte(bt),' ');
        end;
      write('³  ');
      for i:=0 to 15 do
        begin
          bt:=buf[j*16+i];
          if bt<>buf1[j*16+i] then textcolor(14) else textcolor(7);
          if bt>=32 then write(chr(bt)) else write('ú');
        end;
      writeln;
    end;
end;

procedure ViewCmos;
begin
  clrscr;
  repeat
    gotoxy(1,1);
    ReadCmosBuf(Buf);
    Display(Buf,Buf1);
    move(buf,buf1,sizeof(buf));
  until keypressed;
end;

procedure WriteBuf(var buf:buftype);
begin
  write('(Write) Filename: ');Readln(str);
  Assign(ff,str);
  Rewrite(ff,1);
  BlockWrite(ff,Buf,SizeOf(Buf));
  Close(ff);
  gotoxy(1,1);
  Display(buf,buf);
end;

procedure ReadBuf(var buf:buftype);
begin
  write('(Read) Filename: ');Readln(str);
  Assign(ff,str);
  Reset(ff,1);
  BlockRead(ff,Buf,SizeOf(Buf));
  Close(ff);
  gotoxy(1,1);
  Display(buf,buf);
end;

procedure Compare;
begin
  writeln('(Compare)');
  ReadBuf(buf1);
  gotoxy(1,1);
  Display(buf,buf1);
  writeln;
  Display(buf1,buf);
  readln;
end;

procedure CompareCmos;
begin
  writeln('(Compare Cmos)');
  ReadCmosBuf(buf1);
  gotoxy(1,1);
  Display(buf,buf1);
  writeln;
  Display(buf1,buf);
  readln;
end;

procedure GetCmos;
begin
  ReadCmosBuf(buf);
  gotoxy(1,1);
  Display(buf,buf);
end;

procedure putbyte;
var ad,bt: byte;
begin
  clrscr;
  GetCmos;
  writeln(#10#10'(Put byte)');
  write('Enter address : ');
  ad:=InHexByte;
  move(buf,buf1,sizeof(buf));
  buf1[ad]:=not buf[ad];
  writeln;
  display(buf,buf1);
  writeln;
  textcolor(14);
  write('Addr: ',hexbyte(ad),'  Enter new byte : ');
  bt:=InHexByte;
  outcmos(ad,bt);
  GetCmos;
end;

procedure putString;
var ad,i : byte;
begin
  clrscr;
  GetCmos;
  writeln(#10#10'(Put string)');
  write('Enter address : ');
  ad:=InHexByte;
  move(buf,buf1,sizeof(buf));
  buf1[ad]:=not buf[ad];
  writeln;
  display(buf,buf1);
  writeln;
  textcolor(14);
  write('Addr: ',hexbyte(ad),'  Enter string : ');
  readln(str);
  for i:=1 to length(str) do outcmos(ad+i-1,ord(str[i]));
  GetCmos;
end;

var
ch      : char;

begin
  TextAttr:=15; ClrScr; Write(TM); Delay(1000);
  HexBegin:='';
  ReadCmosBuf(buf);
  clrscr;
  Display(buf,buf);
  Repeat
    textcolor(3);
    window(1,6,80,25); clrscr; window(1,1,80,25);
    gotoxy(1,6);
    writeln('Files: (R)ead, (W)rite, (F)ile Compare,(C)mos Compare');
    writeln('Cmos:  (V)iew, (G)et;   Put: (B)yte, (S)tring');
    writeln;
    ch:=readkey;
    case ch of
     'r','R'    : ReadBuf(buf);
     'w','W'    : WriteBuf(buf);
     'f','F'    : Compare;
     'c','C'    : CompareCmos;
     'g','G'    : GetCmos;
     'v','V'    : ViewCmos;
     'b','B'    : putByte;
     's','S'    : putString;
    end;
  until ch=#27;
end.
