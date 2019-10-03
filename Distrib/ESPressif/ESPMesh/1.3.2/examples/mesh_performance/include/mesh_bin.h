#ifndef __MESH_BIN_H__
#define __MESH_BIN_H__

#include "c_types.h"

struct mesh_stat_info_type {
    uint32_t time;
    uint32_t ttime;
    uint32_t pps;
    uint32_t bps;
    uint32_t drop;
    uint32_t index;
    uint32_t loop;
};

/*
 * this function is used to parse binary stream
 */
void mesh_bin_proto_parser(const void *mesh_header, uint8_t *pdata, uint16_t len);

#endif
