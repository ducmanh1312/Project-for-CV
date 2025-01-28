% Dau vao
n = 0:299; % 300 m?u
x = cos((20*pi*n)/256) + cos((200*pi*n)/256);

% He thong 1
a1 = [1 -0.53 0.46];
b1 = [0.5 0.27 0.77];
y1 = filter(b1, a1, x);

%He thong 2
a2 = [1 -0.53 0.46];
b2 = [0.45 0.5 0.45];
y2 = filter(b2, a2, x);

% Hien thi dau vao ra cua hai he thong
subplot(3,1,1);
plot(n, x);
title('dau vao');
xlabel('n');
ylabel('x(n)');

subplot(3,1,2);
plot(n, y1);
title('dau ra cua he thong 1');
xlabel('n');
ylabel('y_1(n)');
subplot(3,1,3);

plot(n, y2);
title('dau ra cua he thong 2');
xlabel('n');
ylabel('y_2(n)');
