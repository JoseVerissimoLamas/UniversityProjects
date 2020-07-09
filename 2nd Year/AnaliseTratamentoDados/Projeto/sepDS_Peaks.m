% Cria o cell array dos peaks

function sepPeaks = sepDS_Peaks(sepActi)
    sepPeaks = sepActi;
    sz = size(sepPeaks);
    for i=1:sz(1)
        for j=1:sz(2)
            x=sepActi{i, j};
            if(~isempty(x))
                x = x .* hamming(numel(x));
                sepPeaks{i, j} = firstPeak(x,1,length(x),i);
            end
        end
    end
end