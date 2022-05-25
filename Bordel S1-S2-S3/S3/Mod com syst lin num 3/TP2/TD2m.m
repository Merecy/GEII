% Valeur globale a modif
% F.num = [5 3 1];
% F.den = [16 96 216 216 81];

F.num = [5];
F.den = [3 1];
Te=0.5;


F.num=flip(F.num);
F.den=flip(F.den);

% ----------------------------
m = size(F.num);
m = m(1,2);                  %On fait sa pour recup uniquement la deuxieme valeur de la matrice qu'on a creer avec size

n = size(F.den)-[0,1];
n = n(1,2);


% ----------------------------
C= zeros(1,n);
for i=1:m
    C(1,i)=F.num(1,i);
end

%On chope B
B = zeros(n,1);
B(n,1)=1/F.den(1,n+1);

%On chope A
A = zeros(n,n);
for i=1:n-1
    A(i,i+1)=1;
end
for i=1:n 
   A(n,i)=-F.den(1,i)/F.den(1,n+1);
end


M = zeros(n+1,n+1);

for i = 1:n
    %On remplit avec A
    for j = 1:n
       M(i,j) = A(i,j);
    end
    %On rempli avec B
    M(i,n+1) = B(i,1);
end

%La fonction qui fais l'exponentielle de la matrice
Mexp=expm(M*Te);

Ad=zeros(n,n);
Bd=zeros(n,1);


for i = 1:n
    %On recupere A
    for j = 1:n
       Ad(i,j) = Mexp(i,j);
    end
    %On recupere B
    Bd(i,1) = Mexp(i,n+1);
end

out1 = zeros(n,n);
out2 = zeros(n,1);
[out1,out2]=extractFdt(Ad,Bd,C);






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
