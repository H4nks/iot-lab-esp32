/*
 * IoT-Labs-2018
 * Copyright (C) 2018 Massinissa Hamidi
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


#include "lwip/api.h"
#include "lwip/netdb.h"
#include "lwip/err.h"
#include "lwip/ip_addr.h"

/* mbedtls includes */
#include "mbedtls/net.h"
#include "mbedtls/ssl.h"
#include "mbedtls/entropy.h"
#include "mbedtls/ctr_drbg.h"
#include "mbedtls/debug.h"
/* end of mbedtls includes */

#include "tcpip_adapter.h"
#include "trans_layer.h"

#define REMOTE_PORT    3000             // no sure if this has to be here...
#define REMOTE_HOST    "localhost"      //

struct netconn *cx;

int8_t
establish_conn(int port, char * hostname)
{
    int8_t rc;
    ip_addr_t local_ip;
    ip_addr_t remote_ip;
    tcpip_adapter_ip_info_t ip_info;

    rc = EINPROGRESS;

    cx = netconn_new(NETCONN_TCP);
    if (cx == NULL) {
        // No memory for new connection?
        printf("[IoT-Labs] Error while creating a new NetConn connection\n");
        return rc;
    }

    rc = tcpip_adapter_get_ip_info(TCPIP_ADAPTER_IF_STA, &ip_info);
    if (rc < 0) {
        printf("[IoT-Labs] Error while getting ip information\n");
        return rc;
    }

    local_ip.u_addr.ip4 = ip_info.ip;

    rc = netconn_gethostbyname(REMOTE_HOST, &remote_ip);

    rc = netconn_connect ( cx, &remote_ip, REMOTE_PORT );
    if ( rc != ERR_OK)
    {
        printf("[establish_conn] connection failed\n");
        netconn_delete ( cx );
        return rc;
    }


    return rc;
}

int8_t
trans_send(const void *app_paquet)
{
    int8_t rc;

    rc = ENOSYS;
    // TODO switch whether tls is enabled or not and choose the right function
    // in order to send data over the created socket!
    // will have to use this : http://lwip.wikia.com/wiki/Netconn_write

    rc = netconn_write(cx, app_paquet, sizeof(&app_paquet), NETCONN_NOCOPY);
    // FIXME : netconn_write: invalid conn
    // Impossible to write TCP message over connection

    return rc;
}

int8_t
transport_layer_start(enum trans_protocols trans_proto, int ssl_flag)
{
    int8_t rc;

    switch (trans_proto) {
    case TCP:
        rc = ENOSYS;
        break;
    case UDP:
        rc = ENOSYS;
        break;
    default:
        rc = ENOSYS;
        break;
    }

    return rc;
}


int8_t
establish_secure_conn(const char *cert)
{
    int8_t rc;

    rc = ENOSYS;

    return rc;
}
