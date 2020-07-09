function [vp,fp,vn,fn] =test(dX,dY,dZ,sX,sY,sZ)

%plane function: 2.4x+2.4y+4z-4.8=0
vp=0;
fp=0;
vn=0;
fn=0;

for i= 1 : length(dX)
    x = 2.4*dX(i) + 2.4*dY(i) + 4*dZ(i) - 4.8;
    
    if(x > 0)
        vp = vp +1;
    else
        fn = fn +1;
    end
end

for i= 1 : length(sX)
    x = 4.8*sX(i) + 6*sY(i) + 20*sZ(i) - 24;
    
    if(x < 0)
        vn = vn +1;
    else
        fp = fp +1;
    end
end