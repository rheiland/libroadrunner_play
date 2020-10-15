/*
    test_librr_memory.c - simple test
*/
#undef __cplusplus
#define STATIC_RRC
#include <stdio.h>
#include <stdlib.h>

#include "rrc_api.h"
#include "rrc_types.h"
#include "rrc_utilities.h"

int main (int argc, char *argv[]) 
{
   RRHandle rrHandle;
   RRCDataPtr result;
   int index;
   int col;
   int row;
   printf ("Starting Test Program %s\n", argv[0]);
   rrHandle = createRRInstance();

   printf("getCurrentIntegratorName= %s\n", getCurrentIntegratorName(rrHandle));
   printf("getCurrentIntegratorDescription= %s\n", getCurrentIntegratorDescription(rrHandle));

   if (!loadSBML (rrHandle, "V4_RT_V_VR_sbml.xml")) 
   {
      printf ("Error while loading SBML file\n");
      printf ("Error message: %s\n", getLastError());
      getchar ();
      exit (0);
   }
   printf("API = %s\n", getAPIVersion ());
   printf("getNumberOfIndependentSpecies= %d\n", getNumberOfIndependentSpecies(rrHandle));
   printf("getNumInstantiatedIntegrators= %d\n", getNumInstantiatedIntegrators(rrHandle));
   struct RRVector vec;
   double myvec[9];
   char* ids;

   int r = getNumberOfReactions(rrHandle);
   int m = getNumberOfFloatingSpecies(rrHandle);
   int b = getNumberOfBoundarySpecies(rrHandle);
   int p = getNumberOfGlobalParameters(rrHandle);
   int c = getNumberOfCompartments(rrHandle);

   printf ("Number of reactions = %d\n", r);
   printf ("Number of floating species = %d\n", m);  // 4
   printf ("Number of boundary species = %d\n", b);  // 0
   printf ("Number of compartments = %d\n", c);  // 1

   printf ("Floating species names:\n");
   printf ("-----------------------\n");
   printf("%s\n\n",stringArrayToString(getFloatingSpeciesIds(rrHandle)));

   printf ("Initial Floating species names:\n");
   printf ("-------------------------------\n");
   printf("%s\n\n",stringArrayToString(getFloatingSpeciesInitialConditionIds(rrHandle)));

   printf ("Floating species conc:\n");
   printf ("-------------------------------\n");
   RRVectorPtr vptr = getFloatingSpeciesConcentrations(rrHandle);

   printf ("Reactions names:\n");
   printf ("-----------------------\n");
   printf("%s\n\n",stringArrayToString(getReactionIds(rrHandle)));

  int max_loops = 1000000;
  for (int loop=0; loop<max_loops; loop++)
  {
    if (!(loop % 100))
      printf("---- loop = %d\n",loop);
    vptr->Data[3] += 0.00001;
    setFloatingSpeciesConcentrations(rrHandle, vptr);

    result = simulateEx (rrHandle, 0.0, 0.01, 2);  // start time, end time, and number of points
    index = 0;

    if (!(loop % 100))
      for (col = 0; col < result->CSize; col++)
      {
        printf ("%10s", result->ColumnHeaders[index++]);
        if (col < result->CSize - 1)
        {
            printf ("\t");
        }
      }

    if (!(loop % 100))
    {
        printf ("\n");
        index = 0;
        for (row = 0; row < result->RSize; row++)
        {
            for (col = 0; col < result->CSize; col++)
            {
                printf ("%10f", result->Data[index++]);
                if (col < result->CSize -1)
                {
                    printf ("\t");
                }
            }
            printf ("\n");
        }
    }
   freeRRCData (result);
  }

   freeRRInstance (rrHandle);
   exit (0);
}