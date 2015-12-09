#include "SequenceFilter.h"
#include <algorithm>

SequenceFilter::SequenceFilter(){ Init(); }

SequenceFilter::~SequenceFilter(){}

void SequenceFilter::Init()
{
    fastq_input_    = nullptr;
    sequence_line_  = nullptr;
    trim_threshold_ = 36;
    need_trim_      = true;
    need_upper_     = true;
}

void SequenceFilter::GetFile( const string fileName )
{
    errno_t error_num = fopen_s( &fastq_input_, fileName.c_str(), "r" );
    if ( 0 != error_num )
    {
        //TODO options on certern error code
    }
}

void SequenceFilter::ShowAllHighquality()
{
    while( 0 == GetOneRead() )
    {
        if(need_upper_) { ToUpperCase();   }
        if(need_trim_)  { TrimByQuality(); }
        EncodeOneLine();
    }
}

inline void SequenceFilter::ToUpperCase()
{
    std::transform( ( *sequence_line_ ).begin() ,
                    ( *sequence_line_ ).end()   ,
                    ( *sequence_line_ ).begin() ,
                    ::toupper );
}

inline void SequenceFilter::TrimByQuality()
{
    size_t end = ( *quality_line_ ).size() - 1;

    for (; end >= 1; end--)
    {
        if ( ( *quality_line_ )[end] > trim_threshold_
             && ( *quality_line_ )[end - 1] > trim_threshold_ )
        {
            ( *quality_line_  ) = ( *quality_line_  ).substr( 0, end + 1 );
            ( *sequence_line_ ) = ( *sequence_line_ ).substr( 0, end + 1 );

            break;
        }
    }

    if (end <= 1) 
    {
        end = 1;
        ( *quality_line_  ) = ( *quality_line_  ).substr( 0, end );
        ( *sequence_line_ ) = ( *sequence_line_ ).substr( 0, end );
    }

    size_t beg = 0;
    for ( ; beg <= ( *quality_line_ ).size() - 2; beg++ )
    {
        if ( ( *quality_line_ )[beg] > trim_threshold_
             && ( *quality_line_ )[beg + 1] > trim_threshold_) 
        {
            ( *quality_line_  ) = ( *quality_line_  ).substr(beg, ( *quality_line_  ).size() - beg);
            ( *sequence_line_ ) = ( *sequence_line_ ).substr(beg, ( *sequence_line_ ).size() - beg);

            break;
        }
    }
}

inline void SequenceFilter::EncodeOneLine()
{
    printf("%s\n",sequence_line_->c_str() );
    //TODO
}

int SequenceFilter::GetOneRead()
{
    if ( nullptr == fastq_input_ )
        return 1;

    // iterate on every line, alloc some buffer before doing alignment
    string * line;

    char buffer[2000];

    //get 4 lines of a read
    for (int line_num = 0; line_num < 4; line_num++)
    {
        //no more data in file
        if ( nullptr == fgets( buffer, 1999, fastq_input_ ) )
        {
            return 1;
        }

        //get the line
        line = new string( buffer );

        // skip empty lines, would not be one in common
        if ('\n' == ( *line )[0] || '\r' == ( *line )[0])
        {
            line_num--;
            continue;
        }

        // Remove blanks
        ( *line ).erase( std::remove( ( *line ).begin(), ( *line ).end(), '\n' ), ( *line ).end() );
        ( *line ).erase( std::remove( ( *line ).begin(), ( *line ).end(), '\r' ), ( *line ).end() );
        ( *line ).erase( std::remove( ( *line ).begin(), ( *line ).end(), ' '  ), ( *line ).end() );

        // Fastq format, 0: read name, 1: read seq, 2: read name, 3: quals
        if ( ( ( line_num ) % 4 ) == 1 )
        {
            if( nullptr != sequence_line_ ) { delete sequence_line_; }
            sequence_line_ = line;
        }
        else if ( ( ( line_num ) % 4 ) == 3 )
        {
            if ( nullptr != quality_line_ ) { delete quality_line_;  }
            quality_line_ = line;
        }

    }
    return 0;
}
