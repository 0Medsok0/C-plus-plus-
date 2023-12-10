program problem;
{$APPTYPE CONSOLE}
uses
  SysUtils;
var
  sDv: string;
  iMod, iDch, iDchr :integer;

begin
  Write('Decatichnoe chislo: ');
  Readln(iDch);
  iDchr := iDch;
  while iDch >= 2 do
    begin
      iMod := iDch mod 2;
      iDch := iDch div 2;
      sDv := IntToStr(iMod) + sDv;
    end;
  sDv := IntToStr(iDch) + sDv;
  Writeln(iDchr, '(10) = ', sDv, '(2)');
  Readln;
end.
