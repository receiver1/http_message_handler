#ifndef HTTP_MESSAGE_HANDLER_MESSAGE_PARSER_H
#define HTTP_MESSAGE_HANDLER_MESSAGE_PARSER_H

#include "message_types.h"
#include <vector>

struct http_parser;
struct http_parser_settings;

namespace net {
namespace http {
class message_parser {
  http_parser *parser_{nullptr};
  http_parser_settings *parser_settings_{nullptr};
  std::string target_{};
  headers_pair_t header_pair_{};
  headers_t headers_{};
  std::vector<char> body_{};
  bool start_line_complete_{false};
  bool headers_complete_{false};

  static int on_url(http_parser *parser, const char *at, size_t length);
  static int on_status(http_parser *parser, const char *at, size_t length);
  static int on_header_field(http_parser *parser, const char *at,
                             size_t length);
  static int on_header_value(http_parser *parser, const char *at,
                             size_t length);
  static int on_headers_complete(http_parser *parser);
  static int on_body(http_parser *parser, const char *at, size_t length);

public:
  message_parser(const std::string &buffer, http::type type);
  ~message_parser();

  // getters
  http::method method() const;
  const std::string &target() const { return target_; }
  std::string version() const;
  http::status status() const;
  bool upgrade() const;
  std::size_t content_length() const;
  const headers_t &headers() const { return headers_; }
  const std::vector<char> &body() const { return body_; }

  // checkers
  bool has_start_line() const { return start_line_complete_; }
  /* indicates whether headers are parsed */
  bool has_headers() const { return headers_complete_ && !headers_.empty(); }
  bool has_body() const { return !body_.empty(); }
};

std::string method_str(http::method method);
std::string status_str(http::status status);
} // namespace http
} // namespace net

#endif // HTTP_MESSAGE_HANDLER_MESSAGE_PARSER_H