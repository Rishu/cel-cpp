#include "internal/map_impl.h"
#include "common/macros.h"
#include "internal/status_util.h"

namespace google {
namespace api {
namespace expr {
namespace internal {

google::rpc::Status MapImpl::ForEach(
    const std::function<google::rpc::Status(const Value&, const Value&)>& call)
    const {
  for (const auto& entry : value_) {
    RETURN_IF_STATUS_ERROR(call(entry.first, entry.second));
  }
  return OkStatus();
}

Value MapImpl::GetImpl(const Value& key) const {
  auto itr = value_.find(key);
  if (itr == value_.end()) {
    return Value::FromError(NoSuchKey(key.ToString()));
  }
  return itr->second;
}

}  // namespace internal
}  // namespace expr
}  // namespace api
}  // namespace google
