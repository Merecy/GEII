y = 0.2 * randn(1,1024);
plot(y,'b')
figure(1)
FFTplot(y,1,'g')

u=[1:500,500:-1:1];
y=real(ifft(randn(1,1000).*u));
figure(2)
plot(y,'y')
figure(3)
FFTplot(y,1,'r')


