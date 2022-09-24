#include "Collector.h"

Collector::Collector(RepresenterPDKA* pdkaRepresenter) : info(pdkaRepresenter) {}

void Collector::makeLoopExpression(RegularExpression& loop, const RegularExpression& expr) const {
    if (expr.length() == 1) {
        if (expr == "1") {
            loop = "";
        } else {
            (loop = expr) += "*";
        }
    } else {
        ((loop = "(") += expr) += ")*";
    }
}

void Collector::makeEdgeExpression(RegularExpression& edge, const RegularExpression& begin,
                                   const RegularExpression& loop, const RegularExpression& loopInsideExpr,
                                   const RegularExpression& end, bool edgeExist) const {
    if (edgeExist) {
        if (begin == loopInsideExpr && edge == end) {
            edge = "";
        } else {
            if (end == loopInsideExpr && edge == begin) {
                if (edge.isSum) {
                    ((edge = "(") += begin) += ")";
                }
                edge += loop;
                return;
            }
            edge += "+";
            if (!begin.isSum) {
                edge += (begin == "1" ? "" : begin);
            } else {
                ((edge += "(") += begin) += ")";
            }
        }
    } else {
        edge = (begin == "1" ? "" : begin);
    }
    edge += loop;
    if (!end.isSum) {
        edge += (end == "1" ? "" : end);
    } else {
        ((edge += "(") += end) += ")";
    }
}

RegularExpression Collector::collect() {
    int temp = 0;
    for (int curV = info->size - 1; curV >= 2; --curV) {
        RegularExpression loop;
        auto loopIt = info->edges[curV].find(curV);
        const RegularExpression& loopInsideExpr = (loopIt == info->edges[curV].end() ? "1" : loopIt->second);
        makeLoopExpression(loop, loopInsideExpr);
        for (int from = 1; from < info->size; ++from) {
            if (from == curV || !info->edges[from].count(curV)) {
                continue;
            }
            for (const auto& to : info->edges[curV]) {
                if (to.first == curV) {
                    continue;
                }
                const RegularExpression& begin = info->edges[from][curV];
                const RegularExpression& end = to.second;
                auto edgeIt = info->edges[from].find(to.first);
                bool edgeExist = true;
                if (edgeIt == info->edges[from].end()) {
                    edgeExist = false;
                    info->edges[from][to.first] = "";
                    edgeIt = info->edges[from].find(to.first);
                }
                makeEdgeExpression(edgeIt->second, begin, loop, loopInsideExpr, end, edgeExist);
                ++temp;
            }
            info->edges[from].erase(curV);
        }
        --info->size;
        info->edges[curV].clear();
    }
    //из 0 не выходило ребёр, входили только эпсилон ребра => из него не могло появиться рёбер =>
    //=>возможно остался только цикл в 1 и ребро из 1 в 0
    RegularExpression ans;
    auto loopIt = info->edges[1].find(1);
    if (loopIt != info->edges[1].end() && loopIt->second != "1") {
        if (loopIt->second.length() == 1) {
            (ans = loopIt->second) += "*";
        } else {
            ((ans = "(") += loopIt->second) += ")*";
        }
    }
    ans += info->edges[1][0];
    if (ans.length() == 0) {
        ans = "0";
    }
    return ans;
}