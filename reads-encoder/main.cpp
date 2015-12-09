#include "SequenceFilter.h" 
#include <stdio.h>
using namespace std;


int main()
{
  SequenceFilter test1;
  test1.GetFile("E:\\GeneData\\twoline.fastq");
  test1.ShowAllHighquality();
  system("pause");
}