/*
	Copyright (c) 2017-2018 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#ifndef ORGANIZER_PTABPLUGIN_H
#define ORGANIZER_PTABPLUGIN_H

#include <plugins/Plugin.h>
#include <vendor/additions.h>


class PTabPlugin : public Plugin {
public:
    virtual void readInfo(const json_o &o) = 0;

    virtual void writeInfo(json_o &o) = 0;
};


#endif //ORGANIZER_PTABPLUGIN_H
