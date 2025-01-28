function F = fibonaci(n)
    if n <= 1
        F = n;
    else 
        F = fibonaci(n-1) + fibonaci(n-2);
    end
        