
fich=csvread("EKG_norm.csv");
audiowrite('EKG.wav',fich,250,'BitsPerSample',16);
[audioFich,bps]=audioread('EKG.wav');
%quantiza��o do sinal
x= lpc(audioFich',1);
est_x = filter(-x(2:end),1,audioFich);
e = audioFich-est_x;
%Sinal ap�s aplica��o do LPC
audiowrite('LPC_predicted.wav',e,16);
h = audioread('LPC_predicted.wav');
%Quantiza��o
entrop=entropia(h);
display(entrop);
%Display da entropia do sinal ap�s quantiza��o
b=conta(h);
nbitstotal=hufflen(b);
prob_de_cada_elemento=b/sum(b);
media= nbitstotal'*prob_de_cada_elemento;

display(media);
%Display do n�m�dio de bits necess�rio para codificar o c�digo ap�s previsao e do c�lculo do n� de bits que o c�digo de
%Huffman teria com esse sinal
zip('zip.zip','LPC_predicted.wav');
%Compila��o em zip
