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
    createVSF

Description
    Creates and initialises the vortex-surface field.

Last modified
    Zhen Lu <zhen.lu@pku.edu.cn>

\*---------------------------------------------------------------------------*/

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

vsfControl vsfSol(mesh);

Info<< "Reading the vortex-surface field (VSF)\n" << endl;

volScalarField VSF
(
    IOobject
    (
        "VSF",
        runTime.timeName(),
        mesh,
        IOobject::MUST_READ,
        IOobject::AUTO_WRITE
    ),
    mesh
);

volScalarField lambdaVor
(
    IOobject
    (
        "lambdaVor",
        runTime.timeName(),
        mesh,
        IOobject::READ_IF_PRESENT,
        IOobject::AUTO_WRITE
    ),
    fvc::grad(VSF)&fvc::curl(U)/mag(fvc::grad(VSF))/mag(fvc::curl(U))
);

// VSF monitor file

std::ofstream vsfDevFile("vsfDev.op");

vsfDevFile << "time vsfDevPreMean vsfDevPreMax vsfDevCorMean vsfDevCorMax" 
    << std::endl;

vsfDevFile.close();

std::ofstream vsfTimeFile("vsfTime.op");

vsfTimeFile << "time OFTime VSFTime" 
    << std::endl;

vsfTimeFile.close();

// ************************************************************************* //
