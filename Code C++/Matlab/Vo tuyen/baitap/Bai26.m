function bai26
    % ??nh ngh?a c�c h?ng s?
    a = 1;
    r = 1;
    y0 = 0;
    h = 0.25; % K�ch th??c b??c ?i cho ph??ng ph�p Runge-Kutta b?c 4
    t_end = 2;

    % H�m ??i di?n cho ph??ng tr�nh vi ph�n dy/dt = r - a*y
    dydt = @(y, t)(r - a*y);

    % Kh?i t?o m?ng ?? l?u gi� tr? th?i gian v� gi?i ph�p s?
    t_values = 0:h:t_end; % M?ng c�c gi� tr? th?i gian t? 0 ??n t_end v?i b??c h
    y_values = zeros(1, length(t_values)); % M?ng ?? l?u gi� tr? y t?i m?i b??c th?i gian
    y_values(1) = y0; % ??t gi� tr? ban ??u

    % Th?c hi?n ph??ng ph�p Runge-Kutta b?c 4
    for i = 1:(length(t_values)-1)
        k1 = dydt(y_values(i), t_values(i));
        k2 = dydt(y_values(i) + k1 * h / 2, t_values(i) + h / 2);
        k3 = dydt(y_values(i) + k2 * h / 2, t_values(i) + h / 2);
        k4 = dydt(y_values(i) + k3 * h, t_values(i) + h);
        
        y_values(i + 1) = y_values(i) + h * (k1 + 2*k2 + 2*k3 + k4) / 6;
    end

    % H�m gi?i ph�p ph�n t�ch c?a ph??ng tr�nh vi ph�n
    y_analytical = @(t)(r/a * (1 - exp(-a * t))); % C�ng th?c gi?i ph�p ph�n t�ch

    % T�nh to�n sai s? tuy?t ??i t?i t = 1 v� t = 2
    error_t1 = abs(y_analytical(1) - y_values(t_values == 1)); % Sai s? t?i t = 1
    error_t2 = abs(y_analytical(2) - y_values(t_values == 2)); % Sai s? t?i t = 2

    % Hi?n th? k?t qu?
    fprintf('Giai phap so tai t=1 la %f, voi sai so tuyet doi la %f\n', y_values(t_values == 1), error_t1);
    fprintf('Giai phap so tai t=2 la %f, voi sai so tuyet doi la %f\n', y_values(t_values == 2), error_t2);
end
