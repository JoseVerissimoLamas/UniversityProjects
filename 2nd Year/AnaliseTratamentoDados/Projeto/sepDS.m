% Separa atividades dinamicas de estaticas ( modificacao de sepActivities)

function sepActi = sepDS(x, tipo_mov)
    % Cria uma cell da info do sinal de todas as atividades efetuadas
    y1=1;y2=1;y3=1;
    for i=1:length(tipo_mov)
        
        if(tipo_mov(i,3) <= 3)
            a{1, y1} = x( tipo_mov(i, 4):tipo_mov(i, 5) );
            y1 = y1+1;
        else if(tipo_mov(i,3) <= 6)
            a{2, y2} = x( tipo_mov(i, 4):tipo_mov(i, 5) );
            y2 = y2+1;
            
            else
                a{3, y3} = x( tipo_mov(i, 4):tipo_mov(i, 5) );
                y3 = y3+1;
                
            end
        end
    end
    sepActi = a;
end