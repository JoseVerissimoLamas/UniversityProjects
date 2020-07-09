function plotCores(x, y, z, inicio, fim, cor, activityNumber, labels, place)
% cores dos sinais

Fs = 50;                    % frequencia de amostragem
N = length(x);              % tamanho do sinal x
t = linspace(0,N/Fs, N);    % Vetor de tempo sinal x

indice = (inicio+fim)/2;
indice = int16(indice);

subplot(3,1,1);
hold on
plot(t(inicio:fim), x(inicio:fim), cor);
ylim([-2 2]);
text(t(indice), place, labels{1,2}(activityNumber), 'FontSize', 6, 'Interpreter', 'none', 'FontWeight', 'bold','HorizontalAlignment', 'center')
hold off

subplot(3,1,2);
hold on
plot(t(inicio:fim), y(inicio:fim), cor);
ylim([-2 2]);
text(t(indice), place-1, labels{1,2}(activityNumber), 'FontSize', 6, 'Interpreter', 'none', 'FontWeight', 'bold','HorizontalAlignment', 'center')
hold off


subplot(3,1,3);
hold on
plot(t(inicio:fim), z(inicio:fim), cor);
ylim([-2 2]);
text(t(indice), place-0.5, labels{1,2}(activityNumber), 'FontSize', 6, 'Interpreter', 'none', 'FontWeight', 'bold','HorizontalAlignment', 'center')
hold off

end

