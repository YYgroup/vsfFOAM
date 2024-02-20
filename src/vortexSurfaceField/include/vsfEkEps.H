scalar Ek = 0.0;
scalar Eps = 0.0;

IOdictionary physicalProperties     
(
    IOobject
    (
        "physicalProperties",   
        runTime.constant(),     
        mesh,    
        IOobject::MUST_READ_IF_MODIFIED,    
        IOobject::NO_WRITE      
    )
);
dimensionedScalar nu
(
    "nu",
    dimViscosity,
    physicalProperties.lookup("nu")   
);
scalar nuValue = nu.value();



Ek = 0.5 * gSum(magSqr(U)*mesh.V().field())/gSum(mesh.V().field());

volScalarField EpsMag = mag((fvc::grad(U) && fvc::grad(U))); 

Eps = nuValue * (gSum(EpsMag*mesh.V().field())/gSum(mesh.V().field()));


Info<< " Ek: " << Ek 
    << " Eps: " << Eps << endl;

vsfEkEpsFile << " " << Ek << " " << Eps;