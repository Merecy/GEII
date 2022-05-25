Fe = 8000;
N = 10*Fe;
t = (0:N-1)/Fe;
x = cos(2*pi*(220+352*floor(t)).*t)+cos(2*pi*880*t);
FFTplot(x,Fe,'r')