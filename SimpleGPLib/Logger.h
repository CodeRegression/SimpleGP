//--------------------------------------------------
// A logger for basic applications
//
// @author: Wild Boar
//
// @date: 2022-09-26
//--------------------------------------------------

#pragma once

#include <sstream>
#include <iostream>
using namespace std;

#include <NVLib/StringUtils.h>

namespace NVL_App
{
	class Logger
	{
    private:
        stringstream _stream;
    public:
        struct End 
        { 
            friend ostream& operator << (ostream& stream, const End& value) 
            {
                return stream;
            } 
        };
    public:

        template <typename T>
        Logger& operator << (T param) 
        { 
            if (is_same<T, End>::value) 
            {
                auto message = _stream.str();
                Write(message);
                _stream = stringstream();	
            }
            else _stream << param;
                
            return *this;            
        }

        virtual void Write(const string& message) 
        {
            auto dateString = NVLib::StringUtils::GetDateTimeString();
            cout << "[" << dateString << "] " << message << endl;
        }
 	};
}
