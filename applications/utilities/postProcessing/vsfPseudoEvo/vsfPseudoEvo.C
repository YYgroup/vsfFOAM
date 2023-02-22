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
    vsfPseudoEvo

Description
    Calculate the pseudo-evolution of the vortex-surface field

Last modified
    Zhen Lu <zhen.lu@pku.edu.cn>

\*---------------------------------------------------------------------------*/

#include "argList.H"
#include "timeSelector.H"

#include "fvCFD.H"
#include "vsfControl.H"

using namespace Foam;

int main(int argc, char *argv[])
{
    Foam::timeSelector::addOptions();
    #include "addRegionOption.H"

    #include "setRootCase.H"

    #include "createTime.H"
    Foam::instantList timeDirs = Foam::timeSelector::select0(runTime, args);
    #include "createNamedMesh.H"

    // Initialise the set of selected fields from the command-line options
    HashSet<word> requiredFields;
    if (args.optionFound("fields"))
    {
        args.optionLookup("fields")() >> requiredFields;
    }
    if (args.optionFound("field"))
    {
        requiredFields.insert(args.optionLookup("field")());
    }

    // Externally stored dictionary
    // if not constructed from runTime
    dictionary vsfControlDict("controlDict");

    forAll(timeDirs, timei)
    {
        runTime.setTime(timeDirs[timei], timei);

        //Info<< "Time = " << runTime.userTimeName() << endl;
        Info<< "Time = " << runTime.timeName() << endl;

        FatalIOError.throwExceptions();

        try
        {
            #include "createFields.H"
            #include "vsfEqnCor.H"
            VSF.write();
        }
        catch (IOerror& err)
        {
            Warning<< err << endl;
        }

        Info<< endl;
    }

    Info<< "End\n" << endl;

    return 0;
}


// ************************************************************************* //
