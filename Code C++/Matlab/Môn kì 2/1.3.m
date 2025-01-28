x=-5:0,01:5;
y=exp(-x.^2).*exp(-x+2);
xlabel('x');
ylabel('y');
title('y=exp(-x^2).*exp(-x+2)');
subplot(311);
semilogx(x,y,'k')
grid on
axis([-6 6 -1 10]);
subplot(312);
semilogy(x,y,'r')
title('y=exp(-x^2).*exp(-x+2)');
grid on
axis([-6 6 -1 10]);
subplot(313);
loglog(x,y,'b')
grid on
axis([-6 6 -1 10]);
title('y=exp(-x^2).*exp(-x+2)');
