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

scalar vsfEk = 0.0;
scalar vsfEps = 0.0;
scalar nuValue = nu.value();

vsfEk = 0.5 * gSum(magSqr(U)*mesh.V().field())/gSum(mesh.V().field());

volScalarField epsMag = mag((fvc::grad(U) && fvc::grad(U))); 

vsfEps = nuValue * (gSum(epsMag*mesh.V().field())/gSum(mesh.V().field()));

Info<< "VSF Ek: " << vsfEk 
    << "  VSF Eps: " << vsfEps << endl;

vsfEkEpsFile << " " << vsfEk << " " << vsfEps;