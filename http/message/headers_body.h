#ifndef HTTP_MESSAGE_HANDLER_MESSAGE_HEADERS_BODY_H
#define HTTP_MESSAGE_HANDLER_MESSAGE_HEADERS_BODY_H

#include "message_types.h"

namespace net {
namespace http {
class message_parser;

class headers_body {
  http::headers_t headers_{};
  http::body_t body_{};

public:
  headers_body() = default;
  headers_body(const message_parser &parser) noexcept; // parser copy construct

  // getters
  const http::headers_t &headers() const { return headers_; }
  const std::vector<char> &body() const { return body_; }

  // checkers
  bool has_headers() const { return !headers_.empty(); }
  bool has_body() const { return !body_.empty(); }

  // setters
  virtual headers_body &
  operator=(const message_parser &parser) noexcept; // parser copy assign
  void headers(const http::headers_t &value) { headers_ = value; }
  void body(const http::body_t &value) { body_ = value; }

  virtual std::string str() const;
  virtual operator std::string() const { return this->str(); }
};
} // namespace http
} // namespace net

#endif // HTTP_MESSAGE_HANDLER_MESSAGE_HEADERS_BODY_H
