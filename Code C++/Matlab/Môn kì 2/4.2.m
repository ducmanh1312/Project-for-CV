h = [1 2 3 4 5 6 7 8];
D = 10;
w = -pi:2*pi/255:pi;
k1 = freqz(h,1,w);
k2 = freqz([zeros(1,10) h],1,w);

subplot(221);
plot(w/pi,abs(k1));grid;
title('pho bien do day goc');
subplot(222);
plot(w/pi,abs(k2));grid;
title('pho bien do day tre');
subplot(223);
plot(w/pi,angle(k1));
title('pho pha day goc'); 
subplot(224);
plot(w/pi,angle(k2));grid;
title('pho pha day tre');