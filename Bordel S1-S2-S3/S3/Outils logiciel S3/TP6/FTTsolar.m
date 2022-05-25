load('SolarData.mat');

Fe = 12; %12 mois par an, donc la frequence c'est 12.
T=1/0.092; %1/Ffft C'est donc la periode du soleil avec ces taches (ici 10.9 ans)
FFTplot(y,12,'m');
