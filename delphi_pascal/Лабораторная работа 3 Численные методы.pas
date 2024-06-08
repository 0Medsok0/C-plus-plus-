program metod_nutona;
const min=3.957;
function f(x:real):real;
begin
  f:=power(2,(-x))+sqr(x)/2-10;
end;
function fpr(x:real):real;
begin
  fpr:=Ln(x)*power(2,(-x))+x;
end;
function fpr2(x:real):real;
begin
  fpr2:=power(Ln(x),2)*power(2,(-x))+1
end;
var x,eps:real;
begin
  writeln('Введите начальное приближение');
  read(x);
  writeln('Введите точность вычислений');
  read(eps);
  if(f(x)*fpr2(x)>0) 
  then 
    begin
      
      while(f(x)/min>eps) do
        x:=x-f(x)/fpr(x);
    
    writeln('Корень уравнения=',x,' Значение функции в точке=',f(x));
    end
   else writeln ('Приближение не подходит введите другое');  
  
    
end.