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

#include "luci/Pass/ReplaceMulAddWithDepthwiseConvPass.h"

#include "BatchNormPatternFinder.h"

#include <luci/IR/CircleNodes.h>
#include <luci/Profile/CircleNodeOrigin.h>

namespace
{

luci::CircleConst *create_weights_from_gamma(luci::CircleConst *gamma)
{
  assert(gamma->rank() == 1 or gamma->rank() == 4);

  uint32_t channel_idx = gamma->rank() - 1;
  uint32_t channel_size = gamma->dim(channel_idx).value();

  // Gamma should be broadcastable in the channel direction
  for (uint32_t i = 0; i < gamma->rank(); i++)
  {
    if (i != channel_idx)
      assert(gamma->dim(i).value() == 1); // FIX is_batchnorm_mul UNLESS
  }

  auto name = gamma->name();
  assert(name.length() > 0);

  // Channel-wise MUL is the same as DEPTHWISE_CONV2D with filter shape (1,1,1,channel_size)
  auto weights = gamma->graph()->nodes()->create<luci::CircleConst>();
  weights->dtype(loco::DataType::FLOAT32);
  weights->rank(4);
  weights->dim(0).set(1);
  weights->dim(1).set(1);
  weights->dim(2).set(1);
  weights->dim(3).set(channel_size);
  weights->shape_status(luci::ShapeStatus::VALID);
  weights->size<loco::DataType::FLOAT32>(channel_size);
  for (uint32_t i = 0; i < channel_size; i++)
  {
    weights->at<loco::DataType::FLOAT32>(i) = gamma->at<loco::DataType::FLOAT32>(i);
  }
  weights->name(name + "_weights");

  return weights;
}

luci::CircleConst *create_bias_from_beta(luci::CircleConst *beta)
{
  assert(beta->rank() == 1 or beta->rank() == 4);

  uint32_t channel_idx = beta->rank() - 1;
  uint32_t channel_size = beta->dim(channel_idx).value();

  // Beta should be broadcastable in the channel direction
  for (uint32_t i = 0; i < beta->rank(); i++)
  {
    if (i != channel_idx)
      assert(beta->dim(i).value() == 1); // FIX is_batchnorm_add UNLESS
  }

  auto name = beta->name();
  assert(name.length() > 0);

  // Channel-wise ADD is the same as bias (shape = (channel_size)) of DEPTHWISE_CONV2D
  auto bias = beta->graph()->nodes()->create<luci::CircleConst>();
  bias->dtype(loco::DataType::FLOAT32);
  bias->rank(1);
  bias->dim(0).set(channel_size);
  bias->size<loco::DataType::FLOAT32>(channel_size);
  bias->shape_status(luci::ShapeStatus::VALID);
  for (uint32_t i = 0; i < channel_size; i++)
  {
    bias->at<loco::DataType::FLOAT32>(i) = beta->at<loco::DataType::FLOAT32>(i);
  }
  bias->name(name + "_bias");

  return bias;
}

/**
 *  Replace channel-wise Mul/Add with DepthwiseConv2D
 *
 *  BEFORE
 *
 *             [Node] [gamma]
 *                |  /
 *              [Mul]  [beta]
 *                |   /
 *               [Add]
 *
 *  AFTER
 *
 *              [Node]  [weights]  [bias]
 *                  \      /       /
 *                [DepthwiseConv2D]
 */
bool replace_mul_add_with_dwconv(luci::CircleAdd *add)
{
  luci::CircleNode *pred_node = nullptr;
  luci::CircleMul *mul = nullptr;
  luci::CircleConst *beta = nullptr;
  luci::CircleConst *gamma = nullptr;

  if (!is_batchnorm_add(add, mul, beta))
    return false;

  if (loco::succs(mul).size() != 1)
    return false;

  if (!is_batchnorm_mul(mul, pred_node, gamma))
    return false;

  if (pred_node->rank() != 4)
    return false;

  if (pred_node->dtype() != loco::DataType::FLOAT32 || beta->dtype() != loco::DataType::FLOAT32 ||
      gamma->dtype() != loco::DataType::FLOAT32)
    return false;

  auto weights = create_weights_from_gamma(gamma);
  auto bias = create_bias_from_beta(beta);

  auto name = add->name();
  assert(name.length() > 0);

  auto dwconv = add->graph()->nodes()->create<luci::CircleDepthwiseConv2D>();
  dwconv->input(pred_node);
  dwconv->filter(weights);
  dwconv->bias(bias);
  dwconv->padding(luci::Padding::SAME);
  dwconv->stride()->w(1);
  dwconv->stride()->h(1);
  dwconv->depthMultiplier(1);
  dwconv->dilation()->w(1);
  dwconv->dilation()->h(1);
  dwconv->fusedActivationFunction(add->fusedActivationFunction());
  dwconv->name(name + "/DepthwiseConv2D");
  luci::add_origin(dwconv, luci::composite_origin({luci::get_origin(mul), luci::get_origin(add)}));

  loco::replace(add).with(dwconv);
  return true;
}

} // namespace

namespace luci
{

bool ReplaceMulAddWithDepthwiseConvPass::run(loco::Graph *g)
{
  bool changed = false;
  for (auto node : loco::active_nodes(loco::output_nodes(g)))
  {
    if (auto add = dynamic_cast<luci::CircleAdd *>(node))
    {
      if (replace_mul_add_with_dwconv(add))
        changed = true;
    }
  }

  return changed;
}

} // namespace luci
