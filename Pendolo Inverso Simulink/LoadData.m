clc
load('calibrateVal.mat')
e = exp(1); %Numero di Eulero
Tc = 0.005; %Periodo di Arduino
d_pole = 20; %Posizione polo derivativo
f_pole = 15; %Posizione polo filtro
fprintf('Data loaded successfully\n')