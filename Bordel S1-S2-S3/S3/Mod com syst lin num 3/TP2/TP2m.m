% #le cours d'auto frero, avec le tableau broida et tout !
K=5;
tau=3;
Te=tau/5;
kp=5/K;
Ti=tau;
Td=0;

%Pour smith, le retard n'est plus pris en compte pour le tableau de
%reglabilte, il devient equivalent a zero

%Pour l'identification du truc inconu au bataillon, faut faire comme avec
%la plaque chauffante

DeltaY=2.3;
DeltaU=1;
Kinconnu=DeltaY/DeltaU;
Deltat1=DeltaY*0.63;
t0=3.098;
t1=4.350;
tauinconnu=t1-t0;
%Pour le retard tu fais a taton, ou tu guette avec le step et tu fais le
%delta entre le signal inconnu et l'echellon ici
retard=2.1;
Reg=0/tauinconnu;
