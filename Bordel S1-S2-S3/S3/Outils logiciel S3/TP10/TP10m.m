[y,Fe]=audioread('2intellos.wav'); 
% sound(y,Fe)

t=(0:length(y)-1/Fe);
K=4;
Fs=Fe/2^K;
ts=t(1:2^K:end);
ys=y(1:2^K:end);
FFTplot(y,Fe,'r')
hold on
FFTplot(ys,Fs,'b')
hold off
sound(ys,Fs)