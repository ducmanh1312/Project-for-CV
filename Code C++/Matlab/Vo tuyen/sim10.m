function sim10
% H�m t�nh g?n ?�ng d?a tr�n ph??ng ph�p Newton

% Output:
%   xn: Gi� tr? g?n ?�ng c?a nghi?m

tol = 0.0001;

% Kh?i t?o gi� tr? hi?n t?i v� gi� tr? tr??c ?�
xn_prev = 0;
xn = 2;

% L?p l?i cho ??n khi ??t ?? ch�nh x�c mong mu?n
while (abs(xn - xn_prev) > tol)
    % C?p nh?t gi� tr? hi?n t?i
    xn_prev = xn;
    xn = (xn*xn + 2) / 2*xn;
end
 disp(xn);
end