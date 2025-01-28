num1 = [1 3 5 7 9 11 13];
w = -pi:2*pi/255:pi;
wo = 0.4*pi; % tre tan so
a1 = freqz(num1,1,w);
L=length(num1);
n=0:L-1;
num2=exp(wo*i*n).*num1;
a2= freqz(num2,1,w);
subplot(2,2,1)
plot(w/pi,abs(a1));grid
title('pho bien do day goc');
subplot(2,2,2)
plot(w/pi,abs(a2));grid
title('pho bien do day tre')
subplot(2,2,3)
plot(w/pi,angle(a1));grid
title('pho pha day goc')
subplot(2,2,4)
plot(w/pi,angle(a2));grid
title('pho pha day tre')