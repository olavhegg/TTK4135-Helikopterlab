%close all;

%data er navnet på det feks filen til testen heter i workspacet når den er
%loadet

figure;
%sgtitle("Test 1");

subplot(5, 1, 1);
title("Manipulated variable u");
hold on;
plot(data(1, :), data(2,:));
grid on;
box on;
xlabel("Time [s]");
ylabel("u [rad]");
legend("u");


subplot(5, 1, 2);
title("Travel");
hold on;
plot(data(1, :), data(3,:));
grid on;
box on;
xlabel("Time [s]");
ylabel("lambda [rad]");
hold off;
legend("lambda"); 



subplot(5, 1, 3);
title("Travel rate");
hold on;
plot(data(1, :), data(4,:));
grid on;
box on;
xlabel("Time [s]");
ylabel("r [rad/s]");
hold off;
legend("r"); 


subplot(5, 1, 4);
title("Pitch");
hold on;
plot(data(1, :), data(5,:));
grid on;
box on;
xlabel("Time [s]");
ylabel("p [rad]");
hold off;
legend("p"); 

subplot(5, 1, 5);
title("Pitch rate");
hold on;
plot(data(1, :), data(6,:));
grid on;
box on;
xlabel("Time [s]");
ylabel("pdot [rad/s]");
hold off;
legend("pdot"); 