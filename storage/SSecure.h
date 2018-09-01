/*
	Copyright (c) 2017-2018 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#ifndef ORGANIZER_SSECURE_H
#define ORGANIZER_SSECURE_H

#include <vendor/additions.h>
#include <vendor/additions.h>


class SSecure {
    json_o &obj;

public:
    explicit SSecure(json_o &o) : obj(o) {}

    QString password();

    void initNetworkInfo();
};


#endif //ORGANIZER_SSECURE_H
