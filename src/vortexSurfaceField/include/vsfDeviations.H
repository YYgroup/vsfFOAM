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
    vsfDeviations

Description
    Calculates and outputs the mean and maximum deviations of the 
    vortex-surface field.

Last modified
    Zhen Lu <zhen.lu@pku.edu.cn>

\*---------------------------------------------------------------------------*/

{
    volVectorField vsfGrad = fvc::grad(VSF);

    lambdaVor = vor & vsfGrad / (mag(vor)*mag(vsfGrad));

    volScalarField lambdaVorMag = mag(lambdaVor);

    vsfDevMax = gMax(lambdaVorMag);

    vsfDevMean = 
        gSum(lambdaVorMag*mesh.V().field())/gSum(mesh.V().field());
}

Info<< "VSF deviation mean: " << vsfDevMean 
    << " max: " << vsfDevMax << endl;

vsfDevFile << " " << vsfDevMean << " " << vsfDevMax;

// ************************************************************************* //
