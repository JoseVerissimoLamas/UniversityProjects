function [medias] = calculaMediaPassosXYZ(passosX,passosY, passosZ)
% função que calcula as medias de todos os ficheiros

% vê o eixo de x, y e z e calcula a media dos passos dados num movimento de
% cada ficheiro

%medias(1) = (passosX(1,1) + passosY(1,1) + passosZ(1,1))/3;
indice = 1;
medias = zeros(80,1);
for i=1:10
    for j=1:8
        if(passosX(i,j)==0 || passosY(i,j)==0 || passosZ(i,j)==0)
            medias(indice) = 0;
        else
            medias(indice) = (passosX(i,j) + passosY(i,j) + passosZ(i,j))/3;
        end
        indice = indice+1;
    end
end
end

