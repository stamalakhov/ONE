/*
 * Copyright (c) 2024 Samsung Electronics Co., Ltd. All Rights Reserved
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

#ifndef __ONERT_IR_TRAIN_OPERATION_BINARY_ARITHMETIC_H__
#define __ONERT_IR_TRAIN_OPERATION_BINARY_ARITHMETIC_H__

#include "ir/operation/BinaryArithmetic.h"
#include "ir/train/TrainableOperation.h"

namespace onert::ir::train::operation
{

class BinaryArithmetic : public ir::operation::BinaryArithmetic, public TrainableOperation
{
private:
  using OperationType = ir::operation::BinaryArithmetic;

public:
  BinaryArithmetic(const OperationType &operation);

public:
  std::unique_ptr<ITrainableOperation> clone() const override;
  void accept(OperationVisitor &v) const override;
  void accept(TrainableOperationVisitor &v) const override;
  bool hasTrainableParameter() const override { return false; }
};

} // namespace onert::ir::train::operation

#endif // __ONERT_IR_TRAIN_OPERATION_BINARY_ARITHMETIC_H__
