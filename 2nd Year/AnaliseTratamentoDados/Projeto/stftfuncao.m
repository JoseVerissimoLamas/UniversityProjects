function stftfuncao(signal)

fs = 50;
N = numel(signal);
framePercent = 0.02;                                % sobreposicao das janelas em percentagem
Nframe = round(framePercent*N);                     % numero de amostras por janela
Noverlap = Nframe/framePercent-N+round(Nframe/2);   % numero de amostras sobrepostas

h = hamming(Nframe);                                % janela de hamming para suavizar a segmentacao

X = fftshift(fft(signal));                          % DFT do sinal

signal = detrend(signal, 'constant');
STFT = [];

nfft = 2^ceil(log2(Nframe));
freqRes = fs/nfft;
f=(0:nfft/2)*freqRes;

ncol = fix((N-Noverlap)/(Nframe-Noverlap));
colonIndexs = (0:(ncol-1))*(Nframe-Noverlap);

ts = (colonIndexs)/fs;
ts = ts./60;            % para minutos

for kk = 1:Nframe-Noverlap:N-Nframe
    %Aplicar a janela ao sinal do tempo
    x_frame = signal(kk:kk+Nframe-1).*h;
    
    %Calcular a dft para a janela em questao
    m_X_frame = abs((fft(x_frame,nfft)));
    
    %Considerar apenas a parte positiva da dft
    m_X_frame = m_X_frame(1:end/2+1);
    
    %Guardar os valores de cada janela
    STFT = [STFT m_X_frame];
end

figure()
spectrogram(signal, Nframe, Noverlap, [], fs, 'yaxis');
hold on
STFT = abs(STFT);
STFT = 20*log10(STFT + 1e-6)-40;                        % conversao para decibeis
surf(ts, f, STFT);                                      % plot 3d
shading interp                                          % Ajuste a palete de cores utilizada na representacao
axis tight
xlabel('Time [Mins]')
ylabel('f [Hz]')
title('STFT por janelas');

end

