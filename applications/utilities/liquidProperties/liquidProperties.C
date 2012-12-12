/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | Unsupported Contributions to OpenFOAM
   \\    /   O peration     |
    \\  /    A nd           | Copyright (C) 2012 OpenCFD Ltd.
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is a derivative work of OpenFOAM.

    OpenFOAM is free software; you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by the
    Free Software Foundation; either version 2 of the License, or (at your
    option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM; if not, write to the Free Software Foundation,
    Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

Application
    liquidProperties

Description
    Simple application to output liquid properties for a given temperature
    and pressure, based on the OpenFOAM liquids database

\*---------------------------------------------------------------------------*/

#include "argList.H"
#include "liquidProperties.H"
#include "dictionary.H"
#include "autoPtr.H"
#include "IFstream.H"

using namespace Foam;

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

int main(int argc, char *argv[])
{
    argList::noParallel();
    argList::validArgs.append("dict");

    #include "setRootCase.H"

    fileName dictPath = args.additionalArgs()[0];

    IFstream liquidPropsFile(dictPath);

    if (liquidPropsFile.good())
    {
        dictionary dict(dictionary::null, liquidPropsFile);
        word liquidName = dict.lookup("liquid");
        scalar p = readScalar(dict.lookup("p"));
        scalar T = readScalar(dict.lookup("T"));

        autoPtr<liquidProperties> fluidPtr =
            liquidProperties::New(dict.subDict(liquidName));
        const liquidProperties& fluid = fluidPtr();

        Info<< "Liquid: " << liquidName << nl << endl;

        Info<< "Physical constants:" << nl
            << "    molecular weight, W                 = "
            << fluid.W() << " [kg/kmol]" << nl
            << "    critical temperature, Tc            = "
            << fluid.Tc() << " [K]" << nl
            << "    critical pressure, Pc               = "
            << fluid.Pc() << " [Pa]" << nl
            << "    critical volume, Vc                 = "
            << fluid.Vc() << " [m3/mol]" << nl
            << "    critical compressibility factor, Zc = "
            << fluid.Zc() << " []" << nl
            << "    triple point temperature, Tt        = "
            << fluid.Tt() << " [K]" << nl
            << "    triple point pressure, Pt           = "
            << fluid.Pt() << " [Pa]" << nl
            << "    normal boiling temperature, Tb      = "
            << fluid.Tb() << " [K]" << nl
            << "    dipole moment, dipm                 = "
            << fluid.dipm() << " []" << nl
            << "    pitzer's accentric factor, omega    = "
            << fluid.omega() << " []" << nl
            << "    solubility parameter, delta         = "
            << fluid.delta() << " [(J/m3)^0.5]" << nl
            << endl;


        Info<< "Properties at T=" << T << " and p=" << p << ":" << nl
            << "    density, rho                        = "
            << fluid.rho(p, T) << " [kg/m3]" << nl
            << "    vapour pressure, pv                 = "
            << fluid.pv(p, T) << " [Pa]" << nl
            << "    heat of vapourisation, hl           = "
            << fluid.hl(p, T) << " [J/kg]" << nl
            << "    liquid heat capacity, Cp            = "
            << fluid.Cp(p, T) << " [J/kg/K]" << nl
            << "    liquid enthalpy, h                  = "
            << fluid.h(p, T) << " [J/kg]" << nl
            << "    ideal gas heat capacity, Cpg        = "
            << fluid.Cpg(p, T) << " [J/kg/K]" << nl
            << "    liquid viscosity, mu                = "
            << fluid.mu(p, T) << " [Pa.s]" << nl
            << "    vapour viscosity, mug               = "
            << fluid.mug(p, T) << " [Pa.s]" << nl
            << "    liquid thermal conductivity, K      = "
            << fluid.K(p, T) << " [W/m/K]"<< nl
            << "    vapour thermal conductivity, Kg     = "
            << fluid.Kg(p, T) << " [W/m/K]" << nl
            << "    surface tension, sigma              = "
            << fluid.sigma(p, T) << " [N/m]" << nl
            << "    vapour diffusivity, D               = "
            << fluid.D(p, T) << " [m2/s]" << nl
            << endl;
    }
    else
    {
        Info<< "    dictionary: " << dictPath << " not found" << endl;
    }

    return (0);
}


// ************************************************************************* //
