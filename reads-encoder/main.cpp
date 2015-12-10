#include "SequenceFilter.h" 
#include <stdio.h>
using namespace std;

int main( int argc, char *argv[] )
{
    SequenceFilter ProtoEncoder;
    if( argc != 2 )
    { 
        fprintf(stderr, "usage xxx filename >> outputfilename");
    }
    else
    {
        ProtoEncoder.GetFile( argv[ 1 ] );
        ProtoEncoder.ShowAllHighquality();
    }
}