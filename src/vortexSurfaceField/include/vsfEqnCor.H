/*---------------------------------------------------------------------------*\

Copyright (C) 2023 YYGroup <yyg@pku.edu.cn>
Copyright (C) 2016-2022 OpenFOAM Foundation

License
    This file is part of vsfFOAM.

    vsfFOAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    vsfFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with vsfFOAM. If not, see <http://www.gnu.org/licenses/>.

Global
    vsfEqnCor

Description
    Correctors for the vortex-surface field evolution.

Last modified
    Zhen Lu <zhen.lu@pku.edu.cn>

\*---------------------------------------------------------------------------*/

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

// frozen vorticity

volVectorField vor = fvc::curl(U);

dimensionedScalar lengthScale
(
    "lengthScale",
    dimLength,
    1.
);

surfaceScalarField phiVor
(
    "phiVor",
    fvc::flux(vor) * lengthScale 
);

#include "vsfCourantNo.H"   

// VSF deviations

scalar vsfDevMax = 0.0;
scalar vsfDevMean = 0.0;

vsfDevFile.open("vsfDev.op", std::ofstream::out | std::ofstream::app);
vsfDevFile << runTime.timeName();

vsfEkEpsFile.open("vsfEkEps.op", std::ofstream::out | std::ofstream::app);
vsfEkEpsFile << runTime.timeName();

#include "vsfDeviations.H"

// VSF corrector
while (vsfSol.correct())
{
    VSF.oldTime() = VSF;
    fvScalarMatrix vsfEqnCor  
    (
        fvm::ddt(VSF)
        + fvm::div(phiVor, VSF)
        - fvm::laplacian(vsfSol.epsPre(), VSF)
    );
    vsfEqnCor.solve(); 
}

#include "vsfDeviations.H"
#include "vsfEkEps.H"


vsfDevFile << std::endl;
vsfDevFile.close();

vsfEkEpsFile << std::endl;
vsfEkEpsFile.close();
// ************************************************************************* //
