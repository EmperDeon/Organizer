/*
	Copyright (c) 2017-2018 by Ilya Barykin
	Released under the MIT License.
	See the provided LICENSE.TXT file for details.
*/

#include "additions.h"

std::string md2html(std::string in) {
    auto ins = std::istringstream(in);

    auto *doc = new markdown::Document(ins);

    auto ots = std::ostringstream();
    doc->write(ots);

    return ots.str();
}

void to_json(json &j, const QString &p) {
    j = p.toStdString();
}

void from_json(const json &j, QString &p) {
    p = QString::fromStdString(j);
}
