#include "request.h"
#include "message_parser.h"

net::http::request::request(const std::string &buffer) {
  http::message_parser parser{buffer, http::type::REQUEST};
  if (parser.has_start_line()) {
    method_ = parser.method();
    target_ = parser.target();
  }

  headers_body::operator=(parser);
}

std::string net::http::request::str() const {
  std::string out{};
  out +=
      http::method_str(method_) + " " + target_ + " HTTP/" + version_ + "\r\n";
  out += headers_body::str();
  return out;
}
