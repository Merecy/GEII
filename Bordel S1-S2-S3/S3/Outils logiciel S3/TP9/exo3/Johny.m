[y,Fe]=audioread('soundtrack02.wav');  
FFTplot(y,Fe,'g')
hold
% sound(y,Fe)


Fc=1800;
FiltrePB= designfilt('lowpassiir','FilterOrder',16,'PassbandFrequency',Fc,'PassbandRipple',0.2,'SampleRate',Fe);

yf = filter(FiltrePB, y);
FFTplot(yf,Fe,'r')
legend('y','yf')

sound(yf*100,Fe)

figure
plot(y,'b')
figure(1)
plot(yf,'m')


% C'est bien evidemment raciste ta bite
% Je comprend r jsuis sourd
