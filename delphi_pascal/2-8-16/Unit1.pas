unit Unit1;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, Math;

type
  TForm1 = class(TForm)
    Edit1: TEdit;
    Edit2: TEdit;
    Edit3: TEdit;
    Edit4: TEdit;
    StaticText1: TStaticText;
    StaticText2: TStaticText;
    StaticText3: TStaticText;
    StaticText4: TStaticText;
    procedure Edit1Change(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  Form1: TForm1;

implementation

{$R *.dfm}
const
Symb:array[0..15] of char='0123456789ABCDEF';

function StrToIntM(s:string;M:word):int64;
var
i:integer;
begin
s:='0'+Trim(s);
Result:=0;i:=1;
while (i <= Length(s)) and (s[i] in [Symb[0]..Symb[M-1]]) do inc(i);
if i > Length(s) then
    for i:=1 to length(s) do
        case s[i] of
        '0'..'9':Result:=Result*M + ord(s[i])-48;
        'A'..'F':Result:=Result*M + ord(s[i])-55;
        'a'..'f':Result:=Result*M + ord(s[i])-87;
        end    //case
else
Result:=-1;
end;

function IntToStrM(x:int64;M:word):string;
begin
Result:='';
    repeat
    Result:=Symb[x-M*(x div M)]+Result;
    x:=x div M;
    until x <= 0 ;
end;



procedure TForm1.Edit1Change(Sender: TObject);
var
x:int64;
begin
if Edit1.Focused then x:=StrToIntM(Edit1.Text,2)
else
    if Edit2.Focused then x:=StrToIntM(Edit2.Text,8)
    else
        if Edit3.Focused then x:=StrToIntM(Edit3.Text,10)
        else
            if Edit4.Focused then x:=StrToIntM(Edit4.Text,16);

if x < 0 then Beep;
if not Edit1.Focused then
    if x >= 0 then Edit1.Text:=IntToStrM(x,2)
    else Edit1.Text:='';
if not Edit2.Focused then
    if x >= 0 then Edit2.Text:=IntToStrM(x,8)
    else Edit2.Text:='';
if not Edit3.Focused then
    if x>= 0 then Edit3.Text:=IntToStrM(x,10)
    else Edit3.Text:='';
if not Edit4.Focused then
    if x>=0 then Edit4.Text:=IntToStrM(x,16)
    else Edit4.Text:='';
end;




end.
