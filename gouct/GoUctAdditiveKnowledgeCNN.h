//----------------------------------------------------------------------------
/** @file GoUctAdditiveKnowledgeCNN.h
	A simple implementation of additive knowledge, using Fuego's
    rule-based prior knowledge.
    @todo hack: uses the fact that these prior values are already stored in
    RAVE values of each SgUctMoveInfo.
*/
//----------------------------------------------------------------------------


#ifndef GOUCT_ADDITIVEKNOWLEDGECNN_H
#define GOUCT_ADDITIVEKNOWLEDGECNN_H

#include "GoAdditiveKnowledge.h"
#include "MXNetModel.h"
#include "SgArray.h"

//----------------------------------------------------------------------------

class GoUctAdditiveKnowledgeCNN
    : public GoAdditiveKnowledgeStdProb
{
public:
    /** TODO tunable constant */
    // static const float VALUE_MULTIPLIER;

    GoUctAdditiveKnowledgeCNN(const GoBoard& bd);

    /** Apply as additive predictor */
    void ProcessPosition(std::vector<SgUctMoveInfo>& moves);

    void ProcessPosition(std::vector<SgUctMoveInfo>& moves, const GoBoard& currentBoard);

    void GetPrioProbability(SgArray<SgUctValue, SG_MAX_MOVE_VALUE>& outputArray, SgUctValue& outputValue, const std::vector<float>& inputData);


    MXNetModel m_MXNetModel;

};

//----------------------------------------------------------------------------

#endif // GOUCT_ADDITIVEKNOWLEDGECNN_H
