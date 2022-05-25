
%--------------variables-------------------
%-------------- Broida----------------------------
K = 0.148;
tau = 330;


%-------------- Strejc------------------------------------
tau2= 90.4912;
r2=23.5264;
n = 2;


%--------------fonction-------------------

fs.num = [K];
fs.den = [tau 1];

Strejc.num = K
Strejc.den = [tau2*tau2 2*tau2 1]

%-------------- Strejc au doigt mouille -------------------


Ioutput = 46.6;

ti = 1308.800;  % abscisse du point d'inflexion
yi = 48.241;   % abscisse du point d'inflexion

The_slope = 0.03;

Adequate_StepTime = (Ioutput+The_slope*ti-yi)/The_slope;


%The_slope2 = 0.027;

%Adequate_StepTime2 = (Ioutput+The_slope2*ti-yi)/The_slope2;













