#include "Builder.h"
#include "RepresenterNKA.h"
#pragma once

class BuilderPDKA {
public:
    Builder* builder;
    RepresenterNKA* representer;

    BuilderPDKA(Builder* builder, RepresenterNKA* representer);
    Graph* build();
};
