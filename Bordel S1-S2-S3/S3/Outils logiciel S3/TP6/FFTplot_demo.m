N  = 1024;
Fe = 200;
F1 = 8;
F2 = 35;
t  = (0:N-1)/Fe ;
x  = 3*cos(2*pi*F1*t) + 5*cos(2*pi*F2*t) ;
FFTplot(x,Fe,'b')