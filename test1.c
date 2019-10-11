/*

clang -I/Users/heiland/dev/roadrunner-osx-10.9-cp36m/include/rr/C -L/Users/heiland/dev/roadrunner-osx-10.9-cp36m/lib -lroadrunner test1.c -o test1

clang -I/Users/heiland/dev/roadrunner-osx-10.9-cp36m/include -L/Users/heiland/dev/roadrunner-osx-10.9-cp36m/lib -lroadrunner -L/usr/local/opt/libomp/lib -lomp test1.c  -o test1

*/

#undef __cplusplus
#define STATIC_RRC
#include <stdio.h>
#include <stdlib.h>
#include "rrc_api.h"
#include "rrc_types.h"
#include "rrc_utilities.h"
int main (int argc, char *argv[]) {
   RRHandle rrHandle;
   RRCDataPtr result;
   int index;
   int col;
   int row;
   printf ("Starting Test Program %s\n", argv[0]);
   rrHandle = createRRInstance();
   if (!loadSBML (rrHandle, "feedback.xml")) {
      printf ("Error while loading SBML file\n");
      printf ("Error message: %s\n", getLastError());
      getchar ();
      exit (0);
   }
   result = simulateEx (rrHandle, 0, 10, 10);  // start time, end time, and number of points
   index = 0;
   // Print out column headers... typically time and species.
   for (col = 0; col < result->CSize; col++)
   {
      printf ("%10s", result->ColumnHeaders[index++]);
      if (col < result->CSize - 1)
      {
         printf ("\t");
      }
   }
   printf ("\n");
   index = 0;
   // Print out the data
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
   //Cleanup
   freeRRCData (result);
   freeRRInstance (rrHandle);
   getchar ();
   exit (0);
}
