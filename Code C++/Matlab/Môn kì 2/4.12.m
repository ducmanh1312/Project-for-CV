x = input('Nhap tin hieu goc = ');
M=input('Nhap so mau can dich vong = ');
N = length(x)-1; n = 0:N;
%y = circshift1(x,5);
y = circshift(x,[1,-M]);
XF = fft(x);
YF = fft(y);
subplot(2,2,1)
stem(n,abs(XF)); grid
title('Magnitude of DFT of Original Sequence');
subplot(2,2,2)
stem(n,abs(YF)); grid
title('Magnitude of DFT of Circularly Shifted Sequence');
subplot(2,2,3)
stem(n,angle(XF)); grid
title('Phase of DFT of Original Sequence');
subplot(2,2,4)
stem(n,angle(YF)); grid
title('Phase of DFT of Circularly Shifted Sequence');