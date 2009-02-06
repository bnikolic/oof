// Copyright (2009) Bojan Nikolic <b.nikolic@mrao.cam.ac.uk>
//
// This file is part of BNLib
// BNLIB is free software: you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// BNLIB is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
// or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public
// License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with BNLIB.  If not, see <http://www.gnu.org/licenses/>.
//
// Comments regarding this example welcome at: 
// Bojan Nikolic <b.nikolic@mrao.cam.ac.uk>

#include <iostream>
#include <boost/program_options.hpp>

#include "../src/kolmog/kolmogorov_3d.hxx"
#include "../src/bnrandom.hxx"

int main(int argc,  char* argv[])
{
  using namespace boost::program_options;

  options_description desc("Allowed options");
  desc.add_options()
    ("nx", value<size_t>(),
     "Number of pixels in the X direction")
    ("ny", value<size_t>(),
     "Number of pixels in the Y direction")
    ("nz", value<size_t>(),
     "Number of pixels in the Z direction")
    ("help", "Produce this help message");

  positional_options_description p;
  p.add("nx", 1);
  p.add("ny", 1);
  p.add("nz", 1);

  variables_map vm;
  store(command_line_parser(argc, argv).
	options(desc).positional(p).run(), 
	vm);
  notify(vm);

  if (vm.count("help"))
  {
    std::cout<<"Generate a Kolmogorov phase volume and write it out standard output"
	     <<std::endl
	     <<"This program is part of  BNLib"<<std::endl
	     <<"GPL license -- you have the right to the source code. See COPYING"<<std::endl
	     <<std::endl
	     <<"The dimensions of the volume must each be of 2^n+1 type and nx >= ny >= nz"<<std::endl
	     <<"The output is written as a contiugous sequence of IEEE double-precision floating point values"<<std::endl
	     <<"The endianity is defined by your computer"<<std::endl
	     <<"The output is binary and will go to standard output; therefore it is best"<<std::endl
	     <<"to redirect to a file"<<std::endl
	     <<std::endl
	     <<"For example:"<<std::endl
	     <<"     ./kvolume 1025 257 129 > phasevolume.dat"<<std::endl
	     <<std::endl
	     <<std::endl
	     <<std::endl
	     <<desc;
  }
  else
  {
    using namespace BNLib;

    const size_t nx = vm["nx"].as<size_t>();
    const size_t ny = vm["ny"].as<size_t>();
    const size_t nz = vm["nz"].as<size_t>();

    const size_t totalsize=nx*ny*nz;
    
    double * cube = new double[totalsize];
    BNLib::NormDistZM dist(1.0);    

    Kolmogorov3D(cube,
		 nx,
		 ny,
		 nz,
		 dist,
		 KInitialEFB & KBalancedIters & KEdgeBalanced);    

    std::cout.write((char *)cube,
		    sizeof(double)*totalsize);
    
    delete[] cube;
  }  
}



