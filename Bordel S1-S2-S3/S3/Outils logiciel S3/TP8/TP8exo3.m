[y,Fe]=audioread('bagpipe.wav'); % on a une frequence d'echantillonage de 48kHz
sound(y,Fe);
duree=130166/48000; %La duree du son est donc de 2.7sec

FFTplot(y,Fe,'g')
% La note joue tombe sur 468Hz, c'est donc la#3

r=10; comp1; % On compresse le son avec le facteur r;
% sound(yc,Fe); % On commence a entendre legerement la compresion a partir
% de 20
FFTplot(yc,Fe,'r')

%avec un taux de 10, le premier truc est a 77Hz