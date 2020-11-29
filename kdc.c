/*----------------------------------------------------------------------------
PA-04:  Enhanced Needham-Schroeder Key-Exchange with TWO-way Authentication

FILE:   kdc.c

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

#include "../myCrypto.h"

//*************************************
// The Main Loop
//*************************************
int main ( int argc , char * argv[] )
{
    int       fd_A2K , fd_K2A   ;
    FILE     *log ;
    
    printf ( "\nThis is the KDC's Executable by ABOUTABL\n" ) ;
    if( argc < 3 )
    {
        printf("\nMissing command-line file descriptors: %s <getFr. Amal> "
               "<sendTo Amal>\n\n", argv[0]) ;
        exit(-1) ;
    }
    fd_A2K    = atoi( argv[1] ) ;  // Read from Amal   File Descriptor
    fd_K2A    = atoi( argv[2] ) ;  // Send to   Amal   File Descriptor

    log = fopen("kdc/logKDC.txt" , "w" );
    if( ! log )
    {
        fprintf( stderr , "This is the KDC's Executable by ABOUTABL. "
                          "Could not create log file\n" ) ;
        exit(-1) ;
    }
    fprintf( log , "\nThis is the KDC's Executable by ABOUTABL\n" ) ;
    fprintf( log , "\t<readFr. Amal> FD=%d , <sendTo Amal> FD=%d\n" , fd_A2K , fd_K2A );
    fflush( log ) ;
    
    // Get & Dump Amal's master keys with the KDC

    // Get & Dump Basim's master keys with the KDC

    //*************************************
    // Receive  & Display   Message 1
    //*************************************
    char *IDa , *IDb ;
    Nonce_t  Na ;
    
    MSG1_receive( log , fd_A2K , &IDa , &IDb , &Na ) ;
    
    fprintf( log , "\nKDC received message 1 from Amal on FD %d with\n"
            "    IDa ='%s' , IDb = '%s' , Na=\n" , fd_A2K , IDa , IDb ) ;
    // Dump Na 
    fflush( log ) ;

    //*************************************   
    // Construct & Send    Message 2
    //*************************************

    myKey_t  Ks ;    // Session key for Amal & Basim to use

    // Generate a new raandom bytes for Session Key / IV  Ks

   
    // Create a new MSG2
    uint8_t *msg2 ;
    unsigned LenMsg2 = MSG2_new( log , &msg2 , &Ka , &Kb , &Ks , IDa , IDb , &Na ) ;
    
    // write Len(MSG2) followed by the bytes of MSG2 to Amal

    fprintf( log ,"The KDC sent the above Encrypted MSG2 to FD=%d Successfully\n" , fd_K2A );
    fflush( log ) ;

    //*************************************   
    // Final Clean-Up
    //*************************************
    
    fprintf( log , "\nThe KDC has terminated normally. Goodbye\n" ) ;
    fclose( log ) ;  
    return 0 ;
}
