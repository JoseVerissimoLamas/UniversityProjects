function [cont]=conta(fonte)
    alf=unique(fonte);
    cont=zeros(size(alf));
    for i=1:length(alf)
        n=sum(sum(fonte==alf(i)));
        cont(i)=n;
    end
end