% Projeto ATD 2019 Turma: PL4

% Descricao dos ficheiros de aceleracao:
% The raw triaxial acceleration signal for the experiment number XX and associated to the user number YY. 
% Every row is one acceleration sample (three axis) captured at a frequency of 50Hz. 


% ================ Informacao extra =================================

%frequency = 50;

% labels
fileLabels = fopen('Data/activity_labels.txt');
labels = textscan(fileLabels, '%d %s', 'Delimiter', '\n'); % index of activity and label
fclose(fileLabels);

% numero de atividade, e atividade
%disp(labels{1,1}(2)) % numero da atividade
%disp(labels{1,2}(2)) % atividade label

% labels location file
labelLocation = readLabelLocation("Data/labels.txt", 31, 40);

% inicio e fim dos sinais
sinaisLocation(:,1) = labelLocation(:,4); % inicio
sinaisLocation(:,2) = labelLocation(:,5); % fim

activities(:,1) = labelLocation(:, 3); % numero da atividade

% variavel sinais contem sinais das experiencias
% exemplo: sinais31{1} = experiencia 31 no eixo de x

% ================ Importar os sinais =================================

% --- acc_exp31_user15.txt
sinais31 = readInput('Data/acc_exp31_user15.txt');

% --- acc_exp32_user16.txt
sinais32 = readInput('Data/acc_exp32_user16.txt');

% --- acc_exp33_user16.txt
sinais33 = readInput('Data/acc_exp33_user16.txt');

% --- acc_exp34_user17.txt
sinais34 = readInput('Data/acc_exp34_user17.txt');

% --- acc_exp35_user17.txt
sinais35 = readInput('Data/acc_exp35_user17.txt');

% --- acc_exp36_user18.txt
sinais36 = readInput('Data/acc_exp36_user18.txt');

% --- acc_exp37_user18.txt
sinais37 = readInput('Data/acc_exp37_user18.txt');

% --- acc_exp38_user19.txt
sinais38 = readInput('Data/acc_exp38_user19.txt');

% --- acc_exp39_user19.txt
sinais39 = readInput('Data/acc_exp39_user19.txt');

% --- acc_exp40_user20.txt
sinais40 = readInput('Data/acc_exp40_user20.txt');

% ================ Plot dos sinais ===============

% --- acc_exp31_user15.txt

disp('Plot de Experiencia 31, User 15')
pltXYZ(sinais31{1}, sinais31{2}, sinais31{3}, "Exp 31 User 15", 'k');

% separacao de movimentos
plotAllCores(sinais31{1}, sinais31{2}, sinais31{3}, sinaisLocation, 1, labels, activities);
pause;


% --- acc_exp32_user16.txt

disp('Plot de Experiencia 32, User 16')
pltXYZ(sinais32{1}, sinais32{2}, sinais32{3}, 'Exp 32 User 16', 'k');

% separacao de movimentos
plotAllCores(sinais32{1}, sinais32{2}, sinais32{3}, sinaisLocation, 21, labels, activities);
pause;

% --- acc_exp33_user16.txt

disp('Plot de Experiencia 33, User 16')
pltXYZ(sinais33{1}, sinais33{2}, sinais33{3}, 'Exp 33 User 16', 'k');

% separacao de movimentos
plotAllCores(sinais33{1}, sinais33{2}, sinais33{3}, sinaisLocation, 41, labels, activities);
pause;

% --- acc_exp34_user17.txt

disp('Plot de Experiencia 34, User 17')
pltXYZ(sinais34{1}, sinais34{2}, sinais34{3}, 'Exp 34 User 17', 'k');

% separacao de movimentos
plotAllCores(sinais34{1}, sinais34{2}, sinais34{3}, sinaisLocation, 61, labels, activities);
pause;

% --- acc_exp35_user17.txt

disp('Plot de Experiencia 35, User 17')
pltXYZ(sinais35{1}, sinais35{2}, sinais35{3}, 'Exp 35 User 17', 'k');

% separacao de movimentos
plotAllCores(sinais35{1}, sinais35{2}, sinais35{3}, sinaisLocation, 81, labels, activities);
pause;

% --- acc_exp36_user18.txt

disp('Plot de Experiencia 36, User 18')
pltXYZ(sinais36{1}, sinais36{2}, sinais36{3}, 'Exp 36 User 18', 'k');

% separacao de movimentos
plotAllCores(sinais36{1}, sinais36{2}, sinais36{3}, sinaisLocation, 101, labels, activities);
pause;

% --- acc_exp37_user18.txt

disp('Plot de Experiencia 37, User 18')
pltXYZ(sinais37{1}, sinais37{2}, sinais37{3}, 'Exp 37 User 18', 'k');

% separacao de movimentos
plotAllCores(sinais37{1}, sinais37{2}, sinais37{3}, sinaisLocation, 121, labels, activities);
pause;

% --- acc_exp38_user19.txt

disp('Plot de Experiencia 38, User 19')
pltXYZ(sinais38{1}, sinais38{2}, sinais38{3}, 'Exp 38 User 19', 'k');

% separacao de movimentos
plotAllCores(sinais38{1}, sinais38{2}, sinais38{3}, sinaisLocation, 141, labels, activities);
pause;

% --- acc_exp39_user19.txt

disp('Plot de Experiencia 39, User 19')
pltXYZ(sinais39{1}, sinais39{2}, sinais39{3}, 'Exp 39 User 19', 'k');

% separacao de movimentos
plotAllCores(sinais39{1}, sinais39{2}, sinais39{3}, sinaisLocation, 161, labels, activities);
pause;

% --- acc_exp40_user20.txt

disp('Plot de Experiencia 40, User 20')
pltXYZ(sinais40{1}, sinais40{2}, sinais40{3}, 'Exp 40 User 20', 'k');

% separacao de movimentos
plotAllCores(sinais40{1}, sinais40{2}, sinais40{3}, sinaisLocation, 181, labels, activities);
pause;


% ==================== Ex 4.1 ====================

%viewWindow(sinais31{1}(sinaisLocation(13,1):sinaisLocation(13,2)), @hamming);

% ==================== Ex 4.2 ====================


% calculo do numero de passos por minuto de todos os ficheiros
disp('calculo passos por minuto')
% passos de todos os ficheiros nos diferentes eixos
[passosX, passosY, passosZ] = calculaPassosDinamicos(sinais31, sinais32, sinais33, sinais34, sinais35, sinais36, sinais37, sinais38, sinais39, sinais40, sinaisLocation);

% ----- medias de eixos separados
% walkings eixo x
walkingsX = [passosX(1) passosX(2) passosX(9) passosX(10) passosX(17) passosX(18) passosX(25) passosX(26) passosX(33) passosX(34) passosX(41) passosX(42) passosX(49) passosX(50) passosX(57) passosX(58) passosX(65) passosX(66) passosX(73) passosX(74)];
mediaWalkingX = sum(walkingsX) /sum(walkingsX~=0);
% desvio walkings eixo x
desvioWalkingsX = std(walkingsX);

% walkings eixo y
walkingsY = [passosY(1) passosY(2) passosY(9) passosY(10) passosY(17) passosY(18) passosY(25) passosY(26) passosY(33) passosY(34) passosY(41) passosY(42) passosY(49) passosY(50) passosY(57) passosY(58) passosY(65) passosY(66) passosY(73) passosY(74)];
mediaWalkingY = sum(walkingsY) /sum(walkingsY~=0);
% desvio walkings eixo y
desvioWalkingsY = std(walkingsY);

% walkings eixo z
walkingsZ = [passosZ(1) passosZ(2) passosZ(9) passosZ(10) passosZ(17) passosZ(18) passosZ(25) passosZ(26) passosZ(33) passosZ(34) passosZ(41) passosZ(42) passosZ(49) passosZ(50) passosZ(57) passosZ(58) passosZ(65) passosZ(66) passosZ(73) passosZ(74)];
mediaWalkingZ = sum(walkingsZ) /sum(walkingsZ~=0);
% desvio walkings eixo z
desvioWalkingsZ = std(walkingsZ);

% walking down eixo x
walkingDownX = [passosX(3) passosX(5) passosX(7) passosX(11) passosX(13) passosX(15) passosX(19) passosX(21) passosX(23) passosX(27) passosX(29) passosX(31) passosX(35) passosX(37) passosX(39) passosX(43) passosX(45) passosX(47) passosX(51) passosX(53) passosX(55) passosX(59) passosX(61) passosX(63) passosX(67) passosX(69) passosX(71) passosX(75) passosX(77) passosX(79)];
mediaWalkingDX = sum(walkingDownX) /sum(walkingDownX~=0);
% desvio walking down eixo X
desvioWalkingDownX = std(walkingDownX);

% walking down eixo y
walkingDownY = [passosY(3) passosY(5) passosY(7) passosY(11) passosY(13) passosY(15) passosY(19) passosY(21) passosY(23) passosY(27) passosY(29) passosY(31) passosY(35) passosY(37) passosY(39) passosY(43) passosY(45) passosY(47) passosY(51) passosY(53) passosY(55) passosY(59) passosY(61) passosY(63) passosY(67) passosY(69) passosY(71) passosY(75) passosY(77) passosY(79)];
mediaWalkingDY = sum(walkingDownY) /sum(walkingDownY~=0);
% desvio walking down eixo Y
desvioWalkingDownY = std(walkingDownY);

% walking down eixo z
walkingDownZ = [passosZ(3) passosZ(5) passosZ(7) passosZ(11) passosZ(13) passosZ(15) passosZ(19) passosZ(21) passosZ(23) passosZ(27) passosZ(29) passosZ(31) passosZ(35) passosZ(37) passosZ(39) passosZ(43) passosZ(45) passosZ(47) passosZ(51) passosZ(53) passosZ(55) passosZ(59) passosZ(61) passosZ(63) passosZ(67) passosZ(69) passosZ(71) passosZ(75) passosZ(77) passosZ(79)];
mediaWalkingDZ = sum(walkingDownZ) /sum(walkingDownZ~=0);
% desvio walking down eixo Y
desvioWalkingDownZ = std(walkingDownZ);

% walking up eixo x
walkingUpX = [passosX(4) passosX(6) passosX(8) passosX(12) passosX(14) passosX(16) passosX(20) passosX(22) passosX(24) passosX(28) passosX(30) passosX(32) passosX(36) passosX(38) passosX(40) passosX(44) passosX(46) passosX(48) passosX(52) passosX(54) passosX(56) passosX(60) passosX(62) passosX(64) passosX(68) passosX(70) passosX(72) passosX(76) passosX(78) passosX(80)];
mediaWalkingUX = sum(walkingUpX) /sum(walkingUpX~=0);
% desvio walking down eixo Y
desvioWalkingUpX = std(walkingUpX);

% walking up eixo y
walkingUpY = [passosY(4) passosY(6) passosY(8) passosY(12) passosY(14) passosY(16) passosY(20) passosY(22) passosY(24) passosY(28) passosY(30) passosY(32) passosY(36) passosY(38) passosY(40) passosY(44) passosY(46) passosY(48) passosY(52) passosY(54) passosY(56) passosY(60) passosY(62) passosY(64) passosY(68) passosY(70) passosY(72) passosY(76) passosY(78) passosY(80)];
mediaWalkingUY = sum(walkingUpY) /sum(walkingUpY~=0);
% desvio walking down eixo Y
desvioWalkingUpY = std(walkingUpY);

% walking up eixo z
walkingUpZ = [passosZ(4) passosZ(6) passosZ(8) passosZ(12) passosZ(14) passosZ(16) passosZ(20) passosZ(22) passosZ(24) passosZ(28) passosZ(30) passosZ(32) passosZ(36) passosZ(38) passosZ(40) passosZ(44) passosZ(46) passosZ(48) passosZ(52) passosZ(54) passosZ(56) passosZ(60) passosZ(62) passosZ(64) passosZ(68) passosZ(70) passosZ(72) passosZ(76) passosZ(78) passosZ(80)];
mediaWalkingUZ = sum(walkingUpZ) /sum(walkingUpZ~=0);
% desvio walking down eixo Y
desvioWalkingUpZ = std(walkingUpZ);


fprintf("Media walking\nEixo X: %.4f\nEixo Y: %.4f\nEixoZ: %.4f\n\n",mediaWalkingX, mediaWalkingY, mediaWalkingZ);
fprintf("Desvio walking\nEixo X: %.4f\nEixo Y: %.4f\nEixoZ: %.4f\n\n\n",desvioWalkingsX, desvioWalkingsY, desvioWalkingsZ);

fprintf("Media walking Down\nEixo X: %.4f\nEixo Y: %.4f\nEixoZ: %.4f\n\n",mediaWalkingDX, mediaWalkingDY, mediaWalkingDZ);
fprintf("Desvio walking Down\nEixo X: %.4f\nEixo Y: %.4f\nEixoZ: %.4f\n\n\n",desvioWalkingDownX, desvioWalkingDownY, desvioWalkingDownZ);

fprintf("Media walking Up\nEixo X: %.4f\nEixo Y: %.4f\nEixoZ: %.4f\n\n",mediaWalkingUX, mediaWalkingUY, mediaWalkingUZ);
fprintf("Desvio walking Up\nEixo X: %.4f\nEixo Y: %.4f\nEixoZ: %.4f\n\n\n",desvioWalkingUpX, desvioWalkingUpY, desvioWalkingUpZ);
pause;

% medias apenas dos eixos (x,y,z) -> um valor medio
medias = calculaMediaPassosXYZ(passosX, passosY, passosZ);

% ----- medias dos passos em todos os ficheiros
passosMedios = zeros(10,1);
passosMedios(1) = sum(medias(1:8)) / sum(medias(1:8)~=0);
passosMedios(2) = sum(medias(9:16)) / sum(medias(9:16)~=0);
passosMedios(3) = sum(medias(17:24)) / sum(medias(17:24)~=0);
passosMedios(4) = sum(medias(25:32)) / sum(medias(25:32)~=0);
passosMedios(5) = sum(medias(33:40)) / sum(medias(33:40)~=0);
passosMedios(6) = sum(medias(41:48)) / sum(medias(41:48)~=0);
passosMedios(7) = sum(medias(49:56)) / sum(medias(49:56)~=0);
passosMedios(8) = sum(medias(57:64)) / sum(medias(57:64)~=0);
passosMedios(9) = sum(medias(65:72)) / sum(medias(65:72)~=0);
passosMedios(10) = sum(medias(73:80)) / sum(medias(73:80)~=0);
%disp(passosMedios)

% media de walkings de todos os ficheiros
walkings = [medias(1) medias(2) medias(9) medias(10) medias(17) medias(18) medias(25) medias(26) medias(33) medias(34) medias(41) medias(42) medias(49) medias(50) medias(57) medias(58) medias(65) medias(66) medias(73) medias(74)];
mediaTotalWalking = sum(walkings)/sum(walkings~=0);

% media de walking down's de todos os ficheiros
walkingDowns = [medias(3) medias(5) medias(7) medias(11) medias(13) medias(15) medias(19) medias(21) medias(23) medias(27) medias(29) medias(31) medias(35) medias(37) medias(39) medias(43) medias(45) medias(47) medias(51) medias(53) medias(55) medias(59) medias(61) medias(63) medias(67) medias(69) medias(71) medias(75) medias(77) medias(79)];
mediaTotalWalkingDown = sum(walkingDowns)/sum(walkingDowns~=0);

% media de walking up's de todos os ficheiros
walkingUps = [medias(4) medias(6) medias(8) medias(12) medias(14) medias(16) medias(20) medias(22) medias(24) medias(28) medias(30) medias(32) medias(36) medias(38) medias(40) medias(44) medias(46) medias(48) medias(52) medias(54) medias(56) medias(60) medias(62) medias(64) medias(68) medias(70) medias(72) medias(76) medias(78) medias(80)];
mediaTotalWalkingUp = sum(walkingUps)/sum(walkingUps~=0);

% desvio movimentos isolados
desvioWalkings = std(walkings);
desvioWU = std(walkingUps);
desvioWD = std(walkingDowns);

% desvio padrao de todos os ficheiros
desvio1 = std(medias(1:8));
desvio2 = std(medias(9:16));
desvio3 = std(medias(17:24));
desvio4 = std(medias(25:32));
desvio5 = std(medias(33:40));
desvio6 = std(medias(41:48));
desvio7 = std(medias(49:56));
desvio8 = std(medias(57:64));
desvio9 = std(medias(65:72));
desvio10 = std(medias(73:80));

% ---------- tabela ----------
% ficheiros
arrayFicheiros = zeros(80,1);
arrayFicheiros(1:8) = 31;
arrayFicheiros(9:16) = 32;
arrayFicheiros(17:24) = 33;
arrayFicheiros(25:32) = 34;
arrayFicheiros(33:40) = 35;
arrayFicheiros(41:48) = 36;
arrayFicheiros(49:56) = 37;
arrayFicheiros(57:64) = 38;
arrayFicheiros(65:72) = 39;
arrayFicheiros(73:80) = 40;

% atividades
atividades = ["walking" "walking" "walking down" "walking up" "walking down" "walking up" "walking down" "walking up"]';
arrayAtividades = repmat(atividades, 10,1);

% medias
mediasTabela = zeros(80,1);
mediasTabela(1:8) = passosMedios(1);
mediasTabela(9:16) = passosMedios(2);
mediasTabela(17:24) = passosMedios(3);
mediasTabela(25:32) = passosMedios(4);
mediasTabela(33:40) = passosMedios(5);
mediasTabela(41:48) = passosMedios(6);
mediasTabela(49:56) = passosMedios(7);
mediasTabela(57:64) = passosMedios(8);
mediasTabela(65:72) = passosMedios(9);
mediasTabela(73:80) = passosMedios(10);

% desvios
desviosTabela = zeros(80,1);
desviosTabela(1:8) = desvio1;
desviosTabela(9:16) = desvio2;
desviosTabela(17:24) = desvio3;
desviosTabela(25:32) = desvio4;
desviosTabela(33:40) = desvio5;
desviosTabela(41:48) = desvio6;
desviosTabela(49:56) = desvio7;
desviosTabela(57:64) = desvio8;
desviosTabela(65:72) = desvio9;
desviosTabela(73:80) = desvio10;

% por o numero de passos num array unidimensional
stepsX = reshape(passosX',1,numel(passosX));
stepsY = reshape(passosY',1,numel(passosY));
stepsZ = reshape(passosZ',1,numel(passosZ));
tabela = table(arrayFicheiros, arrayAtividades, stepsX', stepsY', stepsZ', mediasTabela, desviosTabela, 'VariableNames',{'Experiencia','Atividade','Eixo_X','Eixo_Y','Eixo_Z','Media_Exp','Desvios_Exp'});
disp("Tabela de valores experimentais")
% considerando medias de eixos para apenas um valor
disp(tabela)

disp("Tabela de medias e desvios de movimentos")
% considerando medias de eixos para apenas um valor
tabela2 = table(mediaTotalWalking, mediaTotalWalkingDown, mediaTotalWalkingUp, desvioWalkings, desvioWD, desvioWU, 'VariableNames', {'Media_W', 'Media_WD', 'Media_WU', 'Desvio_W', 'Desvio_WD', 'Desvio_WU'});
disp(tabela2)
pause;


% ==================== Ex 4.3 ====================
disp("Exercício 4.3");
arrayXD=[];
arrayYD=[];
arrayZD=[];
arrayXS=[];
arrayYS=[];
arrayZS=[];
arrayXT=[];
arrayYT=[];
arrayZT=[];

Fs = 50;    % Frequencia de amostragem

%sinal31
tipo_mov = readLabelLocation('Data/labels.txt', 31, 31);
% Cria um cell array onde separa as atividades em cada cell
%Dinamicas : linha 1
%Estaticas : linha 2
sepActi_x = sepDS(sinais31{1,1}, tipo_mov);
sepActi_y = sepDS(sinais31{1,2}, tipo_mov);
sepActi_z = sepDS(sinais31{1,3}, tipo_mov);
sepPeak_x = sepDS_Peaks(sepActi_x);
sepPeak_y = sepDS_Peaks(sepActi_y);
sepPeak_z = sepDS_Peaks(sepActi_z);

arrayXD= cat(1,arrayXD,cat(1,sepPeak_x{1,:}));
arrayYD= cat(1,arrayYD,cat(1,sepPeak_y{1,:}));
arrayZD= cat(1,arrayZD,cat(1,sepPeak_z{1,:}));
arrayXS= cat(1,arrayXS,cat(1,sepPeak_x{2,:}));
arrayYS= cat(1,arrayYS,cat(1,sepPeak_y{2,:}));
arrayZS= cat(1,arrayZS,cat(1,sepPeak_z{2,:}));
arrayXT= cat(1,arrayXT,cat(1,sepPeak_x{3,:}));
arrayYT= cat(1,arrayYT,cat(1,sepPeak_y{3,:}));
arrayZT= cat(1,arrayZT,cat(1,sepPeak_z{3,:}));

%sinal 32
tipo_mov = readLabelLocation('Data/labels.txt', 32, 32);
sepActi_x = sepDS(sinais32{1,1}, tipo_mov);
sepActi_y = sepDS(sinais32{1,2}, tipo_mov);
sepActi_z = sepDS(sinais32{1,3}, tipo_mov);
sepPeak_x = sepDS_Peaks(sepActi_x);
sepPeak_y = sepDS_Peaks(sepActi_y);
sepPeak_z = sepDS_Peaks(sepActi_z);

arrayXD= cat(1,arrayXD,cat(1,sepPeak_x{1,:}));
arrayYD= cat(1,arrayYD,cat(1,sepPeak_y{1,:}));
arrayZD= cat(1,arrayZD,cat(1,sepPeak_z{1,:}));
arrayXS= cat(1,arrayXS,cat(1,sepPeak_x{2,:}));
arrayYS= cat(1,arrayYS,cat(1,sepPeak_y{2,:}));
arrayZS= cat(1,arrayZS,cat(1,sepPeak_z{2,:}));
arrayXT= cat(1,arrayXT,cat(1,sepPeak_x{3,:}));
arrayYT= cat(1,arrayYT,cat(1,sepPeak_y{3,:}));
arrayZT= cat(1,arrayZT,cat(1,sepPeak_z{3,:}));

%sinal 33
tipo_mov = readLabelLocation('Data/labels.txt', 33, 33);
sepActi_x = sepDS(sinais33{1,1}, tipo_mov);
sepActi_y = sepDS(sinais33{1,2}, tipo_mov);
sepActi_z = sepDS(sinais33{1,3}, tipo_mov);
sepPeak_x = sepDS_Peaks(sepActi_x);
sepPeak_y = sepDS_Peaks(sepActi_y);
sepPeak_z = sepDS_Peaks(sepActi_z);

arrayXD= cat(1,arrayXD,cat(1,sepPeak_x{1,:}));
arrayYD= cat(1,arrayYD,cat(1,sepPeak_y{1,:}));
arrayZD= cat(1,arrayZD,cat(1,sepPeak_z{1,:}));
arrayXS= cat(1,arrayXS,cat(1,sepPeak_x{2,:}));
arrayYS= cat(1,arrayYS,cat(1,sepPeak_y{2,:}));
arrayZS= cat(1,arrayZS,cat(1,sepPeak_z{2,:}));
arrayXT= cat(1,arrayXT,cat(1,sepPeak_x{3,:}));
arrayYT= cat(1,arrayYT,cat(1,sepPeak_y{3,:}));
arrayZT= cat(1,arrayZT,cat(1,sepPeak_z{3,:}));

%sinal 34
tipo_mov = readLabelLocation('Data/labels.txt', 34, 34);
sepActi_x = sepDS(sinais34{1,1}, tipo_mov);
sepActi_y = sepDS(sinais34{1,2}, tipo_mov);
sepActi_z = sepDS(sinais34{1,3}, tipo_mov);
sepPeak_x = sepDS_Peaks(sepActi_x);
sepPeak_y = sepDS_Peaks(sepActi_y);
sepPeak_z = sepDS_Peaks(sepActi_z);

arrayXD= cat(1,arrayXD,cat(1,sepPeak_x{1,:}));
arrayYD= cat(1,arrayYD,cat(1,sepPeak_y{1,:}));
arrayZD= cat(1,arrayZD,cat(1,sepPeak_z{1,:}));
arrayXS= cat(1,arrayXS,cat(1,sepPeak_x{2,:}));
arrayYS= cat(1,arrayYS,cat(1,sepPeak_y{2,:}));
arrayZS= cat(1,arrayZS,cat(1,sepPeak_z{2,:}));
arrayXT= cat(1,arrayXT,cat(1,sepPeak_x{3,:}));
arrayYT= cat(1,arrayYT,cat(1,sepPeak_y{3,:}));
arrayZT= cat(1,arrayZT,cat(1,sepPeak_z{3,:}));

%sinal 35
tipo_mov = readLabelLocation('Data/labels.txt', 35, 35);
sepActi_x = sepDS(sinais35{1,1}, tipo_mov);
sepActi_y = sepDS(sinais35{1,2}, tipo_mov);
sepActi_z = sepDS(sinais35{1,3}, tipo_mov);
sepPeak_x = sepDS_Peaks(sepActi_x);
sepPeak_y = sepDS_Peaks(sepActi_y);
sepPeak_z = sepDS_Peaks(sepActi_z);

arrayXD= cat(1,arrayXD,cat(1,sepPeak_x{1,:}));
arrayYD= cat(1,arrayYD,cat(1,sepPeak_y{1,:}));
arrayZD= cat(1,arrayZD,cat(1,sepPeak_z{1,:}));
arrayXS= cat(1,arrayXS,cat(1,sepPeak_x{2,:}));
arrayYS= cat(1,arrayYS,cat(1,sepPeak_y{2,:}));
arrayZS= cat(1,arrayZS,cat(1,sepPeak_z{2,:}));
arrayXT= cat(1,arrayXT,cat(1,sepPeak_x{3,:}));
arrayYT= cat(1,arrayYT,cat(1,sepPeak_y{3,:}));
arrayZT= cat(1,arrayZT,cat(1,sepPeak_z{3,:}));

%sinal 36
tipo_mov = readLabelLocation('Data/labels.txt', 36, 36);
sepActi_x = sepDS(sinais36{1,1}, tipo_mov);
sepActi_y = sepDS(sinais36{1,2}, tipo_mov);
sepActi_z = sepDS(sinais36{1,3}, tipo_mov);
sepPeak_x = sepDS_Peaks(sepActi_x);
sepPeak_y = sepDS_Peaks(sepActi_y);
sepPeak_z = sepDS_Peaks(sepActi_z);

arrayXD= cat(1,arrayXD,cat(1,sepPeak_x{1,:}));
arrayYD= cat(1,arrayYD,cat(1,sepPeak_y{1,:}));
arrayZD= cat(1,arrayZD,cat(1,sepPeak_z{1,:}));
arrayXS= cat(1,arrayXS,cat(1,sepPeak_x{2,:}));
arrayYS= cat(1,arrayYS,cat(1,sepPeak_y{2,:}));
arrayZS= cat(1,arrayZS,cat(1,sepPeak_z{2,:}));
arrayXT= cat(1,arrayXT,cat(1,sepPeak_x{3,:}));
arrayYT= cat(1,arrayYT,cat(1,sepPeak_y{3,:}));
arrayZT= cat(1,arrayZT,cat(1,sepPeak_z{3,:}));

%sinal 37
tipo_mov = readLabelLocation('Data/labels.txt', 37, 37);
sepActi_x = sepDS(sinais37{1,1}, tipo_mov);
sepActi_y = sepDS(sinais37{1,2}, tipo_mov);
sepActi_z = sepDS(sinais37{1,3}, tipo_mov);
sepPeak_x = sepDS_Peaks(sepActi_x);
sepPeak_y = sepDS_Peaks(sepActi_y);
sepPeak_z = sepDS_Peaks(sepActi_z);

arrayXD= cat(1,arrayXD,cat(1,sepPeak_x{1,:}));
arrayYD= cat(1,arrayYD,cat(1,sepPeak_y{1,:}));
arrayZD= cat(1,arrayZD,cat(1,sepPeak_z{1,:}));
arrayXS= cat(1,arrayXS,cat(1,sepPeak_x{2,:}));
arrayYS= cat(1,arrayYS,cat(1,sepPeak_y{2,:}));
arrayZS= cat(1,arrayZS,cat(1,sepPeak_z{2,:}));
arrayXT= cat(1,arrayXT,cat(1,sepPeak_x{3,:}));
arrayYT= cat(1,arrayYT,cat(1,sepPeak_y{3,:}));
arrayZT= cat(1,arrayZT,cat(1,sepPeak_z{3,:}));

%sinal 38
tipo_mov = readLabelLocation('Data/labels.txt', 38, 38);
sepActi_x = sepDS(sinais38{1,1}, tipo_mov);
sepActi_y = sepDS(sinais38{1,2}, tipo_mov);
sepActi_z = sepDS(sinais38{1,3}, tipo_mov);
sepPeak_x = sepDS_Peaks(sepActi_x);
sepPeak_y = sepDS_Peaks(sepActi_y);
sepPeak_z = sepDS_Peaks(sepActi_z);

arrayXD= cat(1,arrayXD,cat(1,sepPeak_x{1,:}));
arrayYD= cat(1,arrayYD,cat(1,sepPeak_y{1,:}));
arrayZD= cat(1,arrayZD,cat(1,sepPeak_z{1,:}));
arrayXS= cat(1,arrayXS,cat(1,sepPeak_x{2,:}));
arrayYS= cat(1,arrayYS,cat(1,sepPeak_y{2,:}));
arrayZS= cat(1,arrayZS,cat(1,sepPeak_z{2,:}));
arrayXT= cat(1,arrayXT,cat(1,sepPeak_x{3,:}));
arrayYT= cat(1,arrayYT,cat(1,sepPeak_y{3,:}));
arrayZT= cat(1,arrayZT,cat(1,sepPeak_z{3,:}));

%sinal 39
tipo_mov = readLabelLocation('Data/labels.txt', 39, 39);
sepActi_x = sepDS(sinais39{1,1}, tipo_mov);
sepActi_y = sepDS(sinais39{1,2}, tipo_mov);
sepActi_z = sepDS(sinais39{1,3}, tipo_mov);
sepPeak_x = sepDS_Peaks(sepActi_x);
sepPeak_y = sepDS_Peaks(sepActi_y);
sepPeak_z = sepDS_Peaks(sepActi_z);

arrayXD= cat(1,arrayXD,cat(1,sepPeak_x{1,:}));
arrayYD= cat(1,arrayYD,cat(1,sepPeak_y{1,:}));
arrayZD= cat(1,arrayZD,cat(1,sepPeak_z{1,:}));
arrayXS= cat(1,arrayXS,cat(1,sepPeak_x{2,:}));
arrayYS= cat(1,arrayYS,cat(1,sepPeak_y{2,:}));
arrayZS= cat(1,arrayZS,cat(1,sepPeak_z{2,:}));
arrayXT= cat(1,arrayXT,cat(1,sepPeak_x{3,:}));
arrayYT= cat(1,arrayYT,cat(1,sepPeak_y{3,:}));
arrayZT= cat(1,arrayZT,cat(1,sepPeak_z{3,:}));

%sinal 40
tipo_mov = readLabelLocation('Data/labels.txt', 40, 40);
sepActi_x = sepDS(sinais40{1,1}, tipo_mov);
sepActi_y = sepDS(sinais40{1,2}, tipo_mov);
sepActi_z = sepDS(sinais40{1,3}, tipo_mov);
sepPeak_x = sepDS_Peaks(sepActi_x);
sepPeak_y = sepDS_Peaks(sepActi_y);
sepPeak_z = sepDS_Peaks(sepActi_z);

arrayXD= cat(1,arrayXD,cat(1,sepPeak_x{1,:}));
arrayYD= cat(1,arrayYD,cat(1,sepPeak_y{1,:}));
arrayZD= cat(1,arrayZD,cat(1,sepPeak_z{1,:}));
arrayXS= cat(1,arrayXS,cat(1,sepPeak_x{2,:}));
arrayYS= cat(1,arrayYS,cat(1,sepPeak_y{2,:}));
arrayZS= cat(1,arrayZS,cat(1,sepPeak_z{2,:}));
arrayXT= cat(1,arrayXT,cat(1,sepPeak_x{3,:}));
arrayYT= cat(1,arrayYT,cat(1,sepPeak_y{3,:}));
arrayZT= cat(1,arrayZT,cat(1,sepPeak_z{3,:}));

[vp,fp,vn,fn] = test(arrayXD,arrayYD,arrayZD,cat(1,arrayXS,arrayXT),cat(1,arrayYS,arrayYT),cat(1,arrayZS,arrayZT))

[S,E] = SensEspec(vp,vn,fp,fn);

disp("Sensibilidade:");
S
disp("Especificidade:");
E

PointA = [2,0,0];
PointB = [0,2,0];
PointC = [0,0,1.2];
points = [PointA' PointB' PointC'];

figure()
hold on
plot3(arrayXD,arrayYD,arrayZD,'g.'); %dinamicas
plot3(arrayXS,arrayYS,arrayZS,'r.'); %estaticas
plot3(arrayXT,arrayYT,arrayZT,'r.'); %transicoes
fill3(points(1,:),points(2,:),points(3,:),'k');
hold off

xlabel("X")
ylabel("Y")
zlabel("Z")

pause;

% ==================== Ex 4.4 ======================
disp("Exercicio 4.4");
sepDFT_x=sepActi_DFT(sepActi_x);
sepDFT_y=sepActi_DFT(sepActi_y);
sepDFT_z=sepActi_DFT(sepActi_z);
QuatroQuatro(sepDFT_x, sepDFT_y, sepDFT_z);
pause;

% ==================== Ex 5 ======================

disp('Exercicio 5: Espetrograma tempo e frequencia da experiencia 31 no eixo Z')
stftfuncao(sinais31{3});


