% chuong trinh giai phuong trinh bac 2
% ax^2+bx+c=0
a=input('Nhap he so a:');
b=input('Nhap he so b:');
c=input('Nhap he so c:');
delta = b^2-4*a*c;
if delta > 0
x1= (-b -sqrt(delta))/(2*a);
x2= (-b + sqrt(delta))/(2*a);
disp(['Nghiem cua phuong trinh la x1=' num2str(x1)]);
disp(['Nghiem cua phuong trinh la x2=' num2str(x2)]);
end
if delta == 0
    x=-b/(2*a);
    disp(['Phuong trinh co nghiem kep x=' num2str(x)])
end
if delta<0
    disp('Phuong trinh vo nghiem')
end