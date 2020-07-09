function [arrayX, arrayY, arrayZ] = calculaPassosDinamicos(s1,s2, s3, s4, s5, s6, s7, s8, s9, s10, location)
% calcula os passos de todos os movimentos dinamicos

% ==================== EIXO X ====================
% numero de passos no eixo do x de todos os movimentos dinamicos do
% sinal 1

arrayX(1,1) = calcPassosMovimento(s1{1}, location(13,1), location(13,2));
arrayX(1,2) = calcPassosMovimento(s1{1}, location(14,1), location(14,2));
arrayX(1,3) = calcPassosMovimento(s1{1}, location(15,1), location(15,2));
arrayX(1,4) = calcPassosMovimento(s1{1}, location(16,1), location(16,2));
arrayX(1,5) = calcPassosMovimento(s1{1}, location(17,1), location(17,2));
arrayX(1,6) = calcPassosMovimento(s1{1}, location(18,1), location(18,2));
arrayX(1,7) = calcPassosMovimento(s1{1}, location(19,1), location(19,2));
arrayX(1,8) = calcPassosMovimento(s1{1}, location(20,1), location(20,2));


% numero de passos no eixo do x de todos os movimentos dinamicos do
% sinal 2

arrayX(2,1) = calcPassosMovimento(s2{1}, location(33,1), location(33,2));
arrayX(2,2) = calcPassosMovimento(s2{1}, location(34,1), location(34,2));
arrayX(2,3) = calcPassosMovimento(s2{1}, location(35,1), location(35,2));
arrayX(2,4) = calcPassosMovimento(s2{1}, location(36,1), location(36,2));
arrayX(2,5) = calcPassosMovimento(s2{1}, location(37,1), location(37,2));
arrayX(2,6) = calcPassosMovimento(s2{1}, location(38,1), location(38,2));
arrayX(2,7) = calcPassosMovimento(s2{1}, location(39,1), location(39,2));
arrayX(2,8) = calcPassosMovimento(s2{1}, location(40,1), location(40,2));

% numero de passos no eixo do x de todos os movimentos dinamicos do
% sinal 3

arrayX(3,1) = calcPassosMovimento(s3{1}, location(53,1), location(53,2));
arrayX(3,2) = calcPassosMovimento(s3{1}, location(54,1), location(54,2));
arrayX(3,3) = calcPassosMovimento(s3{1}, location(55,1), location(55,2));
arrayX(3,4) = calcPassosMovimento(s3{1}, location(56,1), location(56,2));
arrayX(3,5) = calcPassosMovimento(s3{1}, location(57,1), location(57,2));
arrayX(3,6) = calcPassosMovimento(s3{1}, location(58,1), location(58,2));
arrayX(3,7) = calcPassosMovimento(s3{1}, location(59,1), location(59,2));
arrayX(3,8) = calcPassosMovimento(s3{1}, location(60,1), location(60,2));

% numero de passos no eixo do x de todos os movimentos dinamicos do
% sinal 4

arrayX(4,1) = calcPassosMovimento(s4{1}, location(73,1), location(73,2));
arrayX(4,2) = calcPassosMovimento(s4{1}, location(74,1), location(74,2));
arrayX(4,3) = calcPassosMovimento(s4{1}, location(75,1), location(75,2));
arrayX(4,4) = calcPassosMovimento(s4{1}, location(76,1), location(76,2));
arrayX(4,5) = calcPassosMovimento(s4{1}, location(77,1), location(77,2));
arrayX(4,6) = calcPassosMovimento(s4{1}, location(78,1), location(78,2));
arrayX(4,7) = calcPassosMovimento(s4{1}, location(79,1), location(79,2));
arrayX(4,8) = calcPassosMovimento(s4{1}, location(80,1), location(80,2));

% numero de passos no eixo do x de todos os movimentos dinamicos do
% sinal 5

arrayX(5,1) = calcPassosMovimento(s5{1}, location(93,1), location(93,2));
arrayX(5,2) = calcPassosMovimento(s5{1}, location(94,1), location(94,2));
arrayX(5,3) = calcPassosMovimento(s5{1}, location(95,1), location(95,2));
arrayX(5,4) = calcPassosMovimento(s5{1}, location(96,1), location(96,2));
arrayX(5,5) = calcPassosMovimento(s5{1}, location(97,1), location(97,2));
arrayX(5,6) = calcPassosMovimento(s5{1}, location(98,1), location(98,2));
arrayX(5,7) = calcPassosMovimento(s5{1}, location(99,1), location(99,2));
arrayX(5,8) = calcPassosMovimento(s5{1}, location(100,1), location(100,2));

% numero de passos no eixo do x de todos os movimentos dinamicos do
% sinal 6

arrayX(6,1) = calcPassosMovimento(s6{1}, location(113,1), location(113,2));
arrayX(6,2) = calcPassosMovimento(s6{1}, location(114,1), location(114,2));
arrayX(6,3) = calcPassosMovimento(s6{1}, location(115,1), location(115,2));
arrayX(6,4) = calcPassosMovimento(s6{1}, location(116,1), location(116,2));
arrayX(6,5) = calcPassosMovimento(s6{1}, location(117,1), location(117,2));
arrayX(6,6) = calcPassosMovimento(s6{1}, location(118,1), location(118,2));
arrayX(6,7) = calcPassosMovimento(s6{1}, location(119,1), location(119,2));
arrayX(6,8) = calcPassosMovimento(s6{1}, location(120,1), location(120,2));

% numero de passos no eixo do x de todos os movimentos dinamicos do
% sinal 7

arrayX(7,1) = calcPassosMovimento(s7{1}, location(133,1), location(133,2));
arrayX(7,2) = calcPassosMovimento(s7{1}, location(134,1), location(134,2));
arrayX(7,3) = calcPassosMovimento(s7{1}, location(135,1), location(135,2));
arrayX(7,4) = calcPassosMovimento(s7{1}, location(136,1), location(136,2));
arrayX(7,5) = calcPassosMovimento(s7{1}, location(137,1), location(137,2));
arrayX(7,6) = calcPassosMovimento(s7{1}, location(138,1), location(138,2));
arrayX(7,7) = calcPassosMovimento(s7{1}, location(139,1), location(139,2));
arrayX(7,8) = calcPassosMovimento(s7{1}, location(140,1), location(140,2));

% numero de passos no eixo do x de todos os movimentos dinamicos do
% sinal 8

arrayX(8,1) = calcPassosMovimento(s8{1}, location(153,1), location(153,2));
arrayX(8,2) = calcPassosMovimento(s8{1}, location(154,1), location(154,2));
arrayX(8,3) = calcPassosMovimento(s8{1}, location(155,1), location(155,2));
arrayX(8,4) = calcPassosMovimento(s8{1}, location(156,1), location(156,2));
arrayX(8,5) = calcPassosMovimento(s8{1}, location(157,1), location(157,2));
arrayX(8,6) = calcPassosMovimento(s8{1}, location(158,1), location(158,2));
arrayX(8,7) = calcPassosMovimento(s8{1}, location(159,1), location(159,2));
arrayX(8,8) = calcPassosMovimento(s8{1}, location(160,1), location(160,2));

% numero de passos no eixo do x de todos os movimentos dinamicos do
% sinal 9

arrayX(9,1) = calcPassosMovimento(s9{1}, location(173,1), location(173,2));
arrayX(9,2) = calcPassosMovimento(s9{1}, location(174,1), location(174,2));
arrayX(9,3) = calcPassosMovimento(s9{1}, location(175,1), location(175,2));
arrayX(9,4) = calcPassosMovimento(s9{1}, location(176,1), location(176,2));
arrayX(9,5) = calcPassosMovimento(s9{1}, location(177,1), location(177,2));
arrayX(9,6) = calcPassosMovimento(s9{1}, location(178,1), location(178,2));
arrayX(9,7) = calcPassosMovimento(s9{1}, location(179,1), location(179,2));
arrayX(9,8) = calcPassosMovimento(s9{1}, location(180,1), location(180,2));

% numero de passos no eixo do x de todos os movimentos dinamicos do
% sinal 10

arrayX(10,1) = calcPassosMovimento(s10{1}, location(193,1), location(193,2));
arrayX(10,2) = calcPassosMovimento(s10{1}, location(194,1), location(194,2));
arrayX(10,3) = calcPassosMovimento(s10{1}, location(195,1), location(195,2));
arrayX(10,4) = calcPassosMovimento(s10{1}, location(196,1), location(196,2));
arrayX(10,5) = calcPassosMovimento(s10{1}, location(197,1), location(197,2));
arrayX(10,6) = calcPassosMovimento(s10{1}, location(198,1), location(198,2));
arrayX(10,7) = calcPassosMovimento(s10{1}, location(199,1), location(199,2));
arrayX(10,8) = calcPassosMovimento(s10{1}, location(200,1), location(200,2));

% ==================== EIXO Y ====================
% numero de passos no eixo do x de todos os movimentos dinamicos do
% sinal 1

arrayY(1,1) = calcPassosMovimento(s1{2}, location(13,1), location(13,2));
arrayY(1,2) = calcPassosMovimento(s1{2}, location(14,1), location(14,2));
arrayY(1,3) = calcPassosMovimento(s1{2}, location(15,1), location(15,2));
arrayY(1,4) = calcPassosMovimento(s1{2}, location(16,1), location(16,2));
arrayY(1,5) = calcPassosMovimento(s1{2}, location(17,1), location(17,2));
arrayY(1,6) = calcPassosMovimento(s1{2}, location(18,1), location(18,2));
arrayY(1,7) = calcPassosMovimento(s1{2}, location(19,1), location(19,2));
arrayY(1,8) = calcPassosMovimento(s1{2}, location(20,1), location(20,2));


% numero de passos no eixo do x de todos os movimentos dinamicos do
% sinal 2

arrayY(2,1) = calcPassosMovimento(s2{2}, location(33,1), location(33,2));
arrayY(2,2) = calcPassosMovimento(s2{2}, location(34,1), location(34,2));
arrayY(2,3) = calcPassosMovimento(s2{2}, location(35,1), location(35,2));
arrayY(2,4) = calcPassosMovimento(s2{2}, location(36,1), location(36,2));
arrayY(2,5) = calcPassosMovimento(s2{2}, location(37,1), location(37,2));
arrayY(2,6) = calcPassosMovimento(s2{2}, location(38,1), location(38,2));
arrayY(2,7) = calcPassosMovimento(s2{2}, location(39,1), location(39,2));
arrayY(2,8) = calcPassosMovimento(s2{2}, location(40,1), location(40,2));

% numero de passos no eixo do x de todos os movimentos dinamicos do
% sinal 3

arrayY(3,1) = calcPassosMovimento(s3{2}, location(53,1), location(53,2));
arrayY(3,2) = calcPassosMovimento(s3{2}, location(54,1), location(54,2));
arrayY(3,3) = calcPassosMovimento(s3{2}, location(55,1), location(55,2));
arrayY(3,4) = calcPassosMovimento(s3{2}, location(56,1), location(56,2));
arrayY(3,5) = calcPassosMovimento(s3{2}, location(57,1), location(57,2));
arrayY(3,6) = calcPassosMovimento(s3{2}, location(58,1), location(58,2));
arrayY(3,7) = calcPassosMovimento(s3{2}, location(59,1), location(59,2));
arrayY(3,8) = calcPassosMovimento(s3{2}, location(60,1), location(60,2));

% numero de passos no eixo do x de todos os movimentos dinamicos do
% sinal 4

arrayY(4,1) = calcPassosMovimento(s4{2}, location(73,1), location(73,2));
arrayY(4,2) = calcPassosMovimento(s4{2}, location(74,1), location(74,2));
arrayY(4,3) = calcPassosMovimento(s4{2}, location(75,1), location(75,2));
arrayY(4,4) = calcPassosMovimento(s4{2}, location(76,1), location(76,2));
arrayY(4,5) = calcPassosMovimento(s4{2}, location(77,1), location(77,2));
arrayY(4,6) = calcPassosMovimento(s4{2}, location(78,1), location(78,2));
arrayY(4,7) = calcPassosMovimento(s4{2}, location(79,1), location(79,2));
arrayY(4,8) = calcPassosMovimento(s4{2}, location(80,1), location(80,2));

% numero de passos no eixo do x de todos os movimentos dinamicos do
% sinal 5

arrayY(5,1) = calcPassosMovimento(s5{2}, location(93,1), location(93,2));
arrayY(5,2) = calcPassosMovimento(s5{2}, location(94,1), location(94,2));
arrayY(5,3) = calcPassosMovimento(s5{2}, location(95,1), location(95,2));
arrayY(5,4) = calcPassosMovimento(s5{2}, location(96,1), location(96,2));
arrayY(5,5) = calcPassosMovimento(s5{2}, location(97,1), location(97,2));
arrayY(5,6) = calcPassosMovimento(s5{2}, location(98,1), location(98,2));
arrayY(5,7) = calcPassosMovimento(s5{2}, location(99,1), location(99,2));
arrayY(5,8) = calcPassosMovimento(s5{2}, location(100,1), location(100,2));

% numero de passos no eixo do x de todos os movimentos dinamicos do
% sinal 6

arrayY(6,1) = calcPassosMovimento(s6{2}, location(113,1), location(113,2));
arrayY(6,2) = calcPassosMovimento(s6{2}, location(114,1), location(114,2));
arrayY(6,3) = calcPassosMovimento(s6{2}, location(115,1), location(115,2));
arrayY(6,4) = calcPassosMovimento(s6{2}, location(116,1), location(116,2));
arrayY(6,5) = calcPassosMovimento(s6{2}, location(117,1), location(117,2));
arrayY(6,6) = calcPassosMovimento(s6{2}, location(118,1), location(118,2));
arrayY(6,7) = calcPassosMovimento(s6{2}, location(119,1), location(119,2));
arrayY(6,8) = calcPassosMovimento(s6{2}, location(120,1), location(120,2));

% numero de passos no eixo do x de todos os movimentos dinamicos do
% sinal 7

arrayY(7,1) = calcPassosMovimento(s7{2}, location(133,1), location(133,2));
arrayY(7,2) = calcPassosMovimento(s7{2}, location(134,1), location(134,2));
arrayY(7,3) = calcPassosMovimento(s7{2}, location(135,1), location(135,2));
arrayY(7,4) = calcPassosMovimento(s7{2}, location(136,1), location(136,2));
arrayY(7,5) = calcPassosMovimento(s7{2}, location(137,1), location(137,2));
arrayY(7,6) = calcPassosMovimento(s7{2}, location(138,1), location(138,2));
arrayY(7,7) = calcPassosMovimento(s7{2}, location(139,1), location(139,2));
arrayY(7,8) = calcPassosMovimento(s7{2}, location(140,1), location(140,2));

% numero de passos no eixo do x de todos os movimentos dinamicos do
% sinal 8

arrayY(8,1) = calcPassosMovimento(s8{2}, location(153,1), location(153,2));
arrayY(8,2) = calcPassosMovimento(s8{2}, location(154,1), location(154,2));
arrayY(8,3) = calcPassosMovimento(s8{2}, location(155,1), location(155,2));
arrayY(8,4) = calcPassosMovimento(s8{2}, location(156,1), location(156,2));
arrayY(8,5) = calcPassosMovimento(s8{2}, location(157,1), location(157,2));
arrayY(8,6) = calcPassosMovimento(s8{2}, location(158,1), location(158,2));
arrayY(8,7) = calcPassosMovimento(s8{2}, location(159,1), location(159,2));
arrayY(8,8) = calcPassosMovimento(s8{2}, location(160,1), location(160,2));

% numero de passos no eixo do x de todos os movimentos dinamicos do
% sinal 9

arrayY(9,1) = calcPassosMovimento(s9{2}, location(173,1), location(173,2));
arrayY(9,2) = calcPassosMovimento(s9{2}, location(174,1), location(174,2));
arrayY(9,3) = calcPassosMovimento(s9{2}, location(175,1), location(175,2));
arrayY(9,4) = calcPassosMovimento(s9{2}, location(176,1), location(176,2));
arrayY(9,5) = calcPassosMovimento(s9{2}, location(177,1), location(177,2));
arrayY(9,6) = calcPassosMovimento(s9{2}, location(178,1), location(178,2));
arrayY(9,7) = calcPassosMovimento(s9{2}, location(179,1), location(179,2));
arrayY(9,8) = calcPassosMovimento(s9{2}, location(180,1), location(180,2));

% numero de passos no eixo do x de todos os movimentos dinamicos do
% sinal 10

arrayY(10,1) = calcPassosMovimento(s10{2}, location(193,1), location(193,2));
arrayY(10,2) = calcPassosMovimento(s10{2}, location(194,1), location(194,2));
arrayY(10,3) = calcPassosMovimento(s10{2}, location(195,1), location(195,2));
arrayY(10,4) = calcPassosMovimento(s10{2}, location(196,1), location(196,2));
arrayY(10,5) = calcPassosMovimento(s10{2}, location(197,1), location(197,2));
arrayY(10,6) = calcPassosMovimento(s10{2}, location(198,1), location(198,2));
arrayY(10,7) = calcPassosMovimento(s10{2}, location(199,1), location(199,2));
arrayY(10,8) = calcPassosMovimento(s10{2}, location(200,1), location(200,2));

% ==================== EIXO Z ====================
% numero de passos no eixo do x de todos os movimentos dinamicos do
% sinal 1

arrayZ(1,1) = calcPassosMovimento(s1{3}, location(13,1), location(13,2));
arrayZ(1,2) = calcPassosMovimento(s1{3}, location(14,1), location(14,2));
arrayZ(1,3) = calcPassosMovimento(s1{3}, location(15,1), location(15,2));
arrayZ(1,4) = calcPassosMovimento(s1{3}, location(16,1), location(16,2));
arrayZ(1,5) = calcPassosMovimento(s1{3}, location(17,1), location(17,2));
arrayZ(1,6) = calcPassosMovimento(s1{3}, location(18,1), location(18,2));
arrayZ(1,7) = calcPassosMovimento(s1{3}, location(19,1), location(19,2));
arrayZ(1,8) = calcPassosMovimento(s1{3}, location(20,1), location(20,2));


% numero de passos no eixo do x de todos os movimentos dinamicos do
% sinal 2

arrayZ(2,1) = calcPassosMovimento(s2{3}, location(33,1), location(33,2));
arrayZ(2,2) = calcPassosMovimento(s2{3}, location(34,1), location(34,2));
arrayZ(2,3) = calcPassosMovimento(s2{3}, location(35,1), location(35,2));
arrayZ(2,4) = calcPassosMovimento(s2{3}, location(36,1), location(36,2));
arrayZ(2,5) = calcPassosMovimento(s2{3}, location(37,1), location(37,2));
arrayZ(2,6) = calcPassosMovimento(s2{3}, location(38,1), location(38,2));
arrayZ(2,7) = calcPassosMovimento(s2{3}, location(39,1), location(39,2));
arrayZ(2,8) = calcPassosMovimento(s2{3}, location(40,1), location(40,2));

% numero de passos no eixo do x de todos os movimentos dinamicos do
% sinal 3

arrayZ(3,1) = calcPassosMovimento(s3{3}, location(53,1), location(53,2));
arrayZ(3,2) = calcPassosMovimento(s3{3}, location(54,1), location(54,2));
arrayZ(3,3) = calcPassosMovimento(s3{3}, location(55,1), location(55,2));
arrayZ(3,4) = calcPassosMovimento(s3{3}, location(56,1), location(56,2));
arrayZ(3,5) = calcPassosMovimento(s3{3}, location(57,1), location(57,2));
arrayZ(3,6) = calcPassosMovimento(s3{3}, location(58,1), location(58,2));
arrayZ(3,7) = calcPassosMovimento(s3{3}, location(59,1), location(59,2));
arrayZ(3,8) = calcPassosMovimento(s3{3}, location(60,1), location(60,2));

% numero de passos no eixo do x de todos os movimentos dinamicos do
% sinal 4

arrayZ(4,1) = calcPassosMovimento(s4{3}, location(73,1), location(73,2));
arrayZ(4,2) = calcPassosMovimento(s4{3}, location(74,1), location(74,2));
arrayZ(4,3) = calcPassosMovimento(s4{3}, location(75,1), location(75,2));
arrayZ(4,4) = calcPassosMovimento(s4{3}, location(76,1), location(76,2));
arrayZ(4,5) = calcPassosMovimento(s4{3}, location(77,1), location(77,2));
arrayZ(4,6) = calcPassosMovimento(s4{3}, location(78,1), location(78,2));
arrayZ(4,7) = calcPassosMovimento(s4{3}, location(79,1), location(79,2));
arrayZ(4,8) = calcPassosMovimento(s4{3}, location(80,1), location(80,2));

% numero de passos no eixo do x de todos os movimentos dinamicos do
% sinal 5

arrayZ(5,1) = calcPassosMovimento(s5{3}, location(93,1), location(93,2));
arrayZ(5,2) = calcPassosMovimento(s5{3}, location(94,1), location(94,2));
arrayZ(5,3) = calcPassosMovimento(s5{3}, location(95,1), location(95,2));
arrayZ(5,4) = calcPassosMovimento(s5{3}, location(96,1), location(96,2));
arrayZ(5,5) = calcPassosMovimento(s5{3}, location(97,1), location(97,2));
arrayZ(5,6) = calcPassosMovimento(s5{3}, location(98,1), location(98,2));
arrayZ(5,7) = calcPassosMovimento(s5{3}, location(99,1), location(99,2));
arrayZ(5,8) = calcPassosMovimento(s5{3}, location(100,1), location(100,2));

% numero de passos no eixo do x de todos os movimentos dinamicos do
% sinal 6

arrayZ(6,1) = calcPassosMovimento(s6{3}, location(113,1), location(113,2));
arrayZ(6,2) = calcPassosMovimento(s6{3}, location(114,1), location(114,2));
arrayZ(6,3) = calcPassosMovimento(s6{3}, location(115,1), location(115,2));
arrayZ(6,4) = calcPassosMovimento(s6{3}, location(116,1), location(116,2));
arrayZ(6,5) = calcPassosMovimento(s6{3}, location(117,1), location(117,2));
arrayZ(6,6) = calcPassosMovimento(s6{3}, location(118,1), location(118,2));
arrayZ(6,7) = calcPassosMovimento(s6{3}, location(119,1), location(119,2));
arrayZ(6,8) = calcPassosMovimento(s6{3}, location(120,1), location(120,2));

% numero de passos no eixo do x de todos os movimentos dinamicos do
% sinal 7

arrayZ(7,1) = calcPassosMovimento(s7{3}, location(133,1), location(133,2));
arrayZ(7,2) = calcPassosMovimento(s7{3}, location(134,1), location(134,2));
arrayZ(7,3) = calcPassosMovimento(s7{3}, location(135,1), location(135,2));
arrayZ(7,4) = calcPassosMovimento(s7{3}, location(136,1), location(136,2));
arrayZ(7,5) = calcPassosMovimento(s7{3}, location(137,1), location(137,2));
arrayZ(7,6) = calcPassosMovimento(s7{3}, location(138,1), location(138,2));
arrayZ(7,7) = calcPassosMovimento(s7{3}, location(139,1), location(139,2));
arrayZ(7,8) = calcPassosMovimento(s7{3}, location(140,1), location(140,2));

% numero de passos no eixo do x de todos os movimentos dinamicos do
% sinal 8

arrayZ(8,1) = calcPassosMovimento(s8{3}, location(153,1), location(153,2));
arrayZ(8,2) = calcPassosMovimento(s8{3}, location(154,1), location(154,2));
arrayZ(8,3) = calcPassosMovimento(s8{3}, location(155,1), location(155,2));
arrayZ(8,4) = calcPassosMovimento(s8{3}, location(156,1), location(156,2));
arrayZ(8,5) = calcPassosMovimento(s8{3}, location(157,1), location(157,2));
arrayZ(8,6) = calcPassosMovimento(s8{3}, location(158,1), location(158,2));
arrayZ(8,7) = calcPassosMovimento(s8{3}, location(159,1), location(159,2));
arrayZ(8,8) = calcPassosMovimento(s8{3}, location(160,1), location(160,2));

% numero de passos no eixo do x de todos os movimentos dinamicos do
% sinal 9

arrayZ(9,1) = calcPassosMovimento(s9{3}, location(173,1), location(173,2));
arrayZ(9,2) = calcPassosMovimento(s9{3}, location(174,1), location(174,2));
arrayZ(9,3) = calcPassosMovimento(s9{3}, location(175,1), location(175,2));
arrayZ(9,4) = calcPassosMovimento(s9{3}, location(176,1), location(176,2));
arrayZ(9,5) = calcPassosMovimento(s9{3}, location(177,1), location(177,2));
arrayZ(9,6) = calcPassosMovimento(s9{3}, location(178,1), location(178,2));
arrayZ(9,7) = calcPassosMovimento(s9{3}, location(179,1), location(179,2));
arrayZ(9,8) = calcPassosMovimento(s9{3}, location(180,1), location(180,2));

% numero de passos no eixo do x de todos os movimentos dinamicos do
% sinal 10

arrayZ(10,1) = calcPassosMovimento(s10{3}, location(193,1), location(193,2));
arrayZ(10,2) = calcPassosMovimento(s10{3}, location(194,1), location(194,2));
arrayZ(10,3) = calcPassosMovimento(s10{3}, location(195,1), location(195,2));
arrayZ(10,4) = calcPassosMovimento(s10{3}, location(196,1), location(196,2));
arrayZ(10,5) = calcPassosMovimento(s10{3}, location(197,1), location(197,2));
arrayZ(10,6) = calcPassosMovimento(s10{3}, location(198,1), location(198,2));
arrayZ(10,7) = calcPassosMovimento(s10{3}, location(199,1), location(199,2));
arrayZ(10,8) = calcPassosMovimento(s10{3}, location(200,1), location(200,2));

%disp(arrayX)
%disp(arrayY)
%disp(arrayZ)
end

