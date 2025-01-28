x=0:0.01:2*pi; 
y1=sin(x).*cos(2*x); 	%nhan tuong ung tung phan tu 
semilogy(x,y1)  
grid on 		%hien thi luoi 
hold on 		%giu hinh, mac nhien la hold off 
y2=sin(x.^2); 	%luy thua tung phan tu 
semilogy(x,y2,'r') 	%duong ve co mau den  
axis([0 4*pi -1.25 1.25]) %dinh lai toa do hien thi 
xlabel('Time') 
ylabel('Amplitude') 
title('y1=sinx.cos2x and y2=sin(x^2)') 
legend('sinx.cos2x','sinx^2')