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

Application
    vsfIcoFoam

Description
    Transient solver for incompressible, laminar flow of Newtonian fluids.

    Uses the two-time method for vortex-surface field evolution.

Last modified
    Zhen Lu <zhen.lu@pku.edu.cn>

\*---------------------------------------------------------------------------*/

#include "fvCFD.H"
#include "pisoControl.H"
#include "vsfControl.H"
#include <time.h>
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

int main(int argc, char *argv[])
{
    #include "setRootCaseLists.H"
    #include "createTime.H"
    #include "createMesh.H"

    pisoControl piso(mesh);

    #include "createFields.H"
    #include "initContinuityErrs.H"

    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

    Info<< "\nStarting time loop\n" << endl;

    while (runTime.loop())
    {
        Info<< "Time = " << runTime.userTimeName() << nl << endl;

        vsfTimeFile.open("vsfTime.op", std::ofstream::out | std::ofstream::app);
        vsfTimeFile << runTime.timeName();

        // Start measuring time
        time_t t_OF = time(NULL);

        #include "CourantNo.H"

        #include "UEqn.H"

        // --- PISO loop
        while (piso.correct())
        {
            #include "pEqn.H"
        }

        // Stop measuring time and calculate the elapsed time
        double cost_tOF = time(NULL) - t_OF;
        Info << "OpenFOAM Execution Time  : " << cost_tOF  << "s" << endl;


        // Start measuring time
        time_t t_VSF = time(NULL);

        // --- VSF evolution
        #include "vsfEqn.H" //TODO:

        // Stop measuring time and calculate the elapsed time
        double cost_tVSF = time(NULL) - t_VSF;
        Info << "VSF Execution Time  : " << cost_tVSF  << "s" << endl;

        vsfTimeFile << " " << cost_tOF << " " << cost_tVSF;
        vsfTimeFile << std::endl;
        vsfTimeFile.close();


        runTime.write();

        Info<< "ExecutionTime = " << runTime.elapsedCpuTime() << " s"
            << "  ClockTime = " << runTime.elapsedClockTime() << " s"
            << nl << endl;
    }

    Info<< "End\n" << endl;

    return 0;
}


// ************************************************************************* //
