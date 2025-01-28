n = 0:99; 
x = (0.8).^n; 
% dau ra cua he thong 1 y1[n]
b1 = [0.3 -0.3 0.4]; 
a1 = [1 0.9 0.8]; 
y1 = filter (b1,a1,x); 
% dau ra cua he thong 2 y2[n]
b2 = [0.2 -0.5 0.3]; 
a2 = [1 0.7 0.85]; 
y2 = filter (b2,a2,y1); 
% ve do thi so sanh
subplot (3,1,1) 
stem (n,x) 
xlabel ('n') 
ylabel ('x[n]') 
title ('Tín hiệu đầu vào') 

subplot (3,1,2) 
stem (n,y1) 
xlabel ('n') 
ylabel ('y1[n]') 
title ('Tín hiệu đầu ra của hệ thống 1')

subplot (3,1,3) 
stem (n,y2) 
xlabel ('n') 
ylabel ('y2[n]') 
title ('Tín hiệu đầu ra của hệ thống 2') 