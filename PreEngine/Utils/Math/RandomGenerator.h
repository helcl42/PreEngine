#ifndef RANDOM_GENERATOR_H
#define RANDOM_GENERATOR_H

#include <ctime>
#include <limits>


#define CMATH_N 624
#define CMATH_M 397
#define CMATH_MATRIX_A 0x9908b0df   /* constant vector a */
#define CMATH_UPPER_MASK 0x80000000 /* most significant w-r bits */
#define CMATH_LOWER_MASK 0x7fffffff /* least significant r bits */


#define CMATH_TEMPERING_MASK_B 0x9d2c5680
#define CMATH_TEMPERING_MASK_C 0xefc60000
#define CMATH_TEMPERING_SHIFT_U(y) (y >> 11)
#define CMATH_TEMPERING_SHIFT_S(y) (y << 7)
#define CMATH_TEMPERING_SHIFT_T(y) (y << 15)
#define CMATH_TEMPERING_SHIFT_L(y) (y >> 18)
namespace PreEngine
{
	namespace Utils
	{
		namespace Math
		{
			class RandomGenerator
			{
			private:
				unsigned int m_rseed;
				unsigned int m_rseedSp;
				unsigned long m_matrix[CMATH_N];
				int m_matrixIndex;

			public:
				RandomGenerator();
				virtual ~RandomGenerator();

			public:
				unsigned int    Random(unsigned int n);
				float           Random();
				void			SetRandomSeed(unsigned int n);
				unsigned int    GetRandomSeed();
				void            Randomize();
			};
		}
	}
}

#endif