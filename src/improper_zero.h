/* -*- c++ -*- ----------------------------------------------------------
   LAMMPS - Large-scale Atomic/Molecular Massively Parallel Simulator
   https://www.lammps.org/, Sandia National Laboratories
   The LAMMPS Developers, developers@lammps.org

   Copyright (2003) Sandia Corporation.  Under the terms of Contract
   DE-AC04-94AL85000 with Sandia Corporation, the U.S. Government retains
   certain rights in this software.  This software is distributed under
   the GNU General Public License.

   See the README file in the top-level LAMMPS directory.
------------------------------------------------------------------------- */

#ifdef IMPROPER_CLASS
// clang-format off
ImproperStyle(zero,ImproperZero);
// clang-format on
#else

#ifndef LMP_IMPROPER_ZERO_H
#define LMP_IMPROPER_ZERO_H

#include "improper.h"

namespace LAMMPS_NS {

class ImproperZero : public Improper {
 public:
  ImproperZero(class LAMMPS *);
  ~ImproperZero() override;
  void compute(int, int) override;
  void coeff(int, char **) override;
  void settings(int, char **) override;

  void write_restart(FILE *) override;
  void read_restart(FILE *) override;
  void write_data(FILE *) override;

 protected:
  int coeffflag;

  virtual void allocate();
};

}    // namespace LAMMPS_NS

#endif
#endif
