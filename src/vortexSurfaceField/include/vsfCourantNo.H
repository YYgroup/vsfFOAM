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
    vsfCourantNo

Description
    Calculates and outputs the mean and maximum Courant Numbers for the
    corrector of vortex-surface field evolution.

Last modified
    Zhen Lu <zhen.lu@pku.edu.cn>

\*---------------------------------------------------------------------------*/

scalar vsfCoNum = 0.0;
scalar meanVsfCoNum = 0.0;

{
    scalarField sumPhiVor
    (
        fvc::surfaceSum(mag(phiVor))().primitiveField()
    );

    vsfCoNum = 
        0.5*gMax(sumPhiVor/mesh.V().field())
        *runTime.deltaTValue()/vsfSol.ratioTimestep();

    meanVsfCoNum =
        0.5*(gSum(sumPhiVor)/gSum(mesh.V().field()))
        *runTime.deltaTValue()/vsfSol.ratioTimestep();
}

Info<< "VSF Courant Number mean: " << meanVsfCoNum
    << " max: " << vsfCoNum << endl;

// ************************************************************************* //
