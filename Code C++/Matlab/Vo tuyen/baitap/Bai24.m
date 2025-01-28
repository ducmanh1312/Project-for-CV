% ??nh ngh?a c�c h?ng s?
a = 1;
r = 1;
y0 = 0;
h = 0.25; % K�ch th??c b??c ?i cho ph??ng ph�p Euler c?i ti?n
t_end = 2; % Th?i ?i?m k?t th�c m� ph?ng

% H�m ??i di?n cho ph??ng tr�nh vi ph�n y'(t) + a*y(t) = r
dydt = @(y, t)(r - a*y);

% Kh?i t?o m?ng ?? l?u gi� tr? th?i gian v� gi?i ph�p
t_values = 0:h:t_end; % M?ng c�c gi� tr? th?i gian t? 0 ??n t_end v?i b??c h
y_values = zeros(1, length(t_values)); % M?ng ?? l?u gi� tr? y t?i m?i b??c th?i gian
y_values(1) = y0; % ??t gi� tr? ban ??u

% Th?c hi?n ph??ng ph�p Euler c?i ti?n
for i = 1:(length(t_values)-1)
    y_predict = y_values(i) + h * dydt(y_values(i), t_values(i)); % D? ?o�n gi� tr? y
    y_correct = y_values(i) + (h/2) * (dydt(y_values(i), t_values(i)) + dydt(y_predict, t_values(i) + h)); % T�nh to�n gi� tr? y ch�nh x�c h?n
    y_values(i + 1) = y_correct; % C?p nh?t gi� tr? y m?i
end

% H�m gi?i ph�p ph�n t�ch c?a ph??ng tr�nh vi ph�n
y_analytical = @(t)(r/a * (1 - exp(-a * t))); % C�ng th?c gi?i ph�p ph�n t�ch

% T�nh to�n sai s? tuy?t ??i t?i t = 1 v� t = 2
error_t1 = abs(y_analytical(1) - y_values(t_values == 1)); % Sai s? t?i t = 1
error_t2 = abs(y_analytical(2) - y_values(t_values == 2)); % Sai s? t?i t = 2

% Hi?n th? k?t qu?
fprintf('Gi?i ph�p s? t?i t=1 l� %f, v?i sai s? tuy?t ??i l� %f\n', y_values(t_values == 1), error_t1);
fprintf('Gi?i ph�p s? t?i t=2 l� %f, v?i sai s? tuy?t ??i l� %f\n', y_values(t_values == 2), error_t2);
