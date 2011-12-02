
ADD_LIBRARY (bnmin1 SHARED
                    bnmin_main.hxx bnmin_main.cxx  markovchain.cxx
                    markovchain.hxx mcmonitor.cxx mcmonitor.hxx
                    mcpoint.cxx mcpoint.hxx metropolis.cxx
                    metropolis.hxx metro_propose.cxx metro_propose.hxx
                    minim.cxx minim.hxx minimio.cxx minimio.hxx
                    minimmodel.cxx minimmodel.hxx monitor.cxx
                    monitor.hxx nestederr.cxx nestederr.hxx
                    nestedinitial.cxx nestedinitial.hxx
                    nestedsampler.cxx nestedsampler.hxx paramalgo.cxx
                    paramalgo.hxx paramctr.hxx pda.hxx
                    prior_sampler.cxx prior_sampler.hxx priors.cxx
                    priors.hxx 
                    sets/cholesky.hpp sets/ellipsoids.cxx
                    sets/ellipsoids.hxx sets/ellipsoids_sample.cxx
                    sets/ellipsoids_sample.hxx sets/spheres.cxx
                    sets/spheres.hxx)

target_link_libraries(bnmin1
        -lgsl -lgslcblas
)

INSTALL_FILES(/include  .hxx minim.hxx minimmodel.hxx paramctr.hxx	
			monitor.hxx 	
			bnmin_main.hxx priors.hxx metropolis.hxx	
                 	nestedsampler.hxx mcpoint.hxx	
			nestederr.hxx nestedinitial.hxx 
			prior_sampler.hxx mcmonitor.hxx )

INSTALL_TARGETS(/lib bnmin1)
