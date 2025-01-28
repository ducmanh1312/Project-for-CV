% Chuong trinh MATLAB ve hinh tron

% Bán kính hình tròn
r = 3;

% Tính chu vi và di?n tích hình tròn
chuVi = 2 * pi * r;
dienTich = pi * r^2;

% V? ???ng tròn
theta = linspace(0, 2*pi, 100);
x = r * cos(theta);
y = r * sin(theta);
plot(x, y, 'b-', 'LineWidth', 2);

% Hi?n th? tr?c t?a ??
axis equal;

% Hi?n th? k?t qu?
disp( num2str(chuVi));
disp(num2str(dienTich));