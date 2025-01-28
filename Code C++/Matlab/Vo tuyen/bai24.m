% Khai báo các tham s?
a = 1;
r = 1;
y0 = 0;
h = 0.25;

% T?o m?ng th?i gian
t = 0:h:2;

% Kh?i t?o m?ng nghi?m
y = zeros(size(t));

% Hàm f(t, y)
f = @(t, y) r;  % Define f(t, y) as an anonymous function

% Ch?y ph??ng pháp Euler bi?n ??i
for i = 1:length(t)-1
  y(i+1) = y(i) + h * (f(t(i), y(i)) - a * y(i));
end

% Tính nghi?m gi?i tích
y_exact = @(t) exp(-a * t) + r * (1 - exp(-a * t)) / a;

% Tính sai s?
error_t1 = abs(y_exact(1) - y(4));
error_t2 = abs(y_exact(2) - y(8));

% Hi?n th? k?t qu?
disp('Nghi?m t?i t = 1:');
disp(y(4));

disp('Nghi?m t?i t = 2:');
disp(y(8));

disp('Sai s? t?i t = 1:');
disp(error_t1);

disp('Sai s? t?i t = 2:');
disp(error_t2);