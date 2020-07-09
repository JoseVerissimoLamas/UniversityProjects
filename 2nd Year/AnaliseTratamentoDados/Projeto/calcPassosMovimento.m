function [passosMin] = calcPassosMovimento(sinal, inicio, fim)
% Calcula numero de passos no movimento 
fs = 50;                        % frequencia de amostragem
x = sinal(inicio:fim);          % porção do sinal que contém o movimento 

X = fftshift(fft(x.*hamming(length(x))));           % DFT do sinal
N = numel(x);                   % periodo fundamental do sinal

% calcular o vetor de frequências
if(mod(N,2) == 0)
    % se o número de pontos do sinal for par
    f = -fs/2 : fs/N : fs/2-fs/N;
else
    % se o número de pontos do sinal for ímpar
    f = -fs/2 + fs/(2*N) : fs/N : fs/2 - fs/(2*N);
end

m_X = abs(X);                   % magnitude do sinal com ruído
%t = linspace(0, (N-1)/fs, N);  % vetor de tempo

%{
figure(2);
plot(f,m_X), hold on
title('|DFT| do sinal')
ylabel('Magnitude = |X|')
xlabel('f [Hz]')
axis tight
hold on
%}

% for debug, replace "~" with peaks

%[peaks,loc] = findpeaks(m_X, 'MinPeakHeight', 1); % nao dinamicas
%[peaks,loc] = findpeaks(m_X, 'MinPeakProminence', 5); % transicoes
[~,loc] = findpeaks(m_X, 'MinPeakProminence', 10); % dinamicas

% frequencias dos picos
%disp(f(loc))

% encontrar os picos com frequencia maior que 0
f(loc) = round(f(loc), 5);
indiceLoc = find(f(loc)>0);

%{
plot(f,m_X), hold on
plot(f(loc(indiceLoc(1))),61.33,'ro')
title('|DFT| do sinal')
ylabel('Magnitude = |X|')
xlabel('f [Hz]')
axis tight
hold off;
pause;
%}
if(~length(indiceLoc)==0)
    
    passosPorSegundo = 1/f(loc(indiceLoc(1)));

    passosMin = passosPorSegundo*60;
else
    passosMin = 0;
end
%disp(passosMin)
end

