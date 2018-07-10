/*
	Copyright (c) 2017 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#ifndef ORGANIZER_VARS_H
#define ORGANIZER_VARS_H

#include <QtCore/QDir>

#ifdef DEBUG
#define STORAGE_DIR QDir::home().filePath(".organizer_dbg") + QDir::separator()
#define LOG_DATE_FORMAT "HH:mm:ss"
#else
#define STORAGE_DIR QDir::home().filePath(".organizer") + QDir::separator()
#define LOG_DATE_FORMAT "dd.MM.yyyy HH:mm:ss"
#endif


// AES
#define CRYPT_DERIVATION_SALT "aXCqolTzlnLqqtAoBrOBlfXf6W2DcO6KDZq2z4TWCc7IP+b2u5S6Zr49AezVqv5x9FQ5qqOffC8XzscZ7CMs0Q=="

// RSA
#define RSA_DEFAULT_SIZE 1024

// Documents
#define S_UID_SIZE 32
#define S_DOC_KEY_SIZE 64
#define S_DOC_CIPHER 128
#define S_REPLACE_KEY "content_replacement"
#define S_DELETE_KEYS "delete_unused_fields"

// Storage
#define STORAGE_CUR_VERSION "1.1"
#define STORAGE_FILE (STORAGE_DIR + "storage.json")
#define STORAGE_KEY "ttpGxMkT4wk7QJx77ak75dtYqaUdRQB5fJQO1NzzYFc="
#define STORAGE_CIPHER "128"

// Storage Backup
#define BACKUP_FILE_WEEK (STORAGE_DIR + "backup_week.json")
#define BACKUP_FILE_LAST (STORAGE_DIR + "backup_last.json")

// Encrypted tabs
#define E_TAB_CIPHER 128
#define DATE_FORMAT "dd.MM.yyyy"


// File Storage
#define FILES_DIR (STORAGE_DIR + "encrypted_files" + QDir::separator())
#define FILES_BUFFER_SIZE 33554432
#define FILES_CIPHER 128
#define FILES_KEY_SIZE 32

#define FILE_KILOBYTE 1024
#define FILE_MEGABYTE 1048576
#define FILE_GIGABYTE 1073741824

// Network
#define NETWORK_URL "http://0.0.0.0:3005/"
#define NETWORK_AES_TYPE 256
#define NETWORK_AES_KEY_SIZE 32
#define NETWORK_RSA_KEY_SIZE 1024
#define NETWORK_DEF_KEY "+7QqHqbuJEursfbU+uaJUmN1obOcZEza3oRUtmS+Qz8="


// Logs
#define LOG_FILE (STORAGE_DIR + "log.log")
#define LOG_COMPRESSION 0

//
// Options
//

//#define OPTION_SYNC // Enable sync (send on save, load on timer, sync menu in WMain MenuBar)
#define LOG_INCLUDE_METHOD

#define GROUP_SELECTED_IF_NULL(gr) (gr).first()


#endif //ORGANIZER_VARS_H
