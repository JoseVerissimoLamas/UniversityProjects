% Cria o cell array para as atividades
% Vai analizar a informa??o lida no acc31_x (por exemplo), vai verificar as
% diferentes atividades que este tem e separa os sinais
% cell = [  
% {atividade 1, primeira vez que ocorre} {ativ 1, segunda vez} ...
% {atividade 2, primeira vez que ocorre} {ativ 2, segunda vez} ...
% {atividade 3, primeira vez que ocorre} {ativ 3, segunda vez} ...
% {atividade 4, primeira vez que ocorre} {ativ 4, segunda vez} ...
% {atividade 5, primeira vez que ocorre} {ativ 5, segunda vez} ...
% {atividade 6, primeira vez que ocorre} {ativ 6, segunda vez} ...
%                                                                   ]

function sepActi = sepActivities(x, tipo_mov)
    % Cria uma cell da info do sinal de todas as atividades efetuadas
    a = cell(6, 1);
    y1=1;y2=1;y3=1;y4=1;y5=1;y6=1;y7=1;y8=1;y9=1;y10=1;y11=1;y12=1;
    for i=1:length(tipo_mov)
        switch tipo_mov(i, 3)
            case 1
               a{1, y1} = x( tipo_mov(i, 4):tipo_mov(i, 5) );
               y1 = y1+1;
            case 2
               a{2, y2} = x( tipo_mov(i, 4):tipo_mov(i, 5) );
               y2 = y2+1;
            case 3
               a{3, y3} = x( tipo_mov(i, 4):tipo_mov(i, 5) );
               y3 = y3+1;
            case 4
               a{4, y4} = x( tipo_mov(i, 4):tipo_mov(i, 5) );
               y4 = y4+1;
            case 5
               a{5, y5} = x( tipo_mov(i, 4):tipo_mov(i, 5) );
               y5 = y5+1;
            case 6
               a{6, y6} = x( tipo_mov(i, 4):tipo_mov(i, 5) );
               y6 = y6+1;
           case 7
               a{7, y7} = x( tipo_mov(i, 4):tipo_mov(i, 5) );
               y7 = y7+1;
           case 8
               a{8, y8} = x( tipo_mov(i, 4):tipo_mov(i, 5) );
               y8 = y8+1;
           case 9
               a{9, y9} = x( tipo_mov(i, 4):tipo_mov(i, 5) );
               y9 = y9+1;
           case 10
               a{10, y10} = x( tipo_mov(i, 4):tipo_mov(i, 5) );
               y10 = y10+1;
           case 11
               a{11, y11} = x( tipo_mov(i, 4):tipo_mov(i, 5) );
               y11 = y11+1;
           case 12
               a{12, y12} = x( tipo_mov(i, 4):tipo_mov(i, 5) );
               y12 = y12+1;
            otherwise
        end
    end
    sepActi = a;
end