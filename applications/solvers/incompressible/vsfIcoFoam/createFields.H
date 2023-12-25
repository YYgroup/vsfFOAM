Info<< "Reading physicalProperties\n" << endl;

IOdictionary physicalProperties     // 创建IOdictionary对象,字典变量名和字典文件名取相同
(
    IOobject
    (
        "physicalProperties",   // 字典名称
        runTime.constant(),     // 字典位置(在constant文件夹下)
        mesh,    // 和mesh相关
        IOobject::MUST_READ_IF_MODIFIED,    // 如果字典文件被修改，则必须从字典读取
        IOobject::NO_WRITE      // 不向字典写入
    )
);
    
dimensionedScalar nu
(
    "nu",
    dimViscosity,
    physicalProperties.lookup("nu")   //由lookup函数读取physicalProperties中的nu的值
);

Info<< "Reading field p\n" << endl;
volScalarField p
(
    IOobject
    (
        "p",
        runTime.timeName(),
        mesh,
        IOobject::MUST_READ,
        IOobject::AUTO_WRITE
    ),
    mesh
);


Info<< "Reading field U\n" << endl;
volVectorField U
(
    IOobject
    (
        "U",
        runTime.timeName(),
        mesh,
        IOobject::MUST_READ,
        IOobject::AUTO_WRITE
    ),
    mesh
);


#include "createPhi.H"

#include "createVSF.H"

label pRefCell = 0;
scalar pRefValue = 0.0;
setRefCell(p, mesh.solution().dict().subDict("PISO"), pRefCell, pRefValue);
mesh.schemes().setFluxRequired(p.name());
