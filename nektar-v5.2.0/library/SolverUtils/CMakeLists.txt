SET(SOLVER_UTILS_SOURCES
  Core/Coupling.cpp
  Core/CouplingFile.cpp
  Core/Misc.cpp
  Core/SessionFunction.cpp
  AdvectionSystem.cpp
  Advection/Advection.cpp
  Advection/Advection3DHomogeneous1D.cpp
  Advection/AdvectionFR.cpp
  Advection/AdvectionNonConservative.cpp
  Advection/AdvectionWeakDG.cpp
  Diffusion/Diffusion.cpp
  Diffusion/Diffusion3DHomogeneous1D.cpp
  Diffusion/DiffusionLDG.cpp
  Diffusion/DiffusionLFR.cpp
  Diffusion/DiffusionLFRNS.cpp
  Diffusion/DiffusionIP.cpp
  Driver.cpp
  DriverAdaptive.cpp
  DriverArnoldi.cpp
  DriverModifiedArnoldi.cpp
  DriverStandard.cpp
  DriverSteadyState.cpp	
  EquationSystem.cpp
  Filters/Filter.cpp
  Filters/FilterAeroForces.cpp
  Filters/FilterAdjointGrad.cpp
  Filters/FilterAverageFields.cpp
  Filters/FilterMaxMinFields.cpp
  Filters/FilterCheckpoint.cpp
  Filters/FilterEnergy1D.cpp
  Filters/FilterEnergy.cpp
  Filters/FilterTangentEnergy.cpp
  Filters/FilterTGVadjgrad.cpp
  Filters/FilterError.cpp
  Filters/FilterHistoryPoints.cpp
  Filters/FilterMean.cpp
  Filters/FilterModalEnergy.cpp
  Filters/FilterMovingAverage.cpp
  Filters/FilterFieldConvert.cpp
  Filters/FilterThresholdMax.cpp
  Filters/FilterThresholdMin.cpp
  RiemannSolvers/RiemannSolver.cpp
  RiemannSolvers/UpwindSolver.cpp
  RiemannSolvers/UpwindLDGSolver.cpp
  UnsteadySystem.cpp
  MMFSystem.cpp
  Forcing/Forcing.cpp
  Forcing/ForcingAbsorption.cpp
  Forcing/ForcingBody.cpp
  Forcing/ForcingMovingReferenceFrame.cpp
  Forcing/ForcingNoise.cpp
  Forcing/ForcingProgrammatic.cpp
  Forcing/ForcingTangentTGV.cpp
  Forcing/ForcingAdjTGV.cpp
  Forcing/ForcingBaseFlow.cpp
)

SET(SOLVER_UTILS_HEADERS
  Core/Coupling.h
  Core/CouplingFile.h
  Core/Misc.h
  Core/SessionFunction.h
  AdvectionSystem.h
  Advection/Advection.h
  Advection/AdvectionFR.h
  Advection/Advection3DHomogeneous1D.h
  Advection/AdvectionNonConservative.h
  Advection/AdvectionWeakDG.h
  Diffusion/Diffusion.h
  Diffusion/Diffusion3DHomogeneous1D.h
  Diffusion/DiffusionLDG.h
  Diffusion/DiffusionLFR.h
  Diffusion/DiffusionLFRNS.h
  Diffusion/DiffusionIP.h
  Driver.h
  DriverAdaptive.h
  DriverArnoldi.h
  DriverModifiedArnoldi.h
  DriverStandard.h
  DriverSteadyState.h
  EquationSystem.h
  Filters/Filter.h
  Filters/FilterAeroForces.h
  Filters/FilterAdjointGrad.h
  Filters/FilterAverageFields.h
  Filters/FilterMaxMinFields.h
  Filters/FilterCheckpoint.h
  Filters/FilterEnergy1D.h
  Filters/FilterEnergy.h
  Filters/FilterTangentEnergy.h
  Filters/FilterTGVadjgrad.h
  Filters/FilterError.h
  Filters/FilterHistoryPoints.h
  Filters/FilterInterfaces.hpp
  Filters/FilterMean.h
  Filters/FilterModalEnergy.h
  Filters/FilterMovingAverage.h
  Filters/FilterFieldConvert.h
  Filters/FilterThresholdMax.h
  Filters/FilterThresholdMin.h
  RiemannSolvers/RiemannSolver.h
  RiemannSolvers/UpwindSolver.h
  RiemannSolvers/UpwindLDGSolver.h
  SolverUtils.hpp
  SolverUtilsDeclspec.h
  UnsteadySystem.h
  Forcing/Forcing.h
  Forcing/ForcingAbsorption.h
  Forcing/ForcingBody.h
  Forcing/ForcingMovingReferenceFrame.h
  Forcing/ForcingNoise.h
  Forcing/ForcingProgrammatic.h
  Forcing/ForcingTangentTGV.h
  Forcing/ForcingAdjTGV.h
  Forcing/ForcingBaseFlow.h
)

IF (NEKTAR_USE_ARPACK)
  SET(SOLVER_UTILS_SOURCES ${SOLVER_UTILS_SOURCES}
    DriverArpack.cpp)
  SET(SOLVER_UTILS_HEADERS ${SOLVER_UTILS_HEADERS}
    DriverArpack.h)
ENDIF (NEKTAR_USE_ARPACK)

IF (NEKTAR_USE_CWIPI)
  SET(SOLVER_UTILS_SOURCES ${SOLVER_UTILS_SOURCES}
    Core/CouplingCwipi.cpp)
  SET(SOLVER_UTILS_HEADERS ${SOLVER_UTILS_HEADERS}
    Core/CouplingCwipi.h)
ENDIF (NEKTAR_USE_CWIPI)

ADD_DEFINITIONS(-DSOLVER_UTILS_EXPORTS)

ADD_NEKTAR_LIBRARY(SolverUtils
    SOURCES ${SOLVER_UTILS_SOURCES}
    HEADERS ${SOLVER_UTILS_HEADERS}
    DEPENDS FieldUtils
    SUMMARY "Nektar++ SolverUtils library"
    DESCRIPTION "This library provides support classes and routines for constructing complete spectral/hp element solvers.")

IF (NEKTAR_USE_VTK)
    IF (VTK_MAJOR_VERSION LESS 6)
        TARGET_LINK_LIBRARIES(SolverUtils LINK_PUBLIC vtkCommon vtkIO vtkGraphics vtkFiltersCore)
    ELSEIF (VTK_MAJOR_VERSION  GREATER_EQUAL 9)
        TARGET_LINK_LIBRARIES(SolverUtils LINK_PUBLIC VTK::CommonCore VTK::IOLegacy VTK::IOXML VTK::FiltersCore)
        vtk_module_autoinit(
                TARGETS SolverUtils
                MODULES VTK::CommonCore VTK::IOLegacy VTK::IOXML VTK::FiltersCore)
    ELSE ()
        TARGET_LINK_LIBRARIES(SolverUtils LINK_PUBLIC vtkCommonCore vtkIOLegacy vtkIOXML vtkFiltersCore)
    ENDIF ()
ENDIF (NEKTAR_USE_VTK)
