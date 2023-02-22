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

Class
Foam::vsfControl

Description
    Vortex surface field (VSF) control class.

Last modified
    Zhen Lu <zhen.lu@pku.edu.cn>

\*---------------------------------------------------------------------------*/

#ifndef vsfControl_H
#define vsfControl_H

#include "fvMesh.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

/*---------------------------------------------------------------------------*\
                         Class vsfControl Declaration
\*---------------------------------------------------------------------------*/

class vsfControl
:
    public IOdictionary
{
protected:

    // Protected data

        //- Maximum number of VSF correctors
        label nCorr_;

        //- Current VSF corrector
        label corr_;

        //- Ratio between the physical and pseudo timesteps
        scalar ratioTimestep_;

        //- Artificial viscosity for predictor
        dimensionedScalar epsPre_;

        //- Aritifical viscosity for corrector
        dimensionedScalar epsCor_;

public:

    // Static data members

        //- Run-time type information
        TypeName("vsfControl");

    // Constructors
        
        //- Construct from a mesh
        vsfControl(fvMesh& mesh);

    // Destructor
    virtual ~vsfControl();

    // Member Functions

        // Access

            //- Maximum number of VSF correctors
            inline label nCorr() const;

            //- Current VSF correctors
            inline label corr() const;

            //- Flag to indicate the first iteration
            inline bool firstIter() const;

            //- Flag to indicate the last iteration
            inline bool finalIter() const;

            //- Dissipation rate for predictor
            inline dimensionedScalar epsPre() const;

            //- Dissipation rate for corrector
            inline dimensionedScalar epsCor() const;

            //- Ratio between the physical timestep and pseudo interval
            inline scalar ratioInterval() const;

            //- Ratio between the physical timestep and pseudo timestep
            inline scalar ratioTimestep() const;

        // Evolution
        
            //- VSF loop
            bool correct();

};

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include "vsfControlI.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
