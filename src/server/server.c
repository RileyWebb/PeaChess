#include "debug.h"

#include "server/server.h"

unsigned int client_id_count = 0;

server_t *SV_Create()
{
	server_t *server = calloc(1, sizeof(server_t));

	server->loop = calloc(1,sizeof(uv_loop_t));

	if (uv_loop_init(server->loop))
		DEBUG_ERROR("Unable to create server loop");

	server->state = SV_SERVER_STATE_ALIVE;

	return server;
}

void SV_ClientDisconnect(sv_client_t *client) 
{
    free(client);
}

void SV_ClientTimeout(uv_timer_t *timer)
{
	sv_client_t *client = (sv_client_t *)timer->data;

	DEBUG_INFO("Client Timeout (ID:%u)", client->id);
	SV_ClientDisconnect(client);
}

void SV_ClientConnect(uv_stream_t *stream, int status)
{
	server_t *server = (server_t *)stream->data;
	sv_client_t *client = calloc(1, sizeof(sv_client_t));

	client->tcp = malloc(sizeof(uv_tcp_t));

	uv_tcp_init(server->loop, client->tcp);

	if (uv_accept(stream, (uv_stream_t *)client->tcp)) {
		DEBUG_ERROR("Unable to accept client connection");
		free(client);
	}

	client->timer = malloc(sizeof(uv_timer_t));
	uv_timer_init(server->loop, client->timer);
	uv_timer_set_repeat(client->timer, 0);
	client->timer->data = client;

	uv_timer_start(client->timer, (uv_timer_cb)SV_ClientTimeout,
				   SV_CLIENT_TIMEOUT, 0);

	client->id = client_id_count;
	client_id_count++;

	client->tcp->data = client;

	server->clients = realloc(server->clients, sizeof(sv_client_t) * server->client_count++);
	server->clients[server->client_count-1] = client;

	DEBUG_INFO("Client connected (ID:%u)", client->id);
}

void SV_StartThreaded(server_t *server)
{
	server->thread = malloc(sizeof(uv_thread_t));
	int err = uv_thread_create(server->thread, (uv_thread_cb)SV_Start, server);
	if (err)
		DEBUG_ERROR("Unable to create server thread: %s", uv_strerror(err));
}

void SV_Start(server_t *server)
{
	if (!server)
		DEBUG_ERROR("Unable to start uninitilised server");

	server->tcp = malloc(sizeof(uv_tcp_t));

	uv_tcp_init(server->loop, server->tcp);
	server->tcp->data = server;

	struct sockaddr_in addr;
	uv_ip4_addr("0.0.0.0", SERVER_PORT, &addr);

	uv_tcp_bind(server->tcp, (const struct sockaddr *)&addr, 0);

	int r = uv_listen((uv_stream_t *)server->tcp, 128 /*DEFAULT_BACKLOG*/,
					  (uv_connection_cb)SV_ClientConnect);
	if (r)
		DEBUG_ERROR("Unable to listen: %s", uv_strerror(r));

	DEBUG_INFO("Starting Server");

	while (server->state != SV_SERVER_STATE_DEAD)
	{
		SV_Update(server);
	}
	
	DEBUG_INFO("Closing Server");
}

void SV_Update(server_t *server)
{
	uv_run(server->loop, UV_RUN_NOWAIT);
}

void SV_Close(uv_handle_t* handle) {
    //free(handle->data);
}

void SV_Walk(uv_handle_t* handle, void* arg) {
    if (!uv_is_closing(handle))
    	uv_close(handle, NULL);
}

void SV_Destroy(server_t *server) 
{
	server->state = SV_SERVER_STATE_DEAD;

	//uv_stop(server->loop);

	uv_thread_join(server->thread);

	uv_stop(server->loop);

	while(uv_loop_close(server->loop) == UV_EBUSY)
	{
		uv_walk(server->loop, SV_Walk, NULL);
		uv_run(server->loop, UV_RUN_ONCE);
	}	

	//uv_close(server->thread, SV_Close);
	free(server->thread);
	free(server->tcp);
	free(server->loop);
	//uv_close(server->tcp, SV_Close);

	for (size_t i = 0; i < server->client_count; i++)
	{
		free(server->clients[i]);
	}
	

	free(server->clients);
	free(server);
}