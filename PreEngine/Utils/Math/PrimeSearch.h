#ifndef PRIMARY_SEARCH_H
#define PRIMARY_SEARCH_H

#include <cstdlib>

namespace PreEngine
{
	namespace Utils
	{
		namespace Math
		{
			class PrimeSearch
			{
			private:
				static int primeArray[];

				int skip;
				int currentPosition;
				int maxElements;
				int *currentPrime;
				int searches;

			public:
				PrimeSearch(int elements);
				virtual ~PrimeSearch();

			public:
				int  GetNext(bool restart = false);
				bool Done();
				void Restart();
			};
		}
	}
}

#endif