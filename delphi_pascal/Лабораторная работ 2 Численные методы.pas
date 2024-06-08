program metod_iteraciy;
const tay=-0.20087;
      psi=0.205221;
function fi(x:real):real;
begin
  fi:=x+tay*(power(2,(-x))+sqr(x)/2-10);
end;
function f(x:real):real;
begin
  f:=power(2,(-x))+sqr(x)/2-10
end;
var x,xn, eps:real;
begin
  writeln('Введите начальное приближение');
  read(x);
  writeln('Введите точность корня');
  read(eps);
  xn:=fi(x);
  while((psi*abs(x-xn)/(1-psi))>eps)do
  begin
    x:=xn;
    xn:=fi(x);
  end;
  writeln('Решение уравнения=', xn, ' значение функции=',f(xn) );
  
  
end.           