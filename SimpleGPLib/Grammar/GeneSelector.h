//--------------------------------------------------
// Select the associated Genes
//
// @author: Wild Boar
//
// @date: 2022-09-30
//--------------------------------------------------

#pragma once

#include <iostream>
using namespace std;

#include <NVLib/RandomUtils.h>

namespace NVL_AI
{
	class GeneSelector
	{
		public:
			GeneSelector() 
			{
				NVLib::RandomUtils::TimeSeedRandomNumbers();
			}

			virtual bool Next() 
			{
				return NVLib::RandomUtils::GetBinaryChoice(0.5);
			}
	};
}
