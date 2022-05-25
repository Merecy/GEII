x=fft(y);
xs=sort(abs(x),'descend');
N=length(y);
s=xs(round(N/2/r));
x(abs(x)<s)=0;
yc=ifft(x);