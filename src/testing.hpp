#pragma once

//? test class for testing out shit

//TODO: work on this shit that I know will take a while...
template <class UserType, size_t m_dimension, size_t n_dimension>
struct Matrix
{
	UserType user_matrix[m_dimension][n_dimension];

	Matrix()
	{
		for (size_t i = 0; i < m_dimension; i++) {
			for (size_t j = 0; j < n_dimension; j++) {
				user_matrix[i][j] = 0;
			}
		}
	}

	size_t rows()
	{
		return m_dimension;
	}

	size_t columns()
	{
		return n_dimension;
	}

	const UserType* operator[](size_t index) const
	{
		return user_matrix[index];
	}
	UserType* operator[](size_t index)
	{
		return user_matrix[index];
	}
};