/*----------------------------------------------------------------------------
PA-04:  Enhanced Needham-Schroeder Key-Exchange with TWO-way Authentication

FILE:   basim.c

Written By: 
     1- Dr. Mohamed Aboutabl
Submitted on: 
----------------------------------------------------------------------------*/

#include "../myCrypto.h"

//*************************************
// The Main Loop
//*************************************
int main ( int argc , char * argv[] )
{
    int       fd_A2B , fd_B2A   ;
    FILE     *log ;

    printf( "\nThis is Basim's   Executable by ABOUTABL\n" ) ;
    if( argc < 3 )
    {
        printf("\nMissing command-line file descriptors: %s <getFr. Amal> "
               "<sendTo Amal>\n\n", argv[0]) ;
        exit(-1) ;
    }
    fd_A2B    = atoi( argv[1] ) ;  // Read from Amal   File Descriptor
    fd_B2A    = atoi( argv[2] ) ;  // Send to   Amal   File Descriptor

    log = fopen("basim/logBasim.txt" , "w" );
    if( ! log )
    {
        fprintf( stderr , "This is Basim's Executable by ABOUTABL. "
                          "Could not create log file\n" ) ;
        exit(-1) ;
    }
    fprintf( log , "\nThis is Basim's Executable by ABOUTABL\n" ) ;
    fprintf( log , "\t<readFr. Amal> FD=%d , <sendTo Amal> FD=%d\n" , fd_A2B , fd_B2A );

    // Get and dump  Basim's master keys with the KDC
    myKey_t   Kb ;    // Basim's master key with the KDC    


    //*************************************
    // Receive  & Process   Message 3
    //*************************************
    myKey_t   Ks ;    // Basim's session key with Amal
    char     *IDa;    // Amal's Identity
    Nonce_t   Na2;    // Amal's nonce to Basim.

    MSG3_receive( log , fd_A2B , &Kb , &Ks , &IDa , &Na2 );

    fprintf( log , "Basim received Message 3 from Amal on FD %d "
                   "with the following Session Ks { Key , IV} \n" , fd_A2B  );
    BIO_dump_indent_fp ( log , (const char *) Ks.key, SYMMETRIC_KEY_LEN , 4 ); fprintf( log , "\n"  );
    BIO_dump_indent_fp ( log , (const char *) Ks.iv , INITVECTOR_LEN , 4 );    fprintf( log , "\n") ;    

    fprintf( log , "Basim also leaned the following\n    IDa= '%s'\n"
                   "    Na2 =\n" , IDa );
    BIO_dump_indent_fp( log , Na2 , NONCELEN , 4 ) ;   fprintf( log , "\n");               

    //*************************************
    // Construct & Send    Message 4
    //*************************************
    Nonce_t   fNa2 , Nb , fNbCpy;
    uint8_t  *msg4 ;
    unsigned  LenMsg4 ;

    // Compute f(Na2)
 
    // Nonce by B to challenge A

    // Create  MSG4 and Send to Amal
    LenMsg4 = MSG4_new( log ,  &msg4 , &Ks , &fNa2 , &Nb ) ;
    

    fprintf( log , "Basim Sent the above Message 4 to Amal on FD %d\n" , fd_B2A );

    fprintf( log , "\nBasim expecting back this fNb in MSG5:\n") ;


    fflush( log ) ;
                   
    //*************************************
    // Receive   & Process Message 5
    //*************************************
    Nonce_t   fNb ;
 
    MSG5_receive( log , fd_A2B , &Ks , &fNb ) ;
    
    fprintf( log , "Basim received Message 5 from Amal on FD %d with this f( Nb ) :\n" , fd_A2B ) ;

    fflush( log ) ;

    // Validate f( Nb ) 

    // Now receive and decrypt the Big Bunny video from Amal using the fd_A2B pipe

    //*************************************   
    // Final Clean-Up
    //*************************************
    free( IDa ) ;

    fprintf( log , "\nBasim has terminated normally. Goodbye\n" ) ;
    fclose( log ) ;  

    return 0 ;
}
