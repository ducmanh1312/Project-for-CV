M=input('Nhap so mau can dich=')
x=input('Nhap day tin hieu goc=')
%y=circshift(x,[1,-M]M)
y=circshift(x,[1,-M])
L=length(x)-1;
n=0:L;
subplot(211)
stem(n,x)
%axis{[0,L,min(x),max(x)]};
title('Day tin hieu goc');
ylabel('Bien do');
subplot(212)
stem(n,y)
%axis([0,L,mix(x),max(x)])
title('Day tin hieu thu duoc sau khi dich vong')
ylabel('Bien do')
xlabel('Thoi gian roi rac')