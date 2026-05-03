#pragma once
#include"TestRunner.hpp"



GTestManager::ResultPrinter::ResultPrinter(GTestManager* mgr) : manager(mgr) {}
void GTestManager::ResultPrinter::onTestPartResult(const ::testing::TestPartResult& result) {
    if (!result.passed()) {

        if (!manager->results.isEmpty()) {
            TestResultData& last = manager->results.getLast();
            std::strncpy(last.message, result.message(), sizeof(last.message) - 1);
            last.passed = false;
            manager->failedCount++;
        }
    }
}

void GTestManager::ResultPrinter::onTestEnd(const ::testing::TestInfo& test_info) {
    TestResultData data;
            
    std::string fullName = std::string(test_info.test_suite_name()) + "." + test_info.name();
    std::strncpy(data.name, fullName.c_str(), sizeof(data.name) - 1);
            
    data.passed = test_info.result()->Passed();
    data.time_ms = test_info.result()->elapsed_time() / 1000.0;
        
    if (data.passed) {
        manager->passedCount++;
    } else {
        manager->failedCount++;
    }
            
    manager->results.append(data);
    manager->totalTests++;
    manager->totalTimeMs += data.time_ms;
}


GTestManager::GTestManager() : totalTests(0), passedCount(0), failedCount(0), totalTimeMs(0), isRunning(false), printer(nullptr) {}


bool GTestManager::run(const char* filter = nullptr) {
    if (isRunning) return false;
    results = LinkedList<TestResultData>();
    totalTests = 0;
    passedCount = 0;
    failedCount = 0;
    totalTimeMs = 0;
    isRunning = true;

    static bool gtestInit = false;
    if (!gtestInit) {
        int argc = 1;
        char* argv[] = {(char*)"tests"};
        ::testing::InitGoogleTest(&argc, argv);
        gtestInit = true;
    }

    printer = new ResultPrinter(this);
    ::testing::UnitTest::GetInstance()->listeners().Append(printer);

    if (filter && std::strlen(filter) > 0) {
        ::testing::GTEST_FLAG(filter) = filter;
    } else {
        ::testing::GTEST_FLAG(filter) = "*";
    }

    RUN_ALL_TESTS();

    ::testing::UnitTest::GetInstance()->listeners().Release(printer);
    delete printer;
    printer = nullptr;
        
    isRunning = false;
    return failedCount == 0;
}

float GTestManager::getProgress() const {
        if (totalTests == 0) return 0.0f;
        return (float)(passedCount + failedCount) / (float)totalTests;
}