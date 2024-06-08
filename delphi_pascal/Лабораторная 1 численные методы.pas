program metod_polovinnogo_deleniya;
function f(x:real):real;
begin
  f:=power(2,(-x))+sqr(x)/2-10;
end;
var a,b,eps,x:real; 
begin
  writeln('Введите интервал [a;b] для поиска корня');
  read(a,b);
  writeln('Введите точность корня');
  read(eps);
  if((f(a)*f(b))<0) then
   begin
    while(abs(b-a)>2*eps) do 
  begin
    x:=(b+a)/2;
    if(f(x)*f(a)<0) then b:=x
    else a:=x; 
  end;
  x:=(b+a)/2;
  writeln('Корень уравнения=',x, ' Значение функции в этой точке=',f(x));
  end
  else writeln('На интервале нет корня введите другой');
  

end.