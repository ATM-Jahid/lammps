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

#ifdef FIX_CLASS
// clang-format off
FixStyle(temp/csld,FixTempCSLD);
// clang-format on
#else

#ifndef LMP_FIX_TEMP_CSLD_H
#define LMP_FIX_TEMP_CSLD_H

#include "fix.h"

namespace LAMMPS_NS {

class FixTempCSLD : public Fix {
 public:
  FixTempCSLD(class LAMMPS *, int, char **);
  ~FixTempCSLD() override;
  int setmask() override;
  void init() override;
  void end_of_step() override;
  int modify_param(int, char **) override;
  void reset_target(double) override;
  double compute_scalar() override;
  void write_restart(FILE *) override;
  void restart(char *buf) override;
  void *extract(const char *, int &) override;

 private:
  double t_start, t_stop, t_period, t_target;
  double **vhold;
  double energy;
  int nmax, which;
  int tstyle, tvar;
  char *tstr;

  char *id_temp;
  class Compute *temperature;
  int tflag;

  class RanMars *random;
};

}    // namespace LAMMPS_NS

#endif
#endif
