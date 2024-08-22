/*******************************************************************************
 *
 * MIT License
 *
 * Copyright (c) 2024 Advanced Micro Devices, Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 *******************************************************************************/

#include "unit_conv_solver.hpp"

namespace {

auto GetConvTestCases(miopenDataType_t datatype)
{
    using TestCase = ConvTestCase;

    return std::vector{
        // clang-format off
        TestCase{{1, 8, 8, 8}, {8, 8, 3, 3}, {0, 0}, {1, 1}, {1, 1}, datatype},
        // clang-format on
    };
}

Gpu GetSupportedDevices()
{
    return Gpu::gfx900 | Gpu::gfx906 | Gpu::gfx908 | Gpu::gfx90A | Gpu::gfx94X | Gpu::gfx103X |
           Gpu::gfx110X;
}

} // namespace

TEST_P(GPU_UnitTestConvSolverWrw_FP16, GemmWrwUniversal)
{
    this->RunTest(miopen::solver::conv::GemmWrwUniversal{});
};

TEST_P(GPU_UnitTestConvSolverWrw_BF16, GemmWrwUniversal)
{
    this->RunTest(miopen::solver::conv::GemmWrwUniversal{});
};

TEST_P(GPU_UnitTestConvSolverWrw_FP32, GemmWrwUniversal)
{
    this->RunTest(miopen::solver::conv::GemmWrwUniversal{});
};

TEST_P(CPU_UnitTestConvSolverDevApplicabilityWrw_NONE, GemmWrwUniversal)
{
    this->RunTest(miopen::solver::conv::GemmWrwUniversal{});
};

// Smoke tests
INSTANTIATE_TEST_SUITE_P(Smoke,
                         GPU_UnitTestConvSolverWrw_FP16,
                         testing::Combine(testing::Values(GetSupportedDevices()),
                                          testing::Values(miopenConvolutionAlgoGEMM),
                                          testing::ValuesIn(GetConvTestCases(miopenHalf))));

INSTANTIATE_TEST_SUITE_P(Smoke,
                         GPU_UnitTestConvSolverWrw_BF16,
                         testing::Combine(testing::Values(GetSupportedDevices()),
                                          testing::Values(miopenConvolutionAlgoGEMM),
                                          testing::ValuesIn(GetConvTestCases(miopenBFloat16))));

INSTANTIATE_TEST_SUITE_P(Smoke,
                         GPU_UnitTestConvSolverWrw_FP32,
                         testing::Combine(testing::Values(GetSupportedDevices()),
                                          testing::Values(miopenConvolutionAlgoGEMM),
                                          testing::ValuesIn(GetConvTestCases(miopenFloat))));

// Device applicability test
INSTANTIATE_TEST_SUITE_P(Smoke,
                         CPU_UnitTestConvSolverDevApplicabilityWrw_NONE,
                         testing::Combine(testing::Values(GetSupportedDevices()),
                                          testing::Values(GetConvTestCases(miopenFloat)[0])));