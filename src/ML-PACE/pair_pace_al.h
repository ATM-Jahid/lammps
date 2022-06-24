/* -*- c++ -*- ----------------------------------------------------------
   LAMMPS - Large-scale Atomic/Molecular Massively Parallel Simulator
   https://www.lammps.org/, Sandia National Laboratories
   Steve Plimpton, sjplimp@sandia.gov

   This software is distributed under the GNU General Public License.

   See the README file in the top-level LAMMPS directory.
------------------------------------------------------------------------- */

/*
Copyright 2022 Yury Lysogorskiy^1, Anton Bochkarev^1,
  Matous Mrovec^1, Ralf Drautz^1

^1: Ruhr-University Bochum, Bochum, Germany
 */

//
// Created by Lysogorskiy Yury on 1.01.22.
//


#ifdef PAIR_CLASS
// clang-format off
PairStyle(pace/al,PairPACEActiveLearning)
// clang-format on
#else

#ifndef LMP_PAIR_PACE_AL_H
#define LMP_PAIR_PACE_AL_H

#include "pair.h"
#include "dump_custom.h"
#include "compute_pace.h"

namespace LAMMPS_NS {

    class PairPACEActiveLearning : public Pair {
        friend class ComputePaceAtom;

    public:
        PairPACEActiveLearning(class LAMMPS *);

        ~PairPACEActiveLearning() override;

        void compute(int, int) override;

        void settings(int, char **) override;

        void coeff(int, char **) override;

        void init_style() override;

        double init_one(int, int) override;

        void *extract(const char *, int &) override;

    protected:
        struct ACEALImpl *aceimpl;

        int gamma_grade_eval_freq = 1;
        bool is_dump_extrapolative_structures = true;
        DumpCustom *dump = nullptr;
        Compute *computePaceAtom = nullptr;
        int natoms; //total number of atoms

        double gamma_lower_bound = 1.5;
        double gamma_upper_bound = 10;
        double max_gamma_grade_per_structure = 0;

        virtual void allocate();

        void read_files(char *, char *);

        inline int equal(double *x, double *y);

        double rcutmax;               // max cutoff for all elements
        int nelements;                // # of unique elements
        int bevaluator_timestep;    // timestep, on which gamma grade were computed
        int bevaluator_timestep_shift = 0; //
        double *extrapolation_grade_gamma; //per-atom gamma value

        double **scale;
    };

}

#endif
#endif