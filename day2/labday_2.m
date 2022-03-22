%%Labday 2 project file

%%System matrices
%Continious time
A_c = [0  1   0   0;
    0   0   -K_2 0;
    0   0   0   1;
    0   0   -K_1*K_pp -K_1*K_pd];

B_c = [0; 0; 0; K_1*K_pp];

%Discrete time, with timestep 0.25sec
delta_t = 0.25;

A = eye(4) + delta_t * A_c;
B = delta_t * B_c;

%Quadratic program for task 3, labday 2
N = 100;
x_0 = [pi; 0; 0; 0]; %inital values

%Computing H matrix
q = 0.1;
Q = q*ones(1, N);

e = [1 0 0 0];
E = repmat(e, 1, N);
h = [E Q];
H = diag(h);

%Contraints
lb = -30*pi/180;
ub = 30*pi/180;

F = [-inf; -inf; lb; -inf];

LB = [repmat(F, 1, N) lb*ones(1, N)];
UB = [repmat(-F, 1, N) ub*ones(1, N)];

%Calculating quadratic program





