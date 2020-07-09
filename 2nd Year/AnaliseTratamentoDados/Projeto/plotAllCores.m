function plotAllCores (x, y, z, sinais, inicio, labels, act)

% Funçao que faz plot de todos os movimentos e labels
%{
    stand: magenta
    sit: blue
    lay: green
    
    transicao: yellow
    
    walking: red
    walking down: blue
    walking up: cyan
%}
plotCores(x, y, z, sinais(inicio,1), sinais(inicio,2),'m', act(inicio), labels, 0);
plotCores(x, y, z, sinais(inicio+1,1), sinais(inicio+1,2),'y', act(inicio+1), labels, 1.8);
plotCores(x, y, z, sinais(inicio+2,1), sinais(inicio+2,2),'b', act(inicio+2), labels, 0);
plotCores(x, y, z, sinais(inicio+3,1), sinais(inicio+3,2),'y', act(inicio+3), labels, 1.8);

plotCores(x, y, z, sinais(inicio+4,1), sinais(inicio+4,2),'m', act(inicio+4), labels, 0);
plotCores(x, y, z, sinais(inicio+5,1), sinais(inicio+5,2),'y', act(inicio+5), labels, 1.8);
plotCores(x, y, z, sinais(inicio+6,1), sinais(inicio+6,2),'g', act(inicio+6), labels, 0);
plotCores(x, y, z, sinais(inicio+7,1), sinais(inicio+7,2),'y', act(inicio+7), labels, 1.8);

plotCores(x, y, z, sinais(inicio+8,1), sinais(inicio+8,2),'b', act(inicio+8), labels, 0);
plotCores(x, y, z, sinais(inicio+9,1), sinais(inicio+9,2),'y', act(inicio+9), labels, 1.8);
plotCores(x, y, z, sinais(inicio+10,1), sinais(inicio+10,2),'g', act(inicio+10), labels, 0);
plotCores(x, y, z, sinais(inicio+11,1), sinais(inicio+11,2),'y', act(inicio+11), labels, 1.8);

plotCores(x, y, z, sinais(inicio+12,1), sinais(inicio+12,2),'r', act(inicio+12), labels, 0);
plotCores(x, y, z, sinais(inicio+13,1), sinais(inicio+13,2),'r', act(inicio+13), labels, 1.8);
plotCores(x, y, z, sinais(inicio+14,1), sinais(inicio+14,2),'b', act(inicio+14), labels, 0);
plotCores(x, y, z, sinais(inicio+15,1), sinais(inicio+15,2),'c', act(inicio+15), labels, 1.8);

plotCores(x, y, z, sinais(inicio+16,1), sinais(inicio+16,2),'b', act(inicio+16), labels, 0);
plotCores(x, y, z, sinais(inicio+17,1), sinais(inicio+17,2),'c', act(inicio+17), labels, 1.8);
plotCores(x, y, z, sinais(inicio+18,1), sinais(inicio+18,2),'b', act(inicio+18), labels, 0);
plotCores(x, y, z, sinais(inicio+19,1), sinais(inicio+19,2),'c', act(inicio+19), labels, 1.8);

hold off
end

