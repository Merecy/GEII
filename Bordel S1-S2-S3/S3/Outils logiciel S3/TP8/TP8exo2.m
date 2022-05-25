y=load('signal.txt');
x=load('signalbase.txt');
Fe=1000;
Feb=10000;
FFTplot(y,Fe,'r')
hold
FFTplot(x,Feb,'g')


% Le nombre d'echnatillon tu veut le max, tant que le signal est
% stationnaire

% La frequence d'echantillonage tu prend le max comme sa tu perd pas d'info

% frequence du filtre c'est la moitier de Fe

% Sur la base, on voit que 3 courbes, donc ils sont cache, faut zoomer
% methodiquement



%45, 47, 452, 454, 2451