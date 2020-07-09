function [stft, f, t] = STFT(x, win, h, nfft, fs)
    % // Short Time Fourier Transform (STFT) //
    % x : sinal
    % win : analysis window function (?)
    % h : salto/ step
    % nfft : numero de pontos do dft
    % fs : frequencia da amostragem

    % f : frequencia do vetor
    % t : vetor tempo, em segundos
    %representaçao do sinal num vetor-coluna
    x = x(:);
    %determinaçao da largura do sinal e da janela
    xlen = length(x);
    wlen = length(win);
    %tamanho da matriz stft e prellocation
    NUP = ceil((1+nfft)/2);     %calcula o numb de pontos unicos no fft
    L = 1+fix((xlen-wlen)/h);   %calc o numb de frames do sinal
    stft = zeros(NUP, L);       %preallocar a matriz sftf 
    % stft via time localized FFT
    for l=0:L-1
        %windowing
        xw = x(1+l*h:wlen+l*h).*win;
        %fft
        X = fft(xw, nfft);
        
        stft(:,1+l) = X(1:NUP);
    end
    %calculo dos vetores da freq e do tempo
    t = (wlen/2:hop:wlen/2+(L-1)*hop)/fs;
    f = (0:NUP-1)*fs/nfft;
end

