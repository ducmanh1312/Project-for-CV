w = -pi:2*pi/255:pi;
x1 = [1 3 5 7 9 11 13 15];
x2 = [1 -1 2 -1 1];
y = conv(x1,x2);
h1 = freqz(x1, 1, w);
h2 = freqz(x2, 1, w);
hp = h1.*h2;
h3 = freqz(y,1,w);
subplot(2,2,1)
plot(w/pi,abs(hp));grid
title('san pham cua quang pho cuong do')
subplot(2,2,2)
plot(w/pi,abs(hp));grid
title('pho bien do day chap')
subplot(2,2,3)
plot(w/pi,angle(hp));grid
title('tong pho pha')
subplot(2,2,4)
plot(w/pi,angle(h3));grid
title('pho pha day chap')