function sim10
% Hàm tính g?n ?úng d?a trên ph??ng pháp Newton

% Output:
%   xn: Giá tr? g?n ?úng c?a nghi?m

tol = 0.0001;

% Kh?i t?o giá tr? hi?n t?i và giá tr? tr??c ?ó
xn_prev = 0;
xn = 2;

% L?p l?i cho ??n khi ??t ?? chính xác mong mu?n
while (abs(xn - xn_prev) > tol)
    % C?p nh?t giá tr? hi?n t?i
    xn_prev = xn;
    xn = (xn*xn + 2) / 2*xn;
end
 disp(xn);
end