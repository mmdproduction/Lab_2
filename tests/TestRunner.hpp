#pragma once
#include <gtest/gtest.h>
#include "Sequence.hpp"
#include <string>
#include <cstring>


struct TestResultData {
    char name[256];
    char message[512]; 
    bool passed;
    double time_ms;
    
    TestResultData() : passed(false), time_ms(0.0f) {
        name[0] = '\0';
        message[0] = '\0';
    }
};


class GTestManager {
private:
    
    ListSequence<TestResultData> results;
    

    int totalTests;
    int passedCount;
    int failedCount;
    double totalTimeMs;
    bool isRunning;


    class ResultPrinter : public ::testing::EmptyTestEventListener {
    public:
        GTestManager* manager;
        
        ResultPrinter(GTestManager* mgr);
        void onTestPartResult(const ::testing::TestPartResult& result) override;
        void onTestEnd(const ::testing::TestInfo& test_info) override;
    };

    ResultPrinter* printer;

public:
    GTestManager() : totalTests(0), passedCount(0), failedCount(0), totalTimeMs(0), isRunning(false), printer(nullptr) {}


    bool run(const char* filter = nullptr);
    const LinkedList<TestResultData>& getResults() const { return results; }
    int getTotal() const { return totalTests; }
    int getPassed() const { return passedCount; }
    int getFailed() const { return failedCount; }
    double getTime() const { return totalTimeMs; }
    bool getIsRunning() const { return isRunning; }

    float getProgress() const;
};