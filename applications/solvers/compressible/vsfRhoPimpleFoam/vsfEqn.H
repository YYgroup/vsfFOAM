// VSF predictor

fvScalarMatrix vsfEqnPre
(
    fvm::ddt(rho, VSF)
  + fvm::div(phi, VSF)
  - fvm::laplacian(vsfSol.epsPre()*rho, VSF)
);

vsfEqnPre.solve();

#include "vsfEqnCor.H"
