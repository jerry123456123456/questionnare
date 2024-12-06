// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: sort.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_sort_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_sort_2eproto

#include <limits>
#include <string>

#include <google/protobuf/port_def.inc>
#if PROTOBUF_VERSION < 3019000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers. Please update
#error your headers.
#endif
#if 3019004 < PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers. Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/port_undef.inc>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata_lite.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_sort_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_sort_2eproto {
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTableField entries[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::AuxiliaryParseTableField aux[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTable schema[2]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::FieldMetadata field_metadata[];
  static const ::PROTOBUF_NAMESPACE_ID::internal::SerializationTable serialization_table[];
  static const uint32_t offsets[];
};
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_sort_2eproto;
namespace mynamespace {
class SortRequest;
struct SortRequestDefaultTypeInternal;
extern SortRequestDefaultTypeInternal _SortRequest_default_instance_;
class SortResponse;
struct SortResponseDefaultTypeInternal;
extern SortResponseDefaultTypeInternal _SortResponse_default_instance_;
}  // namespace mynamespace
PROTOBUF_NAMESPACE_OPEN
template<> ::mynamespace::SortRequest* Arena::CreateMaybeMessage<::mynamespace::SortRequest>(Arena*);
template<> ::mynamespace::SortResponse* Arena::CreateMaybeMessage<::mynamespace::SortResponse>(Arena*);
PROTOBUF_NAMESPACE_CLOSE
namespace mynamespace {

// ===================================================================

class SortRequest final :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:mynamespace.SortRequest) */ {
 public:
  inline SortRequest() : SortRequest(nullptr) {}
  ~SortRequest() override;
  explicit constexpr SortRequest(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  SortRequest(const SortRequest& from);
  SortRequest(SortRequest&& from) noexcept
    : SortRequest() {
    *this = ::std::move(from);
  }

  inline SortRequest& operator=(const SortRequest& from) {
    CopyFrom(from);
    return *this;
  }
  inline SortRequest& operator=(SortRequest&& from) noexcept {
    if (this == &from) return *this;
    if (GetOwningArena() == from.GetOwningArena()
  #ifdef PROTOBUF_FORCE_COPY_IN_MOVE
        && GetOwningArena() != nullptr
  #endif  // !PROTOBUF_FORCE_COPY_IN_MOVE
    ) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const SortRequest& default_instance() {
    return *internal_default_instance();
  }
  static inline const SortRequest* internal_default_instance() {
    return reinterpret_cast<const SortRequest*>(
               &_SortRequest_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(SortRequest& a, SortRequest& b) {
    a.Swap(&b);
  }
  inline void Swap(SortRequest* other) {
    if (other == this) return;
  #ifdef PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() != nullptr &&
        GetOwningArena() == other->GetOwningArena()) {
   #else  // PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() == other->GetOwningArena()) {
  #endif  // !PROTOBUF_FORCE_COPY_IN_SWAP
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(SortRequest* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  SortRequest* New(::PROTOBUF_NAMESPACE_ID::Arena* arena = nullptr) const final {
    return CreateMaybeMessage<SortRequest>(arena);
  }
  using ::PROTOBUF_NAMESPACE_ID::Message::CopyFrom;
  void CopyFrom(const SortRequest& from);
  using ::PROTOBUF_NAMESPACE_ID::Message::MergeFrom;
  void MergeFrom(const SortRequest& from);
  private:
  static void MergeImpl(::PROTOBUF_NAMESPACE_ID::Message* to, const ::PROTOBUF_NAMESPACE_ID::Message& from);
  public:
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  uint8_t* _InternalSerialize(
      uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(SortRequest* other);

  private:
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "mynamespace.SortRequest";
  }
  protected:
  explicit SortRequest(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                       bool is_message_owned = false);
  private:
  static void ArenaDtor(void* object);
  inline void RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  public:

  static const ClassData _class_data_;
  const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*GetClassData() const final;

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kNumbersFieldNumber = 1,
  };
  // repeated int32 numbers = 1;
  int numbers_size() const;
  private:
  int _internal_numbers_size() const;
  public:
  void clear_numbers();
  private:
  int32_t _internal_numbers(int index) const;
  const ::PROTOBUF_NAMESPACE_ID::RepeatedField< int32_t >&
      _internal_numbers() const;
  void _internal_add_numbers(int32_t value);
  ::PROTOBUF_NAMESPACE_ID::RepeatedField< int32_t >*
      _internal_mutable_numbers();
  public:
  int32_t numbers(int index) const;
  void set_numbers(int index, int32_t value);
  void add_numbers(int32_t value);
  const ::PROTOBUF_NAMESPACE_ID::RepeatedField< int32_t >&
      numbers() const;
  ::PROTOBUF_NAMESPACE_ID::RepeatedField< int32_t >*
      mutable_numbers();

  // @@protoc_insertion_point(class_scope:mynamespace.SortRequest)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  ::PROTOBUF_NAMESPACE_ID::RepeatedField< int32_t > numbers_;
  mutable std::atomic<int> _numbers_cached_byte_size_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_sort_2eproto;
};
// -------------------------------------------------------------------

class SortResponse final :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:mynamespace.SortResponse) */ {
 public:
  inline SortResponse() : SortResponse(nullptr) {}
  ~SortResponse() override;
  explicit constexpr SortResponse(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  SortResponse(const SortResponse& from);
  SortResponse(SortResponse&& from) noexcept
    : SortResponse() {
    *this = ::std::move(from);
  }

  inline SortResponse& operator=(const SortResponse& from) {
    CopyFrom(from);
    return *this;
  }
  inline SortResponse& operator=(SortResponse&& from) noexcept {
    if (this == &from) return *this;
    if (GetOwningArena() == from.GetOwningArena()
  #ifdef PROTOBUF_FORCE_COPY_IN_MOVE
        && GetOwningArena() != nullptr
  #endif  // !PROTOBUF_FORCE_COPY_IN_MOVE
    ) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const SortResponse& default_instance() {
    return *internal_default_instance();
  }
  static inline const SortResponse* internal_default_instance() {
    return reinterpret_cast<const SortResponse*>(
               &_SortResponse_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    1;

  friend void swap(SortResponse& a, SortResponse& b) {
    a.Swap(&b);
  }
  inline void Swap(SortResponse* other) {
    if (other == this) return;
  #ifdef PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() != nullptr &&
        GetOwningArena() == other->GetOwningArena()) {
   #else  // PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() == other->GetOwningArena()) {
  #endif  // !PROTOBUF_FORCE_COPY_IN_SWAP
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(SortResponse* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  SortResponse* New(::PROTOBUF_NAMESPACE_ID::Arena* arena = nullptr) const final {
    return CreateMaybeMessage<SortResponse>(arena);
  }
  using ::PROTOBUF_NAMESPACE_ID::Message::CopyFrom;
  void CopyFrom(const SortResponse& from);
  using ::PROTOBUF_NAMESPACE_ID::Message::MergeFrom;
  void MergeFrom(const SortResponse& from);
  private:
  static void MergeImpl(::PROTOBUF_NAMESPACE_ID::Message* to, const ::PROTOBUF_NAMESPACE_ID::Message& from);
  public:
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  uint8_t* _InternalSerialize(
      uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(SortResponse* other);

  private:
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "mynamespace.SortResponse";
  }
  protected:
  explicit SortResponse(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                       bool is_message_owned = false);
  private:
  static void ArenaDtor(void* object);
  inline void RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  public:

  static const ClassData _class_data_;
  const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*GetClassData() const final;

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kSortedNumbersFieldNumber = 1,
  };
  // repeated int32 sorted_numbers = 1;
  int sorted_numbers_size() const;
  private:
  int _internal_sorted_numbers_size() const;
  public:
  void clear_sorted_numbers();
  private:
  int32_t _internal_sorted_numbers(int index) const;
  const ::PROTOBUF_NAMESPACE_ID::RepeatedField< int32_t >&
      _internal_sorted_numbers() const;
  void _internal_add_sorted_numbers(int32_t value);
  ::PROTOBUF_NAMESPACE_ID::RepeatedField< int32_t >*
      _internal_mutable_sorted_numbers();
  public:
  int32_t sorted_numbers(int index) const;
  void set_sorted_numbers(int index, int32_t value);
  void add_sorted_numbers(int32_t value);
  const ::PROTOBUF_NAMESPACE_ID::RepeatedField< int32_t >&
      sorted_numbers() const;
  ::PROTOBUF_NAMESPACE_ID::RepeatedField< int32_t >*
      mutable_sorted_numbers();

  // @@protoc_insertion_point(class_scope:mynamespace.SortResponse)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  ::PROTOBUF_NAMESPACE_ID::RepeatedField< int32_t > sorted_numbers_;
  mutable std::atomic<int> _sorted_numbers_cached_byte_size_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_sort_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// SortRequest

// repeated int32 numbers = 1;
inline int SortRequest::_internal_numbers_size() const {
  return numbers_.size();
}
inline int SortRequest::numbers_size() const {
  return _internal_numbers_size();
}
inline void SortRequest::clear_numbers() {
  numbers_.Clear();
}
inline int32_t SortRequest::_internal_numbers(int index) const {
  return numbers_.Get(index);
}
inline int32_t SortRequest::numbers(int index) const {
  // @@protoc_insertion_point(field_get:mynamespace.SortRequest.numbers)
  return _internal_numbers(index);
}
inline void SortRequest::set_numbers(int index, int32_t value) {
  numbers_.Set(index, value);
  // @@protoc_insertion_point(field_set:mynamespace.SortRequest.numbers)
}
inline void SortRequest::_internal_add_numbers(int32_t value) {
  numbers_.Add(value);
}
inline void SortRequest::add_numbers(int32_t value) {
  _internal_add_numbers(value);
  // @@protoc_insertion_point(field_add:mynamespace.SortRequest.numbers)
}
inline const ::PROTOBUF_NAMESPACE_ID::RepeatedField< int32_t >&
SortRequest::_internal_numbers() const {
  return numbers_;
}
inline const ::PROTOBUF_NAMESPACE_ID::RepeatedField< int32_t >&
SortRequest::numbers() const {
  // @@protoc_insertion_point(field_list:mynamespace.SortRequest.numbers)
  return _internal_numbers();
}
inline ::PROTOBUF_NAMESPACE_ID::RepeatedField< int32_t >*
SortRequest::_internal_mutable_numbers() {
  return &numbers_;
}
inline ::PROTOBUF_NAMESPACE_ID::RepeatedField< int32_t >*
SortRequest::mutable_numbers() {
  // @@protoc_insertion_point(field_mutable_list:mynamespace.SortRequest.numbers)
  return _internal_mutable_numbers();
}

// -------------------------------------------------------------------

// SortResponse

// repeated int32 sorted_numbers = 1;
inline int SortResponse::_internal_sorted_numbers_size() const {
  return sorted_numbers_.size();
}
inline int SortResponse::sorted_numbers_size() const {
  return _internal_sorted_numbers_size();
}
inline void SortResponse::clear_sorted_numbers() {
  sorted_numbers_.Clear();
}
inline int32_t SortResponse::_internal_sorted_numbers(int index) const {
  return sorted_numbers_.Get(index);
}
inline int32_t SortResponse::sorted_numbers(int index) const {
  // @@protoc_insertion_point(field_get:mynamespace.SortResponse.sorted_numbers)
  return _internal_sorted_numbers(index);
}
inline void SortResponse::set_sorted_numbers(int index, int32_t value) {
  sorted_numbers_.Set(index, value);
  // @@protoc_insertion_point(field_set:mynamespace.SortResponse.sorted_numbers)
}
inline void SortResponse::_internal_add_sorted_numbers(int32_t value) {
  sorted_numbers_.Add(value);
}
inline void SortResponse::add_sorted_numbers(int32_t value) {
  _internal_add_sorted_numbers(value);
  // @@protoc_insertion_point(field_add:mynamespace.SortResponse.sorted_numbers)
}
inline const ::PROTOBUF_NAMESPACE_ID::RepeatedField< int32_t >&
SortResponse::_internal_sorted_numbers() const {
  return sorted_numbers_;
}
inline const ::PROTOBUF_NAMESPACE_ID::RepeatedField< int32_t >&
SortResponse::sorted_numbers() const {
  // @@protoc_insertion_point(field_list:mynamespace.SortResponse.sorted_numbers)
  return _internal_sorted_numbers();
}
inline ::PROTOBUF_NAMESPACE_ID::RepeatedField< int32_t >*
SortResponse::_internal_mutable_sorted_numbers() {
  return &sorted_numbers_;
}
inline ::PROTOBUF_NAMESPACE_ID::RepeatedField< int32_t >*
SortResponse::mutable_sorted_numbers() {
  // @@protoc_insertion_point(field_mutable_list:mynamespace.SortResponse.sorted_numbers)
  return _internal_mutable_sorted_numbers();
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__
// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)

}  // namespace mynamespace

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_sort_2eproto