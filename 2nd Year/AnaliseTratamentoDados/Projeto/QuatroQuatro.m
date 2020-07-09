function QuatroQuatro(sepDFT_x, sepDFT_y, sepDFT_z)
    function P = potencia(sep)
        N = numel(sep);
        P = sum(sep.^2)/N;
    end
    
    function plotMaker(sepX, sepY, sepZ, cor)
        Px = potencia(sepX);
        Py = potencia(sepY);
        Pz = potencia(sepZ);

        title('Diferenciação de atividades');
        xlabel('X');
        ylabel('Y');
        zlabel('N');
        plot3(Px, Py, Pz, cor);
        hold on;
    end

    sz = size(sepDFT_x);
    cor = 'g.';
    for i=1:sz(1)
        for j=1:sz(2)
            if(i==4 || i==5 || i==6)
                cor = 'r.';
            elseif(i>6)
                cor = 'b.';
            end
            plotMaker(sepDFT_x{i, j}, sepDFT_y{i, j}, sepDFT_z{i, j}, cor)
        end
    end

end