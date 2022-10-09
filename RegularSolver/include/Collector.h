#include "Builder.h"
#include "RepresenterPDKA.h"
#pragma once

class Collector {
public:
    //Builder* builder;
    RepresenterPDKA* info;

    Collector(RepresenterPDKA* pdkaRepresenter);
    RegularExpression collect();
    void makeLoopExpression(RegularExpression& loop, const RegularExpression& expr) const;
    void makeEdgeExpression(RegularExpression& edge, const RegularExpression& begin,
                            const RegularExpression& loop, const RegularExpression& loopInsideExpr,
                            const RegularExpression& end, bool edgeExist) const;
};

