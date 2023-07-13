#include "response.h"
#include "message_parser.h"

net::http::response::response(const std::string &buffer) {
  http::message_parser parser{buffer, http::type::RESPONSE};
  if (parser.has_start_line())
    status_ = parser.status();

  headers_body::operator=(parser);
}

std::string net::http::response::str() const {
  std::string out{};
  out += "HTTP/" + version_ + " " + std::to_string(static_cast<int>(status_)) +
         " " + http::status_str(status_) + "\r\n";
  out += headers_body::str();
  return out;
}
