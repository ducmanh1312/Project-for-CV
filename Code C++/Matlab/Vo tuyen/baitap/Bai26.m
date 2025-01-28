function bai26
    % ??nh ngh?a các h?ng s?
    a = 1;
    r = 1;
    y0 = 0;
    h = 0.25; % Kích th??c b??c ?i cho ph??ng pháp Runge-Kutta b?c 4
    t_end = 2;

    % Hàm ??i di?n cho ph??ng trình vi phân dy/dt = r - a*y
    dydt = @(y, t)(r - a*y);

    % Kh?i t?o m?ng ?? l?u giá tr? th?i gian và gi?i pháp s?
    t_values = 0:h:t_end; % M?ng các giá tr? th?i gian t? 0 ??n t_end v?i b??c h
    y_values = zeros(1, length(t_values)); % M?ng ?? l?u giá tr? y t?i m?i b??c th?i gian
    y_values(1) = y0; % ??t giá tr? ban ??u

    % Th?c hi?n ph??ng pháp Runge-Kutta b?c 4
    for i = 1:(length(t_values)-1)
        k1 = dydt(y_values(i), t_values(i));
        k2 = dydt(y_values(i) + k1 * h / 2, t_values(i) + h / 2);
        k3 = dydt(y_values(i) + k2 * h / 2, t_values(i) + h / 2);
        k4 = dydt(y_values(i) + k3 * h, t_values(i) + h);
        
        y_values(i + 1) = y_values(i) + h * (k1 + 2*k2 + 2*k3 + k4) / 6;
    end

    % Hàm gi?i pháp phân tích c?a ph??ng trình vi phân
    y_analytical = @(t)(r/a * (1 - exp(-a * t))); % Công th?c gi?i pháp phân tích

    % Tính toán sai s? tuy?t ??i t?i t = 1 và t = 2
    error_t1 = abs(y_analytical(1) - y_values(t_values == 1)); % Sai s? t?i t = 1
    error_t2 = abs(y_analytical(2) - y_values(t_values == 2)); % Sai s? t?i t = 2

    % Hi?n th? k?t qu?
    fprintf('Giai phap so tai t=1 la %f, voi sai so tuyet doi la %f\n', y_values(t_values == 1), error_t1);
    fprintf('Giai phap so tai t=2 la %f, voi sai so tuyet doi la %f\n', y_values(t_values == 2), error_t2);
end
