#include "SequenceFilter.h"
#include "codebook.h"
#include <algorithm>

SequenceFilter::SequenceFilter(){ Init(); }

SequenceFilter::~SequenceFilter(){}

void SequenceFilter::Init()
{   
    trim_threshold_ = 36; // [warning] magic number
    need_trim_      = false;
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

// still has bug can not work well when input sequence has no high quality pair
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
    //printf("%s\n",sequence_line_->c_str() );
    *sequence_line_ += 'E';// add end line mark
    
    int  codelen  = ( sequence_line_->size() ) * 3 / 8;
    int  perfect  = ( sequence_line_->size() ) * 3 % 8;
    codelen += ( 0 == perfect ) ? 0 : 1;
    auto codes = make_unique< unsigned char[] >( codelen );
    int basepari_num = 0;
    int codestate    = 0;
    int code_i       = 0;
    int shift        = 0;
    //fprintf( stderr , "code lenght is %d\n " , codelen );
    
    for ( auto ch : *sequence_line_ )
    {
        codes[ code_i ] += ( unsigned char )( CodeBook[ ch - 'A' ] << 5 ) >> shift;
        shift +=3;
        if( shift > 8 )
        {
            shift -= 8;

            ++code_i;
            codes[ code_i ] += ( unsigned char )( CodeBook[ ch - 'A' ] << ( 8 - shift ) );
        }
        else if ( shift == 8 )
        {
            shift -= 8;
            ++code_i;
        }
    }

    if ( 0 != shift ) //rest bit to 1
    {
        codes[ code_i ] += ( ( unsigned char )( ALL1 << shift ) >> shift );
    }
    
    for ( int i =0 ;i < codelen ;i++ )
    { 
        //fprintf( stderr , "%x " , codes[ i ] );
        printf("%c",codes[ i ]);
    }
    //Add new line mark
}

int SequenceFilter::GetOneRead()
{
    if ( nullptr == fastq_input_ )
        return 1;

    // iterate on every line, alloc some buffer before doing alignment
    unique_ptr<string> line;

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
        line = make_unique<string>(buffer);

        // skip empty lines, would not be one in common
        if ('\n' == ( *line )[0] || '\r' == ( *line )[0])
        {
            fprintf( stderr, "[warning] Empty line!");
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
            sequence_line_ = move(line);
        }
        else if ( ( ( line_num ) % 4 ) == 3 )
        {
            quality_line_ = move(line);
        }

    }
    return 0;
}
