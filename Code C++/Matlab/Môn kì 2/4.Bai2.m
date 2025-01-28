 x = input('Nhap chuoi tin hieu: ');
N = input('Nhap do dai DFT: ');
dft = zeros(1, N);
for k = 0:N-1
    for n = 0:length(x)-1
        dft(k+1) = dft(k+1) + x(n+1) * exp(-2*pi*1i*k*n/N);
    end
end
freqs = (0:N-1)*(1/N);
power_spectrum = abs(dft).^2;
stem(freqs, power_spectrum);
xlabel('Frequency (cycles/sample)');
ylabel('Power');