function [S, E] = SensEspec(vp, vn, fp, fn)
    S = (vp/(fn+vp))*100;
    E = (vn/(fp+vn))*100;
end