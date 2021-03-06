/*
     Multi-thread test for libRoadrunner

export DYLD_LIBRARY_PATH=/Users/heiland/dev/roadrunner-osx-10.9-cp36m/lib

compile:
clang++ -I/Users/heiland/dev/roadrunner-osx-10.9-cp36m/include -L/Users/heiland/dev/roadrunner-osx-10.9-cp36m/lib -lroadrunner -L/usr/local/opt/libomp/lib -lomp roadrunner_test2.cpp  -o rr1

clang++ -I/usr/local/include -L/Users/heiland/anaconda3/lib/python3.6/site-packages/roadrunner -lroadrunner -L/usr/local/opt/libomp/lib -lomp roadrunner_test2.cpp  -o rr1

PATH_TO_OMP := -L/usr/local/opt/libomp/lib
        $(COMPILE_COMMAND) $(PATH_TO_OMP) -lomp -o $(PROGRAM_NAME) $(ALL_OBJECTS) main.cpp

OLD/gcc:
g++-9 -I/usr/local/include -L/usr/local/lib -lsbml -lsbmlsim sbmlsim_test1.cpp  -fopenmp -o rr1

run:
rr1 toy.xml 1
rr1 toy.xml 99
*/

#include <iostream>
#include <sstream>

#include "sbml/SBMLTypes.h"
//#include "libsbmlsim/libsbmlsim.h"

#include "omp.h"

int main (int argc, char* argv[])
{
  double val;

  if(argc < 3) {
    std::cerr << "Provide args: <name of sbml file> <num threads>" << std::endl;
    exit(1);
  }
  std::istringstream iss(argv[2]);
  int nthreads;
  if (!(iss >> nthreads)) {
    std::cerr << "Invalid number: " << argv[2] << '\n';
    exit(1);
  }

  omp_set_num_threads(nthreads);

  #pragma omp parallel for 
  for (int idx=1; idx< 10; idx++)
  {
    libsbml::SBMLDocument* doc = libsbml::readSBML(argv[1]);
    if (doc->getNumErrors() > 0) {
      std::cerr << "  # errors reading SBML = " << doc->getNumErrors()  << std::endl;
      exit(1);
    }
    libsbml::Model_t *mm = libsbml::SBMLDocument_getModel(doc);
    if (mm == NULL)
    {
      std::cerr << "      mm == NULL)" << std::endl;
      exit(1);
    }

    std::cerr << "  mm = " << mm << std::endl;

    if (mm->getElementBySId("Oxygen") == NULL)
    {
      std::cerr << "      mm->getElementBySId('Oxygen') == NULL)" << std::endl;
    }
    else 
    {
      mm->getElementBySId("Oxygen")->getAttribute("initialConcentration", val);
      std::cerr << "      val = " << val << std::endl;
    //   val += 1.0;
    //   // mm->getElementBySId("Oxygen")->setAttribute("initialConcentration", val );
    //   // mm->getElementBySId("Oxygen")->getAttribute("initialConcentration", val);
    //   std::cerr << "      val = " << val << std::endl;
    }

/*
    double sim_time = 6.0;
    double sbml_dt = 0.0001;
    int print_interval = 10;
    int print_amount = 1;
    int method = MTHD_RUNGE_KUTTA;
    boolean use_lazy_method = false;
    double atol = 0.0;
    double rtol = 0.0;
    double facmax = 0.0;

    myResult *mm_res = simulateSBMLModel( mm, sim_time, sbml_dt, print_interval, print_amount, method, use_lazy_method, atol, rtol, facmax);
    simulateSBMLModel( mm, sim_time, sbml_dt, print_interval, print_amount, method, use_lazy_method, atol, rtol, facmax);
*/
  }
}
