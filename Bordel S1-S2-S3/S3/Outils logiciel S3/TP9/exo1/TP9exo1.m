y=0;
Fe=10000; % On prend 10000 pour avoir la frequence de coupure a 5000
for k=1:50
    text=sprintf("data(%d).txt",k)
    y=y+load(text);
end
FFTplot2(y/k,Fe)
figure
FFTplot(y/k,Fe,'g')



% On voit bien le signal qui etait cache a travers le bruit,
% Qu'il a une frequence de 1516 Hz, avec une amplitude de 0.011473.