function FFTplot(x,Fe,couleur) 
N=length(x);
f=(0:N-1)*Fe/N;
y=fft(x); 
plot(f(1:round(N/2)),2*abs(y(1:round(N/2)))/N,couleur);
end