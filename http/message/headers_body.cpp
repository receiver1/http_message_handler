#include "headers_body.h"
#include "message_parser.h"

net::http::headers_body::headers_body(const message_parser &parser) noexcept {
  *this = parser;
}

net::http::headers_body &
net::http::headers_body::operator=(const message_parser &parser) noexcept {
  if (parser.has_headers())
    headers_ = parser.headers();
  if (parser.has_body())
    body_ = parser.body();
  return *this;
}

std::string net::http::headers_body::str() const {
  std::string out{};
  if (this->has_headers()) {
    for (auto &it : headers_)
      out += it.first + ": " + it.second + "\r\n";
    out += "\r\n\r\n";
  }
  if (this->has_body())
    out += std::string{body_.begin(), body_.end()};
  return out;
}
