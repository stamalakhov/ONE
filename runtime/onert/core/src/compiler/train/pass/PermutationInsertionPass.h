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

#ifndef __ONERT_COMPILER_TRAIN_PASS_PERMUTATION_INSERTION_PASS_H__
#define __ONERT_COMPILER_TRAIN_PASS_PERMUTATION_INSERTION_PASS_H__

#include "../../pass/PermutationInsertionPass.h"

namespace onert
{
namespace compiler
{
namespace train
{
namespace pass
{

class PermutationInsertionPass : public compiler::pass::PermutationInsertionPass
{
public:
  using compiler::pass::PermutationInsertionPass::PermutationInsertionPass;

public:
  void callback(const ir::OperandIndex &index, ir::Operand &object) final;
};

} // namespace pass
} // namespace train
} // namespace compiler
} // namespace onert

#endif // __ONERT_COMPILER_TRAIN_PASS_PERMUTATION_INSERTION_PASS_H__