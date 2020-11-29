/*----------------------------------------------------------------------------
My Cryptographic Library

FILE:   myCrypto.h

              D O    N O T    M O D I F Y     T H I S    F I L E
Written By: 
     1- Dr. Mohamed Aboutabl

----------------------------------------------------------------------------*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <fcntl.h>
#include <string.h>
#include <linux/random.h>
#include <assert.h>

/* OpenSSL headers */
#include <openssl/ssl.h>
#include <openssl/evp.h>
#include <openssl/conf.h>
#include <openssl/err.h>
#include <openssl/bio.h>
#include <openssl/bn.h>
#include <openssl/rand.h>
#include <openssl/dh.h>

// Forcing the use of openssl 1.1.1 on STU, which is linking to an old 
// version by default
// Link with   -l:libcrypto.so.1.1
// The old header files do not contain the following prototypes, so we 
// manually add them
void DH_get0_pqg(const DH *dh,
                  const BIGNUM **p, const BIGNUM **q, const BIGNUM **g);
EVP_MD_CTX *EVP_MD_CTX_new(void);
void EVP_MD_CTX_free(EVP_MD_CTX *ctx);

// For symmetric-key Encryption/Decryption, 
// use a 256-bit key and AES in CBC mode (with a 128-bit IV)
// Ensure the (key,IV) being used match the specified algorithm

#define ALGORITHM          EVP_aes_256_cbc
#define SYMMETRIC_KEY_LEN  32
#define INITVECTOR_LEN     16

//***********************************************************************
// LAB-01
//***********************************************************************

#define CIPHER_LEN_MAX     2048
#define PLAINTEXT_LEN_MAX (CIPHER_LEN_MAX-32)
#define DECRYPTED_LEN_MAX (CIPHER_LEN_MAX+32)

void       handleErrors( char *msg ) ;

unsigned   encrypt( uint8_t *pPlainText, unsigned plainText_len, 
                    const uint8_t *key, const uint8_t *iv, uint8_t *pCipherText ) ;

unsigned   decrypt( uint8_t *pCipherText, unsigned cipherText_len, 
                    const uint8_t *key, const uint8_t *iv, uint8_t *pDecryptedText) ;

//***********************************************************************
// PA-01
//***********************************************************************

int    encryptFile( int fd_in, int fd_out, unsigned char *key, unsigned char *iv );
int    decryptFile( int fd_in, int fd_out, unsigned char *key, unsigned char *iv );

//***********************************************************************
// LAB-02
//***********************************************************************

RSA    *getRSAfromFile(char * filename, int public) ;

//***********************************************************************
// PA-02
//***********************************************************************
#define INPUT_CHUNK   (1 << 14)
size_t fileDigest( int fd_in , int fd_out , uint8_t *digest ) ;


//***********************************************************************
// PA-03
//***********************************************************************
int     BN_write_fd( const BIGNUM *bn , int fd_out ) ;
BIGNUM *BN_read_fd ( int fd_in ) ;
BIGNUM *BN_myRandom( const BIGNUM *p ) ;

void    elgamalSign( const uint8_t *digest , int len ,  
                     const BIGNUM *q , const BIGNUM *gen , const BIGNUM *x , 
                     BIGNUM *r , BIGNUM *s , BN_CTX *ctx ) ;

int elgamalValidate( const uint8_t *digest , int len ,  
                  const BIGNUM *q , const BIGNUM *gen , const BIGNUM *y , 
                  BIGNUM *r , BIGNUM *s , BN_CTX *ctx ) ;

//***********************************************************************
// PA-04
//***********************************************************************

typedef uint8_t         Nonce_t[ 128 ] ; /* 128 bytes = 1024 bits */
#define NONCELEN       ( sizeof(Nonce_t)  )
#define LENSIZE        ( sizeof(unsigned) )


// Key Object = symmetricKey || IV in one structure for easier argument passing
typedef struct {
            uint8_t  key[ SYMMETRIC_KEY_LEN ] , 
                     iv [ INITVECTOR_LEN ] ;
        }  myKey_t ; 

void     exitError( char *errText ) ;
int      getMasterKeyFromFiles( char *keyF , char *ivF , myKey_t *x ) ;
unsigned MSG1_new( FILE *log , uint8_t **msg1 , const char *IDa , const char *IDb 
                   , const Nonce_t *Na ) ;
void     MSG1_receive( FILE *log , int fd , char **IDa , char **IDb , Nonce_t *Na ) ;
unsigned MSG2_new( FILE * log , uint8_t **msg2 , const myKey_t *Ka , const myKey_t *Kb , 
                   const myKey_t *Ks , const char *IDa , const char *IDb , Nonce_t *Na ) ;

void     MSG2_receive( FILE *log , int fd , const myKey_t *Ka , myKey_t **Ks, char **IDb , 
                       Nonce_t *Na , unsigned *lenTktCipher , uint8_t **tktCipher ) ;

unsigned MSG3_new( FILE *log , uint8_t **msg3 , const uint8_t *tktCipher, unsigned lenTktCipher , 
                   const Nonce_t *Na2 ) ;

void     MSG3_receive( FILE *log , int fd , myKey_t *Kb , myKey_t *Ks , char **IDa , Nonce_t *Na2 ) ;
unsigned MSG4_new( FILE *log , uint8_t **msg4, myKey_t *Ks , Nonce_t *fNa2 , Nonce_t *Nb ) ;
void     MSG4_receive( FILE *log , int fd , myKey_t *Ks , Nonce_t *fNa2 , Nonce_t *Nb ) ;
unsigned MSG5_new( FILE *log , uint8_t **msg5, myKey_t *Ks ,  Nonce_t *fNb ) ;
void     MSG5_receive( FILE *log , int fd , myKey_t *Ks , Nonce_t *fNb ) ;
