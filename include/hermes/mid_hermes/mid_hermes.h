/*
 * Copyright (c) 2017 Cossack Labs Limited
 *
 * This file is part of Hermes.
 *
 * Hermes is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Hermes is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with Hermes.  If not, see <http://www.gnu.org/licenses/>.
 *
 */


#ifndef MID_HERMES_H
#define MID_HERMES_H

#include <hermes/common/errors.h>
#include <hermes/rpc/transport.h>

#include <stdint.h>
#include <stdlib.h>

typedef struct mid_hermes_type mid_hermes_t;

mid_hermes_t* mid_hermes_create(const uint8_t* user_id,
                                const size_t user_id_length,
                                const uint8_t* sk,
                                const size_t sk_len,
                                hm_rpc_transport_t* ks_transport,
                                hm_rpc_transport_t* ds_transport,
                                hm_rpc_transport_t* cs_transport);

hermes_status_t mid_hermes_destroy(mid_hermes_t** mh);

hermes_status_t mid_hermes_create_block(mid_hermes_t* mh,
                                        uint8_t** id,
                                        size_t* id_length,
                                        const uint8_t* block,
                                        const size_t block_length,
                                        const uint8_t* meta,
                                        const size_t meta_length);

hermes_status_t mid_hermes_read_block(mid_hermes_t* mh,
                                      const uint8_t* block_id,
                                      const size_t block_id_length,
                                      uint8_t** block,
                                      size_t* block_length,
                                      uint8_t** meta,
                                      size_t* meta_length);

hermes_status_t mid_hermes_update_block(mid_hermes_t* mh,
                                        const uint8_t* block_id,
                                        const size_t block_id_length,
                                        const uint8_t* block,
                                        const size_t block_length,
                                        const uint8_t* meta,
                                        const size_t meta_length);

hermes_status_t mid_hermes_delete_block(mid_hermes_t* mh,
                                        const uint8_t* block_id,
                                        const size_t block_id_length);

hermes_status_t mid_hermes_rotate_block(mid_hermes_t* mh,
                                        const uint8_t* block_id,
                                        const size_t block_id_length);

hermes_status_t mid_hermes_grant_read_access(mid_hermes_t* mh,
                                             const uint8_t* block_id,
                                             const size_t bloc_id_length,
                                             const uint8_t* user_id,
                                             const size_t user_id_length);

hermes_status_t mid_hermes_grant_update_access(mid_hermes_t* mh,
                                               const uint8_t* block_id,
                                               const size_t bloc_id_length,
                                               const uint8_t* user_id,
                                               const size_t user_id_length);

hermes_status_t mid_hermes_deny_read_access(mid_hermes_t* mh,
                                            const uint8_t* block_id,
                                            const size_t bloc_id_length,
                                            const uint8_t* user_id,
                                            const size_t user_id_length);

hermes_status_t mid_hermes_deny_update_access(mid_hermes_t* mh,
                                              const uint8_t* block_id,
                                              const size_t bloc_id_length,
                                              const uint8_t* user_id,
                                              const size_t user_id_length);

#endif //MID_HERMES_H