ADD_UTILITIES_EXECUTABLE(FieldConvert
    COMPONENT fieldconvert DEPENDS FieldUtils SOURCES FieldConvert.cpp)

#ADD_NEKTAR_TEST(chan3D_tec)  # This test is covered in bfs_tec
#ADD_NEKTAR_TEST(chan3D_vtu)  # This does not currently work -- hash metric
#ADD_NEKTAR_TEST(chan3D_vort) # This is covered by bfs_vort

ADD_NEKTAR_TEST(chan3D_tec_n10)
ADD_NEKTAR_TEST(chan3D_interppointsplane)
ADD_NEKTAR_TEST(chan3D_interppointsbox)
ADD_NEKTAR_TEST(chan3DH1D_interppointsplane)
ADD_NEKTAR_TEST(chan3DH1D_interppointsbox)
ADD_NEKTAR_TEST(chan_quad_interppointdatatofld)
ADD_NEKTAR_TEST(chan_interpfield_nparts)
ADD_NEKTAR_TEST(compositeid)
ADD_NEKTAR_TEST(bfs_probe)
ADD_NEKTAR_TEST(bfs_tec)
ADD_NEKTAR_TEST(bfs_tec_rng)
ADD_NEKTAR_TEST(bfs_vort)
ADD_NEKTAR_TEST(bfs_vort_rng)
ADD_NEKTAR_TEST(pointdatatofld)
ADD_NEKTAR_TEST(chan3D_csv)
ADD_NEKTAR_TEST(chan3D_pts)
#ADD_NEKTAR_TEST(chan3DH1D_vtu)
ADD_NEKTAR_TEST(chan3DH1D_meanmode)
ADD_NEKTAR_TEST(chan3DH1D_cfl)
ADD_NEKTAR_TEST(chan3DH1D_cfl_meanmode)
ADD_NEKTAR_TEST(chan3DH1D_plane)
ADD_NEKTAR_TEST(chan3DH1D_stretch)
ADD_NEKTAR_TEST(chan3D_modp)
ADD_NEKTAR_TEST(chan3D_probe)
ADD_NEKTAR_TEST(cube_prismhex)
ADD_NEKTAR_TEST(cube_prismhex_range)
ADD_NEKTAR_TEST(chan3D_equispacedoutput)
ADD_NEKTAR_TEST(chan3D_isocontour)
ADD_NEKTAR_TEST(chan3D_cfl)
ADD_NEKTAR_TEST(interpfield)
ADD_NEKTAR_TEST(interpfieldline)
ADD_NEKTAR_TEST(interpfield_4tri_to_1tri)
ADD_NEKTAR_TEST(interpfield_4quad_to_6tri)
ADD_NEKTAR_TEST(interpfield_chan3DH1D_to_chan3DH1D)
ADD_NEKTAR_TEST(interpfield_chan3DH1D_to_hex)
ADD_NEKTAR_TEST(interpfield_hex_to_chan3DH1D)
ADD_NEKTAR_TEST(naca0012_bnd_equispacedoutput)
ADD_NEKTAR_TEST(smallmesh_isocontour)
ADD_NEKTAR_TEST(kovas2)
ADD_NEKTAR_TEST(chan3D_interppointdatatofld)
ADD_NEKTAR_TEST(chan3D_interppointdatatofld_interpcoord)
ADD_NEKTAR_TEST(chan3D_ptsTocsv)
ADD_NEKTAR_TEST(chan3D_csvTopts)
ADD_NEKTAR_TEST(chan3D_npart_tec)
ADD_NEKTAR_TEST(wss_3D_periodic)
ADD_NEKTAR_TEST(scale_compressed_2D)
ADD_NEKTAR_TEST(naca0012_3D_bnd)
ADD_NEKTAR_TEST(Helmholtz)
ADD_NEKTAR_TEST(Hex_channel_C0helmsmoothing)
ADD_NEKTAR_TEST(surfDist)
ADD_NEKTAR_TEST(bndextract)

IF (NEKTAR_USE_METIS OR NEKTAR_USE_SCOTCH)
    ADD_NEKTAR_TEST(chan3D_part_only)
    ADD_NEKTAR_TEST(Tet_channel_npart_wss)
ENDIF()

IF (NEKTAR_USE_MPI)
    ADD_NEKTAR_TEST(chan3D_tec_par)
    #ADD_NEKTAR_TEST(chan3D_vtu_par)a
    ADD_NEKTAR_TEST(chan3D_interppointsplane_par)
    ADD_NEKTAR_TEST(chan3D_interppointsbox_par)
    ADD_NEKTAR_TEST(chan3DH1D_interppointsplane_par)
    ADD_NEKTAR_TEST(chan3DH1D_interppointsbox_par)
    ADD_NEKTAR_TEST(chan3D_vort_par)
ENDIF (NEKTAR_USE_MPI)

IF (NEKTAR_USE_HDF5)
    ADD_NEKTAR_TEST(interpfield_hdf5)
ENDIF()

IF (NEKTAR_USE_VTK)
    #ADD_NEKTAR_TEST(bfs_vtu_multiblock)
    ADD_NEKTAR_TEST(chan3DH1D_vtu_legacy)
    IF (VTK_MAJOR_VERSION GREATER_EQUAL 8)
    #    ADD_NEKTAR_TEST(chan3D_vtu_highorder)
    ENDIF()
ENDIF()
