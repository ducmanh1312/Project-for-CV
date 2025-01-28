a = 1; b = 2; c = 3;
A = [a -b -c; c 2*b -a; a c -3*c];
B = [10; 5; 2];
C = a * ones(b+4)
C(b+4,b+4) = 10;
C(1:3,1:3) = A;

D = rand(5,10);

