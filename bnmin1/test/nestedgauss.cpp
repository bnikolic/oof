/**
   Bojan Nikolic <b.nikolic@mrao.cam.ac.uk>
   
   Command-line interface to Nested Sampling of a simple Gaussian
   model , for testing purposes only

*/

#include "nestedgauss.hpp"

#include <boost/program_options.hpp>


int main(int ac, char* av[])
{   
  using namespace boost::program_options;
  
  options_description desc("Allowed options");
  desc.add_options()
    ("help", "Produce this help message")
    ("monitor", "Monitor the progression of the sampling")
    ("l_sigma", 
     value<double>()->default_value(1.0),
     "The width of the likelihood function");

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
    std::cout<<"Evidence: "
	     <<getEvidence(l_sigma,
			   vm.count("monitor"))
	     <<" (expected: "
	     <<1.0/8* pow(erf(1.0/l_sigma/sqrt(2)),3)
	     <<")"
	     <<std::endl;
  }
  
  return 0;
}

