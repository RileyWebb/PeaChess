typedef struct client_s 
{
    enum 
    {
        CLIENT_TYPE_GUI,
        CLIENT_TYPE_UCI,
    } type; 
} client_t;

