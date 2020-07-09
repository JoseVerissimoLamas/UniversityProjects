function pltXYZ(x, y, z, titleName, cor)
% Plot the x, y and z data [acc_x, acc_y, acc_z, plot title]

Fs = 50;                    % frequencia de amostragem
N = length(x);              % tamanho do sinal x
t = linspace(0,N/Fs, N);    % Vetor de tempo sinal x

figure(1);
subplot(3,1,1);
plot(t, x, cor)
ylim([-2 2]);
xticks([0 60 120 180 240 300 360])

title(titleName)
ylabel('ACC_X');
xlabel('time [seconds]');

subplot(3,1,2);
plot(t, y, cor)
ylim([-2 2]);
xticks([0 60 120 180 240 300 360]);
ylabel('ACC_Y');
xlabel('time [seconds]');

subplot(3,1,3);
plot(t, z, cor)
ylim([-2 2]);
xticks([0 60 120 180 240 300 360]);
ylabel('ACC_Z');
xlabel('time [seconds]');

end

