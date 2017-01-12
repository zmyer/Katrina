//
// Created by StevensChew on 17/1/11.
//

#ifndef KATRINA_HTTPCONNECTION_H
#define KATRINA_HTTPCONNECTION_H

#include <functional>
#include "HttpResponse.h"
#include "../Donet.h"

namespace donet {
    class HttpConnection {
    public:
        typedef std::function<void(const HttpRequest& request)> RequestHandler;
        typedef std::function<void(const std::string &data)> DataHandler;

        HttpConnection(TcpConnection *connection);

        void HandleData(const char *buffer, int32_t size);

        void OnData(DataHandler dataHandler) {
            _dataHandler = dataHandler;
        }

        void OnRequest(RequestHandler requestHandler) {
            _requestHandler = requestHandler;
        }

        void SendResponse(const HttpResponse &response);

    private:
        TcpConnection *_connection;
        HttpRequest _request;
        HttpResponse _response;
        DataHandler _dataHandler;
        RequestHandler _requestHandler;
    };
}
#endif //KATRINA_HTTPCONNECTION_H
