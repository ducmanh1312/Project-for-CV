n = 0:15;
x = cos(pi/2 * n);
x_8 = x(1:8);
N = 8;
dft = zeros(1, N);
for k = 0:N-1
    for n = 0:N-1
        dft(k+1) = dft(k+1) + x_8(n+1) * exp(-2*pi*1i*k*n/N);
    end
end
freqs = (0:N-1)*(1/N);
power_spectrum = abs(dft).^2;
stem(freqs, power_spectrum);
xlabel('Frequency (cycles/sample)');
ylabel('Power');