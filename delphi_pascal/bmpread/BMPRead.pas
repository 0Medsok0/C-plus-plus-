ype
 BITMAPFILEHEADER = packed record
  bfType:WORD; //Сигнатура BM
  bfSize:DWORD; //Размер файла
  bfReserved1:WORD; //Зарезервировано, всегда 0
  bfReserved2:WORD; //Тот же случай
  bfOffBits:DWORD; //Смещение(в байтах) от заголовка(его размер)
 end;
 BITMAPINFOHEADER = packed record
  biSize:DWORD; //Число байтов, необходимых этой структуре
  biWidth:LONGWORD; //Ширина
  biHeight:LONGWORD; //Высота
  biPlanes:WORD; //Число плоскостей устройства. =1
  biBitCount:WORD; //Число битов на пиксел. В примере =24
  biCompression:DWORD; //Тип сжатия. В примере =0(т.е. нет)
  biSizeImage:DWORD; //Размер изобр. 0, если нет сжатия
  biXPelsPerMeter:LONGWORD; //Горизонтальное разрешение (пиксел/м)
  biYPelsPerMeter:LONGWORD; //Вертикальное разрешение (пиксел/м)
  biClrUsed:DWORD; //Используемые цвета. 0 - исп. все
  biClrImportant:DWORD; //Важные цвета. 0 - все важны
 end;

implementation
{$R *.dfm}
procedure FileToBMP(FileName:String;w,h:Integer);
var
bmp,aFile:TStream;
begin
 bmp:=TFileStream.Create(FileName+'.bmp',fmCreate);
 aFile:=TFileStream.Create(FileName,fmOpenRead);
 bf.bfType:=$4D42; //= BM
 bf.bfReserved1:=0;
 bf.bfReserved2:=0;
 bf.bfOffBits:=SizeOf(BITMAPFILEHEADER)+SizeOf(BITMAPINFOHEADER);
 bi.biSize:=SizeOf(BITMAPINFOHEADER);
 bi.biWidth:=w;
 bi.biHeight:=h;
 bi.biPlanes:=1;
 bi.biBitCount:=24;
 bi.biCompression:=0;
 bi.biSizeImage:=w*h*3;//24бита = 3байта
 //остальное в этом примере = 0
 bi.biXPelsPerMeter:=0;
 bi.biYPelsPerMeter:=0;
 bi.biClrUsed:=0;
 bi.biClrImportant:=0;
 bf.bfSize:=bf.bfOffBits+bi.biSizeImage;
 //запись заголовка
 bmp.Write(bf,SizeOf(BITMAPFILEHEADER));
 bmp.Write(bi,SizeOf(BITMAPINFOHEADER));
 //запись точек(кол-во байтов = bi.biSizeImage)
 bmp.CopyFrom(aFile,bi.biSizeImage);
 bmp.Free;
 aFile.Free;
end;