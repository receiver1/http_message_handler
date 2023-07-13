#ifndef HTTP_MESSAGE_HANDLER_REQUEST_H
#define HTTP_MESSAGE_HANDLER_REQUEST_H

#include "headers_body.h"

namespace net {
namespace http {
class request : public headers_body {
  http::method method_{};
  std::string target_;
  std::string version_{};

public:
  request() = default;
  request(const std::string &buffer);

  // getters
  http::method method() const { return method_; }
  const std::string &target() const { return target_; }
  const std::string &version() const { return version_; }

  // setters
  void method(http::method value) { method_ = value; }
  void target(const std::string &value) { target_ = value; }
  void version(const std::string &value) { version_ = value; }

  // builders
  std::string str() const;
  operator std::string() const { return this->str(); }
};
} // namespace http
} // namespace net

#endif // HTTP_MESSAGE_HANDLER_REQUEST_H