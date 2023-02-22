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

Last modified
    Zhen Lu <zhen.lu@pku.edu.cn>

\*---------------------------------------------------------------------------*/

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

inline Foam::label Foam::vsfControl::nCorr() const
{
    return nCorr_;
}

inline Foam::label Foam::vsfControl::corr() const
{
    return corr_;
}

inline bool Foam::vsfControl::firstIter() const
{
    return corr_ == 1;
}

inline bool Foam::vsfControl::finalIter() const
{
    return corr_ >= nCorr_;
}

inline Foam::dimensionedScalar Foam::vsfControl::epsPre() const
{
    return epsPre_;
}

inline Foam::dimensionedScalar Foam::vsfControl::epsCor() const
{
    return epsCor_;
}

inline Foam::scalar Foam::vsfControl::ratioInterval() const
{
    return ratioTimestep_ / nCorr_;
}

inline Foam::scalar Foam::vsfControl::ratioTimestep() const
{
    return ratioTimestep_;
}

// ************************************************************************* //
