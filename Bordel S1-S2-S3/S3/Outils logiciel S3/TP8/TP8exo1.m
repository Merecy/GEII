y=load('data.txt');
Fe=16000;
sound(y,Fe);
FFTplot2(y,Fe,1000,1000)
% 1ere ensemble de note : do4 (528), la3 (440), fa3 (352)
% 2eme ensemble de note : fa3 (352), ré3 (296), si2 (248)
figure
% Avec FFTplot on peut voir de facon precise la hauteur des notes, mais on
% ne voit pas leur ordre
FFTplot(y,Fe,'r')
% On a un si2 (247), ré3 (293.5), fa3 (349), la3 (440), do4 (523)
% Donc si on a un doute, go regarder FFTplot ^^
