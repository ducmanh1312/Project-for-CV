z = [0.5 2.2 -0.2+j*0.3 -0.1-j*0.3];
p = [0.4 -0.75 0.5+j*0.6 0.5-j*0.6 ];
k = 3.7;
[num, den] = zp2tf(z',p',k);
disp(num);
disp(den);
zplane(num, den);