function entropia = entropia(LPCpredicted)
    LPCpredicted = LPCpredicted(:)';
    LPCpredicted = tabulate(LPCpredicted);
    LPCpredicted = LPCpredicted(:,2);
    LPCpredicted = LPCpredicted(LPCpredicted~=0);
    k=sum(LPCpredicted);
    entropia= sum(LPCpredicted .* log2(k./LPCpredicted))/k;
    
end