///~~~~~~~~~~~~~~~~ Rotating Square around the Z-axis clock-wise ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// This example demonstrates using the Vector3 class and the Matrix4 classes.
// By assigning the "M" 4x4 matrix the identity of a rotation matrix on the z-axis
// You can multiply a 3-point vector with the transform_w_matrix function from the matrix.
// This results in the square being rotated by the amount specified in the "angle" 
// variable.

#include <iostream>
#include <ctime>
#include "../head/d_math/d_math.hpp"

int main(int argc, char* argv[])
{
    // A clock to measure performance, though the accuracy is questionably...
    clock_t start = clock();

    // Array of 3-point vectors to create the square.
    Vec3f square[4] =
    {
        {0.0f, 0.0f, 0.0f},
        {0.0f, 1.0f, 0.0f},
        {1.0f, 1.0f, 0.0f},
        {1.0f, 0.0f, 0.0f}
    };

    // result of the matrix multiplication is stored in this array of 3-point vectors.
    Vec3f end_square[4] =
    {
        {0.0f, 0.0f, 0.0f},
        {0.0f, 1.0f, 0.0f},
        {1.0f, 1.0f, 0.0f},
        {1.0f, 0.0f, 0.0f}
    };

    // The matrix that'll be assigned the identity of a Z-rotation matrix (Clock-wise).
    Mat4f M(1.0f);

    // The angle (in degrees) that we'll want to rotate the square object by.
    float angle = 0.0f;

    // Printing the points out before the transformation.
    std::cout
        << "Points on square S...\n"
        << "Point 1: [" << square[0].x << ", " << square[0].y << ", " << square[0].z << "]\n"
        << "Point 2: [" << square[1].x << ", " << square[1].y << ", " << square[1].z << "]\n"
        << "Point 3: [" << square[2].x << ", " << square[2].y << ", " << square[2].z << "]\n"
        << "Point 4: [" << square[3].x << ", " << square[3].y << ", " << square[3].z << "]\n"
        << std::endl;

    // Where the transformation happens
    // In this case, I've set it up so it prints the information about the 3-point vector every
    // 10 degrees.
    for (int i = 0; i <= 9; i++) {

        // Step 1. Get the current angle that the square is rotated by.
        angle = 10.0f * float(i);

        // Step 2. Assign the rotation identity to the matrix.
        M[0][0] = cos(Degs_to_Rads(angle));
        M[0][1] = sin(Degs_to_Rads(angle));
        M[1][0] = -sin(Degs_to_Rads(angle));
        M[1][1] = cos(Degs_to_Rads(angle));
        M[3][3] = 1;// <-------------------------- This is here because the matrix is 4x4, and the SquareMatrix class initializes objects with 0 in all cells. 

        // Step 3. Multiply the rotation matrix by the points, and store the value in the "end_square" 3-point vector.
        end_square[0] = M.transform_w_matrix(square[0]);
        end_square[1] = M.transform_w_matrix(square[1]);
        end_square[2] = M.transform_w_matrix(square[2]);
        end_square[3] = M.transform_w_matrix(square[3]);

        // Step 4. Print out the new points locations.
        std::cout
            << angle << " degrees of rotation...\n"
            << "New points are...\n"
            << "Point 1: [" << end_square[0].x << ", " << end_square[0].y << ", " << end_square[0].z << "]\n"
            << "Point 2: [" << end_square[1].x << ", " << end_square[1].y << ", " << end_square[1].z << "]\n"
            << "Point 3: [" << end_square[2].x << ", " << end_square[2].y << ", " << end_square[2].z << "]\n"
            << "Point 4: [" << end_square[3].x << ", " << end_square[3].y << ", " << end_square[3].z << "]\n"
            << std::endl;
    }

    // Printing the points out after the transformation.
    // For some reason, the points don't land on the coordinates that I expected them to land,
    // they land VERY close to them, but not on them... maybe its my machine?
    std::cout
        << "transformed square S...\n"
        << "Point 1: [" << end_square[0].x << ", " << end_square[0].y << ", " << end_square[0].z << "]\n"
        << "Point 2: [" << end_square[1].x << ", " << end_square[1].y << ", " << end_square[1].z << "]\n"
        << "Point 3: [" << end_square[2].x << ", " << end_square[2].y << ", " << end_square[2].z << "]\n"
        << "Point 4: [" << end_square[3].x << ", " << end_square[3].y << ", " << end_square[3].z << "]\n"
        << std::endl;

    // Printing time it took to execute program
    fprintf(stderr, "Clock time %f\n", (clock() - start) / float(CLOCKS_PER_SEC));
    return 0;
}