function viewWindow(x,win)
fs = 50;
N  = size(x,1);

% calcular o vetor de frequencias
if(mod(N,2) == 0)
    % se o numero de pontos do sinal for par
    f = -fs/2 : fs/N : fs/2-fs/N;
else
    % se o numero de pontos do sinal for impar
    f = -fs/2 + fs/(2*N) : fs/N : fs/2 - fs/(2*N);
end
    
values = window(win,length(x));
    
figure()
hold on
plot(f,x),'k') %sinal sem window
plot(f,values,'r') %window
plot(f,x.*values),'y') %sinal com window
hold off
end

