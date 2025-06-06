/*
 * Copyright (c) 2023 Samsung Electronics Co., Ltd. All Rights Reserved
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef ONERT_MICRO_EXECUTE_PAL_SELECT_V2_H
#define ONERT_MICRO_EXECUTE_PAL_SELECT_V2_H

#include "PALUtils.h"
#include "ProcessBroadcastShapes.h"
#include "core/OMRuntimeShape.h"
#include "core/OMKernelData.h"

namespace onert_micro
{
namespace execute
{
namespace pal
{

template <typename D, typename T>
void Select(const core::OMRuntimeShape &input_condition_shape, const D *input_condition_data,
            const core::OMRuntimeShape &input_x_shape, const T *input_x_data,
            const core::OMRuntimeShape &input_y_shape, const T *input_y_data,
            const core::OMRuntimeShape &output_shape, T *output_data)
{
  int64_t flatsize;
  // Allow select operator executions on mixed scalar tensors and one element
  // tensors.
  if (input_condition_shape.flatSize() == 1 && input_x_shape.flatSize() == 1 &&
      input_y_shape.flatSize() == 1 && output_shape.flatSize() == 1)
  {
    flatsize = 1;
  }
  else
  {
    flatsize = input_condition_shape.flatSize();
  }
  for (int64_t i = 0; i < flatsize; ++i)
  {
    output_data[i] = input_condition_data[i] ? input_x_data[i] : input_y_data[i];
  }
}

} // namespace pal
} // namespace execute
} // namespace onert_micro

#endif // ONERT_MICRO_EXECUTE_PAL_SELECT_V2_H
