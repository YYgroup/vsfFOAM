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
    fvc::flux(vor) * lengthScale //FIXME:这里有区别
    // fvc::interpolate(vor) & mesh.Sf() * lengthScale

);

#include "vsfCourantNo.H"   //TODO:这里计算 vsfcourant number mean

// VSF deviations

scalar vsfDevMax = 0.0;
scalar vsfDevMean = 0.0;

vsfDevFile.open("vsfDev.op", std::ofstream::out | std::ofstream::app);
vsfDevFile << runTime.timeName();

#include "vsfDeviations.H"

// VSF corrector
while (vsfSol.correct())
{
    VSF.oldTime() = VSF;//将当前时刻的变量 VSF 的值赋给了它的 oldTime 属性，即将当前时刻的值保存为旧时刻的值；目的是确保在每一轮迭代中，vsfEqnCor 方程中使用的是上一时刻的值
    fvScalarMatrix vsfEqnCor  
    (
        fvm::ddt(VSF)
        + fvm::div(phiVor, VSF)
        - fvm::laplacian(vsfSol.epsPre(), VSF)
    );
    vsfEqnCor.solve(); 
}

#include "vsfDeviations.H"

vsfDevFile << std::endl;
vsfDevFile.close();

// ************************************************************************* //
