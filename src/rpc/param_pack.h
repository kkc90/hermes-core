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

#ifndef HERMES_RPC_PARAM_PACK_H
#define HERMES_RPC_PARAM_PACK_H

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct hm_param_pack_type hm_param_pack_t;

typedef uint32_t (*send_rouitine_t)(void* user_data, const uint8_t* buffer_to_send, const size_t buffer_to_send_length);
typedef uint32_t (*recv_rouitine_t)(void* user_data, uint8_t* buffer_to_receive, const size_t buffer_to_receive_length); //if really readed less than buffer_to_receive_length bytes need return error!!!

hm_param_pack_t* hm_param_pack_create();
hm_param_pack_t* hm_param_pack_create_(void* unused, ...);
uint32_t hm_param_pack_destroy(hm_param_pack_t** p);

//uint32_t hm_param_pack_push_int32(hm_param_pack_t* p, const int32_t val);
//uint32_t hm_param_pack_push_buffer(hm_param_pack_t* p, const uint8_t* val, const size_t val_length); //p own the val: You not need to free val 


//uint32_t hm_param_pack_pop_int32(hm_param_pack_t* p, uint32_t* val);
//uint32_t hm_param_pack_pop_buffer(hm_param_pack_t* p, uint8_t** val, size_t* val_length);//val steel own by p, not free it youself, after deletind p - val will be anaccessible

uint32_t hm_param_pack_write(hm_param_pack_t* p, uint8_t* buffer, size_t *buffer_length);
hm_param_pack_t* hm_param_pack_read(uint8_t* buffer, size_t buffer_length);

uint32_t hm_param_pack_send(hm_param_pack_t* p, send_rouitine_t* send_rouitine, void* user_data);
hm_param_pack_t* hm_param_pack_receive(recv_rouitine_t* receive_rouitine, void* user_data);

#define HM_PARAM_PACK_MAGIC 0x26048026
#define HM_PARAM_TYPE_INT32 0x26048027
#define HM_PARAM_TYPE_BUFFER 0x26048028

#define HM_PARAM_INT32(p) HM_PARAM_PACK_MAGIC, HM_PARAM_TYPE_INT32, p
#define HM_PARAM_BUFFER(p, p_len) HM_PARAM_PACK_MAGIC, HM_PARAM_TYPE_BUFFER, p, p_len

#define HM_PARAM_PACK(...) hm_param_pack_create_((void*)NULL, __VA_ARGS__, (void*)NULL)
#define HM_PARAM_EXTRACT(p, ...) hm_param_pack_extract_(p, __VA_ARGS__, (void*)NULL)

#endif //HERMES_RPC_PARAM_PACK_H
