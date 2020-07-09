function [sinal] = readInput(fileName)
% Function to read the input files and separate the x, y and z

file = fopen(fileName);
data = textscan(file, '%f%f%f', 'Delimiter', ' ');
fclose(file);

%x = data{1};
%y = data{2};
%z = data{3};

sinal = data;

end

