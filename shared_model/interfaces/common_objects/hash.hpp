/**
 * Copyright Soramitsu Co., Ltd. 2017 All Rights Reserved.
 * http://soramitsu.co.jp
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef IROHA_SHARED_MODEL_HASH_HPP
#define IROHA_SHARED_MODEL_HASH_HPP

#include <string>
#include "interfaces/primitive.hpp"
#include "model/signature.hpp"

namespace shared_model {
  namespace interface {

    /**
     * Hash interface present user-friendly blob for working with low-level
     * stuff, such as cryptography and object hashing
     */
    class Hash : public Primitive<Hash, Hash> {
     public:
      /**
       * @return provides raw representation of hash
       */
      virtual const std::string &blob() const = 0;

      /**
       * @return provides human-readable representation of hash
       */
      virtual const std::string &hex() const = 0;

      /**
       * @return size of raw representation of hash
       */
      virtual size_t size() const = 0;
    };
  }  // namespace interface
}  // namespace shared_model
#endif  // IROHA_SHARED_MODEL_HASH_HPP