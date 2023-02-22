// VSF predictor

fvScalarMatrix vsfEqnPre
(
    fvm::ddt(VSF)
  + fvm::div(phi, VSF)
  - fvm::laplacian(vsfSol.epsPre(), VSF)
);

vsfEqnPre.solve();

#include "vsfEqnCor.H"
