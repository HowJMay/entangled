/*
 * Copyright (c) 2018 IOTA Stiftung
 * https:github.com/iotaledger/entangled
 *
 * MAM is based on an original implementation & specification by apmi.bsu.by
 * [ITSec Lab]
 *
 * Refer to the LICENSE file for licensing information
 */

#include <stdio.h>

#include "mam/examples/send-common.h"

int main(int ac, char **av) {
  mam_api_t api;
  bundle_transactions_t *bundle = NULL;
  tryte_t channel_id[MAM_CHANNEL_ID_TRYTE_SIZE];
  retcode_t ret = RC_OK;

  char *host = "node1.puyuma.org";
  char *port = "14265";
  char *seed = "JDTHZZRZTIBZDYVACFOFLNBSPTIAJBQREXPMLUQPFSPHJLZPG9WCAZTISFDPQ9QUOWVGCKNGJANYUAXOC";
  char *payload1 = "ThisIsNotMessegaNaYo_NUM_1";  
  char *payload2 = "ThisIsNotMessegaNaYo_NUM_2";  

  // Loading or creating MAM API
  if (ret = mam_api_init(&api, seed) != RC_OK) {
      fprintf(stderr, "mam_api_init failed with err %d\n", ret);
      return EXIT_FAILURE;
  }

  // Creating channel
  if ((ret = mam_example_channel_create(&api, channel_id)) != RC_OK) {
    fprintf(stderr, "mam_example_channel_create failed with err %d\n", ret);
    return EXIT_FAILURE;
  }

  bundle_transactions_new(&bundle);

  {
    trit_t msg_id[MAM_MSG_ID_SIZE];

    // Writing header to bundle
    if ((ret = mam_example_write_header_on_channel(&api, channel_id, bundle, msg_id)) != RC_OK) {
      fprintf(stderr, "mam_example_write_header failed with err %d\n", ret);
      return EXIT_FAILURE;
    }

    // Writing packet to bundle
    //bool last_packet = strcmp(av[5], "yes") == 0;
    bool last_packet = true;

    // if (mam_channel_num_remaining_sks(channel) == 0) {
    // TODO
    // - remove old ch
    // - create new ch
    // - add ch via `mam_api_add_channel`

    //   return RC_OK;
    // }

    if ((ret = mam_example_write_packet(&api, bundle, payload1, msg_id, last_packet)) != RC_OK) {
      fprintf(stderr, "mam_example_write_packet failed with err %d\n", ret);
      return EXIT_FAILURE;
    }
  }

  // Sending bundle
  if ((ret = send_bundle(host, atoi(port), bundle)) != RC_OK) {
    fprintf(stderr, "send_bundle failed with err %d\n", ret);
    return EXIT_FAILURE;
  }

#if 0
  // Saving and destroying MAM API
  if ((ret = mam_api_save(&api, MAM_FILE, NULL, 0)) != RC_OK) {
    fprintf(stderr, "mam_api_save failed with err %d\n", ret);
  }
  if ((ret = mam_api_destroy(&api)) != RC_OK) {
    fprintf(stderr, "mam_api_destroy failed with err %d\n", ret);
    return EXIT_FAILURE;
  }
#endif 

  // Cleanup
  bundle_transactions_free(&bundle);

  printf("====================================\n");
  
    bundle_transactions_new(&bundle);

  {
    trit_t msg_id[MAM_MSG_ID_SIZE];

    // Writing header to bundle
    if ((ret = mam_example_write_header_on_channel(&api, channel_id, bundle, msg_id)) != RC_OK) {
      fprintf(stderr, "mam_example_write_header failed with err %d\n", ret);
      return EXIT_FAILURE;
    }

    // Writing packet to bundle
    //bool last_packet = strcmp(av[5], "yes") == 0;
    bool last_packet = true;

    // if (mam_channel_num_remaining_sks(channel) == 0) {
    // TODO
    // - remove old ch
    // - create new ch
    // - add ch via `mam_api_add_channel`

    //   return RC_OK;
    // }

    if ((ret = mam_example_write_packet(&api, bundle, payload2, msg_id, last_packet)) != RC_OK) {
      fprintf(stderr, "mam_example_write_packet failed with err %d\n", ret);
      return EXIT_FAILURE;
    }
  }

  // Sending bundle
  if ((ret = send_bundle(host, atoi(port), bundle)) != RC_OK) {
    fprintf(stderr, "send_bundle failed with err %d\n", ret);
    return EXIT_FAILURE;
  }

  // Saving and destroying MAM API
  if ((ret = mam_api_save(&api, MAM_FILE, NULL, 0)) != RC_OK) {
    fprintf(stderr, "mam_api_save failed with err %d\n", ret);
  }
  if ((ret = mam_api_destroy(&api)) != RC_OK) {
    fprintf(stderr, "mam_api_destroy failed with err %d\n", ret);
    return EXIT_FAILURE;
  }

  // Cleanup
  bundle_transactions_free(&bundle);


  return EXIT_SUCCESS;
}
