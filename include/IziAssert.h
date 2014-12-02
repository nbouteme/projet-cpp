/**
*
* @file    IziAssert.h
*
* @authors Floran NARENJI-SHESHKALANI
*
* @date    24/11/2014
*
* @version V1.0
*
* @brief  IZI_ASSERT
*
**/
#pragma once

#include <iostream>

#define IZI_ASSERT(condition) iziAssert(condition, #condition, __FILE__, __LINE__, __func__);

namespace
{
    void iziAssert(bool success, const char* condition, const char* fileName, const int lineNumber, const char* functionName)
    {
        std::cout << (success ? "\033[32mASSERTION SUCCESS: \n" : "\033[31mASSERTION FAILED: \n")
                  << "\tFunction: "
                  << functionName
                  << "\n\tCondition: "
                  << condition
                  << "\n\tFile: "
                  << fileName
                  << "\n\tLine: "
                  << std::to_string(lineNumber)
                  << "\n\033[0m"
                  << std::endl;
    }
}
