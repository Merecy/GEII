% Fichier de configuration
K = 2.2;
tau = 0.01;
G=45.45;

Fs.num = [K];
Fs.den = [tau, 1, 0];
Rs.num = [G];
Rs.den = [1];

% Representation sous forme de fdt
Fs_transf = tf(Fs.num,Fs.den);
Rs_transf = tf(Rs.num,Rs.den);

figure(1)

nichols(Fs_transf*Rs_transf);

% Representation avce bode le S
figure(2)

bode(Fs_transf*Rs_transf);

% ---

Mp=6; %en degre
w0 = 1e+3;

%reglage Avance de phase
Pdes = 45; %marge de phase du cahier des chrages
Pmax=Pdes-Mp+5;

a=(1+sin(Pmax*pi/180))/(1-sin(Pmax*pi/180));
T=1/w0/sqrt(a);

%---

RsA2P.num=[G*a*T,G];
RsA2P.den=[T,1];

RsA2P_transf=tf(RsA2P.num,RsA2P.den);
figure(1)

hold on
nichols(Fs_transf*RsA2P_transf);
hold off

%---

RsA2P_adj.num=[G*a*T,G];
RsA2P_adj.den=[T,1];

RsA2P_adj_transf=tf(RsA2P_adj.num,RsA2P_adj.den);
figure(1)

hold on
nichols(Fs_transf*RsA2P_adj_transf);
hold off