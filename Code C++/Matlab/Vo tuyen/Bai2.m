function Bai2
x = [-pi:4*pi/100:pi]
f = zeros(1,length(x));
for i = 1:length(x)
    f(i) = (1/2)*1*sinc((x(i)-1)*1)+(1/2)*1*sinc((x(i)-1)*1);
end
plot(x,f);
end
    