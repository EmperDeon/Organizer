/*
	Copyright (c) 2017 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#ifndef ORGANIZER_VARS_H
#define ORGANIZER_VARS_H

// Cryptography
#define AES_IV "jFPXFv/5WGlOou7EG8nIvA=="
#define AES_DEF_KEY_SIZE 32
#define AES_MODE QCA::Cipher::CBC
#define AES_PADDING QCA::Cipher::PKCS7

// RSA
#define RSA_DEFAULT_SIZE 1024
#define RSA_ENC_ALG QCA::EME_PKCS1v15
#define RSA_SIGN_ALG QCA::EMSA3_SHA256

// Sync
#define S_UID_SIZE 32
#define S_DOC_KEY_SIZE 64
#define S_DOC_CIPHER "128"

// Storage
#define STORAGE_CUR_VERSION 1
#define STORAGE_FILE "/home/ilya/.myQtProgs/storage2.json"
#define STORAGE_KEY "ttpGxMkT4wk7QJx77ak75dtYqaUdRQB5fJQO1NzzYFc="
#define STORAGE_CIPHER "128"

// File Storage
#define FILES_DIR "/home/ilya/.myQtProgs/encrypted_files/"
#define FILES_BUFFER_SIZE 33554432
#define FILES_CIPHER "128"
#define FILES_KEY_SIZE 32

#define FILE_HASH "sha256"
#define FILE_KILOBYTE 1024
#define FILE_MEGABYTE 1048576
#define FILE_GIGABYTE 1073741824

// Network
#define NETWORK_URL "http://0.0.0.0:3005/"
#define NETWORK_AES_TYPE "256"
#define NETWORK_AES_KEY_SIZE 32
#define NETWORK_RSA_KEY_SIZE 1024
#define NETWORK_DEF_KEY "+7QqHqbuJEursfbU+uaJUmN1obOcZEza3oRUtmS+Qz8="


//
// Options
//

//#define ENCRYPT_OUT // Encrypt storage output
//#define OPTION_SYNC // Enable sync (send on save, load on timer, sync menu in WMain MenuBar)

#endif //ORGANIZER_VARS_H
