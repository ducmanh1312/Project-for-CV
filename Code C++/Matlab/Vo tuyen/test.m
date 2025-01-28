% Chuong trinh MATLAB ve hinh tron

% B�n k�nh h�nh tr�n
r = 3;

% T�nh chu vi v� di?n t�ch h�nh tr�n
chuVi = 2 * pi * r;
dienTich = pi * r^2;

% V? ???ng tr�n
theta = linspace(0, 2*pi, 100);
x = r * cos(theta);
y = r * sin(theta);
plot(x, y, 'b-', 'LineWidth', 2);

% Hi?n th? tr?c t?a ??
axis equal;

% Hi?n th? k?t qu?
disp( num2str(chuVi));
disp(num2str(dienTich));