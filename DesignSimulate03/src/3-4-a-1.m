Jn = 200 A/cm^2;
Dn = 32  cm^2/s;
nlower=10^{13} cm^{-3};
x0 = 0 m;
x1 = 7*10^{-6} m;
deltax = x1 - x0;
nupper =(Jn * deltax)/(ElectronCharge * Dn) + nlower;
nupperres =  WolframAlpha[ToString[nupper, InputForm], "Result"]
