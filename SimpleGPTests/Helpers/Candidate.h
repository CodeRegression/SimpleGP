//--------------------------------------------------
// Model: A candidate solution for this test case
//
// @author: Wild Boar
//
// @date: 2022-02-07
//--------------------------------------------------

#pragma once

#include <vector>
#include <iostream>
using namespace std;

#include <GeneticLib/Utility/CandidateFactoryBase.h>

namespace NVL_AI
{
	class Candidate : public CandidateBase
	{
	private:
        vector<bool> _data;
    public:

        /**
         * @brief Main Constructor
         * @param id The identifier of the solution
         * @param data The data associated with the solution
         */
		Candidate(int id, vector<bool>& data) : CandidateBase(id, 0), _data(data) {}

        /**
         * @brief Equality check
         * @param candidate The candidate we are checking
         * @return true They are equal
         * @return false They are not equal
         */
        virtual bool Equals(CandidateBase * candidate) override 
        {
            auto c = (Candidate *) candidate;

            if (_data.size() != c->GetData().size()) return false;

            for (auto i = 0; i < _data.size(); i++) 
            {
                if (_data[i] != c->GetData()[i]) return false;
            }

            return true;
        }


        /**
         * @brief Converts the solution to a string
         * @return string A string representation of the solution
         */
        virtual string ToString() override 
        {
            auto result = stringstream();
            for (auto i = 0; i < _data.size(); i++) 
            {
                if (i != 0) result << " ";
                auto value = _data[i] ? "1" : "0";
                result << value;
            }    

            return result.str();
        }

        /**
         * @brief Add the logic to clone a solution
         * @return CandidateBase* The cloned version of this solution
         */
        virtual CandidateBase * Clone() override
        {
            auto result = new Candidate(GetId(), _data);
            result->SetScore(GetScore());
            return result;
        }

        /**
         * @brief Retrieve the underlying data set
         * @return A vector of the data that we are returning
         */
        inline vector<bool>& GetData() { return _data; }
    };
}