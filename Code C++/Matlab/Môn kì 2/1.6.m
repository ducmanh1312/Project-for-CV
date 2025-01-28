%pt: 2*(x^2)+y^2=10 
% Thay x = rcos(theta) và y = rsin(theta) 
% vào phương trình % Ta được r^2 = 10/(2*cos(theta)^2 + sin(theta)^2)
theta=0:0.01:2*pi;
 r = sqrt(10./(2*cos(theta).^2 + sin(theta).^2));
 polar(theta,r)
