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

#ifndef IROHA_MAIN_CLI_HANDLER_START_HPP_
#define IROHA_MAIN_CLI_HANDLER_START_HPP_

#include <boost/assert.hpp>
#include "common/types.hpp"
#include "main/application.hpp"
#include "util/filesystem.hpp"
#include "crypto/keys_manager_impl.hpp"

namespace iroha {
  namespace cli {
    namespace handler {

      inline void start(const ametsuchi::config::Ametsuchi *am,
                        const iroha::config::Cryptography *crypto,
                        const iroha::config::OtherOptions *other,
                        const torii::config::Torii *torii) {
        BOOST_ASSERT_MSG(am, "ametsuchi config is nullptr");
        BOOST_ASSERT_MSG(crypto, "crypto config is nullptr");
        BOOST_ASSERT_MSG(other, "other config is nullptr");
        BOOST_ASSERT_MSG(torii, "torii config is nullptr");

        auto log = logger::log("irohad");

        iroha::keypair_t keypair;
        // TODO(@warchant): rewrite for new model
        // since it will be rewritten later, no need in good code here
        {
          KeysManagerImpl km;
          km.loadKeys(crypto->public_key, crypto->private_key);
        }

        try {
          Application irohad;
          irohad.initStorage(*am);
          irohad.initProtoFactories();
          irohad.initPeerQuery();
          irohad.initCryptoProvider(keypair);
          irohad.initValidators();
          irohad.initOrderingGate(*other);
          irohad.initSimulator();
          irohad.initBlockLoader();
          irohad.initConsensusGate(
              *torii, other->vote_delay, other->load_delay, keypair);
          irohad.initSynchronizer();
          irohad.initPeerCommunicationService();
          irohad.initTransactionCommandService();
          irohad.initQueryService();
          log->info("initialized");

          irohad.run(*torii);

          exit(EXIT_SUCCESS);
        } catch (const std::exception &e) {
          log->error("FATAL: {}", e.what());
          exit(EXIT_FAILURE);
        }
      }
    }
  }
}

#endif  //  IROHA_MAIN_CLI_HANDLER_START_HPP_