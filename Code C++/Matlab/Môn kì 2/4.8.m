t = 0:0.01:0.99;
x = sin(2*pi*15*t) + sin(2*pi*40*t);
dft = fft(x);
N = length(x);
freqs = (0:N-1)*(1/N)/0.01;
y = abs(dft).^2;
plot(freqs(1:N/2), y(1:N/2));
xlabel('Frequency (Hz)');
ylabel('Power');