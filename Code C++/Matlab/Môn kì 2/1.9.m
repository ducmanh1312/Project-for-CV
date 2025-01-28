A=input('Bien do dinh='); %A=+/-1;
N=15;   %Chu ki cua day
DRX=60; % Do rong xung vuong
L=100;  % Chieu dai cua day
t=0:L-1;
y1=A*sawtooth(2*pi*t/N);
y2=A*square(2*pi*t/N,DRX);
subplot(211);
stem(t,y1)
xlabel('Thoi gian');
ylabel('Bien do');
title('Day xung rang cua');
subplot(212);
stem(t,y2)
xlabel('Thoi gian');
ylabel('Bien do');
title('Day xung vuong');
