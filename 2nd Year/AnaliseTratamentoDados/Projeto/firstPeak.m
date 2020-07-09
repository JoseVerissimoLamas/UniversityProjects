function peak = firstPeak(sinal,inicio,fim,type)

x = sinal(inicio:fim);
fs = 50;
N = numel(x);

X = fftshift(fft(x));

%calcular o vector de frequencia
if(mod(N,2)==0)
    % se o numero de pontos do sinal for par
    f = -fs/2:fs/N:fs/2-fs/N;
else
    %se o numero de pontos do sinal for impar
    f = -fs/2+fs/(2*N):fs/N:fs/2-fs/(2*N);
end

m_X = abs(X);

switch(type)
    case 1
        [peaks,locs] = findpeaks(m_X, 'MinPeakProminence', 10); % dinamicas
    case 2
        [peaks,locs] = findpeaks(m_X, 'MinPeakHeight', 1); % nao dinamicas
    case 3
        [peaks,locs] = findpeaks(m_X, 'MinPeakProminence', 5); % transicoes
    otherwise
end


f_relevant = f(locs);
f_relevant = f_relevant(f_relevant>0);  %frequencias relevantes sao > 0
round(f_relevant,5);

if(~isempty(f_relevant))
    peak = f_relevant(1);
else
    peak = 0;
end

% figure()
% hold on
% plot(f,m_X);
% plot(peak,m_X(f == peak),'ro');
% plot(f(locs),peaks,'rx');
% 
% hold off