#ifndef HTTP_MESSAGE_HANDLER_RESPONSE_H
#define HTTP_MESSAGE_HANDLER_RESPONSE_H

#include "headers_body.h"

namespace net {
namespace http {
class response : public headers_body {
  std::string version_{};
  http::status status_{};

public:
  response() = default;
  response(const std::string &buffer);

  // getters
  const std::string &version() const { return version_; }
  http::status status() const { return status_; }

  // setters
  void version(const std::string &value) { version_ = value; }
  void status(http::status value) { status_ = value; }

  // builders
  std::string str() const;
  operator std::string() const { return this->str(); }
};
} // namespace http
} // namespace net

#endif // HTTP_MESSAGE_HANDLER_RESPONSE_H