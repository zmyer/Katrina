//
// Created by StevensChew on 17/1/12.
//

#ifndef KATRINA_HTTPRESPONSE_H
#define KATRINA_HTTPRESPONSE_H

#include "HttpContext.h"

namespace donet {
    class HttpResponse : public HttpContext {
    public:
        HttpResponse() { }

        virtual std::string ToStdString() const override;

        int GetStatusCode() const {
            return _statusCode;
        }

        void SetStatusCode(int statusCode) {
            _statusCode = statusCode;
        }

        const std::string &GetStatusMessage() const {
            return _statusMessage;
        }

        void SetStatusMessage(const std::string &message) {
            _statusMessage = message;
        }

    private:
        std::string GetResponseLine() const;

        int _statusCode;
        std::string _statusMessage;
    };
}
#endif //KATRINA_HTTPRESPONSE_H
