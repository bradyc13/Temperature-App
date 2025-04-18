/**
  ******************************************************************************
  * @file    sk.h
  * @author  MCD Application Team
  * @brief   Symmetric Key Common Definitions
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2015 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CRL_SK_H__
#define __CRL_SK_H__


#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/

/** @addtogroup SymKey
  * @{
  */
/* Exported types ----------------------------------------------------------- */  

typedef enum {  
  E_SK_DEFAULT = (uint32_t) (0x00000000), /*!< User Flag: No flag specified. This is the default value that should be set to this flag  */  
  E_SK_DONT_PERFORM_KEY_SCHEDULE = (uint32_t) (0x00000001), /*!< User Flag: Used to force the init to not reperform key schedule.\n
                                                                 The classic example is where the same key is used on a new message, in this case to redo key scheduling is
                                                                 a useless waste of computation, could be particularly useful on GCM, where key schedule is very complicated. */    
  E_SK_FINAL_APPEND = (uint32_t) (0x00000020),   /*!< User Flag: Must be set in CMAC mode before the final Append call occurs. */
  E_SK_OPERATION_COMPLETED  = (uint32_t) (0x00000002),   /*!< Internal Flag (not to be set/read by user): used to check that the Finish function has been already called */  
  E_SK_NO_MORE_APPEND_ALLOWED = (uint32_t) (0x00000004), /*!< Internal Flag (not to be set/read by user): it is set when the last append has been called. Used where the append is called with an InputSize not
                                                                    multiple of the block size, which means that is the last input.*/
  E_SK_NO_MORE_HEADER_APPEND_ALLOWED = (uint32_t) (0x00000010),   /*!< Internal Flag (not to be set/read by user): only for authenticated encryption modes. \n
                                                                      It is set when the last header append has been called. Used where the header append is called with an InputSize not
                                                                      multiple of the block size, which means that is the last input.*/
  E_SK_APPEND_DONE = (uint32_t) (0x00000040),   /*!< Internal Flag (not to be set/read by user): only for CMAC.It is set when the first append has been called */
  E_SK_SET_COUNTER = (uint32_t)(0x00000080),    /*!< User Flag: With ChaCha20 this is used to indicate a value for the counter, used to process non contiguous blocks (i.e. jump ahead)*/

} SKflags_et; /*!< Type definitation for Symmetric Key Flags */

/**
  * @}
  */

/** @addtogroup InternalAPI Internal functions
  * @{
  */
  
/** @defgroup SymKeylowlevel Symmetric Key Low Level Flags
  * @{
  */
  
#define  C_ENC       (uint32_t) (0x00000000) /*!< Internal constant indicating "Encryption"          */
#define  C_DEC       (uint32_t) (0x00000001) /*!< Internal constant indicating "Decryption"          */
#define  C_DIR_MASK  (uint32_t) (0x00000001) /*!< Internal mask for Encryption/Decryption           */
#define  C_ECB       (uint32_t) (0x00000002) /*!< Internal constant indicating "ECB"                 */
#define  C_CBC       (uint32_t) (0x00000004) /*!< Internal constant indicating "CBC"                 */
#define  C_CTR       (uint32_t) (0x00000006) /*!< Internal constant indicating "CTR"                 */
#define  C_MODE_MASK (uint32_t) (0x00000006) /*!< Internal mask for ECB/CBC/CTR                     */
#define  C_DES       (uint32_t) (0x00000008) /*!< Internal constant indicating "DES"                 */
#define  C_TDES      (uint32_t) (0x00000010) /*!< Internal constant indicating "TDES"                */
#define  C_AES       (uint32_t) (0x00000018) /*!< Internal constant indicating "AES"                 */
#define  C_ALGO_MASK (uint32_t) (0x00000018) /*!< Internal mask for DES/TDES/AES                    */
#define  C_AES128    (uint32_t) (0x10000000) /*!< Internal constant indicating "AES with key of 128" */
#define  C_AES192    (uint32_t) (0x18000000) /*!< Internal constant indicating "AES with key of 192" */
#define  C_AES256    (uint32_t) (0x20000000) /*!< Internal constant indicating "AES with key of 256" */
#define  C_AES_KEY_MASK (uint32_t) (0x00000038) /*!< Internal mask for AES128/AES192/AES256         */


/* Directions of the operations */
#define CRL_ENC 0 /*!< Used to specify an encryption operation. */
#define CRL_DEC 1 /*!< Used to specify a decryption operation.  */

/* Modes of operation */
#define CRL_ECB   0 /*!< Used to specify the Electronic Code Book mode of operation.   */
#define CRL_CBC   1 /*!< Used to specify the Cipher Block Chaining mode of operation.  */
#define CRL_CTR   2 /*!< Used to specify the Counter mode of operation (for AES only). */

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif


#endif /* __CRL_SK_H__ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
