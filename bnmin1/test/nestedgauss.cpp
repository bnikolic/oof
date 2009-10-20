/**
   Bojan Nikolic <b.nikolic@mrao.cam.ac.uk>
   
   Command-line interface to Nested Sampling of a simple Gaussian
   model , for testing purposes only

*/

#include <iostream>
#include <boost/format.hpp>

#include "nestedgauss.hpp"

#include <boost/program_options.hpp>

void printLkl(const std::list<Minim::WPPoint> &lp,
	      std::ostream &os)
{
  for(std::list<Minim::WPPoint>::const_iterator i=lp.begin();
      i != lp.end();
      ++i)
  {
    os<<(boost::format("[%g,%g,%g] : post=%g") % i->p[0] % i->p[1] % i->p[2] % (i->w* exp(-i->ll)))
      <<std::endl;
  }
}

int main(int ac, char* av[])
{   
  using namespace boost::program_options;
  
  options_description desc("Allowed options");
  desc.add_options()
    ("help", "Produce this help message")
    ("monitor", "Monitor the progression of the sampling")
    ("postr", "Print the posterior distribution")
    ("l_sigma", 
     value<double>()->default_value(1.0),
     "The width of the likelihood function")
    ("sigma", 
     value<double>()->default_value(0.1),
     "Sigma for use in the nested sample generation")
    ("nsample", 
     value<size_t>()->default_value(150),
     "Number of nested sampels to make")
    ("ndim", 
     value<size_t>()->default_value(3),
     "Number of dimensions in the problem");


  variables_map vm;        
  store(parse_command_line(ac, av, desc), vm);
  notify(vm);    

  if (vm.count("help"))
  {
    std::cout<<"Exeriment with nested sampling"
	     <<std::endl
	     <<std::endl
	     <<"GPL license -- you have the right to the source code. See COPYING"
	     <<desc;
  }
  else
  {
    const double l_sigma=vm["l_sigma"].as<double>();
    const double sigma=vm["sigma"].as<double>();
    const size_t nsample=vm["nsample"].as<size_t>();
    const size_t ndim=vm["ndim"].as<size_t>();
    
    pdesc d=mkDesc(l_sigma,
		   vm.count("monitor"),
		   sigma,
		   ndim
		   );

    std::cout<<"Evidence: "
	     <<d.s->sample(nsample)
	     <<" (expected: "
	     <<pow(1.0/2.0, ndim)* pow(erf(1.0/l_sigma/sqrt(2)),ndim)
	     <<")"
	     <<std::endl;

    if(vm.count("postr"))
    {
      printLkl(d.s->g_post(),
	       std::cout);
    }
  }
  
  return 0;
}

