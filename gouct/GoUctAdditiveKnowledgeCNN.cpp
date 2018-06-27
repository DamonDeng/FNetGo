//----------------------------------------------------------------------------
/** @file GoUctAdditiveKnowledgeCNN.cpp
    See GoUctAdditiveKnowledgeCNN.h
*/
//----------------------------------------------------------------------------

#include "SgSystem.h"
#include "GoUctAdditiveKnowledgeCNN.h"

#include <cmath>
#include "SgPoint.h"
#include "SgDebug.h"

//----------------------------------------------------------------------------

// not used in CNN knowledge
// const float GoUctAdditiveKnowledgeCNN::VALUE_MULTIPLIER = 4.0f;

//----------------------------------------------------------------------------

GoUctAdditiveKnowledgeCNN::GoUctAdditiveKnowledgeCNN(const GoBoard& bd)
    : GoAdditiveKnowledgeStdProb(bd),
    m_MXNetModel(0)
{ }

// m_raveValue is a SgUctValue which is double by default, but holds
// a predictor value which only has float precision
inline float RaveValueAsFloat(const SgUctMoveInfo& info)
{
    return static_cast<float>(info.m_raveValue);
}

// @todo Assumes that SgMoveInfo has m_raveValue (and m_raveCount) populated
// by prior knowledge.
// This is a hack. Should call prior knowledge directly.
void 
GoUctAdditiveKnowledgeCNN::ProcessPosition(std::vector<SgUctMoveInfo>& moves)
{

    SgDebug() << "Just hacking implementation of ProcessPOsition. \n";
    
}

void 
GoUctAdditiveKnowledgeCNN::ProcessPosition(std::vector<SgUctMoveInfo>& moves, const GoBoard& currentBoard)
{

    // SgDebug() << "Trying to apply cnn additiveKnowledge. \n";

    // const GoBoard& currentBoard = Board();

    

    int historyLength = 8;
    int arrayLength = historyLength*2 + 1;

    int boardSize = 19;

    int dataLength = arrayLength*boardSize*boardSize;

    std::vector<float> historyData(dataLength);

    currentBoard.GetHistoryData(historyData, historyLength);

    // Debug code

    // for (int i=0; i<arrayLength; i++){
    //     for (int row=18; row>=0; row--){
    //         for (int col=0; col<19; col++){
    //             int index = i*boardSize*boardSize + row*boardSize + col;
    //             if (historyData[index] == 0){
    //                 SgDebug() << ". ";
    //             } else {
    //                 SgDebug() << historyData[index] << " ";
    //             }
    //         }
    //         SgDebug() << "\n";
    //     }

    //     SgDebug() << "------------------------- \n";
    // }

    // SgDebug() << currentBoard;

    // end of Debug code

    SgArray<SgUctValue, SG_MAX_MOVE_VALUE> array;
    SgUctValue value;
    
    m_MXNetModel.GetPrioProbability(array, value, historyData);

    SG_ASSERT(moves.size() <= static_cast<unsigned int>(SG_MAX_MOVES));
    for (size_t i = 0; i < moves.size(); ++i) 
    {
        

        if (moves[i].m_move == SG_PASS){
            moves[i].m_predictorValue = array[SG_MAX_MOVE_VALUE-1];
            moves[i].m_prioProbability = array[SG_MAX_MOVE_VALUE-1];
        } else {
            if (moves[i].m_move >= SG_MAX_MOVE_VALUE){
                    SgDebug() << "incorrect move value: " << moves[i].m_move << " !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
            } else {
                moves[i].m_predictorValue = array[moves[i].m_move];  
                moves[i].m_prioProbability = array[moves[i].m_move];  
            }
        }
    }
    

    
}

void GoUctAdditiveKnowledgeCNN::GetPrioProbability(SgArray<SgUctValue, SG_MAX_MOVE_VALUE>& outputArray, SgUctValue& outputValue, const std::vector<float>& inputData){

    SgDebug() << "Trying to apply cnn additiveKnowledge to root node which has no additive knowledge. \n";

    m_MXNetModel.GetPrioProbability(outputArray, outputValue, inputData);



}

//----------------------------------------------------------------------------
