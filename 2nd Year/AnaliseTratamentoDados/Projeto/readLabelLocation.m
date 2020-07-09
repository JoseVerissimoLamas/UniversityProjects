function labelLocation = readLabelLocation(filename, inicio, fim)
% Function to read the input files and separate the x, y and z
    data = zeros(fim-inicio+1, 5);
    
    file = fopen(filename);
    line=1;
    tline = fgetl(file);
    %Lê linha a linha e vai separar os diferentes valores
    %e vai acrescenta los a data
    while ischar(tline)
        aux = str2num(tline);
        if aux(1) >= inicio && aux(1) <= fim
            %display(aux);
            for i=1:5
                data(line, i) = aux(i);
            end
            line = line +1;
        end
        tline = fgetl(file);
    end
    
    fclose(file);
    labelLocation = data;
end