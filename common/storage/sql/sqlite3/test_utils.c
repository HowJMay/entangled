/*
 * Copyright (c) 2019 IOTA Stiftung
 * https://github.com/iotaledger/entangled
 *
 * Refer to the LICENSE file for licensing information
 */

#include "common/storage/test_utils.h"
#include "common/storage/sql/sqlite3/connection.h"
#include "utils/files.h"
#include "utils/macros.h"

retcode_t storage_test_setup(storage_connection_t* const connection, storage_connection_config_t const* const config,
                             char const* const test_db_path, storage_connection_type_t const type) {
  retcode_t ret = RC_OK;

  if (type == STORAGE_CONNECTION_TANGLE) {
    ret = iota_utils_copy_file(test_db_path, "common/storage/sql/sqlite3/tangle.db");
  } else if (type == STORAGE_CONNECTION_SPENT_ADDRESSES) {
    ret = iota_utils_copy_file(test_db_path, "common/storage/sql/sqlite3/spent-addresses.db");
  }

  if (ret != RC_OK) {
    return ret;
  }

  return storage_connection_init(connection, config, type);
}

retcode_t storage_test_teardown(storage_connection_t* const connection, char const* const test_db_path,
                                storage_connection_type_t const type) {
  retcode_t ret = RC_OK;
  UNUSED(type);

  if ((ret = storage_connection_destroy(connection)) != RC_OK) {
    return ret;
  }

  return iota_utils_remove_file(test_db_path);
}
