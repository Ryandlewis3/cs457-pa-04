/*----------------------------------------------------------------------------
PA-04:  Enhanced Needham-Schroeder Key-Exchange with TWO-way Authentication

FILE:   amal.c

Written By: 
     1- Dr. Mohamed Aboutabl
Submitted on: 
----------------------------------------------------------------------------*/
/* OpenSSL headers */
#include <openssl/dh.h>
#include <openssl/ssl.h>
#include <openssl/evp.h>
#include <openssl/conf.h>
#include <openssl/err.h>
#include <openssl/bio.h>
#include <openssl/bn.h>
#include <openssl/rand.h>
#include <openssl/opensslv.h>
#include <linux/random.h>

#include <time.h>
#include <stdlib.h>

#include "../myCrypto.h"

//*************************************
// The Main Loop
//*************************************
int main ( int argc , char * argv[] )
{
    int      fd_A2K , fd_K2A , fd_A2B , fd_B2A  ;
    FILE    *log ;

    
    printf( "\nThis is Amal's    Executable by ABOUTABL\n" ) ;
    
    if( argc < 5 )
    {
        printf("\nMissing command-line file descriptors: %s <getFr. KDC> <sendTo KDC> "
               "<getFr. Basim> <sendTo Basim>\n\n" , argv[0]) ;
        exit(-1) ;
    }
    fd_K2A    = atoi( argv[1] ) ;  // Read from KDC    File Descriptor
    fd_A2K    = atoi( argv[2] ) ;  // Send to   KDC    File Descriptor
    fd_B2A    = atoi( argv[3] ) ;  // Read from Basim  File Descriptor
    fd_A2B    = atoi( argv[4] ) ;  // Send to   Basim  File Descriptor

    log = fopen("amal/logAmal.txt" , "w" );
    if( ! log )
    {
        fprintf( stderr , "This is Amal's Executable by ABOUTABL. "
                          "Could not create my log file\n" ) ;
        exit(-1) ;
    }
    fprintf( log , "\nThis is Amal's Executable by ABOUTABL\n" ) ;

    fprintf( log , "<readFr. KDC> FD=%d , <sendTo KDC> FD=%d , "
                   "<readFr. Basim> FD=%d , <sendTo Basim> FD=%d\n" , 
                   fd_K2A , fd_A2K , fd_B2A , fd_A2B );

    // Get and dump Amal's master key with the KDC
    myKey_t  Ka ;  // Amal's master key with the KDC

    //*************************************
    // Construct & Send    Message 1
    //*************************************
    char     *IDa = "Amal is Hope" ,  *IDb = "Basim is Smiley" ;
    unsigned  LenMsg1 ;
    uint8_t  *msg1 ;
    Nonce_t   Na;  

    // First Nonce by A
    
    
    LenMsg1 = MSG1_new( log , &msg1 , IDa , IDb , &Na ) ;
    
    write( fd_A2K , &LenMsg1 , sizeof(unsigned) ) ;
    write( fd_A2K , msg1     , LenMsg1 ) ;

    fprintf( log , "Amal sent message 1 ( %d bytes ) to the KDC on FD %d with\n"
                   "    IDa ='%s' , IDb = '%s' , Na=\n" , LenMsg1 , fd_A2K , IDa , IDb ) ;
    BIO_dump_indent_fp( log , Na , NONCELEN , 4 ) ;   fprintf( log , "\n");
    fflush( log ) ;

    free( msg1 ) ;

    //*************************************
    // Receive   & Process Message 2
    //*************************************
    
    myKey_t  *Ks ;       // Amal's session key with Basim. Created by the KDC   
    char     *IDb2 ;     // IDb as received from KDC .. must match what was sent in MSG1
    Nonce_t   NaCpy ;
    uint8_t  *tktCipher ;
    unsigned  lenTktCipher , LenKs= sizeof( myKey_t ) ;

    MSG2_receive( log , fd_K2A, &Ka, &Ks, &IDb2, &NaCpy, &lenTktCipher, &tktCipher );


    // Verify IDb = IDb2
    
    // Verify Na == NaCpy    

    fprintf( log , "Amal received this Session Ks { Key , IV } "
                   "from the KDC (%d bytes)\n" , LenKs );
    
    // Dump Ks.key and Ks.iv

    fprintf( log , "Amal received this TktCipher from the KDC (%d bytes):\n" , lenTktCipher ) ;
    // Dump  tktCipher

    fflush( log ) ;
            
    //*************************************
    // Construct & Send    Message 3
    //*************************************

    //*************************************
    // Receive   & Process Message 4
    //*************************************
    
    //*************************************
    // Construct & Send    Message 5
    //*************************************


    // Now send the Big Bunny video to Basim encrypted with this session key Ks
    // using the fd_A2B  pipe
    
    
    //*************************************   
    // Final Clean-Up
    //*************************************
   
    fprintf( log , "\nAmal has terminated normally. Goodbye\n" ) ;  
    fclose( log ) ;
    return 0 ;
}

