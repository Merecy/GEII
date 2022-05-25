function FFTplot2(x,Fe,nt,nf)
if nargin<4
    nf = 300;
    if nargin<3
        nt = 300;
        if nargin<2 % mode démo...
            [x,Fe]=audioread('sample.wav');
        end
    end
end
N = length(x);
t = (0:nt-1)/nt*N/Fe;
f = (0:nf-1)*Fe/2/nf;
Y = zeros(nf,nt);
for k=1:nt
    i=floor((N-2*nf)*(k-1)/nt);
    y=fft(x(i+1:i+2*nf));
    y=y(:);
    Y(:,k)=abs(y(1:nf));
end
clf()
cmap =  hot(256);
cmap(1,:) = 0;
Y(1,:)=0;
imagesc('XData',t,'YData',f,'CData',log(Y+10))
colormap(cmap)
xlabel('Temps (s)')
ylabel('Fréquence (Hz)')
axis([0,t(end),0,f(end)])
end