% TTK4135 - Helicopter lab
% Hints/template for problem 2.
% Updated spring 2018, Andreas L. Flåten

%% Initialization and model definition
init_01; % Change this to the init file corresponding to your helicopter
global  N alpha beta mx lambda_t

% Discrete time system model. x = [lambda r p p_dot]'
delta_t	= 0.25; % sampling time
A_c = [0  1   0   0 0 0;
    0   0   -K_2 0 0 0;
    0   0   0   1 0 0;
    0   0   -K_1*K_pp -K_1*K_pd 0 0;
    0 0 0 0 0 1;
    0 0 0 0 -K_3*K_ep -K_3*K_ed];

B_c = [0 0; 0 0; 0 0; K_1*K_pp 0; 0 0; 0 K_3*K_ep ];

%Discrete time, with timestep 0.25sec

A1 = eye(6) + delta_t * A_c;
B1 = delta_t * B_c;

% Number of states and inputs
mx = size(A1,2); % Number of states (number of columns in A)
mu = size(B1,2); % Number of inputs(number of columns in B)

% Initial values
x1_0 = pi;                               % Lambda
x2_0 = 0;                               % r
x3_0 = 0;                               % p
x4_0 = 0;                               % p_dot
x0 = [x1_0 x2_0 x3_0 x4_0 0 0]';           % Initial values

% Time horizon and initialization
N  = 40;                                  % Time horizon for states
M  = N;                                 % Time horizon for inputs
z  = zeros(N*mx+M*mu,1); % Initialize z for the whole horizon
z0 = z; 
for i=5:6:N*(mx)
    z0(i) = 0.1;
end
                                % Initial value for optimization

% Bounds
ul 	    = -30*pi/180;                   % Lower bound on control
uu 	    = -ul;                   % Upper bound on control

xl      = -Inf*ones(mx,1);              % Lower bound on states (no bound)
xu      = Inf*ones(mx,1);               % Upper bound on states (no bound)
xl(3)   = ul;                           % Lower bound on state x3
xu(3)   = uu;                           % Upper bound on state x3

% Generate constraints on measurements and inputs
[vlb,vub]       = gen_constraints(N, M, xl, xu, ul, uu); % hint: gen_constraints
vlb(N*mx+M*mu)  = 0;                    % We want the last input to be zero
vub(N*mx+M*mu)  = 0;                    % We want the last input to be zero

% Generate the matrix Q and the vector c (objecitve function weights in the QP problem) 
Q1 = zeros(mx,mx);
Q1(1,1) = 1;                            % Weight on state x1                         
P1 = diag([4 4]);                                % Weight on input
Q = gen_q(Q1, P1, N, M);                                  % Generate Q, hint: gen_q
c = zeros(5*N, 1);                                  % Generate c, this is the linear constant term in the QP

%% Generate system matrixes for linear model
Aeq = gen_aeq(A1, B1, N, mx, mu);             % Generate A, hint: gen_aeq
beq = [A1*x0; zeros(6*(N-1),1)];% Generate b

%% Day 3, feedback control

Q_lqr = [2 0 0 0 0 0;
    0 1 0 0 0 0;
    0 0 1 0 0 0;
    0 0 0 1 0 0
    0 0 0 0 1 0
    0 0 0 0 0 1];

R_lqr = [0.1 0;
        0 0.1];

K_lqr = dlqr(A1, B1, Q_lqr, R_lqr);

%% Solve QP with nonlinear solver
alpha = 0.2;
beta = 20;
lambda_t = 2*pi/3;
q1 = 1;
q2 = 1;


%z0 = [x0;0;0];

f = @(z) 1/2 * (z)'*Q*(z);

opt = optimoptions('fmincon', 'Algorithm', 'sqp', 'MaxFunEvals', 100000);

tic
[z fval exitflag] = fmincon(f, z0, [], [], Aeq, beq, vlb, vub, @non_lil_constraints, opt);
t1=toc;


%% Solve QP problem with linear model

% Calculate objective value
phi1 = 0.0;
PhiOut = zeros(N*mx+M*mu,1);
for i=1:N*mx+M*mu
  phi1=phi1+Q(i,i)*z(i)*z(i);
  PhiOut(i) = phi1;
end

%% Extract control inputs and states
u  = [z(N*mx+1:N*mx+M*mu);z(N*mx+M*mu);z(N*mx+M*mu)];% Control input from solution
u1 = u(1:2:end);
u2 = u(2:2:end);

x1 = [x0(1);z(1:mx:N*mx)];              % State x1 from solution
x2 = [x0(2);z(2:mx:N*mx)];              % State x2 from solution
x3 = [x0(3);z(3:mx:N*mx)];              % State x3 from solution
x4 = [x0(4);z(4:mx:N*mx)];
x5 = [x0(5);z(5:mx:N*mx)];
x6 = [x0(6);z(6:mx:N*mx)];              % State x4 from solution

num_variables = 5/delta_t;
zero_padding = zeros(num_variables,1);
unit_padding  = ones(num_variables,1);

u1   = [zero_padding; u1; zero_padding];
u2   = [zero_padding; u2; zero_padding];
x1  = [pi*unit_padding; x1; zero_padding];
x2  = [zero_padding; x2; zero_padding];
x3  = [zero_padding; x3; zero_padding];
x4  = [zero_padding; x4; zero_padding];
x5  = [zero_padding; x5; zero_padding];
x6  = [zero_padding; x6; zero_padding];



p_ref = timeseries(u1, 0:0.25:20);
e_ref = timeseries(u2, 0:0.25:20);
x_star = timeseries([x1';x2';x3';x4';x5';x6'], 0:0.25:20); 

%% Plotting
tu = 0:delta_t:delta_t*(length(u)-1)/2;
tx = 0:delta_t:delta_t*(length(x1)-1);

figure(2)
subplot(511)
stairs(tx,u1),grid
ylabel('p_{ref}')
subplot(512)
stairs(tx,u2),grid
ylabel('e_{ref}')
subplot(513)
plot(tx,x1,'m',tx,x1,'mo'),grid
ylabel('lambda')
subplot(514)
plot(tx,x2,'m',tx,x2','mo'),grid
ylabel('r')
subplot(515)
plot(tx,x5,'m',tx,x5,'mo'),grid
ylabel('elevation')


function [c, c_eq] = non_lil_constraints(z)
    N = 40;
    lambda_t = 2*pi/3;
    alpha = 0.2;
    beta = 20;
    mx = 6;
    
    c = zeros(N, 1);
    for k=0:N-1
        c(k+1) = alpha*exp(-beta*(z(1 +k*mx)-lambda_t)^2) - z(5 +k*mx);
    end
    c_eq = [];
end


% function f = gen_f(z)
%     global N lambda_t q1 q2 mx mu
%     f = 0;
%     for i=0:N-1
%         f = f + (z(1 + i*mx) - lambda_t)^2 + q1*z(mx*N + i*mu)^2 + q2*z(mx*N + i*mu + 1)^2;
%     end
% 
% end
% 




