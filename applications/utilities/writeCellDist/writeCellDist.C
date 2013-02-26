/*---------------------------------------------------------------------------*\
=========                 |
\\      /  F ield         | Unsupported Contributions for OpenFOAM
 \\    /   O peration     |
  \\  /    A nd           | Copyright (C) 2013 Michael Wild
   \\/     M anipulation  |
-------------------------------------------------------------------------------

License
    This file is a derivative work of OpenFOAM.

    OpenFOAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

Application
    writeCellDist

Description
    Creates a field cellDist with the value equal to the processor rank into
    the processor directories.

    Compared to "decomposePar -cellDist" this utility has several differences:

    - Can be run after decomposing the case, e.g. for post-processing
    - Allows for random shuffling of the processor numbers.
    - Writes the cellDist field to the processor directories as uniform fields,
      saving a little space.

Usage
    - writeCellDist [OPTIONS]

    \param -random \n
    Randomly shuffle the processor id's before writing them to the file. This
    is useful for visualisation purposes, where one wishes to have stronger
    contrast between neighbouring processors.

    \param -seed  [\<seed\>] \n
    Specify the seed of the RNG which otherwise defaults to 0. Requires
    \a -random to be specified.

Note
    For most applications it only makes sense to run this utility in parallel
    with the \a -parallel flag.

Author
    Michael Wild <themiwi@users.sf.net>

\*---------------------------------------------------------------------------*/

#include "fvCFD.H"
#include "Random.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#if FOAM_HEX_VERSION < 0x200
#define ADD_NOTE(NOTE)
#define ADD_OPTION(NAME, META, DOC) argList::validOptions.insert(NAME, META)
#define ADD_BOOL_OPTION(NAME, DOC) argList::validOptions.insert(NAME, "")
#define REMOVE_OPTION(NAME) argList::validOptions.erase(NAME)
#else
#define ADD_NOTE(NOTE) argList::addNote(NOTE)
#define ADD_OPTION(NAME, META, DOC) argList::addOption(NAME, META, DOC)
#define ADD_BOOL_OPTION(NAME, DOC) argList::addBoolOption(NAME, DOC)
#define REMOVE_OPTION(NAME) argList::removeOption(NAME)
#endif

int main(int argc, char *argv[])
{
    // Set up arguments
    ADD_NOTE
    (
        "Creates a field cellDist with the value equal to the processor rank\n"
        "into the processor directories."
    );

    ADD_BOOL_OPTION
    (
        "random",
        "Randomly shuffle the processor ranks."
    );

    ADD_OPTION
    (
        "seed",
        "seed",
        "The seed of the RNG, defaulting to 0. Requires -random."
    );

    REMOVE_OPTION("noFunctionObjects");

    // Argument parsing and validation
    #include "setRootCase.H"
    bool doRandom = args.optionFound("random");
    label seed = 0;

    if (args.optionFound("seed"))
    {
        if (!doRandom)
        {
            FatalErrorIn("main(int, char**)")
                << "-seed requires -random to be specified\n"
                << exit(FatalError);
        }
        seed = args.optionRead<label>("seed");
    }

    #include "createTime.H"
    #include "createMesh.H"

    label id;
    if (doRandom)
    {
        labelList order(Pstream::nProcs());
        if (Pstream::master())
        {
            // want stable random assignments
            Random rnd(seed);
            scalarList rl(Pstream::nProcs());
            forAll(rl, i)
            {
                rl[i] = rnd.scalar01();
            }
            sortedOrder(rl, order);
        }
        Pstream::scatter(order);
        id = order[Pstream::myProcNo()];
    }
    else
    {
        id = Pstream::myProcNo();
    }

    volScalarField cellDist
    (
        IOobject
        (
            "cellDist",
            runTime.timeName(),
            mesh,
            IOobject::NO_READ,
            IOobject::AUTO_WRITE
        ),
        mesh,
        dimensionedScalar("cellDist", dimless, id)
    );

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

    cellDist.write();

    Info<< "end" << endl;

    return 0;
}


// ************************************************************************* //
