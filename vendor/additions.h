/*
	Copyright (c) 2017-2018 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#ifndef ORGANIZER_ADDITIONS_H
#define ORGANIZER_ADDITIONS_H

#include <QtCore/QString>
#include <QtCore/QList>
#include <crypt/CBytes.h>
#include "cpp-markdown/src/markdown.h"

// byte macro defined in tomcrypt_macros.h and conflicts with variable name byte
#ifdef byte
#undef byte

#include "nlohmann/json.hpp"

// Define from tomcrypt_macros.h
#ifdef _MSC_VER
#define byte(x, n) ((unsigned char)((x) >> (8 * (n))))
#else
#define byte(x, n) (((x) >> (8 * (n))) & 255)
#endif

#else

#include "nlohmann/json.hpp"

#endif


std::string md2html(std::string in);

using json = nlohmann::json;

inline json::json_pointer operator "" _json_r(const char *s, std::size_t n) {
    return json::json_pointer(std::string(s, n));
}


typedef json json_a;
typedef json json_o;


// Serializers for Qt types
void to_json(json &j, const QString &p);

void from_json(const json &j, QString &p);

void to_json(json &j, const CBytes &p);

void from_json(const json &j, CBytes &p);

#endif //ORGANIZER_ADDITIONS_H
