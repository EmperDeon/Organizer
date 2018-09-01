/*
	Copyright (c) 2017-2018 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#ifndef ORGANIZER_TFILEGROUP_H
#define ORGANIZER_TFILEGROUP_H

#include <tabs/Tab.h>
#include <plugins/tabs/PTabFiles.h>


class TFileGroup : public Tab {
    PTabFiles *files;

public:
    explicit TFileGroup(const json_o &o);

    void loadCustomParams(const json_o &o) override;

    void saveCustomParams(json_o &o) override;
};


#endif //ORGANIZER_TFILEGROUP_H
