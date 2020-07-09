% Cria o cell array do DFT do sepActivities

function sepDFT = sepActi_DFT(sepActi)
    sepDFT = sepActi;
    sz = size(sepDFT);
    for i=1:sz(1)
        for j=1:sz(2)
            sepDFT{i, j} = abs(fftshift(fft(sepActi{i, j}.*hamming(length(sepActi{i, j})))));
        end
    end
end