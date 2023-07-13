#include "message_parser.h"
#include <http_parser.h>

int net::http::message_parser::on_url(http_parser *parser, const char *at,
                                      size_t length) {
  auto &message_parser =
      *reinterpret_cast<net::http::message_parser *>(parser->data);
  message_parser.target_ = std::string{at, length};
  message_parser.start_line_complete_ = true;
  return 0;
}

int net::http::message_parser::on_status(http_parser *parser, const char *at,
                                         size_t length) {
  auto &message_parser =
      *reinterpret_cast<net::http::message_parser *>(parser->data);
  message_parser.start_line_complete_ = true;
  return 0;
}

int net::http::message_parser::on_header_field(http_parser *parser,
                                               const char *at, size_t length) {
  auto &message_parser =
      *reinterpret_cast<net::http::message_parser *>(parser->data);
  message_parser.header_pair_.first = std::string{at, length};
  return 0;
}

int net::http::message_parser::on_header_value(http_parser *parser,
                                               const char *at, size_t length) {
  auto &message_parser =
      *reinterpret_cast<net::http::message_parser *>(parser->data);
  message_parser.header_pair_.second = std::string{at, length};
  message_parser.headers_.emplace(message_parser.header_pair_);
  return 0;
}

int net::http::message_parser::on_headers_complete(http_parser *parser) {
  auto &message_parser =
      *reinterpret_cast<net::http::message_parser *>(parser->data);
  message_parser.headers_complete_ = true;
  return 0;
}

int net::http::message_parser::on_body(http_parser *parser, const char *at,
                                       size_t length) {
  auto &message_parser =
      *reinterpret_cast<net::http::message_parser *>(parser->data);
  message_parser.body_ = std::vector<char>{at, at + length};
  return 0;
}

net::http::message_parser::message_parser(const std::string &buffer,
                                          http::type type)
    : parser_{new http_parser}, parser_settings_{new http_parser_settings} {
  http_parser_init(parser_, static_cast<http_parser_type>(type));
  parser_->data = this;

  http_parser_settings_init(parser_settings_);
  parser_settings_->on_url = on_url;
  parser_settings_->on_status = on_status;
  parser_settings_->on_header_field = on_header_field;
  parser_settings_->on_header_value = on_header_value;
  parser_settings_->on_headers_complete = on_headers_complete;
  parser_settings_->on_body = on_body;

  http_parser_execute(parser_, parser_settings_, buffer.c_str(), buffer.size());
  if (parser_->http_errno != 0)
    throw std::exception{http_errno_name(HTTP_PARSER_ERRNO(parser_))};
}

net::http::message_parser::~message_parser() {
  delete parser_;
  delete parser_settings_;
}

net::http::method net::http::message_parser::method() const {
  return static_cast<http::method>(parser_->method);
}

std::string net::http::message_parser::version() const {
  return std::to_string(parser_->http_major) + "." +
         std::to_string(parser_->http_minor);
}

net::http::status net::http::message_parser::status() const {
  return static_cast<http::status>(parser_->status_code);
}

bool net::http::message_parser::upgrade() const {
  return static_cast<bool>(parser_->upgrade);
}

std::size_t net::http::message_parser::content_length() const {
  return parser_->content_length;
}

std::string net::http::method_str(http::method method) {
  return http_method_str(static_cast<http_method>(method));
}

std::string net::http::status_str(http::status status) {
  return http_status_str(static_cast<http_status>(status));
}