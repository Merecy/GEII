load('pompe1.txt');
load('pompe2.txt');
load('pompe3.txt');
load('pompe4.txt');
load('pompe5.txt');
load('pompe6.txt');
load('pompe7.txt');

Fe=50000;

 FFTplot(pompe1,Fe,'r');
 hold on;
 FFTplot(pompe2,Fe,'b');
 FFTplot(pompe3,Fe,'g');
 FFTplot(pompe4,Fe,'m');
 FFTplot(pompe5,Fe,'k');
 FFTplot(pompe6,Fe,'y');
 FFTplot(pompe7,Fe,'c');
 legend;
 hold off;