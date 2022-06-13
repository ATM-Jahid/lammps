/* ----------------------------------------------------------------------
   LAMMPS - Large-scale Atomic/Molecular Massively Parallel Simulator
   http://lammps.sandia.gov, Sandia National Laboratories
   Steve Plimpton, sjplimp@sandia.gov

   Copyright (2003) Sandia Corporation.  Under the terms of Contract
   DE-AC04-94AL85000 with Sandia Corporation, the U.S. Government retains
   certain rights in this software.  This software is distributed under
   the GNU General Public License.

   See the README file in the top-level LAMMPS directory.
------------------------------------------------------------------------- */

/* ----------------------------------------------------------------------
   Contributing author: Sebastian Hütter (OvGU)
------------------------------------------------------------------------- */

#include "memory_kokkos.h"
#include "meam_kokkos.h"
using namespace LAMMPS_NS;

/* ---------------------------------------------------------------------- */

template<class DeviceType>
MEAMKokkos<DeviceType>::MEAMKokkos(Memory *mem) : MEAM(mem)
{
}

template<class DeviceType>
MEAMKokkos<DeviceType>::~MEAMKokkos()
{
  MemoryKokkos *memoryKK = (MemoryKokkos *)memory;
  
  memoryKK->destroy_kokkos(k_phirar6,phirar6);
  memoryKK->destroy_kokkos(k_phirar5,phirar5);
  memoryKK->destroy_kokkos(k_phirar4,phirar4);
  memoryKK->destroy_kokkos(k_phirar3,phirar3);
  memoryKK->destroy_kokkos(k_phirar2,phirar2);
  memoryKK->destroy_kokkos(k_phirar1,phirar1);
  memoryKK->destroy_kokkos(k_phirar,phirar);
  memoryKK->destroy_kokkos(k_phir,phir);

  memoryKK->destroy_kokkos(k_rho,rho);
  memoryKK->destroy_kokkos(k_rho0,rho0);
  memoryKK->destroy_kokkos(k_rho1,rho1);
  memoryKK->destroy_kokkos(k_rho2,rho2);
  memoryKK->destroy_kokkos(k_rho3,rho3);
  memoryKK->destroy_kokkos(k_frhop,frhop);
  memoryKK->destroy_kokkos(k_gamma,gamma);
  memoryKK->destroy_kokkos(k_dgamma1,dgamma1);
  memoryKK->destroy_kokkos(k_dgamma2,dgamma2);
  memoryKK->destroy_kokkos(k_dgamma3,dgamma3);
  memoryKK->destroy_kokkos(k_arho2b,arho2b);

  memoryKK->destroy_kokkos(k_arho1,arho1);
  memoryKK->destroy_kokkos(k_arho2,arho2);
  memoryKK->destroy_kokkos(k_arho3,arho3);
  memoryKK->destroy_kokkos(k_arho3b,arho3b);
  memoryKK->destroy_kokkos(k_t_ave,t_ave);
  memoryKK->destroy_kokkos(k_tsq_ave,tsq_ave);

  memoryKK->destroy_kokkos(k_scrfcn,scrfcn);
  memoryKK->destroy_kokkos(k_dscrfcn,dscrfcn);
  memoryKK->destroy_kokkos(k_fcpair,fcpair);
}
#include "meam_setup_done_kokkos.h"
#include "meam_funcs_kokkos.h"
#include "meam_dens_init_kokkos.h"
#include "meam_dens_final_kokkos.h"
#include "meam_force_kokkos.h"
//

