/*
 * share memory
 * Copyright (c) 2017 Hubugui
 *
 * This file is part of FFmpeg.
 *
 * FFmpeg is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * FFmpeg is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with FFmpeg; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

#include "libavutil/avstring.h"
#include "libavutil/internal.h"
#include "libavutil/opt.h"
#include "avformat.h"
#if HAVE_DIRENT_H
#include <dirent.h>
#endif
#include <fcntl.h>
#if HAVE_IO_H
#include <io.h>
#endif
#if HAVE_UNISTD_H
#include <unistd.h>
#endif
#include <sys/stat.h>
#include <stdlib.h>
#include "os_support.h"
#include "url.h"

typedef struct ShmContext {
    const AVClass *class;
    int fd;
    char *name;
} ShmContext;

#define OFFSET(x) offsetof(ShmContext, x)
#define D AV_OPT_FLAG_DECODING_PARAM
#define E AV_OPT_FLAG_ENCODING_PARAM
static const AVOption shm_options[] = {
    { "name", "name", OFFSET(name), AV_OPT_TYPE_STRING, { .str = NULL }, .flags = D|E },
    { NULL }
};

static const AVClass shm_class = {
    .class_name = "shm",
    .item_name  = av_default_item_name,
    .option     = shm_options,
    .version    = LIBAVUTIL_VERSION_INT,
};

#if CONFIG_SHM_PROTOCOL
static int shm_open(URLContext *h, const char *url, int flags)
{
    ShmContext *c = h->priv_data;

    av_log(h, AV_LOG_DEBUG, "%s(0x%x, %s, %d)\n", __FUNCTION__, h, url, flags);
    return 0;
}

static int shm_read(URLContext *h, unsigned char *buf, int size)
{
    ShmContext *c = h->priv_data;

    av_log(h, AV_LOG_DEBUG, "%s(0x%x, %d)\n", __FUNCTION__, h, size);
    return 0;
}

static int shm_write(URLContext *h, const unsigned char *buf, int size)
{
    av_log(h, AV_LOG_DEBUG, "%s(0x%x, %d)\n", __FUNCTION__, h, size);
    return 0;
}

static int shm_get_handle(URLContext *h)
{
    av_log(h, AV_LOG_DEBUG, "%s(0x%x)\n", __FUNCTION__, h);
    return 0;
}

static int shm_close(URLContext *h)
{
    ShmContext *c = h->priv_data;
    av_log(h, AV_LOG_DEBUG, "%s(0x%x)\n", __FUNCTION__, h);
    return 0;
}

const URLProtocol ff_shm_protocol = {
    .name                = "shm",
    .url_open            = shm_open,
    .url_read            = shm_read,
    .url_write           = shm_write,
    .url_get_file_handle = shm_get_handle,
    .url_close           = shm_close,
    .priv_data_size      = sizeof(ShmContext),
    .priv_data_class     = &shm_class,
    .default_whitelist   = "crypto"
};

#endif /* CONFIG_SHM_PROTOCOL */
