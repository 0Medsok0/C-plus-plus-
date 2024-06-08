program sistema_yravneniy_metod_iteraciy;
const alpha=0.4;
var A: array of array of real; x,xn,b:array of real; n,i,j:integer;  max,eps:real;
begin
  writeln('Введите порядок системы');
  read(n);
  writeln('Введите точность вычислений');
  read(eps);
  setlength(A,n);
  setlength(b,n);
  setlength(x,n);
  setlength(xn,n);
  for i:=0 to n-1 do
    setLength(A[i],n);
  writeln('Введите преображенную матрицу системы');
  for i:=0 to (n-1) do
    for j:=0 to (n-1) do
      read(A[i][j]);
    writeln('Введите преображенный столбец свободных членов');
    read(b[i]);
    for i:=0 to n-1 do
      x[i]:=b[i];
    for i:=0 to n-1 do
      begin
      xn[i]:=b[i];
    for j:=0 to n-1 do
      xn[i]:=xn[i]+A[i][j]*x[j];
    end;
    max:=0;
    for i:=0 to n-1 do
      if(abs(xn[i]-x[i])>max) then max:=abs(xn[i]-x[i]);
    while((alpha/(1-alpha))*max>eps) do
      begin
      for i:=0 to n-1 do
        x[i]:=xn[i];
      for i:=0 to n-1 do
      begin
        xn[i]:=b[i];
        for j:=0 to n-1 do
          xn[i]:=xn[i]+A[i][j]*x[j];
      end;
      max:=0;
      for i:=0 to n-1 do
      if((abs(x[i]-xn[i]))>max)then max:=abs(x[i]-xn[i]);
      end;
      writeln('Решение системы');
      for i:=0 to n-1 do
        writeln('x[',i+1,']=',xn[i]);
      
      
      
      
end.