// Copyright (c) 2015 Yhgenomics. All rights reserved.
// Description: Ouput only high quality sub-sequence 
// Creator: Ke Yang
// Date: 2015/12/9

#ifndef SEQUENCE_FILTER_H_
#define SEQUENCE_FILTER_H_

#include <stdio.h>
#include <string>
#include <memory>

using namespace std;

// Implement the IDataReader to fetch the genome reads data
// one(4 lines for certern) by one from a fastq file 
// and do the data cleaning work
class SequenceFilter 
{
public:

    SequenceFilter();
    ~SequenceFilter();

    void            Init();
    void            GetFile( const string fileName );

    // Redirect the std cout to file or it will be on monitor 
    void            ShowAllHighquality();

private:

    // Makes all As, Cs, Gs, Ts and Ns to upper case 
    inline  void    ToUpperCase();

    // Cuts less Quality head and tail sequence off by a threshold
    inline  void    TrimByQuality();

    // Encode one line and put it to monitor
    inline  void    EncodeOneLine();

    // Gets genome reads(4 useable lines) from the .fastq file
    int             GetOneRead();

    FILE                    *fastq_input_;
    unique_ptr< string >    sequence_line_;
    unique_ptr< string >    quality_line_;
    bool                    need_trim_;
    bool                    need_upper_;
    char                    buffer[2000];
    unsigned char           trim_threshold_;
    unsigned char           code[8];
};
#endif