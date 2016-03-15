#include "RandomGenerator.h"

namespace PreEngine
{
	namespace Utils
	{
		namespace Math
		{
			RandomGenerator::RandomGenerator(void)
			{
				m_rseed = 1;
				m_rseedSp = 0;
				m_matrixIndex = CMATH_N + 1;
			}

			RandomGenerator::~RandomGenerator()
			{
			}

			// Returns a number from 0 to n (excluding n)
			unsigned int RandomGenerator::Random(unsigned int n)
			{
				unsigned long y;
				static unsigned long mag01[2] = { 0x0, CMATH_MATRIX_A };

				if (n == 0) return 0;

				// mag01[x] = x * MATRIX_A  for x = 0,1
				if (m_matrixIndex >= CMATH_N)  // generate N words at one time
				{
					int kk;

					if (m_matrixIndex == CMATH_N + 1) SetRandomSeed(4357);

					for (kk = 0; kk < CMATH_N - CMATH_M; kk++)
					{
						y = (m_matrix[kk] & CMATH_UPPER_MASK) | (m_matrix[kk + 1] & CMATH_LOWER_MASK);
						m_matrix[kk] = m_matrix[kk + CMATH_M] ^ (y >> 1) ^ mag01[y & 0x1];
					}

					for (; kk < CMATH_N - 1; kk++)
					{
						y = (m_matrix[kk] & CMATH_UPPER_MASK) | (m_matrix[kk + 1] & CMATH_LOWER_MASK);
						m_matrix[kk] = m_matrix[kk + (CMATH_M - CMATH_N)] ^ (y >> 1) ^ mag01[y & 0x1];
					}

					y = (m_matrix[CMATH_N - 1] & CMATH_UPPER_MASK) | (m_matrix[0] & CMATH_LOWER_MASK);
					m_matrix[CMATH_N - 1] = m_matrix[CMATH_M - 1] ^ (y >> 1) ^ mag01[y & 0x1];

					m_matrixIndex = 0;
				}

				y = m_matrix[m_matrixIndex++];
				y ^= CMATH_TEMPERING_SHIFT_U(y);
				y ^= CMATH_TEMPERING_SHIFT_S(y) & CMATH_TEMPERING_MASK_B;
				y ^= CMATH_TEMPERING_SHIFT_T(y) & CMATH_TEMPERING_MASK_C;
				y ^= CMATH_TEMPERING_SHIFT_L(y);

				return (y % n);
			}

			float RandomGenerator::Random()
			{
				unsigned int max = std::numeric_limits<unsigned int>::max();
				float r = (float)Random(max);
				float divisor = (float)max;
				return (r / divisor);
			}

			void RandomGenerator::SetRandomSeed(unsigned int n)
			{
				m_matrix[0] = n & 0xffffffff;
				for (m_matrixIndex = 1; m_matrixIndex < CMATH_N; m_matrixIndex++)
				{
					m_matrix[m_matrixIndex] = (69069 * m_matrix[m_matrixIndex - 1]) & 0xffffffff;
				}

				m_rseed = n;
			}

			unsigned int RandomGenerator::GetRandomSeed(void)
			{
				return m_rseed;
			}

			void RandomGenerator::Randomize(void)
			{
				SetRandomSeed((unsigned int)time(NULL));
			}
		}
	}
}
