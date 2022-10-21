/* ----------------------------------------------------------------------
   LAMMPS - Large-scale Atomic/Molecular Massively Parallel Simulator
   https://www.lammps.org/, Sandia National Laboratories
   The LAMMPS Developers, developers@lammps.org

   Copyright (2003) Sandia Corporation.  Under the terms of Contract
   DE-AC04-94AL85000 with Sandia Corporation, the U.S. Government retains
   certain rights in this software.  This software is distributed under
   the GNU General Public License.

   See the README file in the top-level LAMMPS directory.
------------------------------------------------------------------------- */

#include "nstencil_half_bin_3d.h"

using namespace LAMMPS_NS;

/* ---------------------------------------------------------------------- */

NStencilHalfBin3d::NStencilHalfBin3d(LAMMPS *lmp) : NStencil(lmp) {}

/* ----------------------------------------------------------------------
   create stencil based on bin geometry and cutoff
------------------------------------------------------------------------- */

void NStencilHalfBin3d::create()
{
  int i, j, k;

  nstencil = 0;

  for (k = 0; k <= sz; k++)
    for (j = -sy; j <= sy; j++)
      for (i = -sx; i <= sx; i++)
        if (k > 0 || j > 0 || (j == 0 && i > 0))
          if (bin_distance(i, j, k) < cutneighmaxsq)
            stencil[nstencil++] = k * mbiny * mbinx + j * mbinx + i;
}
