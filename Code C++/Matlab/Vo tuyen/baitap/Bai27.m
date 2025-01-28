function [y] = bai27(N, a, b ,x0, y0, f)
    t = zeros(1, N+1);
    y = zeros(1, N+1);
    t(1) = x0;
    y(1) = y0;
    h = (b - a) / N;
    
    for i = 2:(N+1)
        t(i) = t(i-1) + h;
        y(i) = y(i-1) + h * f(t(i-1), y(i-1));
    end
  plot(t,y);
end 
