/*
 * Copyright (c) 2020 Samsung Electronics Co., Ltd. All Rights Reserved
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

#include "FullyConnectedOptions.h"
#include "DataLookup.h"

#include <cassert>

namespace tflite2circle
{

flatbuffers::Offset<circle::FullyConnectedOptions>
build_circle_FullyConnectedOptions(flatbuffers::FlatBufferBuilder &fb, const tflite::Operator *op)
{
  auto tflite_builtin_options = op->builtin_options_as_FullyConnectedOptions();
  assert(tflite_builtin_options);
  circle::FullyConnectedOptionsBuilder builtin_options_builder{fb};
  builtin_options_builder.add_fused_activation_function(
    get_circle_activation_function_type(tflite_builtin_options->fused_activation_function()));
  // Get FullyConnectedOptionsWeightsFormat
  auto tflite_weight_format = tflite_builtin_options->weights_format();
  if (tflite_weight_format == tflite::FullyConnectedOptionsWeightsFormat_DEFAULT)
    builtin_options_builder.add_weights_format(circle::FullyConnectedOptionsWeightsFormat_DEFAULT);
  else if (tflite_weight_format == tflite::FullyConnectedOptionsWeightsFormat_SHUFFLED4x16INT8)
    builtin_options_builder.add_weights_format(
      circle::FullyConnectedOptionsWeightsFormat_SHUFFLED4x16INT8);
  builtin_options_builder.add_keep_num_dims(tflite_builtin_options->keep_num_dims());
  return builtin_options_builder.Finish();
}

} // namespace tflite2circle