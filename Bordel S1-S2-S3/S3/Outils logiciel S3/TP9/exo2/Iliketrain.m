[y,Fe]=audioread('tchoutchou.wav');  
FFTplot(y,Fe,'g')
hold
% sound(y,Fe)

yb = y + 0.2 * randn(size(y));
% sound(yb,Fe)
FFTplot(yb,Fe,'b')

Fc=3500;
FiltrePB= designfilt('lowpassiir','FilterOrder',16,'PassbandFrequency',Fc,'PassbandRipple',0.2,'SampleRate',Fe);

yf = filter(FiltrePB, yb);
FFTplot(yf,Fe,'r')
legend('y','yb','yf')
sound(yf,Fe)























