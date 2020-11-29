/*----------------------------------------------------------------------------
My Cryptographic Library

FILE:   myCrypto.c

Written By: 
     1- Mohamed Aboutabl

Submitted on: 
----------------------------------------------------------------------------*/

#include "myCrypto.h"
//***********************************************************************
// LAB-01
//***********************************************************************

void handleErrors( char *msg)
{
    fprintf( stderr , "%s\n" , msg ) ;
    ERR_print_errors_fp(stderr);
    exit(-1);
}

//-----------------------------------------------------------------------------
// Encrypt the plaint text stored at 'pPlainText' into the 
// caller-allocated memory at 'pCipherText'
// Caller must allocate sufficient memory for the cipher text
// Returns size of the cipher text in bytes

unsigned encrypt( uint8_t *pPlainText, unsigned plainText_len, 
             const uint8_t *key, const uint8_t *iv, uint8_t *pCipherText )
{

}

//-----------------------------------------------------------------------------
// Decrypt the cipher text stored at 'pCipherText' into the 
// caller-allocated memory at 'pDecryptedText'
// Caller must allocate sufficient memory for the decrypted text
// Returns size of the decrypted text in bytes

unsigned decrypt( uint8_t *pCipherText, unsigned cipherText_len, 
                  const uint8_t *key, const uint8_t *iv, uint8_t *pDecryptedText)
{

}

//***********************************************************************
// PA-01
//***********************************************************************

int encryptFile( int fd_in, int fd_out, unsigned char *key, unsigned char *iv )
{

}

//-----------------------------------------------------------------------------
int decryptFile( int fd_in, int fd_out, unsigned char *key, unsigned char *iv )
{

}

//***********************************************************************
// LAB-02
//***********************************************************************

RSA *getRSAfromFile(char * filename, int public)
{

}

//***********************************************************************
// PA-02
//***********************************************************************

size_t fileDigest( int fd_in , int fd_out , uint8_t *digest )
// Read all the incoming data stream from 'fd_in' file descriptor
// Compute the SHA256 hash value of this incoming data into the array 'digest'
// If the file descriptor 'fd_out' is > 0, store a copy of the incoming data
// file to 'fd_out'
// Returns actual size in bytes of the computed hash value
{

}

//***********************************************************************
// PA-03
//***********************************************************************

int BN_write_fd( const BIGNUM *bn , int fd_out )
// Sends the #of bytes , then the bytes themselves of a BIGNUM to file descriptor fd_out
// Returns 1 on success, 0 on failure
{

}

//-----------------------------------------------------------------------------
#define MAXBNBYTES  1030   /* up to 8192  bits for the BN */

BIGNUM * BN_read_fd( int fd_in )
// Read the #of bytes , then the bytes themselves of a BIGNUM from file descriptor fd_in
// Returns: a newly-created BIGNUM, which should be freed later by the caller
//          NULL on failure
{

}

//-----------------------------------------------------------------------------
BIGNUM * BN_myRandom( const BIGNUM *p )
// Returns a newly-created BIGNUM such that 1 < BN < (p-1)
{

}

//-----------------------------------------------------------------------------
void elgamalSign( const uint8_t *digest , int len ,  
                  const BIGNUM *q , const BIGNUM *gen , const BIGNUM *x , 
                  BIGNUM *r , BIGNUM *s , BN_CTX *ctx )
// Use the prime 'q', the primitive root 'gen',  and the private 'x' 
// to compute the Elgamal signature (r,s) on the 'len'-byte long 'digest'
{

}

//-----------------------------------------------------------------------------
int elgamalValidate( const uint8_t *digest , int len ,  
                  const BIGNUM *q , const BIGNUM *gen , const BIGNUM *y , 
                  BIGNUM *r , BIGNUM *s , BN_CTX *ctx )
// Use the prime 'q', the primitive root 'gen',  and the public 'y' 
// to validate the Elgamal signature (r,s) on the 'len'-byte long 'digest'
// Return 1 if valid, 0 otherswise

{

}

//***********************************************************************
// PA-04
//***********************************************************************

void exitError( char *errText )
{
    fprintf( stderr , "%s\n" , errText ) ;
    exit(-1) ;
}

//-----------------------------------------------------------------------------
// Allocate & Build a new Message #1 from Amal to the KDC 
// Where Msg1 is:  Len(A) || A  || Len(B) || B  || Len(Na) || Na
// All Len(*) fields are unsigned integers
// Set *msg1 to point at the newly built message
// Msg1 is not encrypted
// Returns the size (in bytes) of Message #1 
// Print milestone information to the Caller's log file as illustrated in the sample run

unsigned MSG1_new ( FILE *log , uint8_t **msg1 , const char *IDa , const char *IDb , const Nonce_t *Na )
{
    // Check for incoming NULL pointers

    // Compute size of MSG1 and allocate memory
    unsigned LenMsg1 ; 
    
    // Fill in Msg1:  L(A) || A  || L(B) || B  || L(Na) || Na

    fprintf( log , "The following new MSG1 ( %u bytes ) has been created by MSG1_new ():\n" , LenMsg1 ) ;
    BIO_dump_indent_fp( log , *msg1 , LenMsg1 , 4 ) ;
    fprintf( log , "\n" ) ;
    
    return LenMsg1 ;
}


//-----------------------------------------------------------------------------
// Receive Message #1 by the KDC from Amal
// Parse the incoming msg1 into the values IDa, IDb, and Na
// Print milestone information to the Caller's log file as illustrated in the sample run

void  MSG1_receive( FILE *log , int fd , char **IDa , char **IDb , Nonce_t *Na )
{
    // Check for incoming NULL pointers

    unsigned LenMsg1 ;

    // Read Len(Message 1) & Check for possible read() errors 
    // Parse Msg1:  L(A) || A  || L(B) || B  || L(Na) || Na

   // Read Len(IDa)  

   // Allocate and Read IDa

    // Read Len(IDb)

    // Allocate and Read IDb
    
    // Read Len(Na)

    // Read Na

    fprintf( log , "MSG1 ( %u bytes ) has been received"
                   " on FD %d by MSG1_receive():\n" ,  LenMsg1 , fd  ) ;   
    fflush( log ) ;

    return ;
}

//-----------------------------------------------------------------------------
// Build a new Message #2 from the KDC to Amal
// Where Msg2 before encryption:  L(Ks) || Ks || L(IDb) || IDb  || L(Na) || Na || L(TktCipher) || TktCipher
// All Len(*) fields are unsigned integers
// Set *msg2 to point at the newly built message
// Print milestone information to the Caller's log file as illustrated in the sample run
// Returns the size (in bytes) of the encrypted (using Ka) Message #2  

unsigned MSG2_new( FILE *log , uint8_t **msg2, const myKey_t *Ka , const myKey_t *Kb , 
                   const myKey_t *Ks , const char *IDa , const char *IDb  , Nonce_t *Na )
{
    static uint8_t ciphertext[CIPHER_LEN_MAX]; // Temporarily store outcome of encryption

    // Check for incoming NULL pointers

    // Allocate and Construct TktPlain = { L(Ks) || Ks  || L(IDa)  || IDa }
    
    // Now, set TktCipher = encrypt( Kb , TktPlain );

    // Allocate and Construct the rest of Message 2 then encrypt it using Ka
    // MSG2 plain = { L(Ks) || Ks || L(IDb) || IDb  || L(Na) || Na || L(TktCipher) || TktCipher }

    // Fill in Msg2 Plaintext:  L(Ks) || Ks || L(IDb) || IDb  || L(Na) || Na || lenTktCipher) || TktCipher
   
    // Now, encrypt Message 2 using Ka

    // Allocate buffer for Caller's *msg2 and copy the ciphertext of Message 2 there

    fprintf( log , "The following new Encrypted MSG2 ( %u bytes ) has been"
                   " created by MSG2_new ():  \n" , LenMsg2 ) ;
    BIO_dump_indent_fp( log , *msg2 , LenMsg2 , 4 ) ;    fprintf( log , "\n" ) ;    
    fflush( log ) ;    
    
    return LenMsg2 ;    
}

//-----------------------------------------------------------------------------
// Receive Message #2 by Amal from by the KDC
// Parse the incoming msg2 into the component fields 
// *Ks, *IDb, *Na and TktCipher = Encr{ L(Ks) || Ks  || L(IDa)  || IDa }
// Print milestone information to the Caller's log file as illustrated in the sample run

void MSG2_receive( FILE *log , int fd , const myKey_t *Ka , myKey_t **Ks, char **IDb , 
                       Nonce_t *Na , unsigned *lenTktCipher , uint8_t **tktCipher )
{
    // Here, using static arrays to avoid slow performance of malloc()
    static uint8_t   ciphertext[CIPHER_LEN_MAX];
    static uint8_t   msg2Plain [DECRYPTED_LEN_MAX];

    // Check for incoming NULL pointers

    // Read Len(Message 2) and make sure its length is <= CIPHER_LEN_MAX

    // Now read MSG2 itself into the static array ciphertext[]

    fprintf( log ,"The following Encrypted MSG2 has been received from FD %d Successfully\n" , fd );
    BIO_dump_indent_fp( log , ciphertext , msg2CipherLen , 4 ) ;   fprintf( log , "\n");
    fflush( log ) ;

    // Decrypt  MSG2 using Ka. Place decrypted MSG2 into the static array msg2Plain[]
    // Check that length of the decrypted outcome is <= DECRYPTED_LEN_MAX
    unsigned msg2Len ;
    
    // Parse the Decrypted Msg2 into its components: 
    // { L(Ks) || Ks || L(IDb) || IDb  || L(Na) || Na || L(TktCipher) || TktCipher }

    // Parse Ks & copy it to Caller's buffer    
    // Parse IDb & copy it to Caller's buffer
    // Parse Na & copy it to Caller's buffer
    // Parse the Encrypted Ticket & copy it to Caller's buffer

    return ;
}

//-----------------------------------------------------------------------------
// Utility to read Key/IV from files
// Return:  0 on success, or -1 on failure

int getMasterKeyFromFiles( char *keyF , char *ivF , myKey_t *x )
{
    int   fd_key , fd_iv ;
    
    fd_key = open( keyF , O_RDONLY )  ;
    if( fd_key == -1 ) 
    { 
        fprintf( stderr , "\nCould not open key file '%s'\n" , keyF ); 
        fflush( stderr ) ;       
        return -1 ; 
    }
    read ( fd_key , x->key , SYMMETRIC_KEY_LEN ) ;
    close( fd_key ) ;

    fd_iv = open(ivF , O_RDONLY )  ;
    if( fd_iv == -1 ) 
    { 
        fprintf( stderr , "\nCould not open IV file '%s'\n" , ivF ); 
        fflush( stderr ) ;     
        return -1 ; 
    }
    read ( fd_iv , x->iv , INITVECTOR_LEN ) ;
    close( fd_iv ) ;
    
    return 0;  //  success
}
