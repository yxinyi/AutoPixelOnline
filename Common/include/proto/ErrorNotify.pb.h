// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: ErrorNotify.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_ErrorNotify_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_ErrorNotify_2eproto

#include <limits>
#include <string>

#include <google/protobuf/port_def.inc>
#if PROTOBUF_VERSION < 3009000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers. Please update
#error your headers.
#endif
#if 3009000 < PROTOBUF_MIN_PROTOC_VERSION
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
#include <google/protobuf/inlined_string_field.h>
#include <google/protobuf/metadata.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_ErrorNotify_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_ErrorNotify_2eproto {
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTableField entries[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::AuxillaryParseTableField aux[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTable schema[1]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::FieldMetadata field_metadata[];
  static const ::PROTOBUF_NAMESPACE_ID::internal::SerializationTable serialization_table[];
  static const ::PROTOBUF_NAMESPACE_ID::uint32 offsets[];
};
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_ErrorNotify_2eproto;
class ErrorMsg;
class ErrorMsgDefaultTypeInternal;
extern ErrorMsgDefaultTypeInternal _ErrorMsg_default_instance_;
PROTOBUF_NAMESPACE_OPEN
template<> ::ErrorMsg* Arena::CreateMaybeMessage<::ErrorMsg>(Arena*);
PROTOBUF_NAMESPACE_CLOSE

// ===================================================================

class ErrorMsg :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:ErrorMsg) */ {
 public:
  ErrorMsg();
  virtual ~ErrorMsg();

  ErrorMsg(const ErrorMsg& from);
  ErrorMsg(ErrorMsg&& from) noexcept
    : ErrorMsg() {
    *this = ::std::move(from);
  }

  inline ErrorMsg& operator=(const ErrorMsg& from) {
    CopyFrom(from);
    return *this;
  }
  inline ErrorMsg& operator=(ErrorMsg&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return GetMetadataStatic().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return GetMetadataStatic().reflection;
  }
  static const ErrorMsg& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const ErrorMsg* internal_default_instance() {
    return reinterpret_cast<const ErrorMsg*>(
               &_ErrorMsg_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(ErrorMsg& a, ErrorMsg& b) {
    a.Swap(&b);
  }
  inline void Swap(ErrorMsg* other) {
    if (other == this) return;
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  inline ErrorMsg* New() const final {
    return CreateMaybeMessage<ErrorMsg>(nullptr);
  }

  ErrorMsg* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<ErrorMsg>(arena);
  }
  void CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void CopyFrom(const ErrorMsg& from);
  void MergeFrom(const ErrorMsg& from);
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  #if GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  #else
  bool MergePartialFromCodedStream(
      ::PROTOBUF_NAMESPACE_ID::io::CodedInputStream* input) final;
  #endif  // GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
  void SerializeWithCachedSizes(
      ::PROTOBUF_NAMESPACE_ID::io::CodedOutputStream* output) const final;
  ::PROTOBUF_NAMESPACE_ID::uint8* InternalSerializeWithCachedSizesToArray(
      ::PROTOBUF_NAMESPACE_ID::uint8* target) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  inline void SharedCtor();
  inline void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(ErrorMsg* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "ErrorMsg";
  }
  private:
  inline ::PROTOBUF_NAMESPACE_ID::Arena* GetArenaNoVirtual() const {
    return nullptr;
  }
  inline void* MaybeArenaPtr() const {
    return nullptr;
  }
  public:

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;
  private:
  static ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadataStatic() {
    ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&::descriptor_table_ErrorNotify_2eproto);
    return ::descriptor_table_ErrorNotify_2eproto.file_level_metadata[kIndexInFileMessages];
  }

  public:

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kParamFieldNumber = 2,
    kErrorIdFieldNumber = 1,
  };
  // repeated string param = 2;
  int param_size() const;
  void clear_param();
  const std::string& param(int index) const;
  std::string* mutable_param(int index);
  void set_param(int index, const std::string& value);
  void set_param(int index, std::string&& value);
  void set_param(int index, const char* value);
  void set_param(int index, const char* value, size_t size);
  std::string* add_param();
  void add_param(const std::string& value);
  void add_param(std::string&& value);
  void add_param(const char* value);
  void add_param(const char* value, size_t size);
  const ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField<std::string>& param() const;
  ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField<std::string>* mutable_param();

  // uint32 error_id = 1;
  void clear_error_id();
  ::PROTOBUF_NAMESPACE_ID::uint32 error_id() const;
  void set_error_id(::PROTOBUF_NAMESPACE_ID::uint32 value);

  // @@protoc_insertion_point(class_scope:ErrorMsg)
 private:
  class _Internal;

  ::PROTOBUF_NAMESPACE_ID::internal::InternalMetadataWithArena _internal_metadata_;
  ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField<std::string> param_;
  ::PROTOBUF_NAMESPACE_ID::uint32 error_id_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_ErrorNotify_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// ErrorMsg

// uint32 error_id = 1;
inline void ErrorMsg::clear_error_id() {
  error_id_ = 0u;
}
inline ::PROTOBUF_NAMESPACE_ID::uint32 ErrorMsg::error_id() const {
  // @@protoc_insertion_point(field_get:ErrorMsg.error_id)
  return error_id_;
}
inline void ErrorMsg::set_error_id(::PROTOBUF_NAMESPACE_ID::uint32 value) {
  
  error_id_ = value;
  // @@protoc_insertion_point(field_set:ErrorMsg.error_id)
}

// repeated string param = 2;
inline int ErrorMsg::param_size() const {
  return param_.size();
}
inline void ErrorMsg::clear_param() {
  param_.Clear();
}
inline const std::string& ErrorMsg::param(int index) const {
  // @@protoc_insertion_point(field_get:ErrorMsg.param)
  return param_.Get(index);
}
inline std::string* ErrorMsg::mutable_param(int index) {
  // @@protoc_insertion_point(field_mutable:ErrorMsg.param)
  return param_.Mutable(index);
}
inline void ErrorMsg::set_param(int index, const std::string& value) {
  // @@protoc_insertion_point(field_set:ErrorMsg.param)
  param_.Mutable(index)->assign(value);
}
inline void ErrorMsg::set_param(int index, std::string&& value) {
  // @@protoc_insertion_point(field_set:ErrorMsg.param)
  param_.Mutable(index)->assign(std::move(value));
}
inline void ErrorMsg::set_param(int index, const char* value) {
  GOOGLE_DCHECK(value != nullptr);
  param_.Mutable(index)->assign(value);
  // @@protoc_insertion_point(field_set_char:ErrorMsg.param)
}
inline void ErrorMsg::set_param(int index, const char* value, size_t size) {
  param_.Mutable(index)->assign(
    reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_set_pointer:ErrorMsg.param)
}
inline std::string* ErrorMsg::add_param() {
  // @@protoc_insertion_point(field_add_mutable:ErrorMsg.param)
  return param_.Add();
}
inline void ErrorMsg::add_param(const std::string& value) {
  param_.Add()->assign(value);
  // @@protoc_insertion_point(field_add:ErrorMsg.param)
}
inline void ErrorMsg::add_param(std::string&& value) {
  param_.Add(std::move(value));
  // @@protoc_insertion_point(field_add:ErrorMsg.param)
}
inline void ErrorMsg::add_param(const char* value) {
  GOOGLE_DCHECK(value != nullptr);
  param_.Add()->assign(value);
  // @@protoc_insertion_point(field_add_char:ErrorMsg.param)
}
inline void ErrorMsg::add_param(const char* value, size_t size) {
  param_.Add()->assign(reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_add_pointer:ErrorMsg.param)
}
inline const ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField<std::string>&
ErrorMsg::param() const {
  // @@protoc_insertion_point(field_list:ErrorMsg.param)
  return param_;
}
inline ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField<std::string>*
ErrorMsg::mutable_param() {
  // @@protoc_insertion_point(field_mutable_list:ErrorMsg.param)
  return &param_;
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)


// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_ErrorNotify_2eproto
