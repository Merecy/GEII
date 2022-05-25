% Valeur globale a modif
F.num = [5,3,1,];
F.den = [16,96,216,216,81];

F.num=flip(F.num);
F.den=flip(F.den);

% ----------------------------
m = size(F.num)-[0,1];
m = m(1,2);                  %On fait sa pour recup uniquement la deuxieme valeur de la matrice qu'on a creer avec size

n = size(F.den)-[0,1];
n = n(1,2);

F.num(1,m+2)=0;
% ----------------------------
C= F.num;

B = zeros(n,1);
B(n,1)=1/F.den(1,n+1);


A = zeros(n,n);
for i=1:n-1
    A(i,i+1)=1;
end
for i=1:n 
   A(n,i)=-F.den(1,i)/F.den(1,n+1);; 
end