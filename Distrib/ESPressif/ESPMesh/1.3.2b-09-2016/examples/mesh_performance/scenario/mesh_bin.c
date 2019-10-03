/******************************************************************************
 * Copyright 2015-2016 Espressif Systems
 *
 * FileName: mesh_bin.c
 *
 * Description: mesh demo for binary stream parser
 *
 * Modification history:
 *     2016/03/15, v1.1 create this file.
*******************************************************************************/
#include "mem.h"
#include "mesh.h"
#include "osapi.h"
#include "mesh_parser.h"

extern struct espconn g_ser_conn;

static os_timer_t g_stat_timer;
static os_timer_t g_stat_check_timer;
static os_timer_t g_disp_timer;
static uint32_t g_pkt_len = 64;
static uint32_t g_pkt_tx_idx = 0;
static uint32_t g_pkt_rx_idx = 0;
static uint8_t g_dummy_count = 0;
static bool g_mesh_stat_init = false;
static struct mesh_stat_info_type g_stat_info;

void mesh_sent_cb(void *arg);
void mesh_stat_start(void *len);

void ICACHE_FLASH_ATTR mesh_bin_proto_parser(const void *mesh_header, uint8_t *pdata, uint16_t len)
{
    uint8_t *src = NULL, *dst = NULL;
    struct mesh_stat_info_type *stat = NULL;
    struct mesh_header_format *header = (struct mesh_header_format *)mesh_header;

    if (!header || !pdata || len < sizeof(*stat))
        return;

    stat = (struct mesh_stat_info_type *)pdata;

    /*
     * if the packet is forwarded from parent
     * the current node update statistic information
     */
    if (!stat->loop) {
        //MESH_DEMO_PRINT("rx-idx:%u, idx:%u\n", g_pkt_rx_idx, stat->index);
        uint32_t time = system_get_time();
        if (stat->index != ++g_pkt_rx_idx) {
            g_stat_info.drop += stat->index - g_pkt_rx_idx + 1;
            g_pkt_rx_idx = stat->index + 1;
        }
        g_stat_info.pps += stat->pps;
        g_stat_info.bps += stat->bps;
        if (time > stat->time)
            g_stat_info.ttime += time - stat->time;
        else
            g_stat_info.ttime += time + ((uint32_t)0xFFFFFFFF - stat->time);
        return;
    }

    /*
     * parent receives packet from child node
     * it clears loop flag, then echo it back
     */
    stat->loop = 0;

    if (!espconn_mesh_get_src_addr(header, &src) || !espconn_mesh_get_dst_addr(header, &dst)) {
        MESH_DEMO_PRINT("get addr fail\n");
        return;
    }

    header = (struct mesh_header_format *)espconn_mesh_create_packet(
                            src,   // destiny address
                            dst,   // source address
                            false, // not p2p packet
                            true,  // piggyback congest request
                            M_PROTO_BIN,  // packe with JSON format
                            len,  // data length
                            false, // no option
                            0,     // option len
                            false, // no frag
                            0,     // frag type, this packet doesn't use frag
                            false, // more frag
                            0,     // frag index
                            0);    // frag length
    if (!header) {
        MESH_DEMO_PRINT("create packet fail\n");
        return;
    }

    if (!espconn_mesh_set_usr_data(header, (uint8_t *)stat, len)) {
        MESH_DEMO_PRINT("set user data fail\n");
        MESH_DEMO_FREE(header);
        return;
    }

    if (espconn_mesh_sent(&g_ser_conn, (uint8_t *)header, header->len)) {
        MESH_DEMO_PRINT("forward mesh sent fail, heap:%u, dst:" MACSTR "\n",
                system_get_free_heap_size(), MAC2STR(src));
        espconn_mesh_connect(&g_ser_conn);
        espconn_mesh_print_status(0);
    } else {
        //MESH_DEMO_PRINT("forward-idx:%u\n", stat->index);
    }

    MESH_DEMO_FREE(header);
}

void ICACHE_FLASH_ATTR mesh_stat_init()
{
    if (g_mesh_stat_init)
        return;
    g_mesh_stat_init = true;

    MESH_DEMO_MEMSET(&g_stat_info, 0, sizeof(g_stat_info));
}

void ICACHE_FLASH_ATTR mesh_stat_reinit()
{
    MESH_DEMO_MEMSET(&g_stat_info, 0, sizeof(g_stat_info));
}

void ICACHE_FLASH_ATTR mesh_stat_disp()
{
    static uint32_t ttime = 1;
    static uint8_t repeat = 0;
    static uint32_t pps = 0;
    uint16_t pkt_len = g_pkt_len + ESP_MESH_HLEN;

    if (!g_mesh_stat_init)
        return;

    if (ttime * 1000 > g_stat_info.ttime) {
        /* 
         * overflow, we reset the statistic
         */
        ttime = 1;
        os_memset(&g_stat_info, 0, sizeof(g_stat_info));
    }

    if (espconn_mesh_is_root()) {  // root doesn't need to test
        repeat ++;
        if (repeat > 10) {
            os_timer_disarm(&g_stat_timer);
            os_timer_disarm(&g_disp_timer);
        }
        return;
    }

    repeat = 0;

    if (g_stat_info.ttime == 0)
        return;

    /*
     * the test case stop,
     * we restart it
     */
    if (pps == g_stat_info.pps) {
        g_stat_info.drop += g_pkt_tx_idx - g_pkt_rx_idx;
        g_pkt_rx_idx = g_pkt_tx_idx;
        mesh_stat_start(&g_pkt_len);
    }

    pps = g_stat_info.pps;

    ttime = g_stat_info.ttime / 1000;

    MESH_DEMO_PRINT("total time: %u us\n", g_stat_info.ttime);
    MESH_DEMO_PRINT("total pkt: %u, pkt_len:%u\n", g_stat_info.pps, pkt_len);
    MESH_DEMO_PRINT("pps: %d.%d%dpps\n", g_stat_info.pps * 1000 / ttime,
            (g_stat_info.pps * 1000 % ttime) * 10 / ttime,
            ((g_stat_info.pps * 1000 % ttime) * 10 % ttime) * 10 / ttime);
    MESH_DEMO_PRINT("bps: %d.%d%dkbps\n", g_stat_info.pps * pkt_len * 8 / ttime,
            (g_stat_info.pps * pkt_len * 8 % ttime) * 10 / ttime,
            ((g_stat_info.pps * pkt_len * 8 % ttime) * 10 % ttime) * 10 / ttime);

    if (g_stat_info.pps == 0)
        return;

    MESH_DEMO_PRINT("drop: %d.%d%\n\n", g_stat_info.drop * 100 / g_stat_info.pps,
            (g_stat_info.drop * 100 % g_stat_info.pps) * 10 / g_stat_info.pps);

    //espconn_mesh_print_status(0);
    //espconn_mesh_print_status(1);
}

void ICACHE_FLASH_ATTR mesh_stat_start(void *len)
{
    int8_t status;
    uint8_t src[6];
    uint16_t parent = 0;
    uint8_t *dst = NULL;
    uint8_t *data = NULL;
    uint16_t pkt_len = 0;
    struct mesh_stat_info_type *stat = NULL;
    struct mesh_header_format *header = NULL;
    uint32_t time = 5000;

    if (!len) {
        pkt_len = ESP_MESH_PKT_LEN_MAX - ESP_MESH_HLEN;
    } else {
        pkt_len = *((uint16_t *)len);
    }

    if (pkt_len < sizeof(*stat) || pkt_len > ESP_MESH_PKT_LEN_MAX - ESP_MESH_HLEN) {
        MESH_DEMO_PRINT("len should be in range of %d, %d\n",
                sizeof(*stat), ESP_MESH_PKT_LEN_MAX - ESP_MESH_HLEN);
        return;
    }

    status = espconn_mesh_get_status();

    if (status != MESH_ONLINE_AVAIL && status != MESH_LOCAL_AVAIL) {
        MESH_DEMO_PRINT("not ready for test\n");
        goto FREE_PKT;
    }

    if (espconn_mesh_is_root()) {  // root doesn't need to test
        //MESH_DEMO_PRINT("root device\n");
        return;
    }

    if (g_pkt_tx_idx > g_pkt_rx_idx + 1)
        goto FREE_PKT;

    if (!wifi_get_macaddr(STATION_IF, src)) {
        MESH_DEMO_PRINT("get sta mac fail\n");
        goto FREE_PKT;
    }

    if (!espconn_mesh_get_node_info(MESH_NODE_PARENT, &dst, &parent)) {
        MESH_DEMO_PRINT("get parent fail\n");
        goto FREE_PKT;
    }

    header = (struct mesh_header_format *)espconn_mesh_create_packet(
                            dst,     // destiny address of parent
                            src,     // source address
                            true,   // not p2p packet
                            true,    // piggyback congest request
                            M_PROTO_BIN,  // packe with JSON format
                            pkt_len,       // data length
                            false,    // no option
                            0,  // option total len
                            false,   // no frag
                            0,       // frag type, this packet doesn't use frag
                            false,   // more frag
                            0,       // frag index
                            0);      // frag length
    if (!header) {
        MESH_DEMO_PRINT("create packet fail\n");
        goto FREE_PKT;
    }

    if (!espconn_mesh_get_usr_data(header, (uint8_t **)&stat, &pkt_len)) {
        MESH_DEMO_PRINT("get data fail\n");
        goto FREE_PKT;
    }

    stat->pps = 1;
    stat->bps = pkt_len * 8;  // bits per second
    stat->time = system_get_time();
    stat->index = ++g_pkt_tx_idx;
    stat->loop = 1;

    if (espconn_mesh_sent(&g_ser_conn, (uint8_t *)header, header->len)) {
        MESH_DEMO_PRINT("bin mesh sent fail, heap:%u\n", system_get_free_heap_size());
        time = 10000;
        espconn_mesh_connect(&g_ser_conn);
        g_pkt_tx_idx --;
        //espconn_mesh_print_status(0);
        //espconn_mesh_print_status(1);
    } else {
        //MESH_DEMO_PRINT("tx-idx:%u\n", stat->index);
    }

FREE_PKT:
    header ? MESH_DEMO_FREE(header) : 0;
    espconn_mesh_setup_timer(&g_stat_timer, time,
            (os_timer_func_t *)mesh_stat_start, (void *)&g_pkt_len, false);
}

void ICACHE_FLASH_ATTR mesh_sent_cb(void *arg)
{
    mesh_stat_start(&g_pkt_len);
    os_timer_disarm(&g_stat_timer);
    //MESH_DEMO_PRINT("%s, time:%u\n", __func__, time);
}

void ICACHE_FLASH_ATTR mesh_reconnect_cb(void *arg, int8_t err)
{
    /*
     * when connection is disconected,
     * we try to establish it again and restart test-case
     */
    MESH_DEMO_PRINT("%s\n", __func__);
    espconn_mesh_connect(&g_ser_conn);
}

void ICACHE_FLASH_ATTR mesh_disconnect_cb(void *arg)
{
    /*
     * when connection is reconected,
     * we try to establish it again and restart test-case
     */
    MESH_DEMO_PRINT("%s\n", __func__);
    espconn_mesh_connect(&g_ser_conn);
}

void ICACHE_FLASH_ATTR mesh_stat_check_func()
{
    static uint32_t pps = 0;

    if (pps == g_stat_info.pps &&
        espconn_mesh_get_status() >= MESH_LOCAL_AVAIL &&
        espconn_mesh_get_status() <= MESH_SOFTAP_AVAIL)
        mesh_stat_start(&g_pkt_len);

    pps = g_stat_info.pps;
}

void ICACHE_FLASH_ATTR mesh_stat_start_init(uint16_t pkt_len)
{
    MESH_DEMO_PRINT("%s\n", __func__);
    g_pkt_len = pkt_len;

    mesh_stat_init();

    /*
     * setup timer to trigger test-case
     */
    espconn_mesh_setup_timer(&g_stat_check_timer, 3000,
            (os_timer_func_t *)mesh_stat_check_func, NULL, true);

    /*
     * Display the statistic result per 60s.
     */
    espconn_mesh_setup_timer(&g_disp_timer, 30000,
            (os_timer_func_t *)mesh_stat_disp, NULL, true);

    espconn_regist_sentcb(&g_ser_conn, mesh_sent_cb);
    espconn_regist_reconcb(&g_ser_conn, mesh_reconnect_cb);
    espconn_regist_disconcb(&g_ser_conn, mesh_disconnect_cb);
}
