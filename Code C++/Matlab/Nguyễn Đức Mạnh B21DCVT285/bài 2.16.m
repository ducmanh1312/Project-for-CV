N = 40;
num = [0.3 0.2 -0.3];
den = [1 0.9 -0.9];
h = impz(num,den,N);
stem(h);
x = randn(1,10);
y = conv(x,h);
subplot(311),stem(x); title('x(n)');
subplot(312),stem(h); title('h(n)');
subplot(313),stem(y); title('y(n)');

% Xac dinh tinh on dinh cua he thong dãy y(n)
if all(abs(roots(den)) < 1)
    disp('H? th?ng ?n ??nh');
else
    disp('H? th?ng không ?n ??nh');
end






