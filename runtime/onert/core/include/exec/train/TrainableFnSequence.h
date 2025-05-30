/*
 * Copyright (c) 2023 Samsung Electronics Co., Ltd. All Rights Reserved
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef __ONERT_EXEC_TRAIN_TRAINABLE_FN_SEQUENCE_H__
#define __ONERT_EXEC_TRAIN_TRAINABLE_FN_SEQUENCE_H__

#include "exec/train/ITrainableFunction.h"
#include "exec/train/IGradientApplier.h"

#include <memory>
#include <vector>
#include <functional>

namespace onert::exec::train
{
class TrainableFnSequence
{
public:
  void forward(bool training);
  void backward(uint32_t training_step, bool weight_update_enabled);

  void append(std::unique_ptr<ITrainableFunction> &&fn);
  void append(std::unique_ptr<IGradientApplier> &&applier);
  void iterate(const std::function<void(ITrainableFunction &)> &fn);

public:
  // TODO Change members
  std::vector<std::unique_ptr<ITrainableFunction>> _functions;
  std::vector<std::unique_ptr<IGradientApplier>> _appliers;
};
} // namespace onert::exec::train

#endif // __ONERT_EXEC_TRAIN_TRAINABLE_FN_SEQUENCE_H__
