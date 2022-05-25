%Clear les variables des anciens calcul
clear;
%Définition de la FtD F4:
F4.num = [5, 3, 1];
F4.den = [16, 96 216, 216, 81];
Te = 0.5;

%On determine la taille des matrices => n
[Taille_ligne,Taille_colone] = size(F4.den);
n = Taille_colone - 1;

%On crée les matrices vides
A = zeros(n,n);
B = zeros(n,1);
C = zeros(1,n);

%On remplit la matrice A
for i = 1:(n-1)
    A(i,i+1) = 1;
end
for i = 1:n
    A(n,i) = -F4.den(Taille_colone-i+1)/F4.den(1);
end

%On remplit la matrice B
B(n,1) = 1/F4.den(1);

%On remplit la matrice C
[Taille_ligne_Num,Taille_colone_Num] = size(F4.num);
n_num = Taille_colone_Num - 1;
for i = 1:(Taille_colone_Num)
    C(1,i) = F4.num(Taille_colone_Num-i+1);
end

%On défini la matrice m
M = zeros(n+1,n+1);
%ajout de A dans M
for i = 1:n
    for j = 1:n
       M(i,j) = A(i,j);
    end
end
%ajout de B dans M
for i = 1:n
       M(i,5) = B(i,1);
end

%on exprime M sous exponentiel
Mm = expm(M*Te);

%On crée les matrices vides Ad et Bd
Ad = zeros(n,n);
Bd = zeros(n,1);

%on remplit la matrice Ad
for i = 1:n
    for j = 1:n
       Ad(i,j) = Mm(i,j);
    end
end

%on remplit la matrice Bd
for i = 1:n
   Bd(i,1) = Mm(i,5);
end

%On crée les matrices vides Aa et Bb
Aa = zeros(n,n);
Ba = zeros(n,1);
[Aa,Bb]=extractFdt(Ad,Bd,C);


% this script accepts as inputs the matrix Ad and the vectors Bd and C,
% where EXP([A,B;0,0]*t)=[Ad,Bd;0,1], and gives as output two vectors
% [out1,out2], out1 being the numerator of the transfer function of the
% sampled system, out2 being its denominator. They can be directly read by
% Simulink
function [out1,out2]=extractFdt(Ad,Bd,C)
syms z;
n=size(Ad)*[1;0];
Fz = C*(eye(n)*z-Ad)^(-1)*Bd;

[N,D]=numden(Fz);

Dpz=coeffs(D);
out1 = double(coeffs(N)/Dpz(n+1));
out2 = double(Dpz/Dpz(n+1));


out2=flip(out2);

out1=flip(out1);

end


