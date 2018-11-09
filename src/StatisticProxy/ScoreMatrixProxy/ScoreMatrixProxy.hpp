#ifndef __SCORE_MATRIX_PROXY__
#define __SCORE_MATRIX_PROXY__

#include <unordered_map>
#include <string>
#include <iostream>
#include <sstream>
#include <memory>
#include <fstream>
#include <cassert>
#include <cstdlib>
#include "Dependency/ScoreMatrix.hpp"
#include "StatisticProxy/ProxyModule.hpp"
#include "common/Exception.hpp"
#include "Log/Log.hpp"

class ScoreMatrixProxy : public ProxyModule {
private:

    ScoreMatrix m_scoreMatrix;

    std::ifstream m_scoreMatrixFile;

    std::ifstream m_inactiveUserFile;

public:
    ScoreMatrixProxy(const std::string& scoreMatrixFile, const std::string& inactiveUserFile) throw();

    virtual ~ScoreMatrixProxy();

    virtual void parse();

    virtual void show();

    ScoreMatrix& get();

};

#endif
