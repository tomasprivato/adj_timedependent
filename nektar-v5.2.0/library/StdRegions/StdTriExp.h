///////////////////////////////////////////////////////////////////////////////
//
// File StdTriExp.h
//
// For more information, please see: http://www.nektar.info
//
// The MIT License
//
// Copyright (c) 2006 Division of Applied Mathematics, Brown University (USA),
// Department of Aeronautics, Imperial College London (UK), and Scientific
// Computing and Imaging Institute, University of Utah (USA).
//
// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the "Software"),
// to deal in the Software without restriction, including without limitation
// the rights to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included
// in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
// OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
// THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.
//
// Description: Header field for triangle routines built upon StdExpansion2D
//
///////////////////////////////////////////////////////////////////////////////

#ifndef NEKTAR_LIB_STDREGIONS_STDTRIEXP_H
#define NEKTAR_LIB_STDREGIONS_STDTRIEXP_H

#include <StdRegions/StdExpansion2D.h>
#include <StdRegions/StdRegions.hpp>
#include <StdRegions/StdRegionsDeclspec.h>

namespace Nektar
{
namespace StdRegions
{
class StdMatrixKey;

class StdTriExp : virtual public StdExpansion2D
{
public:
    STD_REGIONS_EXPORT StdTriExp();
    STD_REGIONS_EXPORT StdTriExp(const LibUtilities::BasisKey &Ba,
                                 const LibUtilities::BasisKey &Bb);
    STD_REGIONS_EXPORT StdTriExp(const StdTriExp &T);
    STD_REGIONS_EXPORT ~StdTriExp();

protected:
    //-------------------------------
    // Integration Methods
    //-------------------------------
    STD_REGIONS_EXPORT virtual NekDouble v_Integral(
        const Array<OneD, const NekDouble> &inarray);

    //----------------------------
    // Differentiation Methods
    //----------------------------
    STD_REGIONS_EXPORT virtual void v_PhysDeriv(
        const Array<OneD, const NekDouble> &inarray,
        Array<OneD, NekDouble> &out_d0, Array<OneD, NekDouble> &out_d1,
        Array<OneD, NekDouble> &out_d2 = NullNekDouble1DArray);
    STD_REGIONS_EXPORT virtual void v_PhysDeriv(
        const int dir, const Array<OneD, const NekDouble> &inarray,
        Array<OneD, NekDouble> &outarray);
    STD_REGIONS_EXPORT virtual void v_StdPhysDeriv(
        const Array<OneD, const NekDouble> &inarray,
        Array<OneD, NekDouble> &out_d0, Array<OneD, NekDouble> &out_d1,
        Array<OneD, NekDouble> &out_d2 = NullNekDouble1DArray);
    STD_REGIONS_EXPORT virtual void v_StdPhysDeriv(
        const int dir, const Array<OneD, const NekDouble> &inarray,
        Array<OneD, NekDouble> &outarray);

    //---------------------------------------
    // Transforms
    //---------------------------------------
    STD_REGIONS_EXPORT virtual void v_BwdTrans(
        const Array<OneD, const NekDouble> &inarray,
        Array<OneD, NekDouble> &outarray);
    STD_REGIONS_EXPORT virtual void v_BwdTrans_SumFac(
        const Array<OneD, const NekDouble> &inarray,
        Array<OneD, NekDouble> &outarray);
    STD_REGIONS_EXPORT virtual void v_BwdTrans_SumFacKernel(
        const Array<OneD, const NekDouble> &base0,
        const Array<OneD, const NekDouble> &base1,
        const Array<OneD, const NekDouble> &inarray,
        Array<OneD, NekDouble> &outarray, Array<OneD, NekDouble> &wsp,
        bool doCheckCollDir0, bool doCheckCollDir1);
    STD_REGIONS_EXPORT virtual void v_FwdTrans(
        const Array<OneD, const NekDouble> &inarray,
        Array<OneD, NekDouble> &outarray);
    STD_REGIONS_EXPORT virtual void v_FwdTransBndConstrained(
        const Array<OneD, const NekDouble> &inarray,
        Array<OneD, NekDouble> &outarray);

    //---------------------------------------
    // Inner product functions
    //---------------------------------------
    STD_REGIONS_EXPORT virtual void v_IProductWRTBase(
        const Array<OneD, const NekDouble> &inarray,
        Array<OneD, NekDouble> &outarray);
    STD_REGIONS_EXPORT virtual void v_IProductWRTBase_MatOp(
        const Array<OneD, const NekDouble> &inarray,
        Array<OneD, NekDouble> &outarray);
    STD_REGIONS_EXPORT virtual void v_IProductWRTBase_SumFac(
        const Array<OneD, const NekDouble> &inarray,
        Array<OneD, NekDouble> &outarray, bool multiplybyweights = true);
    STD_REGIONS_EXPORT virtual void v_IProductWRTBase_SumFacKernel(
        const Array<OneD, const NekDouble> &base0,
        const Array<OneD, const NekDouble> &base1,
        const Array<OneD, const NekDouble> &inarray,
        Array<OneD, NekDouble> &outarray, Array<OneD, NekDouble> &wsp,
        bool doCheckCollDir0, bool doCheckCollDir1);
    STD_REGIONS_EXPORT virtual void v_IProductWRTDerivBase(
        const int dir, const Array<OneD, const NekDouble> &inarray,
        Array<OneD, NekDouble> &outarray);
    STD_REGIONS_EXPORT virtual void v_IProductWRTDerivBase_MatOp(
        const int dir, const Array<OneD, const NekDouble> &inarray,
        Array<OneD, NekDouble> &outarray);
    STD_REGIONS_EXPORT virtual void v_IProductWRTDerivBase_SumFac(
        const int dir, const Array<OneD, const NekDouble> &inarray,
        Array<OneD, NekDouble> &outarray);

    //---------------------------------------
    // Evaluation functions
    //---------------------------------------
    STD_REGIONS_EXPORT virtual void v_LocCoordToLocCollapsed(
        const Array<OneD, const NekDouble> &xi, Array<OneD, NekDouble> &eta);
    STD_REGIONS_EXPORT virtual void v_LocCollapsedToLocCoord(
        const Array<OneD, const NekDouble> &eta, Array<OneD, NekDouble> &xi);
    STD_REGIONS_EXPORT virtual void v_FillMode(
        const int mode, Array<OneD, NekDouble> &outarray);
    STD_REGIONS_EXPORT NekDouble v_PhysEvaluateBasis(
        const Array<OneD, const NekDouble> &coords, int mode) final;

    //---------------------------
    // Helper functions
    //---------------------------
    STD_REGIONS_EXPORT virtual int v_GetNverts() const;
    STD_REGIONS_EXPORT virtual int v_GetNtraces() const;
    STD_REGIONS_EXPORT virtual LibUtilities::ShapeType v_DetShapeType() const;
    STD_REGIONS_EXPORT virtual int v_NumBndryCoeffs() const;
    STD_REGIONS_EXPORT virtual int v_NumDGBndryCoeffs() const;
    STD_REGIONS_EXPORT virtual int v_GetTraceNcoeffs(const int i) const;
    STD_REGIONS_EXPORT virtual int v_GetTraceNumPoints(const int i) const;
    STD_REGIONS_EXPORT virtual int v_CalcNumberOfCoefficients(
        const std::vector<unsigned int> &nummodes, int &modes_offset);
    STD_REGIONS_EXPORT virtual void v_GetCoords(
        Array<OneD, NekDouble> &coords_x, Array<OneD, NekDouble> &coords_y,
        Array<OneD, NekDouble> &coords_z);
    STD_REGIONS_EXPORT virtual bool v_IsBoundaryInteriorExpansion();
    STD_REGIONS_EXPORT virtual const LibUtilities::BasisKey v_GetTraceBasisKey(
        const int i, const int j) const;

    //--------------------------
    // Mappings
    //--------------------------
    STD_REGIONS_EXPORT virtual int v_GetVertexMap(int localVertexId,
                                                  bool useCoeffPacking = false);
    STD_REGIONS_EXPORT virtual void v_GetInteriorMap(
        Array<OneD, unsigned int> &outarray);

    STD_REGIONS_EXPORT virtual void v_GetBoundaryMap(
        Array<OneD, unsigned int> &outarray);

    STD_REGIONS_EXPORT virtual void v_GetTraceCoeffMap(
        const unsigned int traceid, Array<OneD, unsigned int> &maparray);
#if 0 
            STD_REGIONS_EXPORT  virtual void v_GetTraceToElementMap(
                const int                  eid,
                Array<OneD, unsigned int>& maparray,
                Array<OneD,          int>& signarray,
                Orientation          edgeOrient = eForwards,
                int P = -1,
                int Q = -1);
#endif

    STD_REGIONS_EXPORT virtual void v_GetTraceInteriorToElementMap(
        const int eid, Array<OneD, unsigned int> &maparray,
        Array<OneD, int> &signarray, const Orientation edgeOrient = eForwards);

    //---------------------------------------
    // Wrapper functions
    //---------------------------------------
    STD_REGIONS_EXPORT virtual DNekMatSharedPtr v_GenMatrix(
        const StdMatrixKey &mkey);
    STD_REGIONS_EXPORT virtual DNekMatSharedPtr v_CreateStdMatrix(
        const StdMatrixKey &mkey);

    //---------------------------------------
    // Operator evaluation functions
    //---------------------------------------
    STD_REGIONS_EXPORT virtual void v_MassMatrixOp(
        const Array<OneD, const NekDouble> &inarray,
        Array<OneD, NekDouble> &outarray, const StdMatrixKey &mkey);
    STD_REGIONS_EXPORT virtual void v_LaplacianMatrixOp(
        const Array<OneD, const NekDouble> &inarray,
        Array<OneD, NekDouble> &outarray, const StdMatrixKey &mkey);
    STD_REGIONS_EXPORT virtual void v_SVVLaplacianFilter(
        Array<OneD, NekDouble> &array, const StdMatrixKey &mkey);
    STD_REGIONS_EXPORT virtual void v_ReduceOrderCoeffs(
        int numMin, const Array<OneD, const NekDouble> &inarray,
        Array<OneD, NekDouble> &outarray);
    STD_REGIONS_EXPORT virtual void v_LaplacianMatrixOp(
        const int k1, const int k2, const Array<OneD, const NekDouble> &inarray,
        Array<OneD, NekDouble> &outarray, const StdMatrixKey &mkey);
    STD_REGIONS_EXPORT virtual void v_WeakDerivMatrixOp(
        const int i, const Array<OneD, const NekDouble> &inarray,
        Array<OneD, NekDouble> &outarray, const StdMatrixKey &mkey);
    STD_REGIONS_EXPORT virtual void v_HelmholtzMatrixOp(
        const Array<OneD, const NekDouble> &inarray,
        Array<OneD, NekDouble> &outarray, const StdMatrixKey &mkey);
    STD_REGIONS_EXPORT virtual void v_GeneralMatrixOp_MatOp(
        const Array<OneD, const NekDouble> &inarray,
        Array<OneD, NekDouble> &outarray, const StdMatrixKey &mkey);

    STD_REGIONS_EXPORT virtual void v_MultiplyByStdQuadratureMetric(
        const Array<OneD, const NekDouble> &inarray,
        Array<OneD, NekDouble> &outarray);

    //---------------------------------------
    // Output interpolation functions
    //---------------------------------------
    STD_REGIONS_EXPORT virtual void v_GetSimplexEquiSpacedConnectivity(
        Array<OneD, int> &conn, bool standard = true);
};
typedef std::shared_ptr<StdTriExp> StdTriExpSharedPtr;
} // namespace StdRegions
} // namespace Nektar
#endif // STDTRIEXP_H
