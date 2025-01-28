% ??nh ngh?a các h?ng s?
a = 1;
r = 1;
y0 = 0;
h = 0.25; % Kích th??c b??c ?i cho ph??ng pháp Euler c?i ti?n
t_end = 2; % Th?i ?i?m k?t thúc mô ph?ng

% Hàm ??i di?n cho ph??ng trình vi phân y'(t) + a*y(t) = r
dydt = @(y, t)(r - a*y);

% Kh?i t?o m?ng ?? l?u giá tr? th?i gian và gi?i pháp
t_values = 0:h:t_end; % M?ng các giá tr? th?i gian t? 0 ??n t_end v?i b??c h
y_values = zeros(1, length(t_values)); % M?ng ?? l?u giá tr? y t?i m?i b??c th?i gian
y_values(1) = y0; % ??t giá tr? ban ??u

% Th?c hi?n ph??ng pháp Euler c?i ti?n
for i = 1:(length(t_values)-1)
    y_predict = y_values(i) + h * dydt(y_values(i), t_values(i)); % D? ?oán giá tr? y
    y_correct = y_values(i) + (h/2) * (dydt(y_values(i), t_values(i)) + dydt(y_predict, t_values(i) + h)); % Tính toán giá tr? y chính xác h?n
    y_values(i + 1) = y_correct; % C?p nh?t giá tr? y m?i
end

% Hàm gi?i pháp phân tích c?a ph??ng trình vi phân
y_analytical = @(t)(r/a * (1 - exp(-a * t))); % Công th?c gi?i pháp phân tích

% Tính toán sai s? tuy?t ??i t?i t = 1 và t = 2
error_t1 = abs(y_analytical(1) - y_values(t_values == 1)); % Sai s? t?i t = 1
error_t2 = abs(y_analytical(2) - y_values(t_values == 2)); % Sai s? t?i t = 2

% Hi?n th? k?t qu?
fprintf('Gi?i pháp s? t?i t=1 là %f, v?i sai s? tuy?t ??i là %f\n', y_values(t_values == 1), error_t1);
fprintf('Gi?i pháp s? t?i t=2 là %f, v?i sai s? tuy?t ??i là %f\n', y_values(t_values == 2), error_t2);
