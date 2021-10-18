#include <pthread.h>
#include <stdlib.h>
#include <sys/queue.h>

#include "neu_log.h"
#include "neu_plugin.h"
#include "parser/neu_json_fn.h"
#include "parser/neu_json_rw.h"

#include "handle.h"
#include "http.h"

#include "rw_handle.h"

struct cmd_ctx {
    uint32_t event_id;
    nng_aio *aio;

    TAILQ_ENTRY(cmd_ctx) node;
};

TAILQ_HEAD(, cmd_ctx) read_cmd_ctxs;
TAILQ_HEAD(, cmd_ctx) write_cmd_ctxs;
static pthread_mutex_t read_ctx_mtx;
static pthread_mutex_t write_ctx_mtx;

static void            read_add_ctx(uint32_t event_id, nng_aio *aio);
static void            write_add_ctx(uint32_t event_id, nng_aio *aio);
static struct cmd_ctx *read_find_ctx(uint32_t event_id);
static struct cmd_ctx *write_find_ctx(uint32_t event_id);

void handle_rw_init()
{
    TAILQ_INIT(&read_cmd_ctxs);
    TAILQ_INIT(&write_cmd_ctxs);

    pthread_mutex_init(&read_ctx_mtx, NULL);
    pthread_mutex_init(&write_ctx_mtx, NULL);
}

void handle_rw_uninit()
{
    struct cmd_ctx *ctx = NULL;

    pthread_mutex_lock(&read_ctx_mtx);
    ctx = TAILQ_FIRST(&read_cmd_ctxs);
    while (ctx != NULL) {
        TAILQ_REMOVE(&read_cmd_ctxs, ctx, node);
        nng_aio_finish(ctx->aio, 0);
        free(ctx);
        ctx = TAILQ_FIRST(&read_cmd_ctxs);
    }
    pthread_mutex_unlock(&read_ctx_mtx);

    pthread_mutex_lock(&write_ctx_mtx);
    ctx = TAILQ_FIRST(&write_cmd_ctxs);
    while (ctx != NULL) {
        TAILQ_REMOVE(&write_cmd_ctxs, ctx, node);
        nng_aio_finish(ctx->aio, 0);
        free(ctx);
        ctx = TAILQ_FIRST(&write_cmd_ctxs);
    }
    pthread_mutex_unlock(&write_ctx_mtx);

    pthread_mutex_destroy(&read_ctx_mtx);
    pthread_mutex_destroy(&write_ctx_mtx);
}

static void read_add_ctx(uint32_t event_id, nng_aio *aio)
{
    struct cmd_ctx *ctx = calloc(1, sizeof(struct cmd_ctx));

    pthread_mutex_lock(&read_ctx_mtx);

    ctx->aio      = aio;
    ctx->event_id = event_id;

    TAILQ_INSERT_TAIL(&read_cmd_ctxs, ctx, node);

    pthread_mutex_unlock(&read_ctx_mtx);
}

static void write_add_ctx(uint32_t event_id, nng_aio *aio)
{
    struct cmd_ctx *ctx = calloc(1, sizeof(struct cmd_ctx));

    pthread_mutex_lock(&write_ctx_mtx);

    ctx->aio      = aio;
    ctx->event_id = event_id;

    TAILQ_INSERT_TAIL(&write_cmd_ctxs, ctx, node);

    pthread_mutex_unlock(&write_ctx_mtx);
}

static struct cmd_ctx *read_find_ctx(uint32_t event_id)
{
    struct cmd_ctx *ctx = NULL;
    struct cmd_ctx *ret = NULL;

    pthread_mutex_lock(&read_ctx_mtx);
    TAILQ_FOREACH(ctx, &read_cmd_ctxs, node)
    {
        if (ctx->event_id == event_id) {
            TAILQ_REMOVE(&read_cmd_ctxs, ctx, node);
            ret = ctx;
            break;
        }
    }

    pthread_mutex_unlock(&read_ctx_mtx);

    return ret;
}

static struct cmd_ctx *write_find_ctx(uint32_t event_id)
{
    struct cmd_ctx *ctx = NULL;
    struct cmd_ctx *ret = NULL;

    pthread_mutex_lock(&write_ctx_mtx);

    TAILQ_FOREACH(ctx, &write_cmd_ctxs, node)
    {
        if (ctx->event_id == event_id) {
            TAILQ_REMOVE(&write_cmd_ctxs, ctx, node);
            ret = ctx;
            break;
        }
    }

    pthread_mutex_unlock(&write_ctx_mtx);

    return ret;
}

void handle_read(nng_aio *aio)
{
    neu_plugin_t *plugin = neu_rest_get_plugin();

    REST_PROCESS_HTTP_REQUEST(
        aio, neu_parse_read_req_t, neu_parse_decode_read, {
            neu_taggrp_config_t *config = neu_system_find_group_config(
                plugin, req->node_id, req->group_config_name);
            uint32_t event_id =
                neu_plugin_send_read_cmd(plugin, req->node_id, config);
            read_add_ctx(event_id, aio);
        })
}

void handle_write(nng_aio *aio)
{
    neu_plugin_t *plugin = neu_rest_get_plugin();

    REST_PROCESS_HTTP_REQUEST(
        aio, neu_parse_write_req_t, neu_parse_decode_write, {
            neu_taggrp_config_t *config = neu_system_find_group_config(
                plugin, req->node_id, req->group_config_name);
            neu_data_val_t *data = neu_parse_write_req_to_val(req);
            uint32_t        event_id =
                neu_plugin_send_write_cmd(plugin, req->node_id, config, data);
            write_add_ctx(event_id, aio);
        })
}

void handle_read_resp(void *cmd_resp)
{
    neu_request_t * req = (neu_request_t *) cmd_resp;
    struct cmd_ctx *ctx = read_find_ctx(req->req_id);

    http_ok(ctx->aio, "{\"status\": \"OK\"}");
    free(ctx);
}

void handle_write_resp(void *cmd_resp)
{
    neu_request_t * req = (neu_request_t *) cmd_resp;
    struct cmd_ctx *ctx = write_find_ctx(req->req_id);

    http_ok(ctx->aio, "{\"status\": \"OK\"}");
    free(ctx);
}