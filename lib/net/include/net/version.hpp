#ifndef NET_VERSION_HPP_
#define NET_VERSION_HPP_

#include <string_view>

namespace net {

// Host-only code, so the hosted standard library is available here; the
// portable core in `datalink` is held to a stricter subset.
[[nodiscard]] std::string_view version() noexcept;

}  // namespace net

#endif  // NET_VERSION_HPP_
