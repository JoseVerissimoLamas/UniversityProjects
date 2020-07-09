function X = DFT(x)
    X = abs(fftshift(fft(x)));
end