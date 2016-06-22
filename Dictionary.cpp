//
// Created by Edward on 6/15/2016.
//

#include <dawg-builder.h>
#include "Dictionary.h"

Dictionary::Dictionary() {
    dawgdic::DawgBuilder dawg_builder;
    dawg_builder.Insert("apple");
    dawg_builder.Insert("orange");

    dawgdic::Dawg dawg;
    dawg_builder.Finish(&dawg);

    dawgdic::Dictionary dict;
    dawgdic::DictionaryBuilder::Build(dawg, &dict);
}
