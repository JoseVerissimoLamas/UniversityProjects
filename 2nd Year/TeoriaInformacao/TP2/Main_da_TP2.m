
fich=csvread("EKG_norm.csv");
audiowrite('EKG.wav',fich,250,'BitsPerSample',16);
[audioFich,bps]=audioread('EKG.wav');
%quantização do sinal
x= lpc(audioFich',1);
est_x = filter(-x(2:end),1,audioFich);
e = audioFich-est_x;
%Sinal após aplicação do LPC
audiowrite('LPC_predicted.wav',e,16);
h = audioread('LPC_predicted.wav');
%Quantização
entrop=entropia(h);
display(entrop);
%Display da entropia do sinal após quantização
b=conta(h);
nbitstotal=hufflen(b);
prob_de_cada_elemento=b/sum(b);
media= nbitstotal'*prob_de_cada_elemento;

display(media);
%Display do nºmédio de bits necessário para codificar o código após previsao e do cálculo do nº de bits que o código de
%Huffman teria com esse sinal
zip('zip.zip','LPC_predicted.wav');
%Compilação em zip
